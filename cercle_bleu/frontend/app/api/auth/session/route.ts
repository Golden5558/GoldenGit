import { NextResponse } from 'next/server';

// Session management is handled by NextAuth at /api/auth/[...nextauth]
export async function POST() {
  return NextResponse.json({ error: 'Use NextAuth session' }, { status: 410 });
}

export async function DELETE() {
  return NextResponse.json({ error: 'Use NextAuth signOut' }, { status: 410 });
}
