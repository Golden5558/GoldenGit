-- Make onChainPatientId optional (nullable)
ALTER TABLE "patient" ALTER COLUMN "onChainPatientId" DROP NOT NULL;

-- Add revokedAt to dataset_reference for DB-based consent revocation
ALTER TABLE "dataset_reference" ADD COLUMN "revokedAt" TIMESTAMPTZ;
