# Account Abstraction — Cercle Bleu

## Objectif

Supprimer la friction liée à MetaMask pour les utilisateurs (patients diabétiques, chercheurs) en remplaçant l'authentification par wallet par une connexion email/Google. Les transactions blockchain sont gérées en arrière-plan via un smart account, sans que l'utilisateur n'ait besoin d'ETH ni de comprendre la blockchain.

---

## Stack choisie

| Rôle | Outil | Pourquoi |
|------|-------|----------|
| Auth & wallet embedded | **Privy** | Login email/Google, crée un wallet automatiquement |
| Intégration wagmi | **@privy-io/wagmi** | Connecte le wallet Privy aux hooks wagmi existants |
| Smart account | **Kernel (ZeroDev)** | Intégré dans Privy, ERC-4337 compatible |
| Bundler & Paymaster | **Pimlico** | Soumet les UserOperations et sponsorise le gas |
| SDK UserOperations | **Permissionless.js** | Sous le capot de Privy Smart Wallets |

---

## Architecture auth (nouvelle)

```
Utilisateur
    │
    ▼
Login email / Google (modal Privy)
    │
    ▼
Privy crée un wallet embedded (EOA) + un smart account dessus
    │
    ├── Frontend : usePrivy().authenticated = true
    │             useAccount().address = adresse smart account
    │
    ▼
AuthContext appelle POST /api/auth/session
    │
    ├── Vérifie le JWT Privy via JWKS (https://auth.privy.io/api/v1/apps/{id}/jwks)
    ├── Cherche l'utilisateur en DB par walletAddress
    └── Crée un cookie de session (JWT interne, 15 min)
    │
    ▼
Routes API protégées → verifyWalletAuth()
    ├── 1. Cookie de session (utilisateurs déjà inscrits)
    └── 2. Bearer JWT + x-wallet-address (flow d'inscription avant session)
```

### Flux d'inscription (nouvel utilisateur)

```
1. Login Privy → wallet embedded créé
2. AuthContext tente POST /api/auth/session → 404 USER_NOT_FOUND
3. sessionCreated = false
4. Utilisateur va sur /patient/profile ou /researcher/profile
5. Remplit le formulaire → submit
6. authenticatedFetch envoie Authorization: Bearer {privyToken} + x-wallet-address
7. /api/patient/register vérifie le JWT Privy → crée l'entrée DB → crée la session
8. Session cookie set → accès au dashboard
```

---

## Ce qui a été implémenté

### Packages

```bash
# Supprimé
@rainbow-me/rainbowkit

# Ajoutés
@privy-io/react-auth    # Provider Privy + hooks usePrivy()
@privy-io/wagmi         # Connecteur wagmi pour Privy
@privy-io/node          # SDK serveur pour vérifier les JWT
```

### Fichiers créés / modifiés

#### `frontend/app/PrivyAndWagmiProvider.tsx` (nouveau)
Provider racine qui remplace `RainbowKitAndWagmiProvider`. Configure :
- `PrivyProvider` avec login email + Google + wallet externe
- `WagmiProvider` via `@privy-io/wagmi`
- Embedded wallets activés pour tous les utilisateurs
- Affiche une page d'erreur si `NEXT_PUBLIC_PRIVY_APP_ID` n'est pas configuré

#### `frontend/app/RainbowKitAndWagmiProvider.tsx`
Redirige vers `PrivyAndWagmiProvider` pour compatibilité avec l'import dans `layout.tsx`.

#### `frontend/contexts/AuthContext.tsx`
- Supprime `useSignMessage` (plus de signature wallet)
- Utilise `usePrivy().getAccessToken()` pour obtenir le JWT
- `authenticate()` retourne l'adresse wallet (compatibilité interfaces)
- `authenticatedFetch()` : envoie Bearer JWT si pas de session, sinon cookie automatique
- `logout()` : vide la session serveur + déconnecte Privy
- Auto-création de session au login Privy

#### `frontend/app/api/auth/session/route.ts`
- Remplace `verifyMessage` (viem) par `verifyAccessToken` (@privy-io/node)
- Vérifie le JWT via JWKS distant (pas de clé secrète partagée)
- Corps de requête : `{ privyToken, walletAddress }` au lieu de `{ walletAddress, signature, message }`

#### `frontend/lib/auth.ts`
- `verifyWalletAuth()` vérifie en priorité le cookie de session
- Fallback sur Bearer JWT + `x-wallet-address` pour le flow d'inscription
- Toutes les routes API existantes fonctionnent sans modification

#### `frontend/components/shared/Header.tsx`
- Remplace `<ConnectButton />` (RainbowKit) par des boutons "Se connecter" / "Déconnexion"
- Affiche l'adresse wallet tronquée quand connecté

#### `frontend/components/shared/WelcomePage.tsx`
- Remplace `isConnected` + `ConnectButton` par `authenticated` + `login()` Privy
- Message mis à jour : "aucun wallet requis"

