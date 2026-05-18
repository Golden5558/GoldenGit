'use client';

import { useRouter } from 'next/navigation';
import { useEffect, useState } from 'react';
import PatientFormFields, { PatientFormData } from '@/components/patient/PatientFormFields';
import { toast } from 'sonner';
import { Button } from '@/components/ui/button';
import {
  AlertDialog,
  AlertDialogAction,
  AlertDialogCancel,
  AlertDialogContent,
  AlertDialogDescription,
  AlertDialogFooter,
  AlertDialogHeader,
  AlertDialogTitle,
} from '@/components/ui/alert-dialog';
import { useAuthContext } from '@/contexts/AuthContext';

export default function EditProfilePage() {
  const router = useRouter();
  const { userData, authenticatedFetch } = useAuthContext();
  const [isLoading, setIsLoading] = useState(true);
  const [isSubmitting, setIsSubmitting] = useState(false);
  const [showConfirmDialog, setShowConfirmDialog] = useState(false);
  const [formData, setFormData] = useState<PatientFormData>({
    firstName: '',
    lastName: '',
    email: '',
    birthYear: 0,
  });

  useEffect(() => {
    if (!userData) return;
    const patient = userData as { firstName?: string; lastName?: string; email?: string; birthYear?: number; weightKg?: number; sex?: string; diabeteType?: string };
    setFormData({
      firstName: patient.firstName || '',
      lastName: patient.lastName || '',
      email: patient.email || '',
      birthYear: patient.birthYear || 0,
      weightKg: patient.weightKg,
      sex: patient.sex || '',
      diabeteType: patient.diabeteType || '',
    });
    setIsLoading(false);
  }, [userData]);

  const handleFormSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    if (!formData.firstName || !formData.lastName || !formData.birthYear) {
      toast.error('Prénom, nom et année de naissance sont obligatoires');
      return;
    }
    setShowConfirmDialog(true);
  };

  const handleConfirmUpdate = async () => {
    const patient = userData as { id?: number } | null;
    if (!patient?.id) {
      toast.error('Informations patient manquantes');
      return;
    }

    setIsSubmitting(true);
    setShowConfirmDialog(false);

    try {
      const response = await authenticatedFetch(`/api/patient/${patient.id}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(formData),
      });

      if (response.ok) {
        toast.success('Profil mis à jour avec succès!');
        setTimeout(() => router.push('/patient/dashboard'), 1500);
      } else {
        const errorData = await response.json();
        toast.error(errorData.error || 'Erreur lors de la mise à jour');
      }
    } catch (error) {
      console.error('Erreur lors de la mise à jour:', error);
      toast.error('Erreur lors de la mise à jour');
    } finally {
      setIsSubmitting(false);
    }
  };

  if (isLoading) {
    return (
      <div className="min-h-screen bg-gray-50 py-12">
        <div className="max-w-2xl mx-auto px-4">
          <div className="bg-white rounded-lg shadow-md p-8">
            <div className="flex items-center justify-center py-8">
              <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-blue-600"></div>
              <span className="ml-2 text-gray-600">Chargement du profil...</span>
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
            <h1 className="text-3xl font-bold text-gray-900">Modifier mon profil</h1>
            <p className="text-gray-600 mt-2">Mettez à jour vos informations personnelles</p>
          </div>

          <PatientFormFields
            formData={formData}
            onFormDataChange={setFormData}
            onSubmit={handleFormSubmit}
            isLoading={isSubmitting}
            submitButtonText="Mettre à jour le profil"
            showBlockchainId={false}
          />

          <div className="mt-4 text-center">
            <Button variant="outline" onClick={() => router.push('/patient/dashboard')} disabled={isSubmitting}>
              Annuler
            </Button>
          </div>

          <AlertDialog open={showConfirmDialog} onOpenChange={setShowConfirmDialog}>
            <AlertDialogContent>
              <AlertDialogHeader>
                <AlertDialogTitle>Confirmer la modification</AlertDialogTitle>
                <AlertDialogDescription>
                  Êtes-vous sûr de vouloir modifier vos informations personnelles ?
                </AlertDialogDescription>
              </AlertDialogHeader>
              <AlertDialogFooter>
                <AlertDialogCancel onClick={() => setShowConfirmDialog(false)}>Annuler</AlertDialogCancel>
                <AlertDialogAction onClick={handleConfirmUpdate} disabled={isSubmitting}>
                  {isSubmitting ? 'Mise à jour...' : 'Confirmer'}
                </AlertDialogAction>
              </AlertDialogFooter>
            </AlertDialogContent>
          </AlertDialog>
        </div>
      </div>
    </div>
  );
}
