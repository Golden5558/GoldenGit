import { NextRequest, NextResponse } from 'next/server';
import { prisma } from '@/lib/prisma';
import { verifyWalletAuth, forbiddenResponse } from '@/lib/auth';

export async function POST(
  request: NextRequest,
  { params }: { params: Promise<{ hash: string }> }
) {
  try {
    const authResult = await verifyWalletAuth(request);
    if (!authResult.success) {
      return NextResponse.json(
        { error: authResult.error, code: authResult.code },
        { status: authResult.status }
      );
    }

    if (authResult.user.userType !== 'patient') {
      return forbiddenResponse('Only patients can revoke their consents', 'ACCESS_DENIED');
    }

    const { hash } = await params;
    const patientId = authResult.user.userId as number;

    const consent = await prisma.datasetReference.findUnique({
      where: { datasetHash: hash }
    });

    if (!consent) {
      return NextResponse.json(
        { error: 'Consentement non trouvé', code: 'CONSENT_NOT_FOUND' },
        { status: 404 }
      );
    }

    if (consent.patientId !== patientId) {
      return forbiddenResponse('You can only revoke your own consents', 'ACCESS_DENIED');
    }

    if (consent.revokedAt !== null) {
      return NextResponse.json(
        { error: 'Ce consentement est déjà révoqué', code: 'ALREADY_REVOKED' },
        { status: 409 }
      );
    }

    const updated = await prisma.datasetReference.update({
      where: { datasetHash: hash },
      data: { revokedAt: new Date() }
    });

    return NextResponse.json({
      success: true,
      revokedAt: updated.revokedAt!.toISOString()
    });
  } catch (error) {
    console.error('Erreur lors de la révocation du consentement:', error);
    return NextResponse.json(
      { error: 'Erreur interne du serveur', code: 'INTERNAL_SERVER_ERROR' },
      { status: 500 }
    );
  }
}
