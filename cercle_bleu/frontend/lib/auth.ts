import { NextRequest, NextResponse } from 'next/server';
import { prisma } from '@/lib/prisma';
import { auth } from '@/lib/auth-config';

export type AuthenticatedUser = {
  email: string;
  userType: 'patient' | 'researcher';
  userId: string | number;
};

export type AuthResult =
  | { success: true; user: AuthenticatedUser }
  | { success: false; error: string; code: string; status: number };

async function lookupUserByEmail(email: string): Promise<AuthenticatedUser> {
  const normalized = email.toLowerCase();

  const patient = await prisma.patient.findUnique({ where: { email: normalized } });
  if (patient) {
    return { email: normalized, userType: 'patient', userId: patient.id };
  }

  const researcher = await prisma.researcher.findUnique({ where: { email: normalized } });
  if (researcher) {
    return { email: normalized, userType: 'researcher', userId: researcher.id };
  }

  // Not registered yet — allowed for registration endpoints
  return { email: normalized, userType: 'patient', userId: 0 };
}

/**
 * Verify authentication via NextAuth session.
 * Works in Next.js App Router API routes.
 */
export async function verifyWalletAuth(_request: NextRequest): Promise<AuthResult> {
  const session = await auth();

  if (!session?.user?.email) {
    return {
      success: false,
      error: 'Authentication required',
      code: 'AUTH_REQUIRED',
      status: 401,
    };
  }

  const user = await lookupUserByEmail(session.user.email);
  return { success: true, user };
}

// Keep the old name as an alias for backward compatibility
export const verifyAuth = verifyWalletAuth;

export async function verifyPatientOwnership(
  authUser: AuthenticatedUser,
  patientId: number
): Promise<{ authorized: boolean; error?: string }> {
  if (authUser.userType === 'patient') {
    if (authUser.userId !== patientId) {
      return { authorized: false, error: 'You can only access your own data' };
    }
    return { authorized: true };
  }
  return { authorized: false, error: 'Access denied' };
}

export async function verifyResearcherOwnership(
  authUser: AuthenticatedUser,
  researcherId: string
): Promise<{ authorized: boolean; error?: string }> {
  if (authUser.userType !== 'researcher') {
    return { authorized: false, error: 'Only researchers can access this resource' };
  }
  if (authUser.userId !== researcherId) {
    return { authorized: false, error: 'You can only access your own data' };
  }
  return { authorized: true };
}

/** @deprecated - use email comparison instead */
export function verifyWalletMatch(
  authUser: AuthenticatedUser,
  _targetWallet: string
): boolean {
  // Wallet matching is no longer used - always return true for registered users
  return authUser.userId !== 0;
}

export function unauthorizedResponse(error: string, code: string): NextResponse {
  return NextResponse.json({ error, code }, { status: 401 });
}

export function forbiddenResponse(error: string, code: string): NextResponse {
  return NextResponse.json({ error, code }, { status: 403 });
}
