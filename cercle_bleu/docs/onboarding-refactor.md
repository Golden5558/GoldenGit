# Onboarding Refactor — Cercle Bleu

> **Context:** Cercle Bleu is a blockchain-based healthcare platform for diabetes patients.
> This document benchmarks best-in-class onboarding patterns (2025–2026) against our
> current flows and defines a prioritized action plan to reduce drop-off and accelerate
> time-to-value (TTV).

---

## 1. Current State

### Patient Flow (2 steps)

| Step | Screen | What happens |
|------|--------|-------------|
| 0 | Welcome page | Emotional hero + role-specific value prop + dual CTA (patient / researcher). Role intent stored before login via `useRoleIntent` hook — skips role picker after auth. |
| 1 | `/patient/profile` | Blockchain registration — `registerPatient()` on-chain |
| 2 | `/patient/profile` | Profile form — 7 required fields (name, email, birth year, weight, sex, diabetes type) |
| ✓ | `/patient/dashboard` | Dashboard: data upload, consents, rank & CERCLE tokens |

**Remaining friction points:**
- The blockchain transaction happens before any value is shown — users don't know *why* yet.
- 7 mandatory fields upfront, including sensitive medical data (weight, sex, diabetes type).
- No progress indicator; the two-step split is invisible to the user.
- No explanation of what CERCLE tokens are or what the patient gains by registering.

### Researcher Flow (1 step)

| Step | Screen | What happens |
|------|--------|-------------|
| 0 | Welcome page | Emotional hero + role-specific value prop + dual CTA. Role intent stored before login — skips role picker after auth. |
| 1 | `/researcher/profile` | Registration form — name (required), institution, email (optional) |
| ✓ | `/researcher/dashboard` | Dashboard: create studies, data access, analytics |

**Remaining friction points:**
- Wallet connection requirement is not explained before the form.
- Post-registration dashboard has no empty-state guidance (what to do first?).

---

## 2. Best-in-Class Benchmarks (2025–2026)

### Reference products

| Product | Why it's relevant | Key lesson |
|---------|-------------------|------------|
| **Canva** (prosumer SaaS) | Users create a real artefact on session 1 via guided templates | Show value *through* the action, not before |
| **Make** (automation SaaS) | Role- and goal-based routing; short surveys branch into tailored flows | 1–3 questions → personalized path |
| **Top AI tools** (Gamma, Perplexity…) | Ask 1–3 lightweight questions then drop users into a tailored first success path | Outcome-first, setup-later |
| **Modern fintechs** (Titan, Revolut…) | Completion jumped 31% → 78% after cutting steps + progressive disclosure | KYC feels like protection, not bureaucracy |

### Onboarding archetypes

1. **Quick-Win / Value-First** — expose real functionality before heavy account setup. The "aha" happens in 1–2 actions.
2. **Progressive Profiling** — collect only what is absolutely required now; defer optional fields to later in context.
3. **Goal / Use-Case Picker** — ask "What do you want to do?" right after entry and deep-link to the relevant flow.
4. **Interactive Walkthrough** — embed guidance inside the first real task instead of a static tour.
5. **Transparent Paywall / Benefit Preview** — surface what the user *gains* during or just after signup so motivation is clear before commitment.

### Friction vs. Fuel model

Every onboarding step is either **Friction** (data collection, compliance, configuration) or **Fuel** (value, progress, emotion). Best flows keep friction narrow and wrap it in fuel.

| Friction reduction | Fuel addition |
|--------------------|---------------|
| Social / wallet login first, details later | Show outcome before requiring full setup |
| Progressive disclosure — only ask what is needed now | Visible progress bar ("Step 2 of 3") |
| Explain *why* each sensitive field is needed | Trust & social proof copy near KYC steps |
| Short 1–3 question survey instead of long form | Milestone celebration (confetti, badge) |

---

## 3. Gap Analysis

