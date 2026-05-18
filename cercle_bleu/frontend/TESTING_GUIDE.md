# Testing Guide: Authentication & Navigation

## Overview

This guide covers testing the authentication system and navigation flows in Cercle Bleu.

## Test Files Created

1. **Unit Tests**: `__tests__/navigation.test.ts`
   - Tests navigation logic with mocked dependencies
   - Fast, runs in Node.js environment
   - Tests authentication state management

2. **E2E Tests**: `e2e/navigation.spec.ts`
   - Tests actual browser navigation
   - Runs in real browser environment
   - Tests complete user journeys

---

## Setup

### 1. Install Test Dependencies

```bash
cd frontend

# Install Jest dependencies (if not already installed)
npm install --save-dev jest @jest/globals @types/jest ts-jest

# Install Playwright dependencies
npm install --save-dev @playwright/test

# Install Playwright browsers
npx playwright install
```

### 2. Update package.json

Add test scripts to `frontend/package.json`:

```json
{
  "scripts": {
    "test": "jest",
    "test:watch": "jest --watch",
    "test:coverage": "jest --coverage",
    "test:e2e": "playwright test",
    "test:e2e:ui": "playwright test --ui",
    "test:e2e:headed": "playwright test --headed",
    "test:e2e:debug": "playwright test --debug"
  }
}
```

### 3. Create Jest Configuration

Create `frontend/jest.config.js`:

```javascript
const nextJest = require('next/jest');

const createJestConfig = nextJest({
  // Path to your Next.js app
  dir: './',
});

const customJestConfig = {
  setupFilesAfterEnv: ['<rootDir>/jest.setup.js'],
  testEnvironment: 'jest-environment-jsdom',
  moduleNameMapper: {
    '^@/(.*)$': '<rootDir>/$1',
  },
  testMatch: [
    '**/__tests__/**/*.test.[jt]s?(x)',
    '**/?(*.)+(spec|test).[jt]s?(x)',
  ],
  collectCoverageFrom: [
    'lib/**/*.{js,jsx,ts,tsx}',
    'contexts/**/*.{js,jsx,ts,tsx}',
    'hooks/**/*.{js,jsx,ts,tsx}',
    'components/**/*.{js,jsx,ts,tsx}',
    '!**/*.d.ts',
    '!**/node_modules/**',
  ],
};

module.exports = createJestConfig(customJestConfig);
```

### 4. Create Jest Setup

Create `frontend/jest.setup.js`:

```javascript
import '@testing-library/jest-dom';
```

---

## Running Tests

### Unit Tests (Jest)

```bash
# Run all unit tests
npm test

# Run in watch mode
npm run test:watch

# Run with coverage
npm run test:coverage

# Run specific test file
npm test -- navigation.test.ts
```

### E2E Tests (Playwright)

```bash
# Start dev server first (in separate terminal)
npm run dev

# Then run E2E tests
npm run test:e2e

# Run with UI mode (interactive)
npm run test:e2e:ui

# Run with headed browsers (visible)
npm run test:e2e:headed

# Debug mode
npm run test:e2e:debug

# Run specific browser
npx playwright test --project=chromium
npx playwright test --project=firefox
npx playwright test --project=webkit

# Run specific test file
npx playwright test e2e/navigation.spec.ts
```

---

## Test Coverage

### What's Tested

#### ✅ Public Routes
- [x] Homepage accessible without wallet
- [x] Welcome page displays correct content
- [x] Marketing pages accessible (blog, community, sponsor)
- [x] Public API endpoints work without auth

#### ✅ Protected Routes
- [x] Patient dashboard requires authentication
- [x] Researcher dashboard requires authentication
- [x] All protected routes redirect to home when unauthenticated
- [x] Middleware blocks unauthorized access

#### ✅ Registration Routes
- [x] Patient profile accessible with wallet (no session)
- [x] Researcher profile accessible with wallet (no session)
- [x] Redirect to home if no wallet connected
- [x] Redirect to dashboard if already registered

#### ✅ Authentication Flow
- [x] New user journey (welcome → connect → register → dashboard)
- [x] Returning user journey (connect → auto-redirect)
- [x] Session expiration handling
- [x] Wallet disconnect clears session

