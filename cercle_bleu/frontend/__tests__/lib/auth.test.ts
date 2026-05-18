/**
 * @jest-environment node
 *
 * TDD — lib/auth.ts
 *
 * Tests de verifyWalletAuth() :
 *   1. Authentification via cookie de session
 *   2. Authentification via Bearer JWT Privy (flow d'inscription)
 *   3. Cas d'erreur (token invalide, champs manquants, pas d'auth)
 */

import { describe, it, expect, beforeEach, jest } from '@jest/globals';
import { NextRequest } from 'next/server';

// ─── Mocks ────────────────────────────────────────────────────────────────────

const mockVerifySession = jest.fn<() => Promise<unknown>>();
jest.mock('@/lib/session', () => ({
  verifySession: (...args: Array<unknown>) => mockVerifySession(...args as []),
}));

const mockPrismaPatientFindUnique = jest.fn<() => Promise<unknown>>();
const mockPrismaResearcherFindUnique = jest.fn<() => Promise<unknown>>();
jest.mock('@/lib/prisma', () => ({
  prisma: {
    patient: {
      findUnique: (...args: Array<unknown>) => mockPrismaPatientFindUnique(...args as []),
    },
    researcher: {
      findUnique: (...args: Array<unknown>) => mockPrismaResearcherFindUnique(...args as []),
    },
  },
}));

const mockVerifyAccessToken = jest.fn<(token: string) => Promise<unknown>>();
jest.mock('@/lib/privyClient', () => ({
  getPrivyClient: jest.fn(() => ({
    utils: jest.fn(() => ({
      auth: jest.fn(() => ({
        verifyAccessToken: (...args: Array<unknown>) =>
          mockVerifyAccessToken(...args as [string]),
      })),
    })),
  })),
}));

// ─── Helpers ──────────────────────────────────────────────────────────────────

function makeRequest(opts: {
  cookieValue?: string;
  authorization?: string;
  walletAddress?: string;
} = {}): NextRequest {
  const headers: Record<string, string> = {};
  if (opts.authorization) headers['Authorization'] = opts.authorization;
  if (opts.walletAddress) headers['x-wallet-address'] = opts.walletAddress;

  const req = new NextRequest('http://localhost/api/test', { headers });
  if (opts.cookieValue) {
    Object.defineProperty(req, 'cookies', {
      value: {
        get: (name: string) =>
          name === 'cercle_session' ? { value: opts.cookieValue } : undefined,
      },
    });
  }
  return req;
}

// ─── Tests : session cookie ───────────────────────────────────────────────────

describe('verifyWalletAuth — session cookie path', () => {
  beforeEach(() => {
    jest.clearAllMocks();
  });

  it('🟢 returns success for a valid patient session cookie', async () => {
    mockVerifySession.mockResolvedValue({ walletAddress: '0xabc123' });
    mockPrismaPatientFindUnique.mockResolvedValue({ id: 1, walletAddress: '0xabc123' });
    mockPrismaResearcherFindUnique.mockResolvedValue(null);

    const { verifyWalletAuth } = await import('@/lib/auth');
    const req = makeRequest({ cookieValue: 'valid-session-token' });
    const result = await verifyWalletAuth(req);

    expect(result.success).toBe(true);
    if (result.success) {
      expect(result.user.userType).toBe('patient');
      expect(result.user.walletAddress).toBe('0xabc123');
      expect(result.user.userId).toBe(1);
    }
  });

  it('🟢 returns success for a valid researcher session cookie', async () => {
    mockVerifySession.mockResolvedValue({ walletAddress: '0xresearcher' });
    mockPrismaPatientFindUnique.mockResolvedValue(null);
    mockPrismaResearcherFindUnique.mockResolvedValue({
      id: 'uuid-1',
      walletAddress: '0xresearcher',
    });

    const { verifyWalletAuth } = await import('@/lib/auth');
    const req = makeRequest({ cookieValue: 'valid-session-token' });
    const result = await verifyWalletAuth(req);

    expect(result.success).toBe(true);
    if (result.success) {
      expect(result.user.userType).toBe('researcher');
      expect(result.user.userId).toBe('uuid-1');
    }
  });

  it('🔴 falls through to Bearer check when session cookie is invalid', async () => {
    mockVerifySession.mockResolvedValue(null);
    const { verifyWalletAuth } = await import('@/lib/auth');
    const req = makeRequest({ cookieValue: 'expired-token' });
    const result = await verifyWalletAuth(req);

    expect(result.success).toBe(false);
    if (!result.success) {
      expect(result.status).toBe(401);
    }
  });

  it('🟢 normalises wallet address to lowercase', async () => {
    mockVerifySession.mockResolvedValue({ walletAddress: '0xABC123' });
    mockPrismaPatientFindUnique.mockResolvedValue({ id: 1, walletAddress: '0xabc123' });
    mockPrismaResearcherFindUnique.mockResolvedValue(null);

    const { verifyWalletAuth } = await import('@/lib/auth');
    const req = makeRequest({ cookieValue: 'valid-token' });
    const result = await verifyWalletAuth(req);

    expect(result.success).toBe(true);
    if (result.success) {
      expect(result.user.walletAddress).toBe('0xabc123');
    }
  });
});

