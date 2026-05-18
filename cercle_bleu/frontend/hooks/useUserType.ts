'use client';

import { useAuthContext, UserData } from '@/contexts/AuthContext';

export type UserType = 'patient' | 'researcher' | 'unknown' | null;

export type { UserData };

export interface UserTypeResult {
  userType: UserType;
  isLoading: boolean;
  error: string | null;
  userData: UserData | null;
  refetch: () => void;
}

export function useUserType(): UserTypeResult {
  const {
    userType,
    userData,
    isLoadingUser,
    userError,
    refreshUserData,
    isAuthenticating
  } = useAuthContext();

  return {
    userType,
    isLoading: isLoadingUser || isAuthenticating,
    error: userError,
    userData,
    refetch: refreshUserData
  };
}