#### ✅ Role-Based Access Control
- [x] Patients can access patient routes
- [x] Patients cannot access researcher routes
- [x] Researchers can access researcher routes
- [x] Researchers cannot access patient routes

#### ✅ API Security
- [x] Protected endpoints require auth headers
- [x] Public endpoints work without auth
- [x] Ownership verification prevents IDOR
- [x] Invalid signatures rejected

---

## Test Scenarios

### Scenario 1: New Patient Registration

```typescript
// Unit test validates state transitions
test('should follow complete new patient journey', () => {
  // 1. Visit homepage - no wallet
  // 2. Connect wallet
  // 3. Choose patient role
  // 4. Complete registration
  // 5. Redirect to dashboard
  // 6. Access protected routes
});
```

```typescript
// E2E test validates actual UI
test('new patient can complete registration', async ({ page }) => {
  await page.goto('/');
  // Click connect wallet
  // Fill registration form
  // Verify redirect to dashboard
});
```

### Scenario 2: Protected Route Access

```typescript
// Unit test
test('should redirect to home without session', () => {
  // Try to access /patient/dashboard
  // No session exists
  // Should redirect to /
});
```

```typescript
// E2E test
test('patient dashboard should redirect without session', async ({ page }) => {
  await page.goto('/patient/dashboard');
  await expectRedirectToHome(page);
});
```

### Scenario 3: API Authentication

```typescript
// E2E test
test('protected API requires auth headers', async ({ request }) => {
  const response = await request.get('/api/patient/1');
  expect(response.status()).toBe(401);

  const data = await response.json();
  expect(data.code).toBe('AUTH_REQUIRED');
});
```

---

## Manual Testing Checklist

Use this checklist for manual testing:

### Public Access
- [ ] Visit `/` without wallet - should show welcome page
- [ ] Browse `/blog`, `/community`, `/sponsor` - should be accessible
- [ ] Call `GET /api/studies` - should return data

### Patient Flow
- [ ] Connect wallet on homepage
- [ ] Click "Je suis un patient"
- [ ] Navigate to `/patient/profile`
- [ ] Complete blockchain registration (sign tx)
- [ ] Complete profile form (medical info)
- [ ] Sign authentication message
- [ ] Redirected to `/patient/dashboard`
- [ ] Dashboard loads successfully
- [ ] Try accessing `/researcher/dashboard` - should redirect
- [ ] Disconnect wallet - should redirect to home
- [ ] Reconnect wallet - should auto-redirect to dashboard

### Researcher Flow
- [ ] Connect wallet on homepage
- [ ] Click "Je suis un chercheur"
- [ ] Navigate to `/researcher/profile`
- [ ] Complete registration form
- [ ] Sign authentication message
- [ ] Redirected to `/researcher/dashboard`
- [ ] Dashboard loads successfully
- [ ] Try accessing `/patient/dashboard` - should redirect
- [ ] Disconnect wallet - should redirect to home

### Security Testing
- [ ] Try accessing `/patient/dashboard` in incognito - should redirect
- [ ] Try accessing `/api/patient/1` without headers - should return 401
- [ ] Try accessing another patient's data - should return 403
- [ ] Clear cookies and reload protected route - should redirect
- [ ] Let session expire (15 min) - should redirect on next request

---

## Common Issues & Solutions

### Issue: Tests failing with "Cannot find module"

**Solution:**
```bash
# Install missing dependencies
npm install --save-dev @jest/globals @types/jest

# Ensure jest.config.js has correct moduleNameMapper
```

### Issue: Playwright can't connect to dev server

**Solution:**
```bash
# Start dev server manually first
npm run dev

# Then run tests in another terminal
npm run test:e2e

# Or configure webServer in playwright.config.ts (already done)
```

### Issue: Tests pass locally but fail in CI

**Solution:**
```bash
# Add to CI workflow
- name: Install Playwright
  run: npx playwright install --with-deps

- name: Run E2E tests
  run: npm run test:e2e
```

### Issue: Wallet connection not working in tests