| Principle | Cercle Bleu today | Target state |
|-----------|-------------------|--------------|
| Value shown before commitment | No — blockchain TX before any value | Quick preview of dashboard/tokens before TX |
| Progressive profiling | No — all 7 fields at once | Split: essential fields now, optional later |
| Progress visibility | No indicator | "Step 2 of 3" stepper with labels |
| Explanation of sensitive fields | None | Inline copy: "We need your weight to anonymize your data safely" |
| Empty-state guidance post-registration | None | First-run checklist / task list on dashboard |
| Role-specific value prop | ✅ Done | Distinct copy, empathy-first headings, tokens framed as recognition, hero with early dual CTA |
| Goal picker | No | Optional: "I want to [share data / earn tokens / join a study]" |

---

## 4. Prioritized TODO List

Priority levels: 🔴 P0 — critical drop-off risk · 🟠 P1 — high impact · 🟡 P2 — medium impact · 🟢 P3 — nice to have

---

### 🔴 P0 — Fix before next user test

- [ ] **Add a step progress indicator to the patient flow**
  Add a `<Stepper>` component (e.g. "1. Connect wallet → 2. Blockchain → 3. Profile") visible on both patient registration screens. Users currently have no sense of where they are or how long it will take.
  _Files: `PatientRegistration.tsx`, `ProfileForm.tsx`_

- [ ] **Explain the blockchain step before triggering the transaction**
  Replace the bare "S'enregistrer sur la blockchain" button with a brief explanation card:
  - What is recorded on-chain and why
  - That it requires a wallet signature (one-time, free on testnet)
  - What the user gets (NFT consent record, ownership of their data)
  _File: `PatientRegistration.tsx`_

- [ ] **Add inline microcopy for sensitive medical fields**
  Each sensitive field (weight, sex, diabetes type) needs a one-liner explaining why it is needed and how it is protected. Reduces anxiety and abandonment.
  _File: `PatientFormFields.tsx`_

---

### 🟠 P1 — High-impact improvements

- [ ] **Split the patient profile form: essential now, optional later**
  Keep only first name, last name, diabetes type, and birth year at registration time. Move weight and sex to an "Complete your profile" card shown on the dashboard after login. This reduces the initial form from 7 fields to 4.
  _Files: `ProfileForm.tsx`, `PatientFormFields.tsx`, API route `patient/register`_

- [ ] **Add an empty-state first-run checklist to both dashboards**
  After registration, show a task list:
  - Patient: "Upload your first health data", "Explore your CERCLE tokens", "Review your consent settings"
  - Researcher: "Create your first study", "Explore available datasets", "Invite a collaborator"
  Mark tasks as complete as the user performs them. Celebrate the first completion.
  _Files: `app/patient/dashboard/page.tsx`, `app/researcher/dashboard/page.tsx`_

- [ ] **Show a value preview before the blockchain step (patient) & (researcher)**
  Before the first blockchain transaction, show a 2–3 sentence benefit preview with a mock dashboard screenshot or token balance illustration. The user should understand *what they will gain* before they sign anything.
  _File: `PatientRegistration.tsx` and `ResearcherRegistration.tsx`

- [x] **Add a role-specific value proposition on the welcome page**
  Implemented. See details in § Done below.
  _File: `components/shared/WelcomePage.tsx`_

---

### 🟡 P2 — Medium-impact polish

- [ ] **Add a "What do you want to do first?" goal picker for patients**
  After blockchain registration, ask one question: "My main goal is: [Share my data / Earn tokens / Learn about research]". Deep-link the dashboard UI to highlight the relevant section first. Implement as a simple card picker, no backend required initially.
  _New component: `components/patient/GoalPicker.tsx`_

- [ ] **Improve researcher empty-state dashboard**
  Show an illustrated empty state with a single primary CTA: "Create your first study". Add a short "Why it matters" blurb linking researcher activity to patient benefits (builds trust and motivation).
  _File: `app/researcher/dashboard/page.tsx`_

- [ ] **Add progress/completion percentage to the patient profile card**
  If optional fields (weight, sex) are not yet filled, show "Profile 60% complete — add your health data to improve research matching" with a fill-in button.
  _File: `components/patient/ProfileCard.tsx` or equivalent_

- [ ] **Explain CERCLE tokens on first dashboard load**
  Add a dismissible tooltip or info banner: "CERCLE tokens represent your contribution to research. They are non-monetary and unlock platform benefits as you accumulate them." This removes confusion for new users.

---

### 🟢 P3 — Nice to have

