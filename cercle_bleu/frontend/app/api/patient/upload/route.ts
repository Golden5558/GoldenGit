import { NextRequest, NextResponse } from 'next/server';
import { Prisma } from '@prisma/client';
import { z } from 'zod';
import { prisma } from '@/lib/prisma';
import { verifyWalletAuth, forbiddenResponse } from '@/lib/auth';
import { computeDatasetHash } from '@/lib/datasetHash';

type MeasurementInput = {
  measurementType: string;
  value: number;
  timestamp: string;
  mealContext?: string;
  labName?: string;
  deviceModel?: string;
};

// Schéma de validation pour les mesures
const measurementSchema = z.object({
  patientId: z.number().int().positive(),
  studyId: z.number().min(1),
  // Hash calculé côté client avant le consentement on-chain
  datasetHash: z.string().regex(/^0x[0-9a-fA-F]{64}$/, 'Hash SHA-256 invalide (format 0x...)'),
  measurements: z.array(z.object({
    measurementType: z.enum(['GLUCOSE', 'INSULIN', 'HBA1C', 'WEIGHT', 'BMI']),
    value: z.number().positive(),
    timestamp: z.string().datetime(),
    mealContext: z.enum(['FASTING', 'BEFORE_MEAL', 'AFTER_MEAL', 'BEDTIME']).optional(),
    labName: z.string().max(100).optional(),
    deviceModel: z.string().max(50).optional()
  })).min(1)
});

export async function POST(request: NextRequest) {
  try {
    // Authenticate the request
    const authResult = await verifyWalletAuth(request);
    if (!authResult.success) {
      return NextResponse.json(
        { error: authResult.error, code: authResult.code },
        { status: authResult.status }
      );
    }

    const body = await request.json();
    const validatedData = measurementSchema.parse(body);

    const { patientId, studyId, datasetHash, measurements } = validatedData;

    // Verify ownership - only the patient can upload their own data
    if (authResult.user.userType !== 'patient') {
      return forbiddenResponse('Only patients can upload measurement data', 'ACCESS_DENIED');
    }

    if (authResult.user.userId !== patientId) {
      return forbiddenResponse('You can only upload data for your own account', 'ACCESS_DENIED');
    }

    // Vérifier que le patient existe
    const patient = await prisma.patient.findUnique({
      where: { id: patientId }
    });

    if (!patient) {
      return NextResponse.json(
        {
          error: 'Patient non trouvé',
          code: 'PATIENT_NOT_FOUND'
        },
        { status: 404 }
      );
    }

    // Vérifier que l'étude existe et est approuvée
    const study = await prisma.study.findUnique({
      where: { id: studyId, isApproved: true }
    });

    if (!study) {
      return NextResponse.json(
        {
          error: 'Étude non trouvée ou non approuvée',
          code: 'STUDY_NOT_FOUND'
        },
        { status: 404 }
      );
    }

    // Vérifier que le hash fourni par le client correspond aux données reçues
    const expectedHash = await computeDatasetHash(patientId, studyId, measurements);
    if (datasetHash.toLowerCase() !== expectedHash.toLowerCase()) {
      return NextResponse.json(
        {
          error: 'Le hash du dataset ne correspond pas aux données fournies',
          code: 'HASH_MISMATCH'
        },
        { status: 400 }
      );
    }

    // Transaction pour créer la référence dataset et les mesures
    const result = await prisma.$transaction(async (tx: Prisma.TransactionClient) => {
      // Créer ou récupérer la référence dataset
      let datasetReference = await tx.datasetReference.findUnique({
        where: { datasetHash }
      });

      if (!datasetReference) {
        datasetReference = await tx.datasetReference.create({
          data: {
            datasetHash,
            patientId,
            studyId
          }
        });
      }

      // Créer les mesures
      const createdMeasurements = await Promise.all(
        measurements.map((measurement: MeasurementInput) =>
          tx.measurement.create({
            data: {
              datasetHash,
              measurementType: measurement.measurementType,
              value: measurement.value,
              timestamp: new Date(measurement.timestamp),
              mealContext: measurement.mealContext,
              labName: measurement.labName,
              deviceModel: measurement.deviceModel
            }
          })
        )
      );

      return {
        datasetReference,
        measurements: createdMeasurements
      };
    });

    return NextResponse.json({
      success: true,
      message: 'Mesures sauvegardées avec succès',
      datasetHash: result.datasetReference.datasetHash,
      measurementCount: result.measurements.length
    });

  } catch (error) {
    console.error('Erreur lors de la sauvegarde des mesures:', error);

    if (error instanceof z.ZodError) {
      return NextResponse.json(
        {
          error: 'Données invalides',
          code: 'VALIDATION_ERROR',
          details: error.errors
        },
        { status: 400 }
      );
    }

    return NextResponse.json(
      {
        error: 'Erreur lors de la sauvegarde des mesures',
        code: 'SAVE_MEASUREMENTS_ERROR'
      },
      { status: 500 }
    );
  }
}
