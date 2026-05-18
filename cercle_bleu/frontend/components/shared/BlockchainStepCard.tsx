interface BlockchainStepItem {
  icon: string;
  title: string;
  description: string;
}

interface BlockchainStepCardProps {
  items: BlockchainStepItem[];
  hash?: `0x${string}`;
  address?: string;
}

export default function BlockchainStepCard({ items, hash, address }: BlockchainStepCardProps) {
  return (
    <>
      <div className="rounded-lg border border-blue-100 bg-blue-50 p-4 space-y-3">
        <h3 className="text-sm font-semibold text-blue-900">Ce qu&apos;il va se passer</h3>
        <ul className="space-y-2 text-sm text-blue-800">
          {items.map((item, i) => (
            <li key={i} className="flex gap-2">
              <span className="mt-0.5 shrink-0">{item.icon}</span>
              <span>
                <strong>{item.title}</strong> {item.description}
              </span>
            </li>
          ))}
        </ul>
      </div>

      {hash && (
        <div className="text-xs text-gray-500 text-center">
          Transaction : {hash.slice(0, 10)}...{hash.slice(-8)}
        </div>
      )}

      {address && (
        <div className="text-xs text-gray-500 text-center">
          Wallet : {address.slice(0, 6)}...{address.slice(-4)}
        </div>
      )}
    </>
  );
}
