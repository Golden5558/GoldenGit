'use client';

import { useState } from 'react';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { toast } from 'sonner';
import { useAuth } from '@/hooks/useAuth';

interface PatientRegistrationProps {
  onRegistrationSuccess: () => void;
}

interface PatientFormData {
  firstName: string;
  lastName: string;
  birthYear: number;
}

export default function PatientRegistration({ onRegistrationSuccess }: PatientRegistrationProps) {
  const { authenticatedFetch, isAuthenticating } = useAuth();
  const [isLoading, setIsLoading] = useState(false);

  const [formData, setFormData] = useState<PatientFormData>({
    firstName: '',
    lastName: '',
    birthYear: 0,
  });

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();

    if (!formData.firstName || !formData.lastName || !formData.birthYear) {
      toast.error('Tous les champs sont obligatoires');
      return;
    }

    setIsLoading(true);

    try {
      const response = await authenticatedFetch('/api/patient/register', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(formData),
      });

      if (response.ok) {
        toast.success('Profil enregistré avec succès!');
        onRegistrationSuccess();
      } else {
        const errorData = await response.json();
        toast.error(errorData.error || 'Erreur lors de l\'enregistrement');
        setIsLoading(false);
      }
    } catch (error) {
      console.error('Erreur lors de l\'enregistrement:', error);
      toast.error('Erreur lors de l\'enregistrement');
      setIsLoading(false);
    }
  };

  return (
    <div className="space-y-6 max-w-md mx-auto">
      <div className="text-center">
        <h2 className="text-2xl font-bold">Profil Patient</h2>
      </div>

      <form onSubmit={handleSubmit} className="space-y-4">
        <div>
          <Label htmlFor="firstName">Prénom *</Label>
          <Input
            id="firstName"
            value={formData.firstName}
            onChange={(e) => setFormData({ ...formData, firstName: e.target.value })}
            required
          />
        </div>

        <div>
          <Label htmlFor="lastName">Nom *</Label>
          <Input
            id="lastName"
            value={formData.lastName}
            onChange={(e) => setFormData({ ...formData, lastName: e.target.value })}
            required
          />
        </div>

        <div>
          <Label htmlFor="birthYear">Année de naissance *</Label>
          <Input
            id="birthYear"
            type="number"
            min="1900"
            max={new Date().getFullYear()}
            value={formData.birthYear || ''}
            onChange={(e) => setFormData({ ...formData, birthYear: e.target.value ? parseInt(e.target.value) : 0 })}
            required
          />
        </div>

        <Button type="submit" disabled={isLoading || isAuthenticating} className="w-full">
          {isLoading || isAuthenticating ? (
            <>
              <div className="animate-spin rounded-full h-4 w-4 border-b-2 border-white mr-2"></div>
              Enregistrement en cours...
            </>
          ) : (
            'Finaliser l\'enregistrement'
          )}
        </Button>
      </form>
    </div>
  );
}
