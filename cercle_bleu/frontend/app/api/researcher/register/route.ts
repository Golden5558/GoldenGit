import { NextRequest, NextResponse } from 'next/server';
import { z } from 'zod';
import { prisma } from '@/lib/prisma';
import { auth } from '@/lib/auth-config';

const registerResearcherSchema = z.object({
  firstName: z.string().min(1, 'Prénom requis').max(100),
  lastName: z.string().min(1, 'Nom requis').max(100),
  institution: z.string().max(255).optional(),
});

export async function POST(request: NextRequest) {
  try {
    const session = await auth();
    if (!session?.user?.email) {
      return NextResponse.json({ error: 'Not authenticated', code: 'AUTH_REQUIRED' }, { status: 401 });
    }

    const email = session.user.email.toLowerCase();
    const body = await request.json();
    const validatedData = registerResearcherSchema.parse(body);

    // If researcher already exists, return success (idempotent)
    const existing = await prisma.researcher.findUnique({ where: { email } });
    if (existing) {
      return NextResponse.json({
        success: true,
        message: 'Chercheur déjà enregistré',
        researcher: { id: existing.id, email: existing.email, firstName: existing.firstName, lastName: existing.lastName, institution: existing.institution, createdAt: existing.createdAt }
      });
    }

    const newResearcher = await prisma.researcher.create({
      data: {
        email,
        firstName: validatedData.firstName,
        lastName: validatedData.lastName,
        institution: validatedData.institution,
      }
    });

    return NextResponse.json({
      success: true,
      message: 'Chercheur enregistré avec succès',
      researcher: { id: newResearcher.id, email: newResearcher.email, firstName: newResearcher.firstName, lastName: newResearcher.lastName, institution: newResearcher.institution, createdAt: newResearcher.createdAt }
    }, { status: 201 });

  } catch (error) {
    console.error('Erreur lors de l\'enregistrement du chercheur:', error);
    if (error instanceof z.ZodError) {
      return NextResponse.json({ error: 'Données invalides', code: 'VALIDATION_ERROR', details: error.errors }, { status: 400 });
    }
    return NextResponse.json({ error: 'Erreur interne du serveur', code: 'INTERNAL_SERVER_ERROR' }, { status: 500 });
  }
}
