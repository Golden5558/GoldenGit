type MeasurementForHash = {
  measurementType: string;
  value: number;
  timestamp: string;
};

/**
 * Builds the canonical JSON string used as input for the dataset hash.
 * Deterministic: measurements are sorted by timestamp, no server-side timestamp included.
 * Must produce the same output on client (browser) and server (Node 18+).
 */
export function buildHashableContent(
  patientId: number,
  studyId: number,
  measurements: MeasurementForHash[]
): string {
  const sorted = [...measurements].sort((a, b) =>
    a.timestamp.localeCompare(b.timestamp)
  );
  return JSON.stringify({
    patientId,
    studyId,
    measurements: sorted.map((m) => ({
      type: m.measurementType,
      value: m.value,
      timestamp: m.timestamp,
    })),
  });
}

/**
 * Computes the dataset hash using the Web Crypto API (available in browsers
 * and Node.js 18+). Returns a `0x`-prefixed lowercase hex string.
 */
export async function computeDatasetHash(
  patientId: number,
  studyId: number,
  measurements: MeasurementForHash[]
): Promise<`0x${string}`> {
  const content = buildHashableContent(patientId, studyId, measurements);
  const encoded = new TextEncoder().encode(content);
  const hashBuffer = await crypto.subtle.digest('SHA-256', encoded);
  const hex = Array.from(new Uint8Array(hashBuffer))
    .map((b) => b.toString(16).padStart(2, '0'))
    .join('');
  return `0x${hex}`;
}
