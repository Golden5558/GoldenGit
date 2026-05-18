'use client';

import { useState, useEffect, useRef } from 'react';
import { CheckCircle2, Circle, X, Sparkles } from 'lucide-react';

export interface ChecklistTask {
  id: string;
  label: string;
  href?: string;
  autoCompleted: boolean;
}

interface StoredState {
  manual: Record<string, boolean>;
  dismissed: boolean;
  celebrated: boolean;
}

interface Props {
  storageKey: string;
  tasks: ChecklistTask[];
  title?: string;
}

export function FirstRunChecklist({ storageKey, tasks, title = 'Premiers pas' }: Props) {
  const lsKey = `cercle_firstrun_${storageKey}`;
  const [stored, setStored] = useState<StoredState | null>(null);
  const [showCelebration, setShowCelebration] = useState(false);
  const storedRef = useRef<StoredState | null>(null);
  storedRef.current = stored;

  useEffect(() => {
    const raw = localStorage.getItem(lsKey);
    const init: StoredState = raw
      ? JSON.parse(raw)
      : { manual: {}, dismissed: false, celebrated: false };
    setStored(init);
  }, [lsKey]);

  const autoCompletedKey = tasks.map(t => `${t.id}:${t.autoCompleted}`).join(',');

  useEffect(() => {
    const s = storedRef.current;
    if (!s || s.celebrated) return;
    const completedCount = tasks.filter(t => t.autoCompleted || s.manual[t.id]).length;
    if (completedCount > 0) {
      const updated = { ...s, celebrated: true };
      localStorage.setItem(lsKey, JSON.stringify(updated));
      setStored(updated);
      setShowCelebration(true);
      setTimeout(() => setShowCelebration(false), 4000);
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [autoCompletedKey]);

  if (!stored || stored.dismissed) return null;

  const completedCount = tasks.filter(t => t.autoCompleted || !!stored.manual[t.id]).length;
  const allDone = completedCount === tasks.length;

  const save = (updated: StoredState) => {
    setStored(updated);
    localStorage.setItem(lsKey, JSON.stringify(updated));
  };

  const handleToggle = (taskId: string) => {
    save({ ...stored, manual: { ...stored.manual, [taskId]: !stored.manual[taskId] } });
  };

  const handleDismiss = () => {
    save({ ...stored, dismissed: true });
  };

  if (allDone) {
    return (
      <div className="bg-green-50 border border-green-200 rounded-lg p-4 mb-6 flex items-center justify-between">
        <div className="flex items-center space-x-2">
          <CheckCircle2 className="w-5 h-5 text-green-600" />
          <span className="text-green-800 font-medium">
            Vous avez complété toutes vos premières étapes !
          </span>
        </div>
        <button onClick={handleDismiss} className="text-green-600 hover:text-green-800">
          <X className="w-4 h-4" />
        </button>
      </div>
    );
  }

  return (
    <div className="bg-white rounded-lg shadow-md p-6 mb-6">
      {showCelebration && (
        <div className="bg-yellow-50 border border-yellow-200 rounded-md p-3 mb-4 flex items-center space-x-2">
          <Sparkles className="w-5 h-5 text-yellow-500" />
          <span className="text-yellow-800 font-medium">
            Félicitations pour votre première étape accomplie !
          </span>
        </div>
      )}

      <div className="flex items-center justify-between mb-3">
        <div>
          <h3 className="text-lg font-semibold text-gray-900">{title}</h3>
          <p className="text-sm text-gray-500">{completedCount}/{tasks.length} terminé</p>
        </div>
        <button onClick={handleDismiss} className="text-gray-400 hover:text-gray-600">
          <X className="w-5 h-5" />
        </button>
      </div>

      <div className="h-1.5 bg-gray-100 rounded-full mb-4">
        <div
          className="h-1.5 bg-blue-500 rounded-full transition-all duration-500"
          style={{ width: `${(completedCount / tasks.length) * 100}%` }}
        />
      </div>

      <ul className="space-y-3">
        {tasks.map(task => {
          const isCompleted = task.autoCompleted || !!stored.manual[task.id];
          return (
            <li key={task.id} className="flex items-center space-x-3">
              <button
                onClick={() => !task.autoCompleted && handleToggle(task.id)}
                className={task.autoCompleted ? 'cursor-default flex-shrink-0' : 'cursor-pointer flex-shrink-0'}
                aria-label={isCompleted ? 'Tâche accomplie' : 'Marquer comme accomplie'}
              >
                {isCompleted
                  ? <CheckCircle2 className="w-5 h-5 text-green-500" />
                  : <Circle className="w-5 h-5 text-gray-300 hover:text-gray-400" />
                }
              </button>
              {task.href ? (
                <a
                  href={task.href}
                  className={`text-sm ${isCompleted ? 'line-through text-gray-400' : 'text-blue-600 hover:underline'}`}
                >
                  {task.label}
                </a>
              ) : (
                <span className={`text-sm ${isCompleted ? 'line-through text-gray-400' : 'text-gray-700'}`}>
                  {task.label}
                </span>
              )}
            </li>
          );
        })}
      </ul>
    </div>
  );
}
