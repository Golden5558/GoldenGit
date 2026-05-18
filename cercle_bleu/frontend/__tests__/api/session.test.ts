/**
 * @jest-environment node
 *
 * TDD — app/api/auth/session/route.ts
 *
 * Tests des endpoints POST (création de session) et DELETE (logout).
 */

import { describe, it, expect, beforeEach, jest } from '@jest/globals';
import { NextRequest } from 'next/server';

// ─── Mocks ────────────────────────────────────────────────────────────────────

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

const mockPrismaPatientFindUnique = jest.fn<(query: unknown) => Promise<unknown>>();
const mockPrismaResearcherFindUnique = jest.fn<(query: unknown) => Promise<unknown>>();
jest.mock('@/lib/prisma', () => ({
  prisma: {
    patient: {
      findUnique: (...args: Array<unknown>) => mockPrismaPatientFindUnique(...args as [unknown]),
    },
    researcher: {
      findUnique: (...args: Array<unknown>) => mockPrismaResearcherFindUnique(...args as [unknown]),
    },
  },
}));

const mockCreateSession = jest.fn<(wallet: string, type: string) => Promise<unknown>>();
const mockDeleteSession = jest.fn<() => Promise<unknown>>();
jest.mock('@/lib/session', () => ({
  createSession: (...args: Array<unknown>) => mockCreateSession(...args as [string, string]),
  deleteSession: (...args: Array<unknown>) => mockDeleteSession(...args as []),
}));

// ─── Helpers ──────────────────────────────────────────────────────────────────

function makePostRequest(body: Record<string, unknown>): NextRequest {
  return new NextRequest('http://localhost/api/auth/session', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(body),
  });
}

// ─── POST /api/auth/session ───────────────────────────────────────────────────

