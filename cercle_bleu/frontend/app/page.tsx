'use client';

import WelcomePage from "@/components/shared/WelcomePage";

/**
 * Home page - always shows WelcomePage
 *
 * Flow:
 * 1. User sees welcome page with features and "Connect Wallet" button
 * 2. User connects wallet - STAYS on welcome page
 * 3. Welcome page shows registration options (Patient/Researcher)
 * 4. User chooses role and completes registration
 * 5. After registration, user is redirected to their dashboard
 */
export default function Home() {
  return <WelcomePage />;
}