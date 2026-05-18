'use client';

import { useState, useEffect } from 'react';
import { useAccount, useWaitForTransactionReceipt, useReadContract } from 'wagmi';
import { Button } from '@/components/ui/button';
import { tokenContractAddress, tokenContractABI } from '@/constants';
import { toast } from 'sonner';
import BlockchainStepCard from '@/components/shared/BlockchainStepCard';
import { useSmartContractWrite } from '@/hooks/useSmartContractWrite';

interface ResearcherBlockchainRegistrationProps {
  onRegistrationSuccess: () => void;
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
    description: 'votre wallet vous demandera de signer une transaction. Pour attester de votre identité et validé votre inscription.',
  },
  {
    icon: '🪪',
    title: 'Ce que vous obtenez :',
    description: 'Une identité sécurisée et immutable — elle vous permets de prouver votre statut de chercheur autorisé et d\'accéder aux fonctionnalités de la plateforme.',
  },
];

export default function ResearcherBlockchainRegistration({
  onRegistrationSuccess,
}: ResearcherBlockchainRegistrationProps) {
  const { address } = useAccount();
  const { execute: writeContractAsync } = useSmartContractWrite();
  const [isRegistering, setIsRegistering] = useState(false);
  const [hash, setHash] = useState<`0x${string}` | undefined>();

  const { data: isAlreadyAuthorized, isLoading: isChecking } = useReadContract({
    address: tokenContractAddress as `0x${string}`,
    abi: tokenContractABI,
    functionName: 'authorizedResearchers',
    args: address ? [address] : undefined,
  });

  const { isLoading: isConfirming, isSuccess } = useWaitForTransactionReceipt({ hash });

  useEffect(() => {
    if (isAlreadyAuthorized) {
      onRegistrationSuccess();
    }
  }, [isAlreadyAuthorized, onRegistrationSuccess]);

  useEffect(() => {
    if (isSuccess) {
      toast.success('Accès blockchain activé !');
      setIsRegistering(false);
      onRegistrationSuccess();
    }
  }, [isSuccess, onRegistrationSuccess]);

  const handleActivate = async () => {
    if (!address) {
      toast.error('Veuillez connecter votre wallet');
      return;
    }
    setIsRegistering(true);
    try {
      const txHash = await writeContractAsync({
        address: tokenContractAddress as `0x${string}`,
        abi: tokenContractABI,
        functionName: 'setAuthorizedResearchers',
        args: [address, true],
      });
      setHash(txHash);
    } catch (err) {
      console.error('Erreur lors de l\'activation blockchain:', err);
      toast.error('Erreur lors de l\'activation sur la blockchain');
      setIsRegistering(false);
    }
  };

  if (isChecking) {
    return (
      <div className="text-center text-blue-600 font-medium">
        🔄 Vérification de l&apos;état d&apos;autorisation...
      </div>
    );
  }

  if (isAlreadyAuthorized) {
    return (
      <div className="text-center text-green-600 font-medium">
        ✅ Vous êtes déjà autorisé sur la blockchain
      </div>
    );
  }

  return (
    <div className="space-y-4">
      <BlockchainStepCard items={EXPLANATION_ITEMS} hash={hash} address={address} />

      <Button
        onClick={handleActivate}
        disabled={isRegistering || isConfirming}
        className="w-full"
      >
        {isRegistering || isConfirming
          ? 'Activation en cours...'
          : 'Activer l\'accès blockchain'}
      </Button>
    </div>
  );
}
