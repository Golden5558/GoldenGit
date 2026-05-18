# Documentation de développement - Cercle Bleu

## Démarrage rapide

### Prérequis

- **Node.js** (version 18+) — [Installer Node.js](https://nodejs.org/en/download/)
- **Docker** et **Docker Compose** — [Installer Docker](https://docs.docker.com/get-docker/)

### Installation

```bash
# 1. Cloner le projet
git clone https://github.com/lasiouce/mon_cercle_sante
cd mon_cercle_sante

# 2. Démarrer PostgreSQL
docker-compose up -d postgres

# 3. Configurer le frontend
cd frontend
npm install
npx prisma generate
npx prisma migrate dev

# 4. Compiler le backend
cd ../backend
npm install
npx hardhat compile
```

### Variables d'environnement

#### Frontend (`.env`)

```env
# Base de données
DATABASE_URL="postgresql://postgres:postgres@localhost:5432/cerclebleu"
DATABASE_DIRECT_URL="postgresql://postgres:postgres@localhost:5432/cerclebleu"

# Blockchain locale (Hardhat)
NEXT_PUBLIC_CHAIN_ID="31337"
NEXT_PUBLIC_RPC_URL="http://127.0.0.1:8545"
NEXT_PUBLIC_CERCLE_CONSENT_ADDRESS="0x..."  # adresse après déploiement
NEXT_PUBLIC_CERCLE_TOKEN_ADDRESS="0x..."

# Privy — Account Abstraction (https://dashboard.privy.io)
NEXT_PUBLIC_PRIVY_APP_ID="votre-privy-app-id"
PRIVY_APP_SECRET="votre-privy-app-secret"

# Session
SESSION_SECRET="chaine-aleatoire-min-32-chars"  # openssl rand -base64 32
```

Générer un `SESSION_SECRET` sécurisé :

```bash
openssl rand -base64 32
```

### Démarrage de l'application

```bash
# Terminal 1 : Blockchain locale
cd backend
npx hardhat node

# Terminal 2 : Déploiement des contrats
cd backend
npx hardhat run scripts/deployConsent.ts --network localhost
npx hardhat run scripts/deployToken.ts --network localhost

# Terminal 3 : Frontend
cd frontend
npm run dev
```

L'application est accessible sur `http://localhost:3000`.

> **Note :** En local, l'authentification Privy utilise le réseau de test Hardhat (chain ID 31337). Aucun wallet externe n'est requis — Privy crée un wallet embarqué via email/Google.

---

## Structure du projet

```text
mon_cercle_sante/
├── backend/                    # Smart contracts Hardhat
│   ├── contracts/              # Contrats Solidity
│   ├── scripts/                # Scripts de déploiement
│   └── test/                   # Tests des contrats
├── frontend/                   # Application Next.js 15
│   ├── app/                    # Pages et layouts Next.js
│   │   ├── patient/            # Interface patient
│   │   ├── researcher/         # Interface chercheur
│   │   └── api/                # API routes
│   ├── components/             # Composants React
│   │   ├── patient/            # Composants patient
│   │   ├── researcher/         # Composants chercheur
│   │   ├── shared/             # Composants partagés (Header, WelcomePage…)
│   │   └── ui/                 # Composants UI (shadcn/ui)
│   ├── contexts/               # AuthContext (Privy + session)
│   ├── hooks/                  # Hooks React personnalisés
│   │   ├── useCercleBalance.ts
│   │   ├── usePatientConsents.ts
│   │   ├── usePatientId.ts
│   │   └── useResearcherData.ts
│   ├── lib/                    # Utilitaires
│   │   ├── auth.ts             # verifyWalletAuth()
│   │   ├── privyClient.ts      # Singleton PrivyClient (@privy-io/node)
│   │   └── session.ts          # JWT session cookie
│   └── schema.prisma           # Schéma de base de données
└── docs/                       # Documentation
```

---

## Tests

```bash
# Tests des contrats
cd backend
npx hardhat test

# Tests du frontend
cd frontend
npm test
```

---

## Outils de développement

```bash
# Interface de base de données
cd frontend
npx prisma studio  # http://localhost:5555

# Reset de la base de données
npx prisma migrate reset

# Redémarrage Docker
docker-compose down -v
docker-compose up -d postgres

# Nettoyage complet backend
cd backend
npx hardhat clean && npx hardhat compile
```

---

## Contribution

### Workflow

1. **Cloner** le repository
2. **Créer une branche** :

   ```bash
   git checkout -b feature/nom-de-la-feature
   ```

3. **Développer** et **tester**
4. **Commit** avec des messages conventionnels :

   ```bash
   git commit -m 'feat: description de la fonctionnalité'
   ```

5. **Push** et créer une **Pull Request**

### Types de branches

- `feature/nom-feature` — Nouvelles fonctionnalités
- `fix/nom-bug` — Corrections de bugs
- `docs/sujet` — Documentation
- `refactor/composant` — Refactoring

### Standards

- Utiliser **ESLint** et **Prettier**
- Écrire des **tests** pour les nouvelles fonctionnalités
- Suivre les **conventions de nommage** existantes

---

## Technologies utilisées

- **Frontend** : Next.js 15, React 19, TypeScript, Tailwind CSS 4, shadcn/ui
- **Auth & Wallet** : Privy (`@privy-io/react-auth`, `@privy-io/wagmi`, `@privy-io/node`)
- **Blockchain** : Hardhat, Wagmi, Viem
- **Base de données** : PostgreSQL, Prisma ORM
- **Tests** : Jest, Hardhat Test
- **Déploiement** : Docker, Vercel

---

## Ressources

- [Documentation Next.js](https://nextjs.org/docs)
- [Documentation Hardhat](https://hardhat.org/docs)
- [Documentation Prisma](https://www.prisma.io/docs)
- [Documentation Wagmi](https://wagmi.sh/)
- [Documentation Privy](https://docs.privy.io/)
- [Account Abstraction — notes d'implémentation](account-abstraction.md)
