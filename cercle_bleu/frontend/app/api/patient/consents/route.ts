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

    if (authResult.user.userType !== 'patient') {
      return forbiddenResponse('Only patients can access their consents', 'ACCESS_DENIED');
    }

    const patientId = authResult.user.userId as number;

    const consents = await prisma.datasetReference.findMany({
      where: { patientId },
      include: {
        study: {
          select: { id: true, description: true, creator: { select: { firstName: true, lastName: true, institution: true } } }
        }
      },
      orderBy: { createdAt: 'desc' }
    });

    return NextResponse.json({
      success: true,
      consents: consents.map(c => ({
        datasetHash: c.datasetHash,
        studyId: c.studyId,
        studyDescription: c.study.description,
        studyCreator: c.study.creator,
        createdAt: c.createdAt.toISOString(),
        revokedAt: c.revokedAt ? c.revokedAt.toISOString() : null,
        isActive: c.revokedAt === null
      }))
    });
  } catch (error) {
    console.error('Erreur lors de la récupération des consentements:', error);
    return NextResponse.json(
      { error: 'Erreur interne du serveur', code: 'INTERNAL_SERVER_ERROR' },
      { status: 500 }
    );
  }
}
