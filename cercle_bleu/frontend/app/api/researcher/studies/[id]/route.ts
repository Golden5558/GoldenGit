import { NextRequest, NextResponse } from 'next/server';
import { z } from 'zod';
import { prisma } from '@/lib/prisma';
import { verifyWalletAuth, forbiddenResponse } from '@/lib/auth';

const patchStudySchema = z.object({
  onChainStudyId: z.number().int().positive()
});

export async function PATCH(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    const authResult = await verifyWalletAuth(request);
    if (!authResult.success) {
      return NextResponse.json(
        { error: authResult.error, code: authResult.code },
        { status: authResult.status }
      );
    }

    if (authResult.user.userType !== 'researcher') {
      return forbiddenResponse('Only researchers can update study authorization', 'ACCESS_DENIED');
    }

    const { id } = await params;
    const studyDbId = parseInt(id);
    if (isNaN(studyDbId)) {
      return NextResponse.json({ error: 'ID d\'étude invalide', code: 'INVALID_STUDY_ID' }, { status: 400 });
    }

    const body = await request.json();
    const { onChainStudyId } = patchStudySchema.parse(body);

    // Verify the study belongs to the authenticated researcher
    const study = await prisma.study.findUnique({
      where: { id: studyDbId },
      include: { creator: { select: { walletAddress: true } } }
    });

    if (!study) {
      return NextResponse.json({ error: 'Étude non trouvée', code: 'STUDY_NOT_FOUND' }, { status: 404 });
    }

    if (study.creator.walletAddress.toLowerCase() !== authResult.user.walletAddress.toLowerCase()) {
      return forbiddenResponse('You can only update your own studies', 'ACCESS_DENIED');
    }

    const updated = await prisma.study.update({
      where: { id: studyDbId },
      data: { onChainStudyId }
    });

    return NextResponse.json({
      success: true,
      study: { id: updated.id, onChainStudyId: updated.onChainStudyId }
    });

  } catch (error) {
    if (error instanceof z.ZodError) {
      return NextResponse.json(
        { error: 'Données invalides', code: 'VALIDATION_ERROR', details: error.errors },
        { status: 400 }
      );
    }
    console.error('Erreur lors de la mise à jour de l\'étude:', error);
    return NextResponse.json(
      { error: 'Erreur interne du serveur', code: 'INTERNAL_SERVER_ERROR' },
      { status: 500 }
    );
  }
}
