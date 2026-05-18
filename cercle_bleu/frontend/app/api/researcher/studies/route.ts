import { NextRequest, NextResponse } from 'next/server';
import { z } from 'zod';
import { prisma } from '@/lib/prisma';
import { verifyWalletAuth, forbiddenResponse } from '@/lib/auth';

// Schéma de validation pour la création d'une étude
const createStudySchema = z.object({
  description: z.string().min(1, 'La description est requise').max(5000, 'Description trop longue'),
  protocolUrl: z.string().url('URL de protocole invalide').max(512, 'URL trop longue').optional().nullable(),
  isApproved: z.boolean().optional().default(false),
  creatorAddress: z.string().regex(/^0x[a-fA-F0-9]{40}$/, 'Adresse wallet invalide')
});


type StudyWithDetails = {
  id: number;
  description: string | null;
  protocolUrl: string | null;
  isApproved: boolean;
  createdAt: Date;
  creator: {
    firstName: string;
    lastName: string;
    institution: string | null;
  };
  _count: {
    datasetReferences: number;
    researcherStudies: number;
  };
};

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

    // Only researchers can create studies
    if (authResult.user.userType !== 'researcher') {
      return forbiddenResponse('Only researchers can create studies', 'ACCESS_DENIED');
    }

    const body = await request.json();

    // Validation des données
    const validatedData = createStudySchema.parse(body);

    // Verify the creator address matches the authenticated researcher
    if (validatedData.creatorAddress.toLowerCase() !== authResult.user.walletAddress.toLowerCase()) {
      return forbiddenResponse(
        'You can only create studies under your own wallet address',
        'WALLET_MISMATCH'
      );
    }

    // Trouver le chercheur par son adresse wallet
    const researcher = await prisma.researcher.findUnique({
      where: { walletAddress: validatedData.creatorAddress.toLowerCase() }
    });

    if (!researcher) {
      return NextResponse.json(
        {
          error: 'Chercheur non trouvé pour cette adresse wallet',
          code: 'RESEARCHER_NOT_FOUND'
        },
        { status: 404 }
      );
    }

    // Créer la nouvelle étude
    const newStudy = await prisma.study.create({
      data: {
        description: validatedData.description,
        protocolUrl: validatedData.protocolUrl,
        createdBy: researcher.id,
        isApproved: validatedData.isApproved || false
      },
      include: {
        creator: {
          select: {
            id: true,
            firstName: true,
            lastName: true,
            institution: true
          }
        }
      }
    });

    return NextResponse.json(
      {
        success: true,
        message: 'Étude créée avec succès',
        study: {
          id: newStudy.id,
          description: newStudy.description,
          protocolUrl: newStudy.protocolUrl,
          isApproved: newStudy.isApproved,
          createdAt: newStudy.createdAt,
          creator: newStudy.creator
        }
      },
      { status: 201 }
    );

  } catch (error) {
    console.error('Erreur lors de la création de l\'étude:', error);

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

    if (error instanceof Error && 'code' in error) {
      // Gestion des erreurs Prisma spécifiques
      if (error.code === 'P2003') {
        return NextResponse.json(
          {
            error: 'Chercheur non trouvé',
            code: 'FOREIGN_KEY_CONSTRAINT'
          },
          { status: 400 }
        );
      }
    }

    return NextResponse.json(
      {
        error: 'Erreur interne du serveur',
        code: 'INTERNAL_SERVER_ERROR'
      },
      { status: 500 }
    );
  }
}

// Endpoint GET pour récupérer les études d'un chercheur
export async function GET(request: NextRequest) {
  try {
    // Authenticate the request
    const authResult = await verifyWalletAuth(request);
    if (!authResult.success) {
      return NextResponse.json(
        { error: authResult.error, code: authResult.code },
        { status: authResult.status }
      );
    }

    // Only researchers can access this endpoint
    if (authResult.user.userType !== 'researcher') {
      return forbiddenResponse('Only researchers can access study lists', 'ACCESS_DENIED');
    }

    const { searchParams } = new URL(request.url);
    const researcherId = searchParams.get('researcherId');

    if (!researcherId) {
      return NextResponse.json(
        {
          error: 'ID chercheur requis',
          code: 'RESEARCHER_ID_REQUIRED'
        },
        { status: 400 }
      );
    }

    // Validation de l'UUID
    if (!z.string().uuid().safeParse(researcherId).success) {
      return NextResponse.json(
        {
          error: 'ID chercheur invalide',
          code: 'INVALID_RESEARCHER_ID'
        },
        { status: 400 }
      );
    }

    // Verify the researcher is accessing their own studies
    if (authResult.user.userId !== researcherId) {
      return forbiddenResponse('You can only access your own studies', 'ACCESS_DENIED');
    }

    // Récupérer les études du chercheur
    const studies = await prisma.study.findMany({
      where: {
        createdBy: researcherId
      },
      include: {
        creator: {
          select: {
            firstName: true,
            lastName: true,
            institution: true
          }
        },
        _count: {
          select: {
            datasetReferences: true,
            researcherStudies: true
          }
        }
      },
      orderBy: {
        createdAt: 'desc'
      }
    });

    return NextResponse.json(
      {
        success: true,
        studies: studies.map((study: StudyWithDetails) => ({
          id: study.id,
          description: study.description,
          protocolUrl: study.protocolUrl,
          isApproved: study.isApproved,
          createdAt: study.createdAt,
          creator: study.creator,
          datasetCount: study._count.datasetReferences,
          collaboratorCount: study._count.researcherStudies
        }))
      },
      { status: 200 }
    );

  } catch (error) {
    console.error('Erreur lors de la récupération des études:', error);

    return NextResponse.json(
      {
        error: 'Erreur interne du serveur',
        code: 'INTERNAL_SERVER_ERROR'
      },
      { status: 500 }
    );
  }
}
