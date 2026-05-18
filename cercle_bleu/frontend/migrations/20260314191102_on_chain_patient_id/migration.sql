/*
  Warnings:

  - You are about to alter the column `onChainPatientId` on the `patient` table. The data in that column could be lost. The data in that column will be cast from `BigInt` to `Integer`.
  - You are about to alter the column `onChainStudyId` on the `study` table. The data in that column could be lost. The data in that column will be cast from `BigInt` to `Integer`.

*/
-- AlterTable
ALTER TABLE "patient" ALTER COLUMN "onChainPatientId" SET DATA TYPE INTEGER;

-- AlterTable
ALTER TABLE "study" ALTER COLUMN "onChainStudyId" SET DATA TYPE INTEGER;
