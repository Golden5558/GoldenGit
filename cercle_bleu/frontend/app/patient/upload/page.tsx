'use client';

import { useRouter } from 'next/navigation';
import { useEffect } from 'react';
import MeasurementUpload from '@/components/patient/MeasurementUpload';
import { useAuthContext } from '@/contexts/AuthContext';

export default function UploadPage() {
  const { isAuthenticated, isAuthenticating } = useAuthContext();
  const router = useRouter();

  useEffect(() => {
    if (!isAuthenticating && !isAuthenticated) {
      router.push('/login');
    }
  }, [isAuthenticating, isAuthenticated, router]);

  if (isAuthenticating || !isAuthenticated) {
    return null;
  }

  return (
    <div className="container mx-auto py-6">
      <MeasurementUpload />
    </div>
  );
}