// ─── Tests : Bearer JWT path ──────────────────────────────────────────────────

describe('verifyWalletAuth — Bearer JWT path (inscription)', () => {
  beforeEach(() => {
    jest.clearAllMocks();
    mockVerifySession.mockResolvedValue(null);
  });

  it('🟢 returns success with valid Bearer token and wallet address', async () => {
    mockVerifyAccessToken.mockResolvedValue({ user_id: 'privy-did:xxx' });
    mockPrismaPatientFindUnique.mockResolvedValue(null);
    mockPrismaResearcherFindUnique.mockResolvedValue(null);

    const { verifyWalletAuth } = await import('@/lib/auth');
    const req = makeRequest({
      authorization: 'Bearer valid-jwt-token',
      walletAddress: '0x1234567890123456789012345678901234567890',
    });
    const result = await verifyWalletAuth(req);

    expect(result.success).toBe(true);
    expect(mockVerifyAccessToken).toHaveBeenCalledWith('valid-jwt-token');
  });

  it('🔴 returns 401 when Bearer token is invalid (PrivyClient throws)', async () => {
    mockVerifyAccessToken.mockImplementation(() => Promise.reject(new Error('Invalid token')));

    const { verifyWalletAuth } = await import('@/lib/auth');
    const req = makeRequest({
      authorization: 'Bearer invalid-token',
      walletAddress: '0x1234567890123456789012345678901234567890',
    });
    const result = await verifyWalletAuth(req);

    expect(result.success).toBe(false);
    if (!result.success) {
      expect(result.status).toBe(401);
      expect(result.code).toBe('INVALID_TOKEN');
    }
  });

  it('🔴 returns 400 when wallet address format is invalid', async () => {
    const { verifyWalletAuth } = await import('@/lib/auth');
    const req = makeRequest({
      authorization: 'Bearer some-token',
      walletAddress: 'not-a-valid-address',
    });
    const result = await verifyWalletAuth(req);

    expect(result.success).toBe(false);
    if (!result.success) {
      expect(result.status).toBe(400);
      expect(result.code).toBe('INVALID_WALLET_ADDRESS');
    }
  });

  it('🔴 returns 401 when x-wallet-address header is missing', async () => {
    const { verifyWalletAuth } = await import('@/lib/auth');
    const req = makeRequest({ authorization: 'Bearer some-token' });
    const result = await verifyWalletAuth(req);

    expect(result.success).toBe(false);
    if (!result.success) {
      expect(result.status).toBe(401);
    }
  });

  it('🔴 returns 401 with AUTH_REQUIRED when no auth provided', async () => {
    const { verifyWalletAuth } = await import('@/lib/auth');
    const req = makeRequest({});
    const result = await verifyWalletAuth(req);

    expect(result.success).toBe(false);
    if (!result.success) {
      expect(result.status).toBe(401);
      expect(result.code).toBe('AUTH_REQUIRED');
    }
  });

  it('🟢 lookupUser returns userId=0 for unregistered wallet (inscription flow)', async () => {
    mockVerifyAccessToken.mockResolvedValue({});
    mockPrismaPatientFindUnique.mockResolvedValue(null);
    mockPrismaResearcherFindUnique.mockResolvedValue(null);

    const { verifyWalletAuth } = await import('@/lib/auth');
    const req = makeRequest({
      authorization: 'Bearer valid-token',
      walletAddress: '0x1234567890123456789012345678901234567890',
    });
    const result = await verifyWalletAuth(req);

    expect(result.success).toBe(true);
    if (result.success) {
      expect(result.user.userId).toBe(0);
    }
  });
});

