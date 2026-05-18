'use client';

import Image from "next/image";
import { useRouter } from 'next/navigation';
import { Button } from '@/components/ui/button';
import { useAuthContext } from '@/contexts/AuthContext';

const Header = () => {
  const { isAuthenticated, logout, sessionEmail, sessionName } = useAuthContext();
  const router = useRouter();

  const handleLogout = async () => { await logout(); };
  const displayName = sessionName ?? sessionEmail?.split('@')[0] ?? '';

  return (
    <header className="bg-gradient-to-r from-blue-600 to-blue-800 shadow-lg border-b-4 border-blue-900">
      <div className="container mx-auto px-6 py-4">
        <div className="flex justify-between items-center">
          <div className="flex items-center space-x-4">
            <div className="bg-white p-2 rounded-full shadow-md cursor-pointer" onClick={() => router.push('/')}>
              <Image src="/logo-cercle.png" alt="Cercle Bleu" width={50} height={50} />
            </div>
            <div>
              <h1 className="text-2xl font-bold text-white tracking-wide">Cercle Bleu</h1>
              <p className="text-blue-100 text-sm font-medium">Plateforme de santé</p>
            </div>
          </div>

          <div className="bg-white/10 backdrop-blur-sm rounded-lg p-1">
            {isAuthenticated ? (
              <div className="flex items-center gap-3">
                <span className="text-white text-sm">{displayName}</span>
                <Button variant="outline" size="sm" onClick={handleLogout}
                  className="bg-white/10 text-white border-white/30 hover:bg-white/20">
                  Déconnexion
                </Button>
              </div>
            ) : (
              <Button onClick={() => router.push('/login')}
                className="bg-white text-blue-700 hover:bg-blue-50 font-semibold">
                Se connecter
              </Button>
            )}
          </div>
        </div>
      </div>
    </header>
  );
};

export default Header;
