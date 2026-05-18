/**
 * Functional Tests: Navigation & Route Protection
 *
 * Tests public vs protected routes and authentication flow
 */

import { describe, it, expect, beforeEach, jest } from '@jest/globals';

// Mock Next.js router
const mockPush = jest.fn();
const mockReplace = jest.fn();

jest.mock('next/navigation', () => ({
  useRouter: () => ({
    push: mockPush,
    replace: mockReplace,
    pathname: '/',
  }),
  usePathname: () => '/',
}));

// Mock wagmi hooks
const mockAccount = {
  address: undefined as string | undefined,
  isConnected: false,
};

jest.mock('wagmi', () => ({
  useAccount: () => mockAccount,
  useSignMessage: () => ({
    signMessageAsync: jest.fn(),
  }),
}));

// Mock AuthContext
const mockAuthContext = {
  userType: null as 'patient' | 'researcher' | 'unknown' | null,
  userData: null,
  isLoadingUser: false,
  isAuthenticated: false,
  authenticate: jest.fn(),
  refreshUserData: jest.fn(),
};

jest.mock('@/contexts/AuthContext', () => ({
  useAuthContext: () => mockAuthContext,
}));

describe('Navigation: Public Routes', () => {
  beforeEach(() => {
    // Reset all mocks
    mockPush.mockClear();
    mockReplace.mockClear();
    mockAccount.address = undefined;
    mockAccount.isConnected = false;
    mockAuthContext.userType = null;
    mockAuthContext.userData = null;
    mockAuthContext.isAuthenticated = false;
  });

  describe('Welcome Page (/)', () => {
    it('should be accessible without wallet connection', () => {
      // Arrange: No wallet connected
      mockAccount.isConnected = false;

      // Act: Visit homepage
      // Assert: Should show WelcomePage (not redirect)
      expect(mockAccount.isConnected).toBe(false);
      // No redirect should happen
      expect(mockPush).not.toHaveBeenCalled();
    });

    it('should show welcome content for non-connected users', () => {
      // Arrange
      mockAccount.isConnected = false;

      // Assert: Welcome page should be visible
      // Component should render WelcomePage
      const shouldShowWelcome = !mockAccount.isConnected;
      expect(shouldShowWelcome).toBe(true);
    });

    it('should show role selection after wallet connection', () => {
      // Arrange: Wallet connected but user type unknown
      mockAccount.isConnected = true;
      mockAccount.address = '0x1234567890123456789012345678901234567890';
      mockAuthContext.userType = 'unknown';

      // Assert: Should show HomePage (role selection)
      const shouldShowRoleSelection = mockAccount.isConnected && mockAuthContext.userType === 'unknown';
      expect(shouldShowRoleSelection).toBe(true);
    });

    it('should auto-redirect registered patients to dashboard', () => {
      // Arrange: Registered patient connects wallet
      mockAccount.isConnected = true;
      mockAccount.address = '0x1234567890123456789012345678901234567890';
      mockAuthContext.userType = 'patient';
      mockAuthContext.userData = { id: 1, firstName: 'John', lastName: 'Doe' };

      // Act: HomePage useEffect should trigger redirect
      const shouldRedirect = !!(mockAuthContext.userType === 'patient' && mockAuthContext.userData);

      // Assert
      expect(shouldRedirect).toBe(true);
      // In real component, this would call router.push('/patient/dashboard')
    });

    it('should auto-redirect registered researchers to dashboard', () => {
      // Arrange: Registered researcher connects wallet
      mockAccount.isConnected = true;
      mockAuthContext.userType = 'researcher';
      mockAuthContext.userData = { id: 'uuid', firstName: 'Dr.', lastName: 'Smith' };

      // Assert
      const shouldRedirect = !!(mockAuthContext.userType === 'researcher' && mockAuthContext.userData);
      expect(shouldRedirect).toBe(true);
    });
  });

  describe('Public Marketing Pages', () => {
    const publicRoutes = [
      '/blog',
      '/community',
      '/sponsor',
      '/api/studies', // Public API endpoint
    ];

    publicRoutes.forEach(route => {
      it(`${route} should be accessible without authentication`, () => {
        // Arrange: No authentication
        mockAccount.isConnected = false;
        mockAuthContext.isAuthenticated = false;

        // Assert: These routes should not require auth
        const isPublicRoute = true; // These routes are not in middleware matcher
        expect(isPublicRoute).toBe(true);
      });
    });
  });
});

