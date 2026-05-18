'use client';

import { useState, useCallback, useEffect } from 'react';
import { useRouter } from 'next/navigation';
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { Alert, AlertDescription } from '@/components/ui/alert';
import { Badge } from '@/components/ui/badge';
import { FileText, CheckCircle, XCircle, Clock, ArrowLeft, RefreshCw } from 'lucide-react';
import { toast } from 'sonner';
import { useAuth } from '@/hooks/useAuth';

interface DbConsent {
  datasetHash: string;
  studyId: number;
  studyDescription: string | null;
  studyCreator: { firstName: string; lastName: string; institution: string | null } | null;
  createdAt: string;
  revokedAt: string | null;
  isActive: boolean;
}

function LoadingState() {
  return (
    <div className="flex items-center justify-center py-12">
      <div className="text-center">
        <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-blue-600 mx-auto mb-4"></div>
        <p className="text-gray-600">Chargement des consentements...</p>
      </div>
    </div>
  );
}

function ErrorState({ error, onRetry }: { error: string; onRetry: () => void }) {
  return (
    <Alert className="mb-6">
      <XCircle className="h-4 w-4" />
      <AlertDescription className="flex items-center justify-between">
        <span>{error}</span>
        <Button variant="outline" size="sm" onClick={onRetry}>
          <RefreshCw className="h-4 w-4 mr-2" />
          Réessayer
        </Button>
      </AlertDescription>
    </Alert>
  );
}

function EmptyState() {
  const router = useRouter();
  return (
    <Card>
      <CardContent className="pt-6">
        <div className="text-center py-8">
          <FileText className="h-12 w-12 text-gray-400 mx-auto mb-4" />
          <h3 className="text-lg font-medium text-gray-900 mb-2">Aucun consentement</h3>
          <p className="text-gray-600 mb-4">
            Vous n&apos;avez encore partagé aucune donnée pour une étude de recherche.
          </p>
          <Button onClick={() => router.push('/patient/upload')}>
            Commencer par uploader des données
          </Button>
        </div>
      </CardContent>
    </Card>
  );
}

function ConsentStats({ consents }: { consents: DbConsent[] }) {
  const activeCount = consents.filter(c => c.isActive).length;
  const revokedCount = consents.filter(c => !c.isActive).length;
  return (
    <div className="grid md:grid-cols-3 gap-6 mb-6">
      <Card><CardContent className="pt-6"><div className="text-center"><div className="text-2xl font-bold text-blue-600">{consents.length}</div><div className="text-sm text-gray-600">Total</div></div></CardContent></Card>
      <Card><CardContent className="pt-6"><div className="text-center"><div className="text-2xl font-bold text-green-600">{activeCount}</div><div className="text-sm text-gray-600">Actifs</div></div></CardContent></Card>
      <Card><CardContent className="pt-6"><div className="text-center"><div className="text-2xl font-bold text-red-600">{revokedCount}</div><div className="text-sm text-gray-600">Révoqués</div></div></CardContent></Card>
    </div>
  );
}

