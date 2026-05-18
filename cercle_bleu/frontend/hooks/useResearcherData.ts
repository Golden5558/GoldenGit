'use client';

import { useState, useEffect, useCallback } from 'react';
import { useAuth } from './useAuth';
import { useAuthContext } from '@/contexts/AuthContext';

export interface Measurement {
  id: number;
  measurementType: string;
  value: number;
  timestamp: string;
  mealContext?: string;
  labName?: string;
  deviceModel?: string;
}

export interface PatientData {
  patientId: string;
  patientAddress?: string;
  birthYear?: number;
  weightKg?: number;
  sex?: string;
  diabeteType?: string;
  consentId: string;
  studyId: string;
  datasetHash: string;
  isActive: boolean;
  measurements: Measurement[];
}

export interface ResearcherInfo {
  id: string;
  firstName: string;
  lastName: string;
  institution?: string;
  email?: string;
  walletAddress: string;
}

export interface Study {
  id: number;
  description: string;
  protocolUrl?: string;
  isApproved: boolean;
  createdAt: string;
}

export function useResearcherData() {
  const { authenticatedFetch } = useAuth();
  const { userData, userType } = useAuthContext();
  const [patientData, setPatientData] = useState<PatientData[]>([]);
  const [studies, setStudies] = useState<Study[]>([]);
  const [isLoading, setIsLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  const researcherInfo: ResearcherInfo | null =
    userType === 'researcher' && userData
      ? {
          id: userData.id as string,
          firstName: userData.firstName,
          lastName: userData.lastName,
          institution: userData.institution,
          email: userData.email,
          walletAddress: userData.walletAddress,
        }
      : null;

  const fetchData = useCallback(async () => {
    if (!researcherInfo) return;

    setIsLoading(true);
    setError(null);

    try {
      // Fetch researcher's studies
      const studiesRes = await authenticatedFetch(`/api/researcher/studies?researcherId=${researcherInfo.id}`);
      const studiesData = await studiesRes.json();

      if (studiesRes.ok && studiesData.success) {
        setStudies(studiesData.studies);
      } else {
        setError('Erreur lors de la récupération des études');
        return;
      }

      // Fetch all consented datasets via DB
      const datasetsRes = await authenticatedFetch('/api/researcher/consents');
      const datasetsData = await datasetsRes.json();

      if (datasetsRes.ok && datasetsData.success) {
        setPatientData(
          datasetsData.datasets.map((d: {
            datasetHash: string;
            studyId: number;
            patient: { id: number; birthYear?: number; weightKg?: number; sex?: string; diabeteType?: string };
            measurements: Measurement[];
          }) => ({
            patientId: d.patient.id.toString(),
            birthYear: d.patient.birthYear,
            weightKg: d.patient.weightKg,
            sex: d.patient.sex,
            diabeteType: d.patient.diabeteType,
            consentId: d.datasetHash,
            studyId: d.studyId.toString(),
            datasetHash: d.datasetHash,
            isActive: true,
            measurements: d.measurements,
          }))
        );
      } else {
        setError('Erreur lors de la récupération des données patients');
      }
    } catch (err) {
      console.error('Erreur useResearcherData:', err);
      setError('Erreur lors du chargement des données');
    } finally {
      setIsLoading(false);
    }
  }, [researcherInfo, authenticatedFetch]);

  useEffect(() => {
    if (researcherInfo) {
      fetchData();
    } else if (userType !== null && userType !== 'researcher') {
      setIsLoading(false);
      setError('Accès réservé aux chercheurs');
    }
  // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [userType]);

  return {
    researcherInfo,
    patientData,
    studies,
    isLoading,
    error,
    refetch: fetchData,
  };
}
