'use client';

import { useState, useEffect } from 'react';
import { useAccount, useWaitForTransactionReceipt, useReadContract } from 'wagmi';
import { Button } from '@/components/ui/button';
import { consentContractAddress, consentContractABI } from '@/constants';
import { toast } from 'sonner';
import BlockchainStepCard from '@/components/shared/BlockchainStepCard';
import { useSmartContractWrite } from '@/hooks/useSmartContractWrite';

interface PatientBlockchainRegistrationProps {
  onRegistrationSuccess: (patientId: number) => void;
}

const EXPLANATION_ITEMS = [
  {
    icon: '🔗',
    title: 'Inscription décentralisée :',
    description: 'votre adresse wallet est inscrite sur la blockchain. Cela creer le lien entre votre identité numérique et votre profil patient dans l\'application.',
  },
  {
    icon: '✍️',
    title: 'Une seule signature :',
    description: 'votre wallet vous demandera de signer une transaction pour valider votre inscription.',
  },
  {
    icon: '🪪',
    title: 'Ce que vous obtenez :',
    description: 'Une identité sécurisée et immutable — elle vous donne le contrôle total sur le partage de vos données.',
  },
];

export default function PatientBlockchainRegistration({ onRegistrationSuccess }: PatientBlockchainRegistrationProps) {
  const { address } = useAccount();
  const { execute: writeContractAsync } = useSmartContractWrite();
  const [isRegistering, setIsRegistering] = useState(false);
  const [hash, setHash] = useState<`0x${string}` | undefined>();

  const { data: isPatientBlockRegistered, isLoading: isCheckingRegistration } = useReadContract({
    address: consentContractAddress as `0x${string}`,
    abi: consentContractABI,
    functionName: 'isPatientRegistered',
    args: address ? [address] : undefined,
  });

  const { data: patientId, refetch: refetchPatientId } = useReadContract({
    address: consentContractAddress as `0x${string}`,
    abi: consentContractABI,
    functionName: 'getPatientId',
    args: address ? [address] : undefined,
    account: address,
    query: { enabled: false },
  });

  const { isLoading: isConfirming, isSuccess } = useWaitForTransactionReceipt({ hash });

  useEffect(() => {
    if (isPatientBlockRegistered && patientId) {
      refetchPatientId().then((result) => {
        if (result.data) {
          onRegistrationSuccess(Number(result.data));
        }
      });
    }
  }, [isPatientBlockRegistered, patientId, refetchPatientId, onRegistrationSuccess]);

  useEffect(() => {
    if (isSuccess) {
      refetchPatientId().then((result) => {
        if (result.data) {
          const blockchainPatientId = Number(result.data);
          toast.success(`Enregistrement réussi! ID Patient: ${blockchainPatientId}`);
          onRegistrationSuccess(blockchainPatientId);
        }
      });
      setIsRegistering(false);
    }
  }, [isSuccess, refetchPatientId, onRegistrationSuccess]);

  const handleRegister = async () => {
    if (!address) {
      toast.error('Veuillez connecter votre wallet');
      return;
    }
    setIsRegistering(true);
    try {
      const txHash = await writeContractAsync({
        address: consentContractAddress as `0x${string}`,
        abi: consentContractABI,
        functionName: 'registerPatient',
      });
      setHash(txHash);
    } catch (err) {
      console.error('Erreur lors de l\'enregistrement:', err);
      toast.error('Erreur lors de l\'enregistrement sur la blockchain');
      setIsRegistering(false);
    }
  };

  if (isCheckingRegistration) {
    return (
      <div className="text-center text-blue-600 font-medium">
        🔄 Vérification de l&apos;état d&apos;enregistrement...
      </div>
    );
  }

  if (isPatientBlockRegistered) {
    return (
      <div className="text-center space-y-2">
        <div className="text-green-600 font-medium">
          ✅ Vous êtes déjà enregistré sur la blockchain
        </div>
        <div className="text-sm text-gray-600">
          Récupération de votre ID patient...
        </div>
      </div>
    );
  }

  return (
    <div className="space-y-4">
      <BlockchainStepCard items={EXPLANATION_ITEMS} hash={hash} address={address} />
      <Button
        onClick={handleRegister}
        disabled={isRegistering || isConfirming}
        className="w-full"
      >
        {isRegistering || isConfirming ? 'Enregistrement en cours...' : 'S\'enregistrer sur la blockchain'}
      </Button>
    </div>
  );
}
