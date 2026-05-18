/**
 * TDD — lib/privyClient.ts
 *
 * Tests du singleton PrivyClient utilisé pour vérifier les JWT Privy côté serveur.
 */

import { describe, it, expect, beforeEach, afterEach, jest } from '@jest/globals';

// Mock @privy-io/node avant tout import du module testé
jest.mock('@privy-io/node', () => ({
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  PrivyClient: (jest.fn() as any).mockImplementation((opts: { appId: string; appSecret: string }) => ({
    _appId: opts.appId,
    utils: jest.fn().mockReturnValue({
      auth: jest.fn().mockReturnValue({
        verifyAccessToken: jest.fn(),
      }),
    }),
  })),
}));

describe('getPrivyClient — singleton PrivyClient', () => {
  const originalEnv = process.env;

  beforeEach(() => {
    jest.resetModules();
    process.env = { ...originalEnv };
  });

  afterEach(() => {
    process.env = originalEnv;
  });

  it('🔴 throws when NEXT_PUBLIC_PRIVY_APP_ID is not set', async () => {
    delete process.env.NEXT_PUBLIC_PRIVY_APP_ID;
    process.env.PRIVY_APP_SECRET = 'test-secret';

    const { getPrivyClient } = await import('@/lib/privyClient');
    expect(() => getPrivyClient()).toThrow('NEXT_PUBLIC_PRIVY_APP_ID is not set');
  });

  it('🔴 throws when PRIVY_APP_SECRET is not set', async () => {
    process.env.NEXT_PUBLIC_PRIVY_APP_ID = 'test-app-id';
    delete process.env.PRIVY_APP_SECRET;

    const { getPrivyClient } = await import('@/lib/privyClient');
    expect(() => getPrivyClient()).toThrow('PRIVY_APP_SECRET is not set');
  });

  it('🟢 returns a PrivyClient instance when env vars are set', async () => {
    process.env.NEXT_PUBLIC_PRIVY_APP_ID = 'test-app-id';
    process.env.PRIVY_APP_SECRET = 'test-secret';

    const { getPrivyClient } = await import('@/lib/privyClient');
    const client = getPrivyClient();

    expect(client).toBeDefined();
    expect(client).toHaveProperty('utils');
  });

  it('🟢 returns the same singleton instance on multiple calls', async () => {
    process.env.NEXT_PUBLIC_PRIVY_APP_ID = 'test-app-id';
    process.env.PRIVY_APP_SECRET = 'test-secret';

    const { getPrivyClient } = await import('@/lib/privyClient');
    const client1 = getPrivyClient();
    const client2 = getPrivyClient();

    expect(client1).toBe(client2);
  });

  it('🟢 initialises PrivyClient with correct appId and appSecret', async () => {
    process.env.NEXT_PUBLIC_PRIVY_APP_ID = 'my-app-id';
    process.env.PRIVY_APP_SECRET = 'my-secret';

    const { PrivyClient } = await import('@privy-io/node');
    const { getPrivyClient } = await import('@/lib/privyClient');
    getPrivyClient();

    expect(PrivyClient).toHaveBeenCalledWith({
      appId: 'my-app-id',
      appSecret: 'my-secret',
    });
  });
});
