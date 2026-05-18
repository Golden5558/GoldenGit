const STORAGE_KEY = 'pendingRole';

// Module-level functions so they're stable references (safe to call in useEffect deps)
export const setRoleIntent = (role: 'patient' | 'researcher') =>
  localStorage.setItem(STORAGE_KEY, role);

export const getRoleIntent = (): 'patient' | 'researcher' | null =>
  localStorage.getItem(STORAGE_KEY) as 'patient' | 'researcher' | null;

export const clearRoleIntent = () => localStorage.removeItem(STORAGE_KEY);

export function useRoleIntent() {
  return { setRoleIntent, getRoleIntent, clearRoleIntent };
}