**Solution:**
E2E tests with real wallet connection require special setup. Options:
1. Use Synpress (Playwright + MetaMask)
2. Mock wallet in browser context
3. Use headless wallet for testing

---

## CI/CD Integration

### GitHub Actions Example

Create `.github/workflows/test.yml`:

```yaml
name: Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v3

      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'

      - name: Install dependencies
        run: cd frontend && npm ci

      - name: Run unit tests
        run: cd frontend && npm test

      - name: Install Playwright
        run: cd frontend && npx playwright install --with-deps

      - name: Run E2E tests
        run: cd frontend && npm run test:e2e

      - name: Upload test results
        if: always()
        uses: actions/upload-artifact@v3
        with:
          name: playwright-report
          path: frontend/playwright-report/
```

---

## Advanced Testing

### Testing with Real Wallet Connection

For testing wallet-connected flows, use Synpress:

```bash
npm install --save-dev @synthetixio/synpress
```

Example:
```typescript
import { MetaMask } from '@synthetixio/synpress';

test('patient can connect wallet and register', async ({ page }) => {
  await page.goto('/');
  await page.click('button:has-text("Connect")');

  // Synpress handles MetaMask popup
  await MetaMask.connect();

  // Continue with registration flow
});
```

### Testing API with Valid Signatures

```typescript
import { signMessage } from 'viem';
import { privateKeyToAccount } from 'viem/accounts';

test('can access protected API with valid signature', async ({ request }) => {
  // Create test wallet
  const account = privateKeyToAccount('0x...');

  // Sign message
  const message = `Authenticate to Cercle Bleu\nTimestamp: ${Date.now()}\nNonce: test123`;
  const signature = await account.signMessage({ message });

  // Make authenticated request
  const response = await request.get('/api/patient/1', {
    headers: {
      'x-wallet-address': account.address,
      'x-wallet-signature': signature,
      'x-wallet-message': btoa(message),
    }
  });

  expect(response.status()).toBe(200);
});
```

---

## Coverage Goals

### Minimum Coverage Targets

- **Unit Tests**: 80% code coverage
- **E2E Tests**: All critical user paths
- **API Tests**: All endpoints tested

### Critical Paths to Test

1. ✅ User registration (patient + researcher)
2. ✅ Authentication flow
3. ✅ Protected route access
4. ✅ API authentication
5. ✅ Session management
6. ✅ Role-based access control

---

## Debugging Tests

### Jest Debugging

```bash
# Run tests in debug mode
node --inspect-brk node_modules/.bin/jest --runInBand

# Or use VS Code debugger with this launch.json:
{
  "type": "node",
  "request": "launch",
  "name": "Jest Debug",
  "program": "${workspaceFolder}/node_modules/.bin/jest",
  "args": ["--runInBand", "--no-cache"],
  "console": "integratedTerminal"
}
```

### Playwright Debugging

```bash
# Debug mode (opens inspector)
npm run test:e2e:debug

# Headed mode (see browser)
npm run test:e2e:headed

# Trace viewer (after test failure)
npx playwright show-trace trace.zip
```

---

## Next Steps

1. **Install dependencies** as shown in Setup section
2. **Run unit tests**: `npm test`
3. **Run E2E tests**: `npm run test:e2e:ui` (interactive)
4. **Check coverage**: `npm run test:coverage`
5. **Add to CI/CD** pipeline
6. **Expand tests** for additional features

---

## Resources

- [Jest Documentation](https://jestjs.io/)
- [Playwright Documentation](https://playwright.dev/)
- [Testing Library](https://testing-library.com/)
- [Synpress (Wallet Testing)](https://github.com/Synthetixio/synpress)
- [Next.js Testing](https://nextjs.org/docs/testing)

---

## Test Maintenance

### When to Update Tests

- ✅ After adding new routes
- ✅ After changing authentication logic
- ✅ After modifying API endpoints
- ✅ After updating middleware configuration
- ✅ When bugs are found (add regression tests)

### Test Naming Convention

```typescript
// Unit tests
describe('Component/Feature', () => {
  it('should do expected behavior', () => {});
});

// E2E tests
test('user can complete task', async ({ page }) => {});
```

---

**Happy Testing! 🧪**
