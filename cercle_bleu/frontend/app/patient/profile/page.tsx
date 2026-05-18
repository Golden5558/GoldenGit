'use client';

import { useRouter } from 'next/navigation';
import { useEffect, useState } from 'react';
import PatientRegistration from '@/components/patient/PatientRegistration';
import { useAuthContext } from '@/contexts/AuthContext';

export default function PatientProfilePage() {
  const router = useRouter();
  const { isAuthenticated, isAuthenticating, userType, userData, isLoadingUser, refreshUserData } = useAuthContext();
  const [isRedirecting, setIsRedirecting] = useState(false);

  useEffect(() => {
    if (!isAuthenticating && !isAuthenticated) {
      router.push('/login');
    }
  }, [isAuthenticating, isAuthenticated, router]);

  // Check if patient is already registered
  useEffect(() => {
    if (isLoadingUser) return;

    if (userType === 'patient' && userData) {
      router.push('/patient/dashboard');
      return;
    }

    if (userType === 'researcher') {
      router.push('/researcher/dashboard');
      return;
    }
  }, [router, userType, userData, isLoadingUser]);

  // Handle successful registration
  const handleRegistrationSuccess = async () => {
    setIsRedirecting(true);

    // Force refresh the user data cache
    await refreshUserData(true);

    // Redirect to dashboard
    setTimeout(() => {
      router.push('/patient/dashboard');
    }, 500);
  };

  // Show loader while checking registration status or redirecting
  if (isLoadingUser || isRedirecting) {
    return (
      <div className="min-h-screen bg-gray-50 py-12">
        <div className="max-w-2xl mx-auto px-4">
          <div className="bg-white rounded-lg shadow-md p-8">
            <div className="flex items-center justify-center py-8">
              <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-blue-600"></div>
              <span className="ml-2 text-gray-600">
                {isRedirecting ? 'Finalisation de l\'enregistrement...' : 'Vérification du profil...'}
              </span>
            </div>
          </div>
        </div>
      </div>
    );
  }

  return (
    <div className="min-h-screen bg-gray-50 py-12">
      <div className="max-w-2xl mx-auto px-4">
        <div className="bg-white rounded-lg shadow-md p-8">
          <div className="text-center mb-8">
            <h1 className="text-3xl font-bold text-gray-900">Enregistrement Patient</h1>
            <p className="text-gray-600 mt-2">
              Créez votre profil patient pour accéder à la plateforme
            </p>
            <div className="mt-4 p-3 bg-blue-50 rounded-md">
              <p className="text-sm text-blue-800">
                📋 Complétez votre profil pour accéder à l&apos;espace patient
              </p>
            </div>
          </div>

          <PatientRegistration onRegistrationSuccess={handleRegistrationSuccess} />
        </div>
      </div>
    </div>
  );
}
