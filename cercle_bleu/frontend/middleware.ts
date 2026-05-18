import { NextRequest, NextResponse } from 'next/server';
import { jwtVerify } from 'jose';

const SESSION_COOKIE_NAME = 'cercle_session';

/**
 * Authentication Flow for New Users:
 *
 * 1. User visits "/" (welcome page) - NO wallet needed, NO session needed
 * 2. User connects wallet via RainbowKit
 * 3. User chooses role (patient or researcher)
 * 4. User goes to /patient/profile or /researcher/profile - NO session needed yet
 * 5. User completes registration (blockchain + database)
 * 6. API creates session via /api/auth/session
 * 7. User is redirected to dashboard (requires session from this point)
 *
 * This middleware protects authenticated routes while allowing registration flow.
 */

function getSecretKey(): Uint8Array {
  const secret = process.env.SESSION_SECRET;
  if (!secret) {
    // In development, allow a fallback but log warning
    console.warn('SESSION_SECRET not set - using insecure fallback for development');
    return new TextEncoder().encode('insecure-dev-secret-change-in-production');
  }
  return new TextEncoder().encode(secret);
}

async function verifySessionToken(token: string): Promise<boolean> {
  try {
    const { payload } = await jwtVerify(token, getSecretKey());

    // Validate payload has required fields
    if (
      typeof payload.walletAddress !== 'string' ||
      (payload.userType !== 'patient' && payload.userType !== 'researcher')
    ) {
      return false;
    }

    return true;
  } catch {
    return false;
  }
}

export async function middleware(request: NextRequest) {
  const { pathname } = request.nextUrl;

  // PUBLIC ROUTES - Accessible without authentication
  // These routes allow new users to complete registration
  const publicRoutes = [
    '/patient/profile',      // Patient registration page
    '/researcher/profile',   // Researcher registration page (if exists)
  ];

  if (publicRoutes.includes(pathname)) {
    return NextResponse.next();
  }

  // PROTECTED ROUTES - Require valid session
  // All other /patient/* and /researcher/* routes need authentication

  // Get session cookie
  const sessionCookie = request.cookies.get(SESSION_COOKIE_NAME);

  if (!sessionCookie?.value) {
    // No session cookie - redirect to home
    return NextResponse.redirect(new URL('/', request.url));
  }

  // Verify session token
  const isValid = await verifySessionToken(sessionCookie.value);

  if (!isValid) {
    // Invalid or expired session - clear cookie and redirect
    const response = NextResponse.redirect(new URL('/', request.url));
    response.cookies.delete(SESSION_COOKIE_NAME);
    return response;
  }

  // Valid session - continue
  return NextResponse.next();
}

export const config = {
  // Only run middleware on patient and researcher routes
  // Homepage "/" is always public and accessible without wallet
  matcher: ['/patient/:path*', '/researcher/:path*'],
};
