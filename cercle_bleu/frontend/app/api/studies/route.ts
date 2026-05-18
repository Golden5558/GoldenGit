import { NextResponse } from 'next/server';
import { prisma } from '@/lib/prisma';

// GET - List all approved studies (public endpoint for patients to see available studies)
// This endpoint does NOT require authentication as it's a public listing
// of approved studies that patients can browse before consenting
export async function GET() {
  try {
    const studies = await prisma.study.findMany({
      where: {
        isApproved: true
      },
      select: {
        id: true,
        description: true,
        createdAt: true,
        creator: {
          select: {
            firstName: true,
            lastName: true,
            institution: true
          }
        }
      },
      orderBy: {
        createdAt: 'desc'
      }
    });

    return NextResponse.json({
      success: true,
      studies
    });
  } catch (error) {
    console.error('Erreur lors de la récupération des études:', error);
    return NextResponse.json(
      {
        error: 'Erreur lors de la récupération des études',
        code: 'FETCH_STUDIES_ERROR'
      },
      { status: 500 }
    );
  }
}