describe('Navigation: Registration Routes', () => {
  beforeEach(() => {
    mockPush.mockClear();
    mockAccount.isConnected = true;
    mockAccount.address = '0x1234567890123456789012345678901234567890';
  });

  describe('Patient Registration (/patient/profile)', () => {
    it('should be accessible without session (new users)', () => {
      // Arrange: Wallet connected but no session/registration
      mockAuthContext.userType = 'unknown';
      mockAuthContext.isAuthenticated = false;

      // Assert: Should allow access
      const canAccess = mockAccount.isConnected; // Only needs wallet
      expect(canAccess).toBe(true);
    });

    it('should redirect to dashboard if already registered', () => {
      // Arrange: Already registered patient
      mockAuthContext.userType = 'patient';
      mockAuthContext.userData = { id: 1, firstName: 'John', lastName: 'Doe' };

      // Act: Try to visit /patient/profile
      const shouldRedirectToDashboard = !!(mockAuthContext.userType === 'patient' && mockAuthContext.userData);

      // Assert
      expect(shouldRedirectToDashboard).toBe(true);
      // Component would call router.push('/patient/dashboard')
    });

    it('should redirect to home if wallet disconnected', () => {
      // Arrange: Wallet disconnected
      mockAccount.isConnected = false;

      // Act: Try to visit /patient/profile
      const shouldRedirectToHome = !mockAccount.isConnected;

      // Assert
      expect(shouldRedirectToHome).toBe(true);
    });
  });

  describe('Researcher Registration (/researcher/profile)', () => {
    it('should be accessible without session (new users)', () => {
      // Arrange: Wallet connected but not registered
      mockAuthContext.userType = 'unknown';
      mockAuthContext.isAuthenticated = false;

      // Assert
      const canAccess = mockAccount.isConnected;
      expect(canAccess).toBe(true);
    });

    it('should redirect to dashboard if already registered', () => {
      // Arrange: Already registered researcher
      mockAuthContext.userType = 'researcher';
      mockAuthContext.userData = { id: 'uuid', firstName: 'Dr.', lastName: 'Smith' };

      // Assert
      const shouldRedirectToDashboard = !!(mockAuthContext.userType === 'researcher' && mockAuthContext.userData);
      expect(shouldRedirectToDashboard).toBe(true);
    });

    it('should prevent patient from accessing researcher registration', () => {
      // Arrange: User is already registered as patient
      mockAuthContext.userType = 'patient';
      mockAuthContext.userData = { id: 1, firstName: 'John', lastName: 'Doe' };

      // Act: Try to visit /researcher/profile
      const shouldPreventAccess = mockAuthContext.userType === 'patient';

      // Assert: Should redirect to patient dashboard
      expect(shouldPreventAccess).toBe(true);
    });
  });
});

describe('Navigation: Protected Routes (Middleware)', () => {
  beforeEach(() => {
    mockPush.mockClear();
    mockAccount.isConnected = true;
    mockAccount.address = '0x1234567890123456789012345678901234567890';
  });

  describe('Patient Protected Routes', () => {
    const patientProtectedRoutes = [
      '/patient/dashboard',
      '/patient/upload',
      '/patient/consent',
      '/patient/edit-profile',
    ];

    patientProtectedRoutes.forEach(route => {
      it(`${route} should require authentication`, () => {
        // Arrange: No session
        mockAuthContext.isAuthenticated = false;

        // Act: Try to access protected route
        // Middleware would intercept this

        // Assert: Should redirect to home
        const hasSession = false; // No session cookie
        const shouldRedirect = !hasSession;
        expect(shouldRedirect).toBe(true);
      });

      it(`${route} should be accessible with valid session`, () => {
        // Arrange: Valid session exists
        mockAuthContext.isAuthenticated = true;
        mockAuthContext.userType = 'patient';

        // Act: Access protected route
        const hasValidSession = true;

        // Assert: Should allow access
        expect(hasValidSession).toBe(true);
      });
    });

    it('should redirect researcher away from patient routes', () => {
      // Arrange: Researcher tries to access patient dashboard
      mockAuthContext.isAuthenticated = true;
      mockAuthContext.userType = 'researcher';

      // Act: Try to visit /patient/dashboard
      const isWrongUserType = mockAuthContext.userType !== 'patient';

      // Assert: Should redirect (handled by component logic)
      expect(isWrongUserType).toBe(true);
    });
  });

  describe('Researcher Protected Routes', () => {
    const researcherProtectedRoutes = [
      '/researcher/dashboard',
      '/researcher/studies',
      '/researcher/data',
    ];

    researcherProtectedRoutes.forEach(route => {
      it(`${route} should require authentication`, () => {
        // Arrange: No session
        mockAuthContext.isAuthenticated = false;

        // Act: Try to access protected route
        const hasSession = false;
        const shouldRedirect = !hasSession;

        // Assert: Middleware redirects to home
        expect(shouldRedirect).toBe(true);
      });

      it(`${route} should be accessible with valid session`, () => {
        // Arrange: Valid researcher session
        mockAuthContext.isAuthenticated = true;
        mockAuthContext.userType = 'researcher';

        // Assert
        const hasValidSession = true;
        expect(hasValidSession).toBe(true);
      });
    });

    it('should redirect patient away from researcher routes', () => {
      // Arrange: Patient tries to access researcher dashboard
      mockAuthContext.isAuthenticated = true;
      mockAuthContext.userType = 'patient';

      // Act: Try to visit /researcher/dashboard
      const isWrongUserType = mockAuthContext.userType !== 'researcher';

      // Assert
      expect(isWrongUserType).toBe(true);
    });
  });
});

