/**
 * @jest-environment node
 *
 * TDD — app/api/patient/upload/route.ts
 *
 * Cas testés :
 *   🔴 Erreurs d'authentification / autorisation
 *   🔴 Patient / étude introuvable
 *   🔴 Hash fourni par le client ne correspond pas aux données (HASH_MISMATCH)
 *   🟢 Chemin nominal — hash correct → 200
 */

import { describe, it, expect, beforeEach, jest } from '@jest/globals';
import { NextRequest } from 'next/server';
import { computeDatasetHash } from '@/lib/datasetHash';

// ─── Mocks ────────────────────────────────────────────────────────────────────

const mockVerifyWalletAuth = jest.fn<() => Promise<unknown>>();
jest.mock('@/lib/auth', () => ({
  verifyWalletAuth: (...args: Array<unknown>) => mockVerifyWalletAuth(...args as []),
  forbiddenResponse: (msg: string, code: string) =>
    Response.json({ error: msg, code }, { status: 403 }),
}));

const mockPatientFindUnique = jest.fn<() => Promise<unknown>>();
const mockStudyFindUnique  = jest.fn<() => Promise<unknown>>();
const mockTransaction      = jest.fn<() => Promise<unknown>>();
jest.mock('@/lib/prisma', () => ({
  prisma: {
    patient: { findUnique: (...args: Array<unknown>) => mockPatientFindUnique(...args as []) },
    study:   { findUnique: (...args: Array<unknown>) => mockStudyFindUnique(...args as []) },
    $transaction: (...args: Array<unknown>) => mockTransaction(...args as []),
  },
}));

// ─── Fixtures ─────────────────────────────────────────────────────────────────

const PATIENT_ID  = 1;
const STUDY_ID    = 42;
const WALLET      = '0xabc0000000000000000000000000000000000001';

const MEASUREMENTS = [
  { measurementType: 'GLUCOSE', value: 5.5, timestamp: '2026-03-10T08:00:00.000Z' },
  { measurementType: 'HBA1C',   value: 6.2, timestamp: '2026-03-10T09:00:00.000Z' },
];

const MOCK_PATIENT = {
  id: PATIENT_ID,
  walletAddress: WALLET,
  onChainPatientId: 1,
};

const MOCK_STUDY = {
  id: STUDY_ID,
  isApproved: true,
  onChainStudyId: 42,
};

// ─── Helper ───────────────────────────────────────────────────────────────────

function makeRequest(body: Record<string, unknown>): NextRequest {
  return new NextRequest('http://localhost/api/patient/upload', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(body),
  });
}

function mockAuthSuccess(userId = PATIENT_ID) {
  mockVerifyWalletAuth.mockResolvedValue({
    success: true,
    user: { userType: 'patient', userId },
  });
}

// ─── Tests ────────────────────────────────────────────────────────────────────

