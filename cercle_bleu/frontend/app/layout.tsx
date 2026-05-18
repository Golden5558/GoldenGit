import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import RainbowKitAndWagmiProvider from "./RainbowKitAndWagmiProvider";
import { AuthProvider } from "@/contexts/AuthContext";
import Layout from "@/components/shared/Layout";
import "./globals.css";

const geistSans = Geist({
  variable: "--font-geist-sans",
  subsets: ["latin"],
});

const geistMono = Geist_Mono({
  variable: "--font-geist-mono",
  subsets: ["latin"],
});

export const metadata: Metadata = {
  title: "Mon Cercle Sante",
  description: "Application de gestion de consentements pour la recherche sur le diabète",
  icons: {
    icon: "/logo-cercle.png",
    shortcut: "/logo-cercle.png",
    apple: "/logo-cercle.png",
  },
};

export default function RootLayout({
  children,
}: Readonly<{ children: React.ReactNode }>) {
  return (
    <html lang="en">
      <body className={`${geistSans.variable} ${geistMono.variable} antialiased`}>
        <RainbowKitAndWagmiProvider>
          <AuthProvider>
            <Layout>
              {children}
            </Layout>
          </AuthProvider>
        </RainbowKitAndWagmiProvider>
      </body>
    </html>
  );
}
