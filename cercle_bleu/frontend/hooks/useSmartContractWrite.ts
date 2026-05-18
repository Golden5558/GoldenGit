import { useSmartWallets } from '@privy-io/react-auth/smart-wallets';
import { useWriteContract } from 'wagmi';

export function useSmartContractWrite() {
  const { client } = useSmartWallets();
  const { writeContractAsync } = useWriteContract();
  const isLocal = parseInt(process.env.NEXT_PUBLIC_CHAIN_ID || '31337') === 31337;

  const execute = async (params: Parameters<typeof writeContractAsync>[0]) => {
    // Sur testnet/mainnet : UserOperation via smart account (gas sponsorisé)
    if (!isLocal && client) {
      return await client.writeContract(params);
    }
    // Sur Hardhat local : transaction directe (pas de bundler nécessaire)
    return await writeContractAsync(params);
  };

  return { execute };
}
