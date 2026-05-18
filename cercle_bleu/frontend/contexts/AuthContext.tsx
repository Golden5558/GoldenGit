'use client';

import { createContext, useContext, useState, useCallback, useRef, useEffect, ReactNode } from 'react';
import { useSession, signOut as nextAuthSignOut } from 'next-auth/react';

export interface AuthHeaders {
  'x-user-email': string;
}

export interface UserData {
  id: number | string;
  email: string;
  firstName: string;
  lastName: string;
  institution?: string;
  createdAt: string;
  // Patient specific
  birthYear?: number;
  weightKg?: number;
  sex?: string;
  diabeteType?: string;
  datasetReferences?: unknown[];
  // Researcher specific
  createdStudies?: unknown[];
}

export type UserType = 'patient' | 'researcher' | 'unknown' | null;

interface AuthContextType {
  isAuthenticated: boolean;
  isAuthenticating: boolean;
  authError: string | null;
  authenticate: () => Promise<AuthHeaders | null>;
  authenticatedFetch: (url: string, options?: RequestInit) => Promise<Response>;
  clearAuth: () => void;
  logout: () => Promise<void>;
  userType: UserType;
  userData: UserData | null;
  isLoadingUser: boolean;
  userError: string | null;
  refreshUserData: (forceRefresh?: boolean) => Promise<void>;
  // NextAuth session user info
  sessionEmail: string | null;
  sessionName: string | null;
}

const AuthContext = createContext<AuthContextType | null>(null);

const USER_DATA_CACHE_DURATION = 5 * 60 * 1000;

export function AuthProvider({ children }: { children: ReactNode }) {
  const { data: session, status } = useSession();

  const isAuthenticated = status === 'authenticated';
  const isAuthenticating = status === 'loading';
  const sessionEmail = session?.user?.email ?? null;
  const sessionName = session?.user?.name ?? null;

  const [authError, setAuthError] = useState<string | null>(null);
  const [userType, setUserType] = useState<UserType>(null);
  const [userData, setUserData] = useState<UserData | null>(null);
  const [isLoadingUser, setIsLoadingUser] = useState(false);
  const [userError, setUserError] = useState<string | null>(null);
  const userDataTimestampRef = useRef<number>(0);
  const dataVersionRef = useRef<number>(0);

  // authenticate() - kept for interface compatibility
  const authenticate = useCallback(async (): Promise<AuthHeaders | null> => {
    if (!isAuthenticated || !sessionEmail) {
      setAuthError('Not authenticated');
      return null;
    }
    return { 'x-user-email': sessionEmail };
  }, [isAuthenticated, sessionEmail]);

  // authenticatedFetch — NextAuth session cookie is sent automatically by the browser
  const authenticatedFetch = useCallback(
    async (url: string, options: RequestInit = {}): Promise<Response> => {
      if (!isAuthenticated) {
        throw new Error('Authentication failed');
      }
      const headers = new Headers(options.headers);
      if (['POST', 'PUT', 'PATCH'].includes(options.method?.toUpperCase() ?? '')) {
        if (!headers.has('Content-Type')) {
          headers.set('Content-Type', 'application/json');
        }
      }
      return fetch(url, { ...options, headers, credentials: 'include' });
    },
    [isAuthenticated]
  );

  const clearAuth = useCallback(() => {
    dataVersionRef.current++;
    setAuthError(null);
    setUserType(null);
    setUserData(null);
    setUserError(null);
    userDataTimestampRef.current = 0;
  }, []);

  const logout = useCallback(async () => {
    clearAuth();
    await nextAuthSignOut({ callbackUrl: '/' });
  }, [clearAuth]);

  const isUserDataValid = useCallback(() => {
    if (!userData) return false;
    return Date.now() - userDataTimestampRef.current < USER_DATA_CACHE_DURATION;
  }, [userData]);

  const refreshUserData = useCallback(async (forceRefresh = false) => {
    if (!isAuthenticated || !sessionEmail) {
      setUserType(null);
      setUserData(null);
      return;
    }

    if (!forceRefresh && isUserDataValid()) return;
    if (forceRefresh) userDataTimestampRef.current = 0;

    const version = dataVersionRef.current;
    setIsLoadingUser(true);
    setUserError(null);

    try {
      // Look up patient by email
      const patientResponse = await authenticatedFetch(`/api/patient/by-email?email=${encodeURIComponent(sessionEmail)}`);
      const patientData = await patientResponse.json();

      if (dataVersionRef.current !== version) return;

      if (patientResponse.ok && patientData.success) {
        setUserType('patient');
        setUserData(patientData.patient);
        userDataTimestampRef.current = Date.now();
        setIsLoadingUser(false);
        return;
      }

      // Look up researcher by email
      const researcherResponse = await authenticatedFetch(`/api/researcher/by-email?email=${encodeURIComponent(sessionEmail)}`);
      const researcherData = await researcherResponse.json();

      if (dataVersionRef.current !== version) return;

      if (researcherResponse.ok && researcherData.success) {
        setUserType('researcher');
        setUserData(researcherData.researcher);
        userDataTimestampRef.current = Date.now();
        setIsLoadingUser(false);
        return;
      }

      setUserType('unknown');
      setUserData(null);
    } catch (err) {
      if (dataVersionRef.current !== version) return;
      console.error('Error fetching user data:', err);
      setUserError(err instanceof Error ? err.message : 'Error fetching user data');
      setUserType('unknown');
    } finally {
      if (dataVersionRef.current === version) {
        setIsLoadingUser(false);
      }
    }
  }, [isAuthenticated, sessionEmail, authenticatedFetch, isUserDataValid]);

  // Load user data when session becomes available
  useEffect(() => {
    if (isAuthenticated && sessionEmail) {
      refreshUserData();
    } else if (status === 'unauthenticated') {
      dataVersionRef.current++;
      setUserType(null);
      setUserData(null);
      userDataTimestampRef.current = 0;
    }
  // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [isAuthenticated, sessionEmail, status]);

  return (
    <AuthContext.Provider
      value={{
        isAuthenticated,
        isAuthenticating,
        authError,
        authenticate,
        authenticatedFetch,
        clearAuth,
        logout,
        userType,
        userData,
        isLoadingUser,
        userError,
        refreshUserData,
        sessionEmail,
        sessionName,
      }}
    >
      {children}
    </AuthContext.Provider>
  );
}

export function useAuthContext() {
  const context = useContext(AuthContext);
  if (!context) {
    throw new Error('useAuthContext must be used within an AuthProvider');
  }
  return context;
}