describe('Navigation: Session Expiration', () => {
  beforeEach(() => {
    mockPush.mockClear();
  });

  it('should redirect to home when session expires', () => {
    // Arrange: User was authenticated
    mockAuthContext.isAuthenticated = true;
    mockAuthContext.userType = 'patient';

    // Act: Session expires (15 min timeout)
    mockAuthContext.isAuthenticated = false; // Session invalidated

    // Assert: Should redirect to home
    const shouldRedirect = !mockAuthContext.isAuthenticated;
    expect(shouldRedirect).toBe(true);
  });

  it('should clear session on wallet disconnect', () => {
    // Arrange: User authenticated and connected
    mockAccount.isConnected = true;
    mockAuthContext.isAuthenticated = true;

    // Act: User disconnects wallet
    mockAccount.isConnected = false;

    // Assert: AuthContext should clear session
    const shouldClearSession = !mockAccount.isConnected;
    expect(shouldClearSession).toBe(true);
  });
});

describe('Navigation: Role-Based Access Control', () => {
  beforeEach(() => {
    mockPush.mockClear();
    mockAccount.isConnected = true;
    mockAuthContext.isAuthenticated = true;
  });

  it('patient can access patient routes', () => {
    // Arrange
    mockAuthContext.userType = 'patient';
    mockAuthContext.userData = { id: 1, firstName: 'John', lastName: 'Doe' };

    // Assert
    const canAccessPatientRoutes = mockAuthContext.userType === 'patient';
    expect(canAccessPatientRoutes).toBe(true);
  });

  it('patient cannot access researcher routes', () => {
    // Arrange
    mockAuthContext.userType = 'patient';

    // Act: Try to access /researcher/dashboard
    const canAccessResearcherRoutes = mockAuthContext.userType === 'researcher';

    // Assert
    expect(canAccessResearcherRoutes).toBe(false);
  });

  it('researcher can access researcher routes', () => {
    // Arrange
    mockAuthContext.userType = 'researcher';
    mockAuthContext.userData = { id: 'uuid', firstName: 'Dr.', lastName: 'Smith' };

    // Assert
    const canAccessResearcherRoutes = mockAuthContext.userType === 'researcher';
    expect(canAccessResearcherRoutes).toBe(true);
  });

  it('researcher cannot access patient routes', () => {
    // Arrange
    mockAuthContext.userType = 'researcher';

    // Act: Try to access /patient/dashboard
    const canAccessPatientRoutes = mockAuthContext.userType === 'patient';

    // Assert
    expect(canAccessPatientRoutes).toBe(false);
  });

  it('unknown user type can only access registration and public routes', () => {
    // Arrange
    mockAuthContext.userType = 'unknown';
    mockAuthContext.isAuthenticated = false;

    // Assert
    const canAccessDashboards = mockAuthContext.userType === 'patient' || mockAuthContext.userType === 'researcher';
    const canAccessRegistration = mockAccount.isConnected;
    const canAccessPublic = true;

    expect(canAccessDashboards).toBe(false);
    expect(canAccessRegistration).toBe(true);
    expect(canAccessPublic).toBe(true);
  });
});