- [ ] **Add a short animated illustration to the blockchain step**
  A simple Lottie animation or static SVG showing "your data → your NFT → your control" reduces the abstract feel of the blockchain interaction.

- [ ] **Add social proof copy near the registration CTA**
  e.g. "Join X patients already contributing to diabetes research" (can be a static number initially). 2025 fintech data shows social proof near signup can lift conversion by ~30%.

- [ ] **Implement a "Skip for now" option for optional profile fields**
  Make it explicit that users can skip optional fields and return later. Reduces decision paralysis on first registration.

- [ ] **Track onboarding funnel events**
  Instrument each step (wallet connected, blockchain TX confirmed, profile submitted, first dashboard action) so drop-off rates become measurable. Required before A/B testing any of the above changes.
  _Suggested: `analytics/onboarding.ts` utility wrapping your preferred analytics provider_

---

## 5. Done

> Changes shipped to `components/shared/WelcomePage.tsx` and `hooks/useRoleIntent.ts` on 2026-03-14.

### Welcome page — full UX overhaul

| Change | Detail |
|--------|--------|
| **Hero rewritten** | Leads with data ownership ("Vos données vous appartiennent…"), not platform description. Subtext frames the 4M patients problem before pitching the solution. |
| **Early dual CTA in hero** | Two role buttons (patient / researcher) appear above the fold — users can act before scrolling. |
| **Features grid removed** | The redundant 3-card Shield/Lock/Heart grid was saying the same thing as the role cards. Removed to reduce noise. |
| **Empathy-first role headings** | "Qui peut utiliser Cercle Bleu ?" replaced by per-card eyebrow labels: *"Vous êtes patient diabétique"* / *"Vous êtes chercheur"* with sub-headings "Reprenez le contrôle" / "Des cohortes prêtes à l'emploi". |
| **Token language reframed** | CERCLE points moved to the last bullet in the patient card, framed as recognition ("Chaque contribution est reconnue par des points CERCLE…"), not as the primary draw. |
| **Page structure fixed** | Order is now: Hero → Role cards → How it works → Trust section → Loading/role picker. CTA no longer interrupts mid-page. |
| **Trust section reframed** | "Pourquoi la blockchain ?" → "Pourquoi vous pouvez nous faire confiance ?". Developer terms (Transparence / Immutabilité / Traçabilité) replaced by patient outcomes: *"Vous savez toujours qui consulte vos données"*, *"Personne ne peut modifier votre consentement sans vous"*, *"Vous révoquez en un clic"*. |
| **Step 4 of how-it-works** | Replaced empty "Accédez à votre tableau de bord" with a motivating outcome: *"Vos premières données alimentent la recherche. Votre premier point CERCLE est attribué. Vous devenez co-acteur."* |

### Role-intent routing (`hooks/useRoleIntent.ts`)

New hook that persists the user's chosen role (`patient` / `researcher`) in `localStorage` before the Privy login modal opens. After auth resolves, the `useEffect` in `WelcomePage` reads the intent and routes directly to `/[role]/profile` — skipping the post-auth role picker entirely. The picker remains as a fallback for users who authenticated without pre-selecting a role.

---

## 6. Implementation Order (suggested sprint plan)

```
Sprint 1 (P0): Step progress indicator · Blockchain step explanation · Field microcopy
Sprint 2 (P1): Form split · First-run checklist · Value preview
Sprint 3 (P2): Goal picker · Researcher empty state · Profile completion · Token explainer
Sprint 4 (P3): Illustration · Social proof · Skip options · Analytics instrumentation
```

> Welcome page value props (originally Sprint 2) — ✅ shipped ahead of schedule.

---

## 7. Resources

| Resource | Use for |
|----------|---------|
| [Mobbin](https://mobbin.com) | Filter: Finance + Onboarding / KYC / Verification — for fintech UI patterns |
| [Growth.design](https://growth.design) | Case-study teardowns of Canva, Notion, and others — for UX principles |
| [PageFlows](https://pageflows.com) | Full-screen recordings of fintech and SaaS signup flows |
| [UserGuiding 2025 AI Onboarding Report](https://userguiding.com) | 140+ screenshots of AI-native onboarding patterns |
