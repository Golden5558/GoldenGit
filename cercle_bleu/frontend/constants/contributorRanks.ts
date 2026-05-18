export interface ContributorRank {
  id: number;
  name: string;
  title: string;
  minTokens: number;
  maxTokens: number | null;
  color: string;
  icon: string;
  benefits: string[];
}

export const CONTRIBUTOR_RANKS: ContributorRank[] = [
  {
    id: 1,
    name: "Bronze",
    title: "Contributeur Bronze",
    minTokens: 0,
    maxTokens: 199,
    color: "#CD7F32",
    icon: "🥉",
    benefits: ["Accès aux travaux de recherche contributeur", "Badge de reconnaissance", "Accès blog éducatif"]
  },
  {
    id: 2,
    name: "Argent",
    title: "Contributeur Argent",
    minTokens: 200,
    maxTokens: 499,
    color: "#C0C0C0",
    icon: "🥈",
    benefits: ["Accès fonctionallités anticipées", "Exportation de données avancée"]
  },
  {
    id: 3,
    name: "Or",
    title: "Contributeur Or",
    minTokens: 500,
    maxTokens: 999,
    color: "#FFD700",
    icon: "🥇",
    benefits: ["Accès prioritaire aux études", "Badge exclusif"]
  },
  {
    id: 4,
    name: "Platine",
    title: "Contributeur Platine",
    minTokens: 1000,
    maxTokens: 1999,
    color: "#E5E4E2",
    icon: "💎",
    benefits: ["Consultation prioritaire", "Certificat de reconnaissance"]
  },
  {
    id: 5,
    name: "Diamant",
    title: "Contributeur Diamant",
    minTokens: 2000,
    maxTokens: null,
    color: "#B9F2FF",
    icon: "💠",
    benefits: ["Accès VIP complet", "Reconnaissance officielle"]
  }
];

export function getCurrentRank(tokenBalance: number): ContributorRank {
  return CONTRIBUTOR_RANKS.find(rank => 
    tokenBalance >= rank.minTokens && 
    (rank.maxTokens === null || tokenBalance <= rank.maxTokens)
  ) || CONTRIBUTOR_RANKS[0];
}

export function getNextRank(tokenBalance: number): ContributorRank | null {
  const currentRank = getCurrentRank(tokenBalance);
  const nextRankIndex = CONTRIBUTOR_RANKS.findIndex(rank => rank.id === currentRank.id) + 1;
  return nextRankIndex < CONTRIBUTOR_RANKS.length ? CONTRIBUTOR_RANKS[nextRankIndex] : null;
}

export function getProgressToNextRank(tokenBalance: number): { current: number; total: number; percentage: number } {
  const nextRank = getNextRank(tokenBalance);
  if (!nextRank) {
    return { current: tokenBalance, total: tokenBalance, percentage: 100 };
  }
  
  const currentRank = getCurrentRank(tokenBalance);
  const current = tokenBalance - currentRank.minTokens;
  const total = nextRank.minTokens - currentRank.minTokens;
  const percentage = Math.min((current / total) * 100, 100);
  
  return { current, total, percentage };
}