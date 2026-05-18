'use client';

import { useState } from 'react';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from '@/components/ui/card';
import { UserPlus, Building, User } from 'lucide-react';
import { toast } from 'sonner';
import { useAuth } from '@/hooks/useAuth';
import RegistrationStepper from '@/components/shared/RegistrationStepper';

interface ResearcherRegistrationProps {
  onRegistrationSuccess: () => void;
}

interface ResearcherFormData {
  firstName: string;
  lastName: string;
  institution: string;
}

const STEPS = [
  { label: 'Connexion' },
  { label: 'Profil chercheur' },
];

export default function ResearcherRegistration({ onRegistrationSuccess }: ResearcherRegistrationProps) {
  const { authenticatedFetch, isAuthenticating } = useAuth();
  const [isRegistering, setIsRegistering] = useState(false);

  const [formData, setFormData] = useState<ResearcherFormData>({
    firstName: '',
    lastName: '',
    institution: '',
  });

  const handleInputChange = (field: keyof ResearcherFormData, value: string) => {
    setFormData(prev => ({ ...prev, [field]: value }));
  };

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();

    if (!formData.firstName.trim() || !formData.lastName.trim()) {
      toast.error('Le prénom et le nom sont obligatoires');
      return;
    }

    try {
      setIsRegistering(true);

      const payload = {
        firstName: formData.firstName.trim(),
        lastName: formData.lastName.trim(),
        institution: formData.institution.trim() || undefined,
      };

      const response = await authenticatedFetch('/api/researcher/register', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(payload)
      });

      const data = await response.json();

      if (data.success) {
        toast.success('Enregistrement réussi ! Bienvenue dans l\'espace chercheur.');
        onRegistrationSuccess();
      } else {
        toast.error(data.error || 'Erreur lors de l\'enregistrement');
      }
    } catch (error) {
      console.error('Erreur lors de l\'enregistrement:', error);
      toast.error('Erreur lors de l\'enregistrement');
    } finally {
      setIsRegistering(false);
    }
  };

  return (
    <div className="max-w-2xl mx-auto p-6">
      <RegistrationStepper steps={STEPS} currentStep={1} />

      <Card>
        <CardHeader>
          <CardTitle className="flex items-center space-x-2">
            <UserPlus className="w-6 h-6" />
            <span>Profil Chercheur</span>
          </CardTitle>
          <CardDescription>
            Complétez votre profil pour accéder à l&apos;espace chercheur.
          </CardDescription>
        </CardHeader>
        <CardContent className="space-y-6">
          <form onSubmit={handleSubmit} className="space-y-6">
            {/* Informations personnelles */}
            <div className="grid md:grid-cols-2 gap-4">
              <div>
                <Label htmlFor="firstName">Prénom *</Label>
                <div className="relative">
                  <User className="absolute left-3 top-3 h-4 w-4 text-gray-400" />
                  <Input
                    id="firstName"
                    type="text"
                    value={formData.firstName}
                    onChange={(e) => handleInputChange('firstName', e.target.value)}
                    placeholder="Votre prénom"
                    className="pl-10"
                    maxLength={100}
                    required
                  />
                </div>
              </div>

              <div>
                <Label htmlFor="lastName">Nom *</Label>
                <div className="relative">
                  <User className="absolute left-3 top-3 h-4 w-4 text-gray-400" />
                  <Input
                    id="lastName"
                    type="text"
                    value={formData.lastName}
                    onChange={(e) => handleInputChange('lastName', e.target.value)}
                    placeholder="Votre nom"
                    className="pl-10"
                    maxLength={100}
                    required
                  />
                </div>
              </div>
            </div>

            {/* Institution */}
            <div>
              <Label htmlFor="institution">Institution</Label>
              <div className="relative">
                <Building className="absolute left-3 top-3 h-4 w-4 text-gray-400" />
                <Input
                  id="institution"
                  type="text"
                  value={formData.institution}
                  onChange={(e) => handleInputChange('institution', e.target.value)}
                  placeholder="Université, hôpital, laboratoire..."
                  className="pl-10"
                  maxLength={255}
                />
              </div>
              <p className="mt-1 text-xs text-gray-500">
                Affiché aux patients lors de leurs demandes de consentement — renforce la confiance et la transparence.
              </p>
            </div>

            {/* Informations automatiques */}
            <div className="bg-gray-50 p-4 rounded-md">
              <h3 className="text-sm font-medium text-gray-700 mb-2">Informations automatiques</h3>
              <ul className="text-sm text-gray-600 space-y-1">
                <li>• <strong>Date d&apos;enregistrement :</strong> Sera automatiquement définie</li>
                <li>• <strong>ID unique :</strong> Sera généré automatiquement</li>
              </ul>
            </div>

            <Button type="submit" disabled={isRegistering || isAuthenticating} className="w-full">
              {isRegistering || isAuthenticating ? (
                <div className="flex items-center space-x-2">
                  <div className="animate-spin rounded-full h-4 w-4 border-b-2 border-white"></div>
                  <span>Enregistrement...</span>
                </div>
              ) : (
                <div className="flex items-center space-x-2">
                  <UserPlus className="w-4 h-4" />
                  <span>Finaliser l&apos;enregistrement</span>
                </div>
              )}
            </Button>
          </form>
        </CardContent>
      </Card>
    </div>
  );
}
