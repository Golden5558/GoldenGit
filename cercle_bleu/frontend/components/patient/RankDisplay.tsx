import React from 'react';
import { ContributorRank } from '../../constants/contributorRanks';

interface RankDisplayProps {
  currentRank: ContributorRank;
  nextRank: ContributorRank | null;
  tokenBalance: number;
  progress: { current: number; total: number; percentage: number };
}

export const RankDisplay: React.FC<RankDisplayProps> = ({
  currentRank,
  nextRank,
  tokenBalance,
  progress
}) => {
  return (
    <div className="bg-white rounded-lg shadow-md p-6 mb-6">
      <div className="flex items-center justify-between mb-4">
        <div className="flex items-center space-x-3">
          <span className="text-3xl">{currentRank.icon}</span>
          <div>
            <h3 className="text-xl font-bold" style={{ color: currentRank.color }}>
              {currentRank.title}
            </h3>
            <p className="text-gray-600">{tokenBalance} CERCLE</p>
          </div>
        </div>
        <div className="text-right">
          <div className="text-2xl font-bold" style={{ color: currentRank.color }}>
            Rang {currentRank.id}
          </div>
        </div>
      </div>

      {nextRank && (
        <div className="mb-4">
          <div className="w-full bg-gray-200 rounded-full h-3">
            <div 
              className="h-3 rounded-full transition-all duration-300 ease-out"
              style={{ 
                width: `${progress.percentage}%`,
                background: `linear-gradient(90deg, ${currentRank.color}, ${nextRank.color})`
              }}
            />
          </div>
          <p className="text-xs text-gray-500 mt-1">
            {Math.round(progress.percentage)}% vers {nextRank.name}
          </p>
        </div>
      )}

      <div className="border-t pt-4">
        <h4 className="font-semibold text-gray-800 mb-2">Avantages de votre rang :</h4>
        <ul className="space-y-1">
          {currentRank.benefits.map((benefit, index) => (
            <li key={index} className="flex items-center text-sm text-gray-600">
              <span className="text-green-500 mr-2">✓</span>
              {benefit}
            </li>
          ))}
        </ul>
      </div>

      {nextRank && (
        <div className="mt-4 p-3 bg-gray-50 rounded-lg">
          <h4 className="font-semibold text-gray-800 mb-2 flex items-center">
            <span className="mr-2">{nextRank.icon}</span>
            Débloquez {nextRank.title} :
          </h4>
          <ul className="space-y-1">
            {nextRank.benefits.map((benefit, index) => (
              <li key={index} className="flex items-center text-sm text-gray-600">
                <span className="text-blue-500 mr-2">→</span>
                {benefit}
              </li>
            ))}
          </ul>
        </div>
      )}
    </div>
  );
};