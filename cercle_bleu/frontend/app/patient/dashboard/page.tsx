'use client';

import { useRouter } from 'next/navigation';
import { useEffect } from 'react';
import { Button } from '@/components/ui/button';
import { Upload, FileText, Settings, User, Calendar, Weight, Mail } from 'lucide-react';
import { useAuthContext } from '@/contexts/AuthContext';
import { FirstRunChecklist } from '@/components/shared/FirstRunChecklist';

interface PatientInfo {
  id: number;
  walletAddress: string;
  firstName: string;
  lastName: string;
  email?: string;
  birthYear?: number;
  weightKg?: number;
  sex?: string;
  diabeteType?: string;
  createdAt: string;
  datasetReferences: [];
}

export default function PatientDashboard() {
  const router = useRouter();
  const { userData, isLoadingUser, userError, userType, isAuthenticated, isAuthenticating } = useAuthContext();

  useEffect(() => {
    if (!isAuthenticating && !isAuthenticated) {
      router.push('/login');
    }
  }, [isAuthenticating, isAuthenticated, router]);


  // Cast userData to PatientInfo type for this component
  const patientInfo = userType === 'patient' ? userData as PatientInfo | null : null;
  const isLoadingPatient = isLoadingUser;
  const patientError = userType === 'unknown' ? 'Patient non trouvé' : userError;

  const formatDiabeteType = (type?: string) => {
    if (!type) return 'Non spécifié';
    return type === 'TYPE_1' ? 'Type 1' : type === 'TYPE_2' ? 'Type 2' : type;
  };

  const formatSex = (sex?: string) => {
    if (!sex) return 'Non spécifié';
    return sex === 'M' ? 'Masculin' : sex === 'F' ? 'Féminin' : sex;
  };

  return (
    <div className="min-h-screen bg-gray-50">
      {/* Main Content */}
      <main className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
        {/* Patient Info Section */}
        <div className="mb-8">
          <div className="bg-white rounded-lg shadow-md p-6">
            <div className="flex items-center space-x-3 mb-6">
              <User className="w-8 h-8 text-blue-600" />
              <h2 className="text-2xl font-semibold text-gray-900">Mes Informations</h2>
            </div>
            
            {isLoadingPatient ? (
              <div className="flex items-center justify-center py-8">
                <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-blue-600"></div>
                <span className="ml-2 text-gray-600">Chargement...</span>
              </div>
            ) : patientError ? (
              <div className="bg-red-50 border border-red-200 rounded-md p-4">
                <p className="text-red-800">{patientError}</p>
                <p className="text-sm text-red-600 mt-1">
                  Vous devez d&apos;abord vous enregistrer comme patient.
                </p>
                <Button 
                  onClick={() => router.push('/patient/profile')}
                  className="mt-3"
                  size="sm"
                >
                  S&apos;enregistrer
                </Button>
              </div>
            ) : patientInfo ? (
              <div className="grid md:grid-cols-2 lg:grid-cols-3 gap-6">
                <div className="space-y-4">
                  <div className="flex items-center space-x-3">
                    <User className="w-5 h-5 text-gray-500" />
                    <div>
                      <p className="text-sm text-gray-500">Nom complet</p>
                      <p className="font-medium">{patientInfo.firstName} {patientInfo.lastName}</p>
                    </div>
                  </div>
                  
                  {patientInfo.email && (
                    <div className="flex items-center space-x-3">
                      <Mail className="w-5 h-5 text-gray-500" />
                      <div>
                        <p className="text-sm text-gray-500">Email</p>
                        <p className="font-medium">{patientInfo.email}</p>
                      </div>
                    </div>
                  )}
                </div>
                  
                <div className="space-y-4">
                  {patientInfo.birthYear && (
                    <div className="flex items-center space-x-3">
                      <Calendar className="w-5 h-5 text-gray-500" />
                      <div>
                        <p className="text-sm text-gray-500">Année de naissance</p>
                        <p className="font-medium">{patientInfo.birthYear}</p>
                      </div>
                    </div>
                  )}
                  
                  <div className="flex items-center space-x-3">
                    <div className="w-5 h-5 flex items-center justify-center">
                      <span className="text-gray-500 text-sm">♂♀</span>
                    </div>
                    <div>
                      <p className="text-sm text-gray-500">Sexe</p>
                      <p className="font-medium">{formatSex(patientInfo.sex)}</p>
                    </div>
                  </div>
                </div>
                
                <div className="space-y-4">
                  {patientInfo.weightKg && (
                    <div className="flex items-center space-x-3">
                      <Weight className="w-5 h-5 text-gray-500" />
                      <div>
                        <p className="text-sm text-gray-500">Poids</p>
                        <p className="font-medium">{patientInfo.weightKg} kg</p>
                      </div>
                    </div>
                  )}
                  
                  <div className="flex items-center space-x-3">
                    <div className="w-5 h-5 flex items-center justify-center">
                      <span className="text-gray-500 text-sm">🩺</span>
                    </div>
                    <div>
                      <p className="text-sm text-gray-500">Type de diabète</p>
                      <p className="font-medium">{formatDiabeteType(patientInfo.diabeteType)}</p>
                    </div>
                  </div>
                </div>
              </div>
            ) : null}
          </div>
        </div>

                {/* First-run checklist */}
        {patientInfo && (
          <FirstRunChecklist
            storageKey={`patient_${patientInfo.id}`}
            title="Vos premières étapes"
            tasks={[
              {
                id: 'upload',
                label: 'Télécharger vos premières données de santé',
                href: '/patient/upload',
                autoCompleted: patientInfo.datasetReferences.length > 0,
              },
              {
                id: 'consent',
                label: 'Consulter vos paramètres de consentement',
                href: '/patient/consent',
                autoCompleted: false,
              },
                           {
                id: 'tokens',
                label: 'Compléter votre profil',
                href: '/patient//edit-profile',
                autoCompleted: false,
              },
            ]}
          />
        )}

        {/* Action Cards */}
        <div className="grid md:grid-cols-2 lg:grid-cols-3 gap-6 mb-8">
          {/* Upload Data Card */}
          <div className="bg-white rounded-lg shadow-md p-6">
            <div className="flex items-center space-x-3 mb-4">
              <Upload className="w-8 h-8 text-blue-600" />
              <h2 className="text-xl font-semibold text-gray-900">Mes Données</h2>
            </div>
            <p className="text-gray-600 mb-4">
              Charger vos données médicales en toute sécurité.
            </p>
              <Button 
              onClick={() => router.push('/patient/upload')}
              className="w-full"
            >
              Charger
            </Button>
          </div>

          {/* Consents Card */}
          <div className="bg-white rounded-lg shadow-md p-6">
            <div className="flex items-center space-x-3 mb-4">
              <FileText className="w-8 h-8 text-green-600" />
              <h2 className="text-xl font-semibold text-gray-900">Mes Consentements</h2>
            </div>
            <p className="text-gray-600 mb-4">
              Consultez et gérez vos consentements pour les études de recherche.
            </p>
            <Button 
              onClick={() => router.push('/patient/consent')}
              className="w-full"
                variant="outline"
              >
              Voir mes consentements
              </Button>
            </div>

          {/* Profile Card */}
          <div className="bg-white rounded-lg shadow-md p-6">
            <div className="flex items-center space-x-3 mb-4">
              <Settings className="w-8 h-8 text-purple-600" />
              <h2 className="text-xl font-semibold text-gray-900">Mon Profil</h2>
            </div>
            <p className="text-gray-600 mb-4">
              Modifiez vos informations personnelles et préférences.
            </p>
            <Button 
              onClick={() => router.push('/patient/edit-profile')}
              className="w-full"
              variant="outline"
            >
              Modifier mon profil
            </Button>
          </div>
        </div>

        {/* Statistics */}
        {patientInfo && (
          <div className="mb-8">
            <div className="bg-white rounded-lg shadow-md p-6">
              <h3 className="text-lg font-semibold text-gray-900 mb-4">Statistiques</h3>
              <div className="space-y-3">
                <div className="flex justify-between">
                  <span className="text-gray-600">Datasets partagés</span>
                  <span className="font-medium">{patientInfo.datasetReferences.length}</span>
                </div>
                <div className="flex justify-between">
                  <span className="text-gray-600">Membre depuis</span>
                  <span className="font-medium">
                    {new Date(patientInfo.createdAt).toLocaleDateString('fr-FR')}
                  </span>
                </div>
                <div className="flex justify-between">
                  <span className="text-gray-600">ID Patient</span>
                  <span className="font-medium">#{patientInfo.id}</span>
                </div>
              </div>
            </div>
          </div>
        )}

        {/* Recent Activity */}
        <div className="mt-8">
          <div className="bg-white rounded-lg shadow-md p-6">
            <h2 className="text-xl font-semibold text-gray-900 mb-4">Activité Récente</h2>
            <div className="text-gray-600">
              {patientInfo?.datasetReferences.length ? (
                <div className="space-y-2">
                  <p>Vous avez partagé {patientInfo.datasetReferences.length} dataset(s) pour la recherche.</p>
                </div>
              ) : (
                <p>Aucune activité récente à afficher.</p>
              )}
            </div>
          </div>
        </div>
      </main>
    </div>
  );
}