describe('POST /api/auth/session', () => {
  beforeEach(() => {
    jest.clearAllMocks();
  });

  it('🔴 returns 400 when privyToken is missing', async () => {
    const { POST } = await import('@/app/api/auth/session/route');
    const req = makePostRequest({ walletAddress: '0x1234567890123456789012345678901234567890' });
    const res = await POST(req);
    const body = await res.json();

    expect(res.status).toBe(400);
    expect(body.code).toBe('MISSING_FIELDS');
  });

  it('🔴 returns 400 when walletAddress is missing', async () => {
    const { POST } = await import('@/app/api/auth/session/route');
    const req = makePostRequest({ privyToken: 'some-token' });
    const res = await POST(req);
    const body = await res.json();

    expect(res.status).toBe(400);
    expect(body.code).toBe('MISSING_FIELDS');
  });

  it('🔴 returns 400 when walletAddress format is invalid', async () => {
    const { POST } = await import('@/app/api/auth/session/route');
    const req = makePostRequest({ privyToken: 'some-token', walletAddress: 'not-valid' });
    const res = await POST(req);
    const body = await res.json();

    expect(res.status).toBe(400);
    expect(body.code).toBe('INVALID_WALLET_ADDRESS');
  });

  it('🔴 returns 401 when Privy token verification fails', async () => {
    mockVerifyAccessToken.mockRejectedValue(new Error('Token expired'));

    const { POST } = await import('@/app/api/auth/session/route');
    const req = makePostRequest({
      privyToken: 'expired-token',
      walletAddress: '0x1234567890123456789012345678901234567890',
    });
    const res = await POST(req);
    const body = await res.json();

    expect(res.status).toBe(401);
    expect(body.code).toBe('INVALID_TOKEN');
  });

  it('🔴 returns 404 when user is not registered (new user flow)', async () => {
    mockVerifyAccessToken.mockResolvedValue({ user_id: 'privy:xxx' });
    mockPrismaPatientFindUnique.mockResolvedValue(null);
    mockPrismaResearcherFindUnique.mockResolvedValue(null);

    const { POST } = await import('@/app/api/auth/session/route');
    const req = makePostRequest({
      privyToken: 'valid-token',
      walletAddress: '0x1234567890123456789012345678901234567890',
    });
    const res = await POST(req);
    const body = await res.json();

    expect(res.status).toBe(404);
    expect(body.code).toBe('USER_NOT_FOUND');
  });

  it('🟢 creates session and returns patient userType for registered patient', async () => {
    mockVerifyAccessToken.mockResolvedValue({ user_id: 'privy:patient' });
    mockPrismaPatientFindUnique.mockResolvedValue({
      id: 1,
      walletAddress: '0x1234567890123456789012345678901234567890',
    });
    mockCreateSession.mockResolvedValue(undefined);

    const { POST } = await import('@/app/api/auth/session/route');
    const req = makePostRequest({
      privyToken: 'valid-token',
      walletAddress: '0x1234567890123456789012345678901234567890',
    });
    const res = await POST(req);
    const body = await res.json();

    expect(res.status).toBe(200);
    expect(body.success).toBe(true);
    expect(body.userType).toBe('patient');
    expect(mockCreateSession).toHaveBeenCalledWith(
      '0x1234567890123456789012345678901234567890',
      'patient'
    );
  });

  it('🟢 creates session and returns researcher userType for registered researcher', async () => {
    mockVerifyAccessToken.mockResolvedValue({ user_id: 'privy:researcher' });
    mockPrismaPatientFindUnique.mockResolvedValue(null);
    mockPrismaResearcherFindUnique.mockResolvedValue({
      id: 'uuid-1',
      walletAddress: '0x1234567890123456789012345678901234567890',
    });
    mockCreateSession.mockResolvedValue(undefined);

    const { POST } = await import('@/app/api/auth/session/route');
    const req = makePostRequest({
      privyToken: 'valid-token',
      walletAddress: '0x1234567890123456789012345678901234567890',
    });
    const res = await POST(req);
    const body = await res.json();

    expect(res.status).toBe(200);
    expect(body.userType).toBe('researcher');
    expect(mockCreateSession).toHaveBeenCalledWith(
      '0x1234567890123456789012345678901234567890',
      'researcher'
    );
  });

  it('🟢 normalises wallet address to lowercase before DB lookup', async () => {
    mockVerifyAccessToken.mockResolvedValue({});
    mockPrismaPatientFindUnique.mockResolvedValue({ id: 1, walletAddress: '0xabcdef' });
    mockCreateSession.mockResolvedValue(undefined);

    const { POST } = await import('@/app/api/auth/session/route');
    const req = makePostRequest({
      privyToken: 'valid-token',
      walletAddress: '0xABCDEF0000000000000000000000000000000000',
    });
    await POST(req);

    expect(mockPrismaPatientFindUnique).toHaveBeenCalledWith({
      where: { walletAddress: '0xabcdef0000000000000000000000000000000000' },
    });
  });

  it('🟢 verifies the Privy token via PrivyClient (not raw JWKS fetch)', async () => {
    mockVerifyAccessToken.mockResolvedValue({});
    mockPrismaPatientFindUnique.mockResolvedValue({ id: 1, walletAddress: '0xtest' });
    mockCreateSession.mockResolvedValue(undefined);

    const { POST } = await import('@/app/api/auth/session/route');
    const req = makePostRequest({
      privyToken: 'the-privy-token',
      walletAddress: '0x1234567890123456789012345678901234567890',
    });
    await POST(req);

    expect(mockVerifyAccessToken).toHaveBeenCalledWith('the-privy-token');
  });
});

// ─── DELETE /api/auth/session ─────────────────────────────────────────────────

describe('DELETE /api/auth/session', () => {
  beforeEach(() => {
    jest.clearAllMocks();
  });

  it('🟢 returns 200 and calls deleteSession', async () => {
    mockDeleteSession.mockResolvedValue(undefined);

    const { DELETE } = await import('@/app/api/auth/session/route');
    const res = await DELETE();
    const body = await res.json();

    expect(res.status).toBe(200);
    expect(body.success).toBe(true);
    expect(mockDeleteSession).toHaveBeenCalledTimes(1);
  });

  it('🔴 returns 500 if deleteSession throws', async () => {
    mockDeleteSession.mockRejectedValue(new Error('Cookie error'));

    const { DELETE } = await import('@/app/api/auth/session/route');
    const res = await DELETE();
    const body = await res.json();

    expect(res.status).toBe(500);
    expect(body.code).toBe('DELETE_FAILED');
  });
});
