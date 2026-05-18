# Flux d'authentification — Cercle Bleu

## Vue d'ensemble

Cercle Bleu utilise **Privy** pour l'authentification. L'utilisateur se connecte via email ou Google — aucun wallet externe ni MetaMask n'est requis. Privy crée automatiquement un wallet embarqué (embedded wallet) et émet un JWT signé que le backend vérifie via son SDK officiel.

---

## Flux complet

### Nouvel utilisateur

```text
1. Arrivée sur "/" (page d'accueil)
   └── Clic sur "Se connecter" → modal Privy

2. Authentification Privy (email OTP ou Google)
   ├── Privy crée un wallet embedded (EOA invisible)
   └── Privy émet un access token JWT (aud = privy-app-id)

3. AuthContext détecte authenticated=true + address disponible
   └── POST /api/auth/session { privyToken, walletAddress }
       ├── Backend vérifie le JWT via PrivyClient.utils().auth().verifyAccessToken()
       ├── Cherche l'utilisateur en DB par walletAddress
       ├── Si USER_NOT_FOUND → sessionCreated=false (flow inscription)
       └── Si trouvé → cookie de session créé (JWT interne, 15 min)

4. Choix du rôle (patient / chercheur) → page de profil

5. Inscription
   ├── authenticatedFetch envoie : Authorization: Bearer {privyToken} + x-wallet-address
   ├── /api/patient/register ou /api/researcher/register vérifie le JWT Privy
   ├── Entrée créée en DB
   └── Cookie de session créé → accès au dashboard
```

### Utilisateur existant

```text
1. Arrivée sur "/" → modal Privy
2. Authentification Privy → JWT émis
3. AuthContext → POST /api/auth/session → cookie de session
4. Redirection automatique vers le dashboard (patient ou chercheur)
```

---

## Architecture technique

### Client

#### `PrivyAndWagmiProvider` (`app/PrivyAndWagmiProvider.tsx`)

- Configure `PrivyProvider` avec login email + Google + wallet externe optionnel
- Configure `WagmiProvider` via `@privy-io/wagmi`
- Active les embedded wallets pour tous les utilisateurs

#### `AuthContext` (`contexts/AuthContext.tsx`)

- Utilise `usePrivy().getAccessToken()` pour obtenir le JWT Privy
- `createSession()` : POST `/api/auth/session` après login Privy
- `authenticatedFetch()` : envoie le Bearer JWT si pas de session, sinon laisse le cookie passer automatiquement
- `logout()` : vide le cookie de session + déconnecte Privy

### Serveur

#### `lib/privyClient.ts`

Singleton `PrivyClient` (`@privy-io/node`) initialisé avec `NEXT_PUBLIC_PRIVY_APP_ID` + `PRIVY_APP_SECRET`. Utilisé pour vérifier les JWT Privy côté serveur via le bon endpoint JWKS.

#### `lib/auth.ts` — `verifyWalletAuth()`

Deux modes de vérification (dans l'ordre) :

1. **Cookie de session** (`cercle_session`) — utilisateurs déjà inscrits
2. **Bearer JWT + `x-wallet-address`** — flow d'inscription avant session

#### `lib/session.ts`

- JWT interne signé avec `SESSION_SECRET`
- Cookie `httpOnly`, `secure`, `sameSite=Lax`
- Expiration : 24 heures

#### `middleware.ts`

Protège toutes les routes `/patient/*` et `/researcher/*`, sauf les pages d'inscription (`/patient/profile`, `/researcher/profile`). Redirige vers `/` si session invalide.

---

## Protection des routes API

| Endpoint | Auth requise | Vérification |
| -------- | ------------ | ------------ |
| `POST /api/auth/session` | JWT Privy (body) | `PrivyClient.verifyAccessToken()` |
| `DELETE /api/auth/session` | — | Logout simple |
| `POST /api/patient/register` | JWT Privy (Bearer) | `verifyWalletAuth()` → wallet match |
| `GET /api/patient/[id]` | Session cookie | Ownership patient |
| `PUT /api/patient/[id]` | Session cookie | Ownership patient |
| `GET /api/patient/wallet/[address]` | Session cookie | Wallet match |
| `POST /api/patient/upload` | Session cookie | Patient uniquement |
| `GET /api/patient/data` | Session cookie | Patient ou chercheur avec consentement |
| `POST /api/researcher/register` | JWT Privy (Bearer) | `verifyWalletAuth()` → wallet match |
| `GET /api/researcher/wallet` | Session cookie | Wallet match |
| `POST /api/researcher/studies` | Session cookie | Chercheur uniquement |
| `GET /api/studies` | Public | — |

---

## Variables d'environnement requises

```env
# Privy
NEXT_PUBLIC_PRIVY_APP_ID="clxxxxxx..."     # depuis dashboard.privy.io
PRIVY_APP_SECRET="privy_app_secret_..."    # depuis dashboard.privy.io (serveur uniquement)

# Session interne
SESSION_SECRET="chaine-aleatoire-32-chars-min"  # openssl rand -base64 32
```

---

## Codes d'erreur API

| Code | Status | Cause | Solution |
| ---- | ------ | ----- | -------- |
| `MISSING_FIELDS` | 400 | Champs manquants dans le body | Vérifier les données envoyées |
| `INVALID_WALLET_ADDRESS` | 400 | Format d'adresse invalide | Vérifier le format `0x...` |
| `INVALID_TOKEN` | 401 | JWT Privy invalide ou expiré | Se reconnecter via Privy |
| `AUTH_REQUIRED` | 401 | Pas de session ni de Bearer token | Se connecter d'abord |
| `USER_NOT_FOUND` | 404 | Wallet non enregistré en DB | Compléter l'inscription |
| `WALLET_MISMATCH` | 403 | Adresse wallet ne correspond pas | Utiliser le bon wallet |
| `ACCESS_DENIED` | 403 | L'utilisateur n'est pas propriétaire de la ressource | Vérifier les droits |

---

## Dépannage

### 401 "Invalid or expired Privy token" en production

Causes possibles :

1. `NEXT_PUBLIC_PRIVY_APP_ID` ou `PRIVY_APP_SECRET` non défini dans Vercel
2. `SESSION_SECRET` non défini ou différent entre les instances

Solution : vérifier les variables d'environnement dans le dashboard Vercel.

### Redirection vers "/" depuis le dashboard

La session a expiré (15 min). Se reconnecter via Privy — le cookie est recréé automatiquement.

### "PRIVY_APP_SECRET is not set"

Ajouter la variable dans `.env` (local) ou dans les variables d'environnement Vercel (production).

---

## Références

- [Privy Documentation](https://docs.privy.io/)
- [Privy Node SDK — verifyAccessToken](https://docs.privy.io/guide/server/authorization/verification)
- [Next.js Middleware](https://nextjs.org/docs/app/building-your-application/routing/middleware)
- [Jose JWT Library](https://github.com/panva/jose)
