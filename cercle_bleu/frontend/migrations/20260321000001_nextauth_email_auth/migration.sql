-- NextAuth tables
CREATE TABLE "auth_user" (
    "id" TEXT NOT NULL,
    "name" TEXT,
    "email" TEXT,
    "emailVerified" TIMESTAMP(3),
    "image" TEXT,
    CONSTRAINT "auth_user_pkey" PRIMARY KEY ("id")
);
CREATE UNIQUE INDEX "auth_user_email_key" ON "auth_user"("email");

CREATE TABLE "auth_account" (
    "id" TEXT NOT NULL,
    "userId" TEXT NOT NULL,
    "type" TEXT NOT NULL,
    "provider" TEXT NOT NULL,
    "providerAccountId" TEXT NOT NULL,
    "refresh_token" TEXT,
    "access_token" TEXT,
    "expires_at" INTEGER,
    "token_type" TEXT,
    "scope" TEXT,
    "id_token" TEXT,
    "session_state" TEXT,
    CONSTRAINT "auth_account_pkey" PRIMARY KEY ("id")
);
CREATE UNIQUE INDEX "auth_account_provider_providerAccountId_key" ON "auth_account"("provider", "providerAccountId");

CREATE TABLE "auth_session" (
    "id" TEXT NOT NULL,
    "sessionToken" TEXT NOT NULL,
    "userId" TEXT NOT NULL,
    "expires" TIMESTAMP(3) NOT NULL,
    CONSTRAINT "auth_session_pkey" PRIMARY KEY ("id")
);
CREATE UNIQUE INDEX "auth_session_sessionToken_key" ON "auth_session"("sessionToken");

CREATE TABLE "verification_token" (
    "identifier" TEXT NOT NULL,
    "token" TEXT NOT NULL,
    "expires" TIMESTAMP(3) NOT NULL
);
CREATE UNIQUE INDEX "verification_token_token_key" ON "verification_token"("token");
CREATE UNIQUE INDEX "verification_token_identifier_token_key" ON "verification_token"("identifier", "token");

ALTER TABLE "auth_account" ADD CONSTRAINT "auth_account_userId_fkey"
    FOREIGN KEY ("userId") REFERENCES "auth_user"("id") ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE "auth_session" ADD CONSTRAINT "auth_session_userId_fkey"
    FOREIGN KEY ("userId") REFERENCES "auth_user"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- Make walletAddress optional on patient and researcher
ALTER TABLE "patient" ALTER COLUMN "walletAddress" DROP NOT NULL;

-- Make email required + unique on patient
ALTER TABLE "patient" ALTER COLUMN "email" SET NOT NULL;
ALTER TABLE "patient" ADD CONSTRAINT "patient_email_key" UNIQUE ("email");

-- Make walletAddress optional on researcher
ALTER TABLE "researcher" ALTER COLUMN "walletAddress" DROP NOT NULL;

-- Make email required + unique on researcher
ALTER TABLE "researcher" ALTER COLUMN "email" SET NOT NULL;
ALTER TABLE "researcher" ADD CONSTRAINT "researcher_email_key" UNIQUE ("email");
