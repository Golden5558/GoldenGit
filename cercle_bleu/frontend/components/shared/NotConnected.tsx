import {
    Alert,
    AlertDescription,
    AlertTitle,
} from "@/components/ui/alert"

import { AlertCircleIcon } from "lucide-react"

const NotConnected = () => {
  return (
    <Alert>
        <AlertCircleIcon />
        <AlertTitle>Warning!</AlertTitle>
        <AlertDescription>
            Veuillez vous connecter pour continuer.
        </AlertDescription>
    </Alert>
  )
}

export default NotConnected