import { createPublicClient, http } from 'viem';
import { hardhat, polygonAmoy } from 'viem/chains';
import {rpcUrl, chainId} from '../constants';

const getChain = () => {
  switch (chainId) {
    case 80002:
      return polygonAmoy;
    case 31337:
    default:
      return hardhat;
  }
};

export const publicClient = createPublicClient({
  chain: getChain(),
  transport: http(rpcUrl)
});