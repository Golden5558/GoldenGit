import { Card, CardContent, CardDescription, CardHeader, CardTitle } from '@/components/ui/card';
import { Mail } from 'lucide-react';
import Link from 'next/link';
import Image from 'next/image';

export default function VerifyPage() {
  return (
    <div className="min-h-screen bg-gradient-to-br from-blue-50 to-indigo-100 flex items-center justify-center p-4">
      <Card className="w-full max-w-sm shadow-xl text-center">
        <CardHeader className="pb-4">
          <div className="flex justify-center mb-4">
            <div className="bg-white p-3 rounded-full shadow-md">
              <Image src="/logo-cercle.png" alt="Cercle Bleu" width={56} height={56} />
            </div>
          </div>
          <div className="w-16 h-16 bg-blue-100 rounded-full flex items-center justify-center mx-auto mb-2">
            <Mail className="w-8 h-8 text-blue-600" />
          </div>
          <CardTitle className="text-xl">Vérifiez votre boîte mail</CardTitle>
          <CardDescription className="text-base">
            Un lien de connexion vous a été envoyé.<br />
            Cliquez dessus pour accéder à votre espace.
          </CardDescription>
        </CardHeader>
        <CardContent>
          <p className="text-sm text-gray-500 mb-4">
            Le lien expire dans 24 heures. Si vous ne le trouvez pas, vérifiez vos spams.
          </p>
          <Link href="/login" className="text-sm text-blue-600 hover:underline">
            ← Utiliser une autre adresse
          </Link>
        </CardContent>
      </Card>
    </div>
  );
}
