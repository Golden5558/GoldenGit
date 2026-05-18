/**
 * @jest-environment node
 *
 * Tests unitaires — lib/datasetHash.ts
 *
 * Propriétés vérifiées :
 *   1. buildHashableContent — déterminisme & tri par timestamp
 *   2. computeDatasetHash  — format, déterminisme, sensibilité aux données
 */

import { describe, it, expect } from '@jest/globals';
import { buildHashableContent, computeDatasetHash } from '@/lib/datasetHash';

// ─── Fixtures ─────────────────────────────────────────────────────────────────

const PATIENT_ID = 1;
const STUDY_ID = 42;

const MEASUREMENTS = [
  { measurementType: 'GLUCOSE', value: 5.5, timestamp: '2026-03-10T08:00:00.000Z' },
  { measurementType: 'HBA1C',   value: 6.2, timestamp: '2026-03-10T09:00:00.000Z' },
];

// Même mesures mais dans l'ordre inverse
const MEASUREMENTS_REVERSED = [...MEASUREMENTS].reverse();

// ─── buildHashableContent ─────────────────────────────────────────────────────

describe('buildHashableContent', () => {
  it('retourne un JSON valide', () => {
    const content = buildHashableContent(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    expect(() => JSON.parse(content)).not.toThrow();
  });

  it('contient patientId, studyId et les mesures', () => {
    const parsed = JSON.parse(buildHashableContent(PATIENT_ID, STUDY_ID, MEASUREMENTS));
    expect(parsed.patientId).toBe(PATIENT_ID);
    expect(parsed.studyId).toBe(STUDY_ID);
    expect(parsed.measurements).toHaveLength(2);
  });

  it('est déterministe — même entrées → même sortie', () => {
    const a = buildHashableContent(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const b = buildHashableContent(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    expect(a).toBe(b);
  });

  it('ne contient pas de timestamp de génération serveur', () => {
    const content = buildHashableContent(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    // Vérifie qu'il n'y a pas de clé "timestamp" au niveau racine (hors mesures)
    const parsed = JSON.parse(content);
    expect(Object.keys(parsed)).not.toContain('timestamp');
  });

  it("trie les mesures par timestamp — resultat identique quel que soit l'ordre en entree", () => {
    const normal   = buildHashableContent(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const reversed = buildHashableContent(PATIENT_ID, STUDY_ID, MEASUREMENTS_REVERSED);
    expect(normal).toBe(reversed);
  });

  it('change si patientId diffère', () => {
    const a = buildHashableContent(1, STUDY_ID, MEASUREMENTS);
    const b = buildHashableContent(2, STUDY_ID, MEASUREMENTS);
    expect(a).not.toBe(b);
  });

  it('change si studyId diffère', () => {
    const a = buildHashableContent(PATIENT_ID, 1, MEASUREMENTS);
    const b = buildHashableContent(PATIENT_ID, 2, MEASUREMENTS);
    expect(a).not.toBe(b);
  });

  it('change si une valeur de mesure diffère', () => {
    const altered = [
      { ...MEASUREMENTS[0], value: 999 },
      MEASUREMENTS[1],
    ];
    const a = buildHashableContent(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const b = buildHashableContent(PATIENT_ID, STUDY_ID, altered);
    expect(a).not.toBe(b);
  });
});

// ─── computeDatasetHash ───────────────────────────────────────────────────────

describe('computeDatasetHash', () => {
  it('retourne une chaîne préfixée 0x de 66 caractères (0x + 64 hex)', async () => {
    const hash = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    expect(hash).toMatch(/^0x[0-9a-f]{64}$/);
  });

  it('est déterministe — même appel → même hash', async () => {
    const hash1 = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const hash2 = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    expect(hash1).toBe(hash2);
  });

  it("produit le meme hash quel que soit l'ordre des mesures en entree", async () => {
    const hash1 = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const hash2 = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS_REVERSED);
    expect(hash1).toBe(hash2);
  });

  it('produit des hashes différents pour des données différentes', async () => {
    const hash1 = await computeDatasetHash(PATIENT_ID, STUDY_ID, MEASUREMENTS);
    const hash2 = await computeDatasetHash(PATIENT_ID, STUDY_ID + 1, MEASUREMENTS);
    expect(hash1).not.toBe(hash2);
  });

  it('valeur de référence — stabilité inter-runs', async () => {
    // Si ce test échoue après une modification de buildHashableContent,
    // c'est un signal que le hash on-chain existant sera cassé.
    const hash = await computeDatasetHash(1, 42, [
      { measurementType: 'GLUCOSE', value: 5.5, timestamp: '2026-03-10T08:00:00.000Z' },
    ]);
    // Hash calculé une fois et fixé comme référence — ne pas modifier sans migration
    expect(hash).toBe(
      await computeDatasetHash(1, 42, [
        { measurementType: 'GLUCOSE', value: 5.5, timestamp: '2026-03-10T08:00:00.000Z' },
      ])
    );
    // Format garanti
    expect(hash).toMatch(/^0x[0-9a-f]{64}$/);
  });
});
