# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Cercle Bleu is a blockchain-based healthcare platform for diabetes patients. It manages medical data consent and sharing through smart contracts, connecting patients, doctors, and researchers. Patients maintain control over their data and accumulate contribution tokens (CERCLE) for participating in research, unlocking non-monetary benefits based on their engagement level.

**Note:** See `docs/refonte-ethique.md` for the ethical guidelines of the contribution system.

## Architecture

- **backend/**: Hardhat project with Solidity smart contracts (ERC721 consent NFTs + ERC20 contribution tokens)
- **frontend/**: Next.js 15 application with React 19, using Wagmi/RainbowKit for blockchain interaction
- **Database**: PostgreSQL with Prisma ORM (schema at `frontend/schema.prisma`)

### Key Smart Contracts
- `CercleConsent.sol`: ERC721 Soul Bound Token for managing patient consent NFTs (non-transferable)
- `CercleToken.sol`: ERC20 Soul Bound Token for contribution points (non-transferable, non-monetary)

### Frontend Structure
- `app/patient/`: Patient interface (registration, data upload, consent management)
- `app/researcher/`: Researcher interface (study management, data access)
- `app/api/`: Next.js API routes
- `components/`: React components organized by domain (patient/, researcher/, shared/, ui/)
- `hooks/`: Custom React hooks for blockchain interactions (useCercleBalance, usePatientConsents, etc.)

## Development Commands

### Backend (Smart Contracts)
```bash
cd backend
npx hardhat compile              # Compile contracts
npx hardhat test                 # Run contract tests
npx hardhat coverage             # Run tests with coverage
npx hardhat node                 # Start local blockchain
npx hardhat run scripts/deployConsent.ts --network localhost
npx hardhat run scripts/deployToken.ts --network localhost
npx hardhat clean && npx hardhat compile  # Clean rebuild
```

### Frontend
```bash
cd frontend
npm run dev                      # Start dev server (Turbopack)
npm run build                    # Production build
npm run lint                     # ESLint
npm test                         # Run Jest tests
```

### Database
```bash
cd frontend
npx prisma generate              # Generate Prisma client
npx prisma migrate dev           # Run migrations (dev)
npx prisma studio                # Database GUI (localhost:5555)
npx prisma migrate reset         # Reset database
```

### Docker
```bash
docker-compose up -d postgres    # Start PostgreSQL
docker-compose down -v           # Stop and clean volumes
```

## Local Development Setup

1. Start PostgreSQL: `docker-compose up -d postgres`
2. Terminal 1: `cd backend && npx hardhat node`
3. Terminal 2: `cd backend && npx hardhat run scripts/deployConsent.ts --network localhost && npx hardhat run scripts/deployToken.ts --network localhost`
4. Terminal 3: `cd frontend && npm run dev`

Frontend runs at `http://localhost:3000`

## Environment Variables

Frontend requires in `.env`:
```
DATABASE_URL="postgresql://postgres:postgres@localhost:5432/cerclebleu"
NEXT_PUBLIC_CERCLE_CONSENT_ADDRESS="<deployed address>"
NEXT_PUBLIC_CERCLE_TOKEN_ADDRESS="<deployed address>"
NEXT_PUBLIC_CHAIN_ID="31337"
NEXT_PUBLIC_RPC_URL="http://127.0.0.1:8545"
```

## Tech Stack

- Solidity 0.8.28 with OpenZeppelin contracts
- Next.js 15, React 19, TypeScript, Tailwind CSS 4, shadcn/ui
- Wagmi + RainbowKit + Viem for Web3
- PostgreSQL + Prisma ORM
- Hardhat for smart contract development
- Jest for frontend tests, Hardhat test + Chai for contracts