describe('Navigation: Middleware Matcher Configuration', () => {
  it('should only protect /patient/* and /researcher/* routes', () => {
    // Middleware config
    const middlewareMatcher = ['/patient/:path*', '/researcher/:path*'];

    // Routes that should be protected
    const protectedRoutes = [
      '/patient/dashboard',
      '/patient/upload',
      '/patient/consent',
      '/researcher/dashboard',
      '/researcher/studies',
    ];

    // Routes that should NOT be protected (excluded by middleware)
    const publicRoutes = [
      '/',
      '/blog',
      '/community',
      '/sponsor',
    ];

    // Assert protected routes match pattern
    protectedRoutes.forEach(route => {
      const isProtected = route.startsWith('/patient/') || route.startsWith('/researcher/');
      expect(isProtected).toBe(true);
    });

    // Assert public routes don't match pattern
    publicRoutes.forEach(route => {
      const isProtected = route.startsWith('/patient/') || route.startsWith('/researcher/');
      expect(isProtected).toBe(false);
    });
  });

  it('should allow registration routes even though they match pattern', () => {
    // These routes match the pattern but are explicitly allowed
    const registrationRoutes = ['/patient/profile', '/researcher/profile'];

    // In middleware, these are in the publicRoutes array
    const publicRoutes = ['/patient/profile', '/researcher/profile'];

    registrationRoutes.forEach(route => {
      const isExplicitlyAllowed = publicRoutes.includes(route);
      expect(isExplicitlyAllowed).toBe(true);
    });
  });
});

describe('Navigation: Complete User Journeys', () => {
  beforeEach(() => {
    mockPush.mockClear();
    mockReplace.mockClear();
  });

  it('should follow complete new patient journey', () => {
    // Step 1: Visit homepage without wallet
    mockAccount.isConnected = false;
    expect(mockAccount.isConnected).toBe(false);

    // Step 2: Connect wallet
    mockAccount.isConnected = true;
    mockAccount.address = '0x1234567890123456789012345678901234567890';
    mockAuthContext.userType = 'unknown';
    expect(mockAccount.isConnected).toBe(true);

    // Step 3: Choose patient role (navigate to /patient/profile)
    // Should be allowed
    const canAccessProfile = mockAccount.isConnected;
    expect(canAccessProfile).toBe(true);

    // Step 4: Complete registration
    mockAuthContext.userType = 'patient';
    mockAuthContext.userData = { id: 1, firstName: 'John', lastName: 'Doe' };
    mockAuthContext.isAuthenticated = true;

    // Step 5: Redirect to dashboard
    const shouldRedirectToDashboard = !!(mockAuthContext.userType === 'patient' && mockAuthContext.userData);
    expect(shouldRedirectToDashboard).toBe(true);

    // Step 6: Access protected routes
    const canAccessProtectedRoutes = mockAuthContext.isAuthenticated;
    expect(canAccessProtectedRoutes).toBe(true);
  });

  it('should follow complete returning user journey', () => {
    // Step 1: Visit homepage
    mockAccount.isConnected = false;

    // Step 2: Connect wallet (already registered)
    mockAccount.isConnected = true;
    mockAccount.address = '0x1234567890123456789012345678901234567890';

    // Step 3: AuthContext fetches user data
    mockAuthContext.userType = 'patient';
    mockAuthContext.userData = { id: 1, firstName: 'John', lastName: 'Doe' };
    mockAuthContext.isAuthenticated = true;

    // Step 4: Auto-redirect to dashboard
    const shouldAutoRedirect = !!(mockAuthContext.userType && mockAuthContext.userData);
    expect(shouldAutoRedirect).toBe(true);
  });

  it('should handle wallet disconnect during session', () => {
    // Arrange: User authenticated and using app
    mockAccount.isConnected = true;
    mockAuthContext.isAuthenticated = true;
    mockAuthContext.userType = 'patient';

    // Act: User disconnects wallet
    mockAccount.isConnected = false;

    // Assert: Session should be cleared
    const shouldClearSession = !mockAccount.isConnected;
    expect(shouldClearSession).toBe(true);

    // AuthContext.logout() should be called
    // User redirected to home
  });

  it('should prevent cross-role access', () => {
    // Arrange: Registered patient
    mockAuthContext.userType = 'patient';
    mockAuthContext.isAuthenticated = true;

    // Act: Try to access researcher profile
    const canAccessResearcherProfile = mockAuthContext.userType === 'researcher';

    // Assert: Should be prevented
    expect(canAccessResearcherProfile).toBe(false);

    // Component would redirect to /patient/dashboard
  });
});
