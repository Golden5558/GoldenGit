'use client';

import { useAuthContext, AuthHeaders } from '@/contexts/AuthContext';

export type { AuthHeaders };

export interface AuthResult {
  isAuthenticated: boolean;
  isAuthenticating: boolean;
  error: string | null;
  authenticate: () => Promise<AuthHeaders | null>;
  getAuthHeaders: () => AuthHeaders | null;
  authenticatedFetch: (url: string, options?: RequestInit) => Promise<Response>;
  clearAuth: () => void;
}

export function useAuth(): AuthResult {
  const {
    isAuthenticated,
    isAuthenticating,
    authError,
    authenticate,
    authenticatedFetch,
    clearAuth
  } = useAuthContext();

  // getAuthHeaders is not needed with context, but kept for compatibility
  const getAuthHeaders = (): AuthHeaders | null => {
    return null; // Auth headers are managed internally by authenticatedFetch
  };

  return {
    isAuthenticated,
    isAuthenticating,
    error: authError,
    authenticate,
    getAuthHeaders,
    authenticatedFetch,
    clearAuth
  };
}
