import { SignJWT, jwtVerify } from 'jose';
import { cookies } from 'next/headers';

export type SessionPayload = {
  walletAddress: string;
  userType: 'patient' | 'researcher';
  iat: number;
  exp: number;
};

const SESSION_COOKIE_NAME = 'cercle_session';
const SESSION_DURATION = 1440 * 60; // 24 hours in seconds

function getSecretKey(): Uint8Array {
  const secret = process.env.SESSION_SECRET;
  if (!secret) {
    throw new Error('SESSION_SECRET environment variable is not set');
  }
  return new TextEncoder().encode(secret);
}

/**
 * Create a session JWT and set it as an httpOnly cookie
 */
export async function createSession(
  walletAddress: string,
  userType: 'patient' | 'researcher'
): Promise<string> {
  const now = Math.floor(Date.now() / 1000);
  const exp = now + SESSION_DURATION;

  const token = await new SignJWT({
    walletAddress: walletAddress.toLowerCase(),
    userType,
  })
    .setProtectedHeader({ alg: 'HS256' })
    .setIssuedAt(now)
    .setExpirationTime(exp)
    .sign(getSecretKey());

  const cookieStore = await cookies();
  cookieStore.set(SESSION_COOKIE_NAME, token, {
    httpOnly: true,
    secure: process.env.NODE_ENV === 'production',
    sameSite: 'lax',
    maxAge: SESSION_DURATION,
    path: '/',
  });

  return token;
}

/**
 * Verify a session token and return the payload
 */
export async function verifySession(token: string): Promise<SessionPayload | null> {
  try {
    const { payload } = await jwtVerify(token, getSecretKey());

    // Validate payload structure
    if (
      typeof payload.walletAddress !== 'string' ||
      (payload.userType !== 'patient' && payload.userType !== 'researcher') ||
      typeof payload.iat !== 'number' ||
      typeof payload.exp !== 'number'
    ) {
      return null;
    }

    return {
      walletAddress: payload.walletAddress,
      userType: payload.userType,
      iat: payload.iat,
      exp: payload.exp,
    };
  } catch {
    return null;
  }
}

/**
 * Get the current session from cookies (for Server Components)
 */
export async function getSession(): Promise<SessionPayload | null> {
  const cookieStore = await cookies();
  const token = cookieStore.get(SESSION_COOKIE_NAME)?.value;

  if (!token) {
    return null;
  }

  return verifySession(token);
}

/**
 * Delete the session cookie
 */
export async function deleteSession(): Promise<void> {
  const cookieStore = await cookies();
  cookieStore.delete(SESSION_COOKIE_NAME);
}

/**
 * Get the session cookie name (for middleware use)
 */
export function getSessionCookieName(): string {
  return SESSION_COOKIE_NAME;
}
