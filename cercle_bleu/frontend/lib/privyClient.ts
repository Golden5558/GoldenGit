import { PrivyClient } from '@privy-io/node';

let _client: PrivyClient | null = null;

export function getPrivyClient(): PrivyClient {
  if (!_client) {
    const appId = process.env.NEXT_PUBLIC_PRIVY_APP_ID;
    const appSecret = process.env.PRIVY_APP_SECRET;
    if (!appId) throw new Error('NEXT_PUBLIC_PRIVY_APP_ID is not set');
    if (!appSecret) throw new Error('PRIVY_APP_SECRET is not set');
    _client = new PrivyClient({ appId, appSecret });
  }
  return _client;
}
