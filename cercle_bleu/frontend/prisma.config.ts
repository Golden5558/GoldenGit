import { config } from 'dotenv'
import { defineConfig, env } from "prisma/config";

// Load .env.local first (higher priority), then .env
config({ path: '.env.local' })
config({ path: '.env' })

export default defineConfig({
  schema: 'schema.prisma',
  migrations: {
    path: 'migrations',
    seed: 'tsx prisma/seed.ts',
  },
  datasource: {
    url: env("DATABASE_URL"),
    directUrl: env("DATABASE_DIRECT_URL")
  }
});