describe('POST /api/patient/upload', () => {
  beforeEach(() => {
    jest.clearAllMocks();
  });

  // ── Authentification ────────────────────────────────────────────────────────

  it('🔴 retourne 401 si non authentifié', async () => {
    mockVerifyWalletAuth.mockResolvedValue({
      success: false,
      error: 'Non authentifié',
      code: 'UNAUTHENTICATED',
      status: 401,
    });

    const { POST } = await import('@/app/api/patient/upload/route');
    const res  = await POST(makeRequest({}));
    const body = await res.json();

    expect(res.status).toBe(401);
    expect(body.code).toBe('UNAUTHENTICATED');
  });

  it("🔴 retourne 403 si l'utilisateur n'est pas un patient", async () => {
    mockVerifyWalletAuth.mockResolvedValue({
      success: true,
      user: { userType: 'researcher', userId: PATIENT_ID },
    });

    const { POST } = await import('@/app/api/patient/upload/route');
    const hash = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const res  = await POST(makeRequest({ patientId: PATIENT_ID, studyId: STUDY_ID, datasetHash: hash, measurements: MEASUREMENTS }));
    const body = await res.json();

    expect(res.status).toBe(403);
    expect(body.code).toBe('ACCESS_DENIED');
  });

  it("🔴 retourne 403 si patientId ne correspond pas a l'utilisateur connecte", async () => {
    mockAuthSuccess(999); // userId différent de PATIENT_ID

    const { POST } = await import('@/app/api/patient/upload/route');
    const hash = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const res  = await POST(makeRequest({ patientId: PATIENT_ID, studyId: STUDY_ID, datasetHash: hash, measurements: MEASUREMENTS }));
    const body = await res.json();

    expect(res.status).toBe(403);
    expect(body.code).toBe('ACCESS_DENIED');
  });

  // ── Validation Zod ──────────────────────────────────────────────────────────

  it('🔴 retourne 400 VALIDATION_ERROR si datasetHash manquant', async () => {
    mockAuthSuccess();

    const { POST } = await import('@/app/api/patient/upload/route');
    const res  = await POST(makeRequest({ patientId: PATIENT_ID, studyId: STUDY_ID, measurements: MEASUREMENTS }));
    const body = await res.json();

    expect(res.status).toBe(400);
    expect(body.code).toBe('VALIDATION_ERROR');
  });

  it("🔴 retourne 400 VALIDATION_ERROR si datasetHash n'est pas un hex 0x valide", async () => {
    mockAuthSuccess();

    const { POST } = await import('@/app/api/patient/upload/route');
    const res  = await POST(makeRequest({
      patientId: PATIENT_ID,
      studyId: STUDY_ID,
      datasetHash: 'not-a-hash',
      measurements: MEASUREMENTS,
    }));
    const body = await res.json();

    expect(res.status).toBe(400);
    expect(body.code).toBe('VALIDATION_ERROR');
  });

  // ── Patient / étude ─────────────────────────────────────────────────────────

  it("🔴 retourne 404 PATIENT_NOT_FOUND si le patient n'existe pas en DB", async () => {
    mockAuthSuccess();
    mockPatientFindUnique.mockResolvedValue(null);

    const { POST } = await import('@/app/api/patient/upload/route');
    const hash = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const res  = await POST(makeRequest({ patientId: PATIENT_ID, studyId: STUDY_ID, datasetHash: hash, measurements: MEASUREMENTS }));
    const body = await res.json();

    expect(res.status).toBe(404);
    expect(body.code).toBe('PATIENT_NOT_FOUND');
  });

  it("🔴 retourne 404 STUDY_NOT_FOUND si l'etude n'est pas approuvee", async () => {
    mockAuthSuccess();
    mockPatientFindUnique.mockResolvedValue(MOCK_PATIENT);
    mockStudyFindUnique.mockResolvedValue(null);

    const { POST } = await import('@/app/api/patient/upload/route');
    const hash = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const res  = await POST(makeRequest({ patientId: PATIENT_ID, studyId: STUDY_ID, datasetHash: hash, measurements: MEASUREMENTS }));
    const body = await res.json();

    expect(res.status).toBe(404);
    expect(body.code).toBe('STUDY_NOT_FOUND');
  });

  it("🔴 retourne 403 STUDY_NOT_ON_CHAIN si l'etude n'a pas de onChainStudyId", async () => {
    mockAuthSuccess();
    mockPatientFindUnique.mockResolvedValue(MOCK_PATIENT);
    mockStudyFindUnique.mockResolvedValue({ ...MOCK_STUDY, onChainStudyId: null });

    const { POST } = await import('@/app/api/patient/upload/route');
    const hash = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const res  = await POST(makeRequest({ patientId: PATIENT_ID, studyId: STUDY_ID, datasetHash: hash, measurements: MEASUREMENTS }));
    const body = await res.json();

    expect(res.status).toBe(403);
    expect(body.code).toBe('STUDY_NOT_ON_CHAIN');
  });

  // ── Hash mismatch ───────────────────────────────────────────────────────────

  it('🔴 retourne 400 HASH_MISMATCH si le hash fourni ne correspond pas aux données', async () => {
    mockAuthSuccess();
    mockPatientFindUnique.mockResolvedValue(MOCK_PATIENT);
    mockStudyFindUnique.mockResolvedValue(MOCK_STUDY);

    const { POST } = await import('@/app/api/patient/upload/route');
    // Hash calculé sur des données différentes
    const wrongHash = await computeDatasetHash(PATIENT_ID, STUDY_ID + 999, MEASUREMENTS);
    const res  = await POST(makeRequest({ patientId: PATIENT_ID, studyId: STUDY_ID, datasetHash: wrongHash, measurements: MEASUREMENTS }));
    const body = await res.json();

    expect(res.status).toBe(400);
    expect(body.code).toBe('HASH_MISMATCH');
  });

  it('🔴 retourne 400 HASH_MISMATCH si les données sont altérées après calcul du hash', async () => {
    mockAuthSuccess();
    mockPatientFindUnique.mockResolvedValue(MOCK_PATIENT);
    mockStudyFindUnique.mockResolvedValue(MOCK_STUDY);

    const { POST } = await import('@/app/api/patient/upload/route');
    // Hash correct, mais mesures altérées dans la requête
    const correctHash = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const alteredMeasurements = [{ ...MEASUREMENTS[0], value: 999 }, MEASUREMENTS[1]];
    const res  = await POST(makeRequest({ patientId: PATIENT_ID, studyId: STUDY_ID, datasetHash: correctHash, measurements: alteredMeasurements }));
    const body = await res.json();

    expect(res.status).toBe(400);
    expect(body.code).toBe('HASH_MISMATCH');
  });

  // ── Chemin nominal ──────────────────────────────────────────────────────────

  it('🟢 retourne 200 avec le hash quand tout est valide', async () => {
    mockAuthSuccess();
    mockPatientFindUnique.mockResolvedValue(MOCK_PATIENT);
    mockStudyFindUnique.mockResolvedValue(MOCK_STUDY);

    const correctHash = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);

    // Simuler la transaction Prisma
    mockTransaction.mockImplementation(async (fn: (tx: unknown) => Promise<unknown>) => {
      const mockTx = {
        datasetReference: {
          findUnique: jest.fn<() => Promise<unknown>>().mockResolvedValue(null),
          create: jest.fn<() => Promise<unknown>>().mockResolvedValue({ datasetHash: correctHash }),
        },
        measurement: {
          create: jest.fn<() => Promise<unknown>>().mockResolvedValue({ id: 1 }),
        },
      };
      return fn(mockTx);
    });

    const { POST } = await import('@/app/api/patient/upload/route');
    const res  = await POST(makeRequest({ patientId: PATIENT_ID, studyId: STUDY_ID, datasetHash: correctHash, measurements: MEASUREMENTS }));
    const body = await res.json();

    expect(res.status).toBe(200);
    expect(body.success).toBe(true);
    expect(body.datasetHash).toBe(correctHash);
    expect(body.measurementCount).toBe(MEASUREMENTS.length);
  });

  it('🟢 le hash stocké en DB est identique à celui passé à selfGrantConsent (cohérence on-chain)', async () => {
    mockAuthSuccess();
    mockPatientFindUnique.mockResolvedValue(MOCK_PATIENT);
    mockStudyFindUnique.mockResolvedValue(MOCK_STUDY);

    // Hash calculé côté client (simulé ici) — même algorithme que le contrat
    const clientHash = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);

    let storedHash: string | undefined;
    mockTransaction.mockImplementation(async (fn: (tx: unknown) => Promise<unknown>) => {
      const mockTx = {
        datasetReference: {
          findUnique: jest.fn<() => Promise<unknown>>().mockResolvedValue(null),
          create: jest.fn<(data: unknown) => Promise<unknown>>().mockImplementation(
            async (data: unknown) => {
              storedHash = (data as { data: { datasetHash: string } }).data.datasetHash;
              return { datasetHash: storedHash };
            }
          ),
        },
        measurement: {
          create: jest.fn<() => Promise<unknown>>().mockResolvedValue({ id: 1 }),
        },
      };
      return fn(mockTx);
    });

    const { POST } = await import('@/app/api/patient/upload/route');
    await POST(makeRequest({ patientId: PATIENT_ID, studyId: STUDY_ID, datasetHash: clientHash, measurements: MEASUREMENTS }));

    // Le hash en DB doit être exactement celui que le client aurait passé à selfGrantConsent
    expect(storedHash).toBe(clientHash);
  });
});
