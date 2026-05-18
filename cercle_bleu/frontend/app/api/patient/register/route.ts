import { NextRequest, NextResponse } from 'next/server';
import { z } from 'zod';
import { prisma } from '@/lib/prisma';
import { auth } from '@/lib/auth-config';

const registerPatientSchema = z.object({
  firstName: z.string().min(1).max(50),
  lastName: z.string().min(1).max(50),
  birthYear: z.number().int().min(1900).max(new Date().getFullYear()).optional(),
  weightKg: z.number().positive().optional(),
  sex: z.enum(['M', 'F']).optional(),
  diabeteType: z.enum(['TYPE_1', 'TYPE_2']).optional()
});

export async function POST(request: NextRequest) {
  try {
    const session = await auth();
    if (!session?.user?.email) {
      return NextResponse.json({ error: 'Not authenticated', code: 'AUTH_REQUIRED' }, { status: 401 });
    }

    const email = session.user.email.toLowerCase();
    const body = await request.json();
    const validatedData = registerPatientSchema.parse(body);

    // If patient already exists, return success (idempotent)
    const existing = await prisma.patient.findUnique({ where: { email } });
    if (existing) {
      return NextResponse.json({
        success: true,
        message: 'Patient déjà enregistré',
        patient: { id: existing.id, email: existing.email, firstName: existing.firstName, lastName: existing.lastName, createdAt: existing.createdAt }
      });
    }

    const newPatient = await prisma.patient.create({
      data: {
        email,
        firstName: validatedData.firstName,
        lastName: validatedData.lastName,
        birthYear: validatedData.birthYear,
        weightKg: validatedData.weightKg,
        sex: validatedData.sex,
        diabeteType: validatedData.diabeteType
      }
    });

    return NextResponse.json({
      success: true,
      message: 'Patient enregistré avec succès',
      patient: { id: newPatient.id, email: newPatient.email, firstName: newPatient.firstName, lastName: newPatient.lastName, createdAt: newPatient.createdAt }
    }, { status: 201 });

  } catch (error) {
    console.error('Erreur lors de l\'enregistrement du patient:', error);
    if (error instanceof z.ZodError) {
      return NextResponse.json({ error: 'Données invalides', code: 'VALIDATION_ERROR', details: error.errors }, { status: 400 });
    }
    return NextResponse.json({ error: 'Erreur interne du serveur', code: 'INTERNAL_SERVER_ERROR' }, { status: 500 });
  }
}