// ─── Tests : verifyWalletMatch ────────────────────────────────────────────────

describe('verifyWalletMatch', () => {
  it('🟢 returns true when addresses match (case-insensitive)', async () => {
    const { verifyWalletMatch } = await import('@/lib/auth');
    const user = { walletAddress: '0xabc123', userType: 'patient' as const, userId: 1 };
    expect(verifyWalletMatch(user, '0xABC123')).toBe(true);
    expect(verifyWalletMatch(user, '0xabc123')).toBe(true);
  });

  it('🔴 returns false when addresses differ', async () => {
    const { verifyWalletMatch } = await import('@/lib/auth');
    const user = { walletAddress: '0xabc123', userType: 'patient' as const, userId: 1 };
    expect(verifyWalletMatch(user, '0xdeadbeef')).toBe(false);
  });
});

// ─── Tests : verifyPatientOwnership ──────────────────────────────────────────

describe('verifyPatientOwnership', () => {
  it('🟢 grants access when patient owns the record', async () => {
    const { verifyPatientOwnership } = await import('@/lib/auth');
    const user = { walletAddress: '0xabc', userType: 'patient' as const, userId: 42 };
    const result = await verifyPatientOwnership(user, 42);
    expect(result.authorized).toBe(true);
  });

  it('🔴 denies when patient userId does not match patientId', async () => {
    const { verifyPatientOwnership } = await import('@/lib/auth');
    const user = { walletAddress: '0xabc', userType: 'patient' as const, userId: 1 };
    const result = await verifyPatientOwnership(user, 99);
    expect(result.authorized).toBe(false);
  });

  it('🔴 denies when user is a researcher', async () => {
    const { verifyPatientOwnership } = await import('@/lib/auth');
    const user = { walletAddress: '0xabc', userType: 'researcher' as const, userId: 'uuid' };
    const result = await verifyPatientOwnership(user, 1);
    expect(result.authorized).toBe(false);
  });
});

// ─── Tests : verifyResearcherOwnership ───────────────────────────────────────

describe('verifyResearcherOwnership', () => {
  it('🟢 grants access when researcher owns the record', async () => {
    const { verifyResearcherOwnership } = await import('@/lib/auth');
    const user = { walletAddress: '0xabc', userType: 'researcher' as const, userId: 'uuid-1' };
    const result = await verifyResearcherOwnership(user, 'uuid-1');
    expect(result.authorized).toBe(true);
  });

  it('🔴 denies when researcher userId does not match', async () => {
    const { verifyResearcherOwnership } = await import('@/lib/auth');
    const user = { walletAddress: '0xabc', userType: 'researcher' as const, userId: 'uuid-1' };
    const result = await verifyResearcherOwnership(user, 'uuid-other');
    expect(result.authorized).toBe(false);
  });

  it('🔴 denies when user is a patient', async () => {
    const { verifyResearcherOwnership } = await import('@/lib/auth');
    const user = { walletAddress: '0xabc', userType: 'patient' as const, userId: 1 };
    const result = await verifyResearcherOwnership(user, 'uuid-1');
    expect(result.authorized).toBe(false);
  });
});

// ─── Tests : response helpers ─────────────────────────────────────────────────

describe('unauthorizedResponse / forbiddenResponse', () => {
  it('🟢 unauthorizedResponse returns 401 JSON with code', async () => {
    const { unauthorizedResponse } = await import('@/lib/auth');
    const res = unauthorizedResponse('Not allowed', 'AUTH_REQUIRED');
    expect(res.status).toBe(401);
    const body = await res.json();
    expect(body.code).toBe('AUTH_REQUIRED');
  });

  it('🟢 forbiddenResponse returns 403 JSON with code', async () => {
    const { forbiddenResponse } = await import('@/lib/auth');
    const res = forbiddenResponse('Forbidden', 'ACCESS_DENIED');
    expect(res.status).toBe(403);
    const body = await res.json();
    expect(body.code).toBe('ACCESS_DENIED');
  });
});
