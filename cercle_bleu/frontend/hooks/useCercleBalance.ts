'use client';

import { useAccount, useReadContract } from 'wagmi';
import { tokenContractAddress, tokenContractABI } from '@/constants';
import { getCurrentRank, getNextRank, getProgressToNextRank, type ContributorRank } from '../constants/contributorRanks';

export const useCercleBalance = () => {
  const { address, isConnected } = useAccount();

  const { data: cercleBalance, isLoading: isLoadingBalance, error: balanceError, refetch } = useReadContract({
    address: tokenContractAddress as `0x${string}`,
    abi: tokenContractABI,
    functionName: 'balanceOf',
    args: address ? [address] : undefined,
    query: {
      enabled: !!address && isConnected,
    },
  });

  const formatCercleBalance = (balance?: bigint) => {
    if (!balance) return '0';
    return balance.toString();
  };

  const balanceAsNumber = cercleBalance ? Number(cercleBalance) : 0;
  const formattedBalance = formatCercleBalance(cercleBalance);
  
  const currentRank = getCurrentRank(balanceAsNumber);
  const nextRank = getNextRank(balanceAsNumber);
  const rankProgress = getProgressToNextRank(balanceAsNumber);

  return {
    balance: formattedBalance,
    balanceAsNumber,
    isLoading: isLoadingBalance,
    error: balanceError,
    refetch,
    currentRank,
    nextRank,
    rankProgress,
    progressPercentage: rankProgress.percentage
  };
};