function ConsentCard({ consent, onRevoke }: { consent: DbConsent; onRevoke: () => void }) {
  const { authenticatedFetch } = useAuth();
  const [isRevoking, setIsRevoking] = useState(false);

  const getStatus = () => {
    if (!consent.isActive) return { label: 'Révoqué', variant: 'destructive' as const, icon: XCircle };
    return { label: 'Actif', variant: 'default' as const, icon: CheckCircle };
  };

  const status = getStatus();
  const StatusIcon = status.icon;

  const handleRevoke = async () => {
    if (!confirm('Révoquer ce consentement ? Les chercheurs n\'auront plus accès à ces données.')) return;
    setIsRevoking(true);
    try {
      const res = await authenticatedFetch(`/api/patient/consents/${consent.datasetHash}/revoke`, { method: 'POST' });
      const data = await res.json();
      if (data.success) {
        toast.success('Consentement révoqué');
        onRevoke();
      } else {
        toast.error(data.error || 'Erreur lors de la révocation');
      }
    } catch {
      toast.error('Erreur lors de la révocation');
    } finally {
      setIsRevoking(false);
    }
  };

  return (
    <Card className="hover:shadow-md transition-shadow">
      <CardHeader>
        <div className="flex justify-between items-start">
          <div>
            <CardTitle className="flex items-center gap-2">
              <StatusIcon className="h-5 w-5" />
              {consent.studyDescription ?? `Étude #${consent.studyId}`}
            </CardTitle>
            {consent.studyCreator && (
              <CardDescription>
                {consent.studyCreator.firstName} {consent.studyCreator.lastName}
                {consent.studyCreator.institution ? ` — ${consent.studyCreator.institution}` : ''}
              </CardDescription>
            )}
          </div>
          <div className="flex items-center gap-2">
            <Badge variant={status.variant}>{status.label}</Badge>
            {consent.isActive && (
              <Button variant="outline" size="sm" onClick={handleRevoke} disabled={isRevoking} className="text-red-600 border-red-200 hover:bg-red-50">
                {isRevoking ? <Clock className="h-4 w-4 animate-spin" /> : 'Révoquer'}
              </Button>
            )}
          </div>
        </div>
      </CardHeader>
      <CardContent>
        <div className="grid md:grid-cols-2 gap-4 text-sm">
          <div>
            <span className="font-medium text-gray-700">Partagé le :</span>
            <p className="text-gray-600">{new Date(consent.createdAt).toLocaleDateString('fr-FR', { year: 'numeric', month: 'long', day: 'numeric' })}</p>
          </div>
          {consent.revokedAt && (
            <div>
              <span className="font-medium text-gray-700">Révoqué le :</span>
              <p className="text-gray-600">{new Date(consent.revokedAt).toLocaleDateString('fr-FR', { year: 'numeric', month: 'long', day: 'numeric' })}</p>
            </div>
          )}
          <div>
            <span className="font-medium text-gray-700">Hash des données :</span>
            <p className="text-gray-600 font-mono text-xs break-all">{consent.datasetHash}</p>
          </div>
        </div>
      </CardContent>
    </Card>
  );
}

export default function PatientConsents() {
  const router = useRouter();
  const { authenticatedFetch } = useAuth();
  const [consents, setConsents] = useState<DbConsent[]>([]);
  const [isLoading, setIsLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  const fetchConsents = useCallback(async () => {
    setIsLoading(true);
    setError(null);
    try {
      const res = await authenticatedFetch('/api/patient/consents');
      const data = await res.json();
      if (data.success) {
        setConsents(data.consents);
      } else {
        setError(data.error || 'Erreur lors du chargement');
      }
    } catch {
      setError('Erreur lors du chargement des consentements');
    } finally {
      setIsLoading(false);
    }
  }, [authenticatedFetch]);

  useEffect(() => { fetchConsents(); }, [fetchConsents]);

  return (
    <div className="min-h-screen bg-gray-50">
      <main className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
        <div className="mb-8">
          <div className="flex items-center gap-4 mb-4">
            <Button variant="outline" size="sm" onClick={() => router.push('/patient/dashboard')}>
              <ArrowLeft className="h-4 w-4 mr-2" />
              Retour au dashboard
            </Button>
          </div>
          <div className="flex items-center justify-between">
            <div className="flex items-center space-x-3">
              <FileText className="w-8 h-8 text-green-600" />
              <div>
                <h1 className="text-3xl font-bold text-gray-900">Mes Consentements</h1>
                <p className="text-gray-600">Gérez vos partages de données pour les études de recherche</p>
              </div>
            </div>
            {!isLoading && !error && (
              <Button variant="outline" onClick={fetchConsents}>
                <RefreshCw className="h-4 w-4 mr-2" />
                Actualiser
              </Button>
            )}
          </div>
        </div>

        {isLoading ? (
          <LoadingState />
        ) : error ? (
          <ErrorState error={error} onRetry={fetchConsents} />
        ) : consents.length === 0 ? (
          <EmptyState />
        ) : (
          <div className="space-y-6">
            <ConsentStats consents={consents} />
            <div className="space-y-4">
              {consents.map(consent => (
                <ConsentCard key={consent.datasetHash} consent={consent} onRevoke={fetchConsents} />
              ))}
            </div>
          </div>
        )}
      </main>
    </div>
  );
}
