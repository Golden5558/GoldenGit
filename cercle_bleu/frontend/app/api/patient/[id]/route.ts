import { NextRequest, NextResponse } from 'next/server';
import { z } from 'zod';
import { prisma } from '@/lib/prisma';
import { verifyWalletAuth, verifyPatientOwnership, forbiddenResponse } from '@/lib/auth';

// Schéma de validation pour la mise à jour d'un patient
const updatePatientSchema = z.object({
  firstName: z.string().min(1).max(50),
  lastName: z.string().min(1).max(50),
  email: z.string().email(),
  birthYear: z.number().int().min(1900).max(new Date().getFullYear()),
  weightKg: z.number().positive(),
  sex: z.enum(['M', 'F']),
  diabeteType: z.enum(['TYPE_1', 'TYPE_2'])
});

// GET - Récupérer un patient par ID
export async function GET(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    // Authenticate the request
    const authResult = await verifyWalletAuth(request);
    if (!authResult.success) {
      return NextResponse.json(
        { error: authResult.error, code: authResult.code },
        { status: authResult.status }
      );
    }

    // Attendre les paramètres avant de les utiliser
    const { id } = await params;
    const patientId = parseInt(id);

    if (isNaN(patientId)) {
      return NextResponse.json(
        {
          error: 'ID patient invalide',
          code: 'INVALID_PATIENT_ID'
        },
        { status: 400 }
      );
    }

    // Verify ownership - users can only access their own data
    const ownership = await verifyPatientOwnership(authResult.user, patientId);
    if (!ownership.authorized) {
      return forbiddenResponse(ownership.error || 'Access denied', 'ACCESS_DENIED');
    }

    const patient = await prisma.patient.findUnique({
      where: { id: patientId },
      include: {
        datasetReferences: {
          include: {
            study: true,
            measurements: {
              take: 10,
              orderBy: { timestamp: 'desc' }
            }
          }
        }
      }
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

    return NextResponse.json({
      success: true,
      patient: {
        id: patient.id,
        walletAddress: patient.walletAddress,
        firstName: patient.firstName,
        lastName: patient.lastName,
        email: patient.email,
        birthYear: patient.birthYear,
        weightKg: patient.weightKg,
        sex: patient.sex,
        diabeteType: patient.diabeteType,
        createdAt: patient.createdAt,
        datasetReferences: patient.datasetReferences
      }
    });

  } catch (error) {
    console.error('Erreur lors de la récupération du patient:', error);
    return NextResponse.json(
      {
        error: 'Erreur interne du serveur',
        code: 'INTERNAL_SERVER_ERROR'
      },
      { status: 500 }
    );
  }
}

// PUT - Mettre à jour un patient
export async function PUT(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    // Authenticate the request
    const authResult = await verifyWalletAuth(request);
    if (!authResult.success) {
      return NextResponse.json(
        { error: authResult.error, code: authResult.code },
        { status: authResult.status }
      );
    }

    // Attendre les paramètres avant de les utiliser
    const { id } = await params;
    const patientId = parseInt(id);

    if (isNaN(patientId)) {
      return NextResponse.json(
        {
          error: 'ID patient invalide',
          code: 'INVALID_PATIENT_ID'
        },
        { status: 400 }
      );
    }

    // Verify ownership - users can only modify their own data
    const ownership = await verifyPatientOwnership(authResult.user, patientId);
    if (!ownership.authorized) {
      return forbiddenResponse(ownership.error || 'Access denied', 'ACCESS_DENIED');
    }

    const body = await request.json();
    const validatedData = updatePatientSchema.parse(body);

    // Vérifier si le patient existe
    const existingPatient = await prisma.patient.findUnique({
      where: { id: patientId }
    });

    if (!existingPatient) {
      return NextResponse.json(
        {
          error: 'Patient non trouvé',
          code: 'PATIENT_NOT_FOUND'
        },
        { status: 404 }
      );
    }

    const updatedPatient = await prisma.patient.update({
      where: { id: patientId },
      data: validatedData
    });

    return NextResponse.json({
      success: true,
      message: 'Patient mis à jour avec succès',
      patient: {
        id: updatedPatient.id,
        walletAddress: updatedPatient.walletAddress,
        firstName: updatedPatient.firstName,
        lastName: updatedPatient.lastName,
        email: updatedPatient.email,
        birthYear: updatedPatient.birthYear,
        weightKg: updatedPatient.weightKg,
        sex: updatedPatient.sex,
        diabeteType: updatedPatient.diabeteType,
        createdAt: updatedPatient.createdAt
      }
    });

  } catch (error) {
    console.error('Erreur lors de la mise à jour du patient:', error);

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
        error: 'Erreur interne du serveur',
        code: 'INTERNAL_SERVER_ERROR'
      },
      { status: 500 }
    );
  }
}

// DELETE - Supprimer un patient
export async function DELETE(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    // Authenticate the request
    const authResult = await verifyWalletAuth(request);
    if (!authResult.success) {
      return NextResponse.json(
        { error: authResult.error, code: authResult.code },
        { status: authResult.status }
      );
    }

    // Attendre les paramètres avant de les utiliser
    const { id } = await params;
    const patientId = parseInt(id);

    if (isNaN(patientId)) {
      return NextResponse.json(
        {
          error: 'ID patient invalide',
          code: 'INVALID_PATIENT_ID'
        },
        { status: 400 }
      );
    }

    // Verify ownership - users can only delete their own account
    const ownership = await verifyPatientOwnership(authResult.user, patientId);
    if (!ownership.authorized) {
      return forbiddenResponse(ownership.error || 'Access denied', 'ACCESS_DENIED');
    }

    // Vérifier si le patient existe
    const existingPatient = await prisma.patient.findUnique({
      where: { id: patientId }
    });

    if (!existingPatient) {
      return NextResponse.json(
        {
          error: 'Patient non trouvé',
          code: 'PATIENT_NOT_FOUND'
        },
        { status: 404 }
      );
    }

    await prisma.patient.delete({
      where: { id: patientId }
    });

    return NextResponse.json({
      success: true,
      message: 'Patient supprimé avec succès'
    });

  } catch (error) {
    console.error('Erreur lors de la suppression du patient:', error);

    if ((error as { code?: string }).code === 'P2003') {
      return NextResponse.json(
        {
          error: 'Impossible de supprimer - Le patient a des données associées',
          code: 'FOREIGN_KEY_CONSTRAINT'
        },
        { status: 409 }
      );
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