#### `frontend/app/patient/layout.tsx`
- Guard remplacé : `isConnected` → `usePrivy().authenticated + ready`

#### `frontend/lib/session.ts`
- Durée de session étendue à **24 heures** (`SESSION_DURATION = 1440 * 60`)

#### `frontend/hooks/useSmartContractWrite.ts` (nouveau)
Abstraction pour les transactions blockchain, gère automatiquement local vs testnet/mainnet :
- Local Hardhat : `writeContractAsync` (wagmi direct, pas de bundler)
- Testnet/Mainnet : `client.writeContract` via smart account Privy (UserOperation, gas sponsorisé)

#### `frontend/contexts/AuthContext.tsx` — refresh automatique de session
`authenticatedFetch` intercepte les 401 reçus quand la session cookie a expiré : il appelle `createSession()` silencieusement et retente la requête une fois. Sans impact sur le flow d'inscription (Bearer token).

#### Pages Researcher — Guard uniforme
`isConnected` (wagmi) remplacé par `usePrivy().authenticated + ready` dans :
- `app/researcher/dashboard/page.tsx`
- `app/researcher/studies/page.tsx`
- `app/researcher/data/page.tsx`

#### Composants write — migration vers `useSmartContractWrite`
Tous les composants écrivant sur la blockchain utilisent désormais `useSmartContractWrite` :
- `components/patient/PatientBlockchainRegistration.tsx` — était `useWriteContract`
- `components/researcher/ResearcherBlockchainRegistration.tsx` — était `useWriteContract`
- `components/patient/DataUploadTriggerConsent.tsx` — était `useSmartWallets` direct
- `components/patient/RevokeConsentButton.tsx` — était `useSmartWallets` direct
- `components/researcher/AuthorizeStudyOnContract.tsx` — était `useSmartWallets` direct

#### `frontend/.env`
```env
NEXT_PUBLIC_PRIVY_APP_ID="your-privy-app-id"
PRIVY_APP_SECRET="your-privy-app-secret"
SESSION_SECRET="change-me-in-production-min-32-chars"
```

---

## Ce qui reste à faire

### 1. Smart Contracts — Récupération de compte (Phase 2)

Problème : les SBT (Soul Bound Tokens) sont liés à une adresse. Si un utilisateur perd accès à son smart account, ses NFTs de consentement sont bloqués.

**`backend/contracts/CercleConsent.sol`** — Ajouter :
```solidity
// Réservé à l'admin du contrat
function migratePatient(address oldAddress, address newAddress) external onlyOwner {
    uint256 patientId = addressToPatientId[oldAddress];
    if (patientId == 0) revert PatientNotRegistered();
    if (isPatientRegistered(newAddress)) revert AddressAlreadyRegistered();

    patients[patientId].walletAddress = newAddress;
    addressToPatientId[newAddress] = patientId;
    delete addressToPatientId[oldAddress];

    emit PatientMigrated(oldAddress, newAddress, patientId);
}
```

Même logique pour `CercleToken.sol`.

### 2. Gas Sponsorship — Configuration dashboard (Phase 5)

Le hook `useSmartContractWrite` est en place. Il reste à configurer l'infrastructure externe :

**Dashboard Privy** (dashboard.privy.io)
- Smart Wallets → Activer (type : Kernel/ZeroDev)
- Ajouter clé API Pimlico comme bundler

**Dashboard Pimlico** — Créer une Paymaster Policy pour sponsoriser :
- `registerPatient()`
- `selfGrantConsent()`
- `revokeConsent()`

---

## Flux utilisateur final (cible)

```
1. Utilisateur arrive sur Cercle Bleu
2. Clique "Se connecter" → modal Privy s'ouvre
3. Entre son email → reçoit un code OTP
4. Privy crée un wallet embedded en arrière-plan (invisible)
5. Choisit son rôle (patient / chercheur)
6. Remplit son profil → clique "S'enregistrer"
7. Transaction blockchain envoyée en arrière-plan (gas sponsorisé par Pimlico)
8. Accède au dashboard — sans jamais voir MetaMask, seed phrase, ou payer de gas
```

---

## Variables d'environnement complètes

```env
# Base de données
DATABASE_URL="postgresql://postgres:postgres@localhost:5432/cerclebleu"

# Blockchain
NEXT_PUBLIC_CHAIN_ID="31337"                    # 80002 pour Polygon Amoy
NEXT_PUBLIC_RPC_URL="http://127.0.0.1:8545"
NEXT_PUBLIC_CERCLE_CONSENT_ADDRESS="0x..."
NEXT_PUBLIC_CERCLE_TOKEN_ADDRESS="0x..."

# Privy (Account Abstraction)
NEXT_PUBLIC_PRIVY_APP_ID="clxxxxxx..."          # depuis dashboard.privy.io
PRIVY_APP_SECRET="xxxxxx..."                     # depuis dashboard.privy.io (serveur uniquement)

# Session
SESSION_SECRET="chaine-aleatoire-32-chars-min"  # openssl rand -base64 32
```
