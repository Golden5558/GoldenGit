'use client';

import { Button } from '@/components/ui/button';
import { Heart, Shield, Database, Search, Lock, Eye, ArrowRight } from 'lucide-react';
import { useRouter } from 'next/navigation';
import { useEffect } from 'react';
import { useAuthContext } from '@/contexts/AuthContext';
import { useRoleIntent, getRoleIntent, clearRoleIntent } from '@/hooks/useRoleIntent';

export default function WelcomePage() {
  const router = useRouter();
  const { userType, isLoadingUser, isAuthenticated } = useAuthContext();
  const { setRoleIntent } = useRoleIntent();

  useEffect(() => {
    if (userType === 'patient') {
      clearRoleIntent();
      router.push('/patient/dashboard');
    } else if (userType === 'researcher') {
      clearRoleIntent();
      router.push('/researcher/dashboard');
    } else if (isAuthenticated && !isLoadingUser) {
      const intent = getRoleIntent();
      if (intent) {
        clearRoleIntent();
        router.push(intent === 'patient' ? '/patient/profile' : '/researcher/profile');
      }
    }
  }, [userType, router, isAuthenticated, isLoadingUser]);

  const handleRoleSelect = (role: 'patient' | 'researcher') => {
    if (!isAuthenticated) {
      setRoleIntent(role);
      router.push('/login');
    } else {
      router.push(role === 'patient' ? '/patient/profile' : '/researcher/profile');
    }
  };

  return (
    <div className="min-h-screen bg-gradient-to-br from-blue-50 to-indigo-100">

      {/* Hero — emotional hook + early dual CTA */}
      <section className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-20">
        <div className="text-center mb-12">
          <h1 className="text-5xl font-bold text-gray-900 mb-6 leading-tight">
            Vos données de santé vous appartiennent.<br />
            <span className="text-blue-600">Pas à votre hôpital. Pas à un laboratoire. À vous.</span><br />
            <span className="text-indigo-500 text-3xl">Pour accéder, en avant-première, aux soins innovants faits pour vous.</span>
          </h1>
          <p className="text-xl text-gray-600 max-w-3xl mx-auto mb-10">
            Participer à la recherche clinique quand on vit avec le diabète, c&apos;est compliqué.
            Les protocoles, les consentements, les données à fournir — chaque étape est un obstacle.
            Cercle Bleu est votre facilitateur : il simplifie chaque démarche pour que vous contribuiez à la science qui vous concerne
            et accédiez en avant-première aux thérapies et soins adaptés à votre profil.
          </p>
          <div className="flex flex-col sm:flex-row gap-4 justify-center">
            <Button
              onClick={() => handleRoleSelect('patient')}
              size="lg"
              className="bg-blue-600 hover:bg-blue-700 text-white font-semibold px-8 py-4 text-lg rounded-xl shadow-lg flex items-center gap-2"
            >
              Je suis patient diabétique
              <ArrowRight className="w-5 h-5" />
            </Button>
            <Button
              onClick={() => handleRoleSelect('researcher')}
              size="lg"
              variant="outline"
              className="border-2 border-purple-600 text-purple-700 hover:bg-purple-50 font-semibold px-8 py-4 text-lg rounded-xl flex items-center gap-2"
            >
              Je suis chercheur
              <ArrowRight className="w-5 h-5" />
            </Button>
          </div>
        </div>
      </section>

      {/* Role value props — empathy-first headings, tokens framed as recognition */}
      <section className="bg-white py-16">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
          <div className="grid md:grid-cols-2 gap-12">

            {/* Patient card */}
            <div className="border-2 border-blue-200 rounded-xl p-8 bg-blue-50">
              <div className="flex items-center mb-6">
                <div className="w-12 h-12 bg-blue-600 rounded-lg flex items-center justify-center mr-4">
                  <Heart className="w-6 h-6 text-white" />
                </div>
                <div>
                  <p className="text-xs font-semibold text-blue-600 uppercase tracking-wide">Vous êtes patient diabétique</p>
                  <h3 className="text-2xl font-bold text-gray-900">Votre facilitateur de recherche clinique</h3>
                </div>
              </div>

              <p className="text-gray-700 mb-4">
                Participer à un essai clinique quand on est diabétique, c&apos;est compliqué. Cercle Bleu prend en charge toute la complexité — pour que vous puissiez vous concentrer sur l&apos;essentiel : votre santé.
              </p>

              <p className="text-xs font-semibold text-blue-700 uppercase tracking-wide mb-3">Ce que vous obtenez concrètement</p>
              <ul className="space-y-3 mb-6">
                <li className="flex items-start">
                  <span className="text-blue-600 mr-2 mt-0.5">✓</span>
                  <span className="text-gray-700"><strong>Accédez en avant-première à des soins innovants</strong> adaptés à votre profil — thérapies émergentes, protocoles personnalisés, dispositifs de nouvelle génération.</span>
                </li>
                <li className="flex items-start">
                  <span className="text-blue-600 mr-2 mt-0.5">✓</span>
                  <span className="text-gray-700"><strong>Participez à la recherche en quelques clics</strong> — Cercle Bleu gère les consentements, les protocoles et le partage de données à votre place.</span>
                </li>
                <li className="flex items-start">
                  <span className="text-blue-600 mr-2 mt-0.5">✓</span>
                  <span className="text-gray-700"><strong>Comparez vos indicateurs à des patients aux profils similaires</strong> pour anticiper les risques et agir en amont des complications.</span>
                </li>
                <li className="flex items-start">
                  <span className="text-blue-600 mr-2 mt-0.5">✓</span>
                  <span className="text-gray-700"><strong>Chaque contribution est reconnue</strong> par des points CERCLE qui débloquent l&apos;accès à votre benchmark de cohorte et des avantages non-monétaires.</span>
                </li>
              </ul>

              <Button
                onClick={() => handleRoleSelect('patient')}
                className="w-full bg-blue-600 hover:bg-blue-700 text-white font-semibold py-3 rounded-xl flex items-center justify-center gap-2"
              >
                Commencer en tant que patient
                <ArrowRight className="w-4 h-4" />
              </Button>
            </div>

            {/* Researcher card */}
            <div className="border-2 border-purple-200 rounded-xl p-8 bg-purple-50">
              <div className="flex items-center mb-6">
                <div className="w-12 h-12 bg-purple-600 rounded-lg flex items-center justify-center mr-4">
                  <Search className="w-6 h-6 text-white" />
                </div>
                <div>
                  <p className="text-xs font-semibold text-purple-600 uppercase tracking-wide">Vous êtes chercheur</p>
                  <h3 className="text-2xl font-bold text-gray-900">Des cohortes prêtes à l&apos;emploi</h3>
                </div>
              </div>

              <p className="text-gray-700 mb-4">
                Des données longitudinales du quotidien, une validation éthique intégrée, un recrutement qui prend des semaines — pas des années.
              </p>

              <p className="text-xs font-semibold text-purple-700 uppercase tracking-wide mb-3">Ce que vous obtenez concrètement</p>
              <ul className="space-y-3 mb-6">
                <li className="flex items-start">
                  <span className="text-purple-600 mr-2 mt-0.5">✓</span>
                  <span className="text-gray-700"><strong>Accédez à des cohortes anonymisées</strong> de patients consentants — glycémie continue, HbA1c, alimentation, activité physique, comorbidités — pour des études impossibles à construire autrement.</span>
                </li>
                <li className="flex items-start">
                  <span className="text-purple-600 mr-2 mt-0.5">✓</span>
                  <span className="text-gray-700"><strong>Créez une étude en quelques jours</strong> : publiez votre protocole, laissez les patients consentants s&apos;auto-sélectionner — là où le recrutement classique prend des années.</span>
                </li>
                <li className="flex items-start">
                  <span className="text-purple-600 mr-2 mt-0.5">✓</span>
                  <span className="text-gray-700"><strong>Chaque consentement est traçable par contrat</strong> : déclenché programmatiquement via smart contract, enregistré sur la blockchain et vérifiable à tout moment.</span>
                </li>
                <li className="flex items-start">
                  <span className="text-purple-600 mr-2 mt-0.5">✓</span>
                  <span className="text-gray-700"><strong>Accélérez la validation translationnelle</strong> : testez vos hypothèses directement sur des données de vie réelle, sans les coûts et délais des études cliniques classiques.</span>
                </li>
              </ul>

              <Button
                onClick={() => handleRoleSelect('researcher')}
                className="w-full bg-purple-600 hover:bg-purple-700 text-white font-semibold py-3 rounded-xl flex items-center justify-center gap-2"
              >
                Accéder en tant que chercheur
                <ArrowRight className="w-4 h-4" />
              </Button>
            </div>
          </div>
        </div>
      </section>

      {/* How it works — moved above CTA, step 4 rewritten */}
      <section className="py-16 max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <h2 className="text-3xl font-bold text-center text-gray-900 mb-12">
          Comment ça marche ?
        </h2>

        <div className="grid md:grid-cols-4 gap-8">
          <div className="text-center">
            <div className="w-16 h-16 bg-blue-600 text-white rounded-full flex items-center justify-center mx-auto mb-4 text-2xl font-bold">
              1
            </div>
            <h4 className="font-semibold text-gray-900 mb-2">Connexion</h4>
            <p className="text-gray-600 text-sm">
              Connectez-vous avec votre email ou Google — aucun wallet requis pour commencer.
            </p>
          </div>

          <div className="text-center">
            <div className="w-16 h-16 bg-blue-600 text-white rounded-full flex items-center justify-center mx-auto mb-4 text-2xl font-bold">
              2
            </div>
            <h4 className="font-semibold text-gray-900 mb-2">Votre profil</h4>
            <p className="text-gray-600 text-sm">
              Choisissez votre rôle et complétez votre profil. Votre identité est enregistrée sur la blockchain — vous en restez propriétaire.
            </p>
          </div>

          <div className="text-center">
            <div className="w-16 h-16 bg-blue-600 text-white rounded-full flex items-center justify-center mx-auto mb-4 text-2xl font-bold">
              3
            </div>
            <h4 className="font-semibold text-gray-900 mb-2">Consentement</h4>
            <p className="text-gray-600 text-sm">
              Choisissez les études auxquelles vous participez. Chaque consentement est révocable et tracé de façon transparente.
            </p>
          </div>

          <div className="text-center">
            <div className="w-16 h-16 bg-blue-600 text-white rounded-full flex items-center justify-center mx-auto mb-4 text-2xl font-bold">
              4
            </div>
            <h4 className="font-semibold text-gray-900 mb-2">Contribution</h4>
            <p className="text-gray-600 text-sm">
              Vos premières données alimentent la recherche. Vos premiers CERCLE sont attribués. Vous devenez co-acteur de la science qui vous concerne.
            </p>
          </div>
        </div>
      </section>

      {/* Trust section — reframed from developer terms to patient-centered outcomes */}
      <section className="bg-gradient-to-r from-blue-600 to-indigo-700 py-16">
        <div className="max-w-4xl mx-auto px-4 sm:px-6 lg:px-8 text-center text-white">
          <h2 className="text-3xl font-bold mb-3">Pourquoi vous pouvez nous faire confiance ?</h2>
          <p className="text-blue-100 mb-10 text-lg">La confiance ne se déclare pas — elle se prouve. Voici comment.</p>
          <div className="grid md:grid-cols-3 gap-8">
            <div>
              <Eye className="w-12 h-12 mx-auto mb-4" />
              <h4 className="font-semibold mb-2">Vous savez toujours qui consulte vos données</h4>
              <p className="text-blue-100 text-sm">
                Chaque accès est enregistré de façon permanente et publique. Aucun accès silencieux, aucune opacité.
              </p>
            </div>
            <div>
              <Shield className="w-12 h-12 mx-auto mb-4" />
              <h4 className="font-semibold mb-2">Personne ne peut modifier votre consentement sans vous</h4>
              <p className="text-blue-100 text-sm">
                Votre accord est gravé dans un contrat immuable. Ni l&apos;hôpital, ni le chercheur, ni nous ne pouvons le contourner.
              </p>
            </div>
            <div>
              <Lock className="w-12 h-12 mx-auto mb-4" />
              <h4 className="font-semibold mb-2">Vous révoquez l&apos;accès en un clic, à tout moment</h4>
              <p className="text-blue-100 text-sm">
                Le consentement n&apos;est pas définitif. Vous changez d&apos;avis — l&apos;accès est coupé immédiatement, sans justification à fournir.
              </p>
            </div>
          </div>
        </div>
      </section>

      {/* Loading / role picker fallback for edge cases */}
      {isLoadingUser ? (
        <section className="py-16 text-center">
          <div className="max-w-2xl mx-auto px-4">
            <div className="bg-white rounded-2xl shadow-xl p-12">
              <div className="animate-spin rounded-full h-16 w-16 border-b-4 border-blue-600 mx-auto mb-6"></div>
              <h3 className="text-2xl font-semibold text-gray-900 mb-2">
                Vérification de votre profil...
              </h3>
              <p className="text-gray-600">
                Nous vérifions si vous êtes déjà enregistré
              </p>
            </div>
          </div>
        </section>
      ) : isAuthenticated && !userType ? (
        <section className="py-16">
          <div className="max-w-4xl mx-auto px-4">
            <div className="bg-gradient-to-r from-blue-600 to-indigo-700 rounded-2xl shadow-2xl p-8 md:p-12 text-center text-white">
              <h2 className="text-3xl md:text-4xl font-bold mb-4">
                Connecté avec succès !
              </h2>
              <p className="text-xl mb-8 text-blue-100">
                Choisissez votre rôle pour commencer votre parcours sur Cercle Bleu
              </p>

              <div className="grid md:grid-cols-2 gap-6 max-w-3xl mx-auto">
                <button
                  onClick={() => router.push('/patient/profile')}
                  className="bg-white text-gray-900 rounded-xl p-6 hover:shadow-2xl transition-all transform hover:scale-105 group"
                >
                  <div className="flex items-center justify-center mb-3">
                    <div className="w-12 h-12 bg-blue-100 rounded-lg flex items-center justify-center">
                      <Database className="w-6 h-6 text-blue-600" />
                    </div>
                  </div>
                  <h3 className="text-xl font-bold mb-2">Je suis un patient</h3>
                  <p className="text-gray-600 text-sm mb-4">
                    Gérez vos données médicales et participez à la recherche
                  </p>
                  <div className="flex items-center justify-center text-blue-600 font-semibold group-hover:translate-x-1 transition-transform">
                    Commencer
                    <ArrowRight className="w-4 h-4 ml-2" />
                  </div>
                </button>

                <button
                  onClick={() => router.push('/researcher/profile')}
                  className="bg-white text-gray-900 rounded-xl p-6 hover:shadow-2xl transition-all transform hover:scale-105 group"
                >
                  <div className="flex items-center justify-center mb-3">
                    <div className="w-12 h-12 bg-purple-100 rounded-lg flex items-center justify-center">
                      <Search className="w-6 h-6 text-purple-600" />
                    </div>
                  </div>
                  <h3 className="text-xl font-bold mb-2">Je suis un chercheur</h3>
                  <p className="text-gray-600 text-sm mb-4">
                    Accédez aux données et créez des études de recherche
                  </p>
                  <div className="flex items-center justify-center text-purple-600 font-semibold group-hover:translate-x-1 transition-transform">
                    Commencer
                    <ArrowRight className="w-4 h-4 ml-2" />
                  </div>
                </button>
              </div>

              <div className="mt-8 pt-6 border-t border-blue-500">
                <p className="text-sm text-blue-100">
                  Vous avez déjà un compte ? Votre identité vous connectera automatiquement
                </p>
              </div>
            </div>
          </div>
        </section>
      ) : null}
    </div>
  );
}
