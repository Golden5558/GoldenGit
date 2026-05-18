interface Step {
  label: string;
}

interface RegistrationStepperProps {
  steps: Step[];
  currentStep: number; // index of the active step
}

export default function RegistrationStepper({ steps, currentStep }: RegistrationStepperProps) {
  return (
    <ol className="flex items-center w-full mb-6">
      {steps.map((s, i) => {
        const done = i < currentStep;
        const active = i === currentStep;
        return (
          <li key={i} className={`flex items-center ${i < steps.length - 1 ? 'flex-1' : ''}`}>
            <span
              className={`flex items-center justify-center w-7 h-7 rounded-full text-xs font-semibold shrink-0 border-2 transition-colors
                ${done ? 'bg-green-600 border-green-600 text-white' : active ? 'bg-blue-600 border-blue-600 text-white' : 'bg-white border-gray-300 text-gray-400'}`}
            >
              {done ? '✓' : i + 1}
            </span>
            <span className={`ml-1.5 text-xs font-medium whitespace-nowrap hidden sm:block
              ${done ? 'text-green-700' : active ? 'text-blue-700' : 'text-gray-400'}`}>
              {s.label}
            </span>
            {i < steps.length - 1 && (
              <span className={`flex-1 h-0.5 mx-2 ${done ? 'bg-green-600' : 'bg-gray-200'}`} />
            )}
          </li>
        );
      })}
    </ol>
  );
}
