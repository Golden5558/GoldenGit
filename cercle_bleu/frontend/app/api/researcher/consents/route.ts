import { NextRequest, NextResponse } from 'next/server';
import { prisma } from '@/lib/prisma';
import { verifyWalletAuth, forbiddenResponse } from '@/lib/auth';

export async function GET(request: NextRequest) {
  try {
    const authResult = await verifyWalletAuth(request);
    if (!authResult.success) {
      return NextResponse.json(
        { error: authResult.error, code: authResult.code },
        { status: authResult.status }
      );
    }

    if (authResult.user.userType !== 'researcher') {
      return forbiddenResponse('Only researchers can access this endpoint', 'ACCESS_DENIED');
    }

    const researcherId = authResult.user.userId as string;

    const datasets = await prisma.datasetReference.findMany({
      where: {
        revokedAt: null,
        study: { createdBy: researcherId, isApproved: true }
      },
      include: {
        patient: {
          select: { id: true, birthYear: true, weightKg: true, sex: true, diabeteType: true }
        },
        study: { select: { id: true, description: true } },
        measurements: true
      },
      orderBy: { createdAt: 'desc' }
    });

    return NextResponse.json({
      success: true,
      datasets: datasets.map(d => ({
        datasetHash: d.datasetHash,
        studyId: d.studyId,
        studyDescription: d.study.description,
        createdAt: d.createdAt.toISOString(),
        patient: {
          id: d.patient.id,
          birthYear: d.patient.birthYear,
          weightKg: d.patient.weightKg ? Number(d.patient.weightKg) : undefined,
          sex: d.patient.sex,
          diabeteType: d.patient.diabeteType
        },
        measurements: d.measurements.map(m => ({
          id: m.id,
          measurementType: m.measurementType,
          value: Number(m.value),
          timestamp: m.timestamp.toISOString(),
          mealContext: m.mealContext,
          labName: m.labName,
          deviceModel: m.deviceModel
        }))
      }))
    });
  } catch (error) {
    console.error('Erreur lors de la récupération des datasets chercheur:', error);
    return NextResponse.json(
      { error: 'Erreur interne du serveur', code: 'INTERNAL_SERVER_ERROR' },
      { status: 500 }
    );
  }
}
