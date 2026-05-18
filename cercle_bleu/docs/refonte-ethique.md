# Refonte éthique de Cercle Bleu
## Vers un modèle de consentement souverain sans incitation financière

Ce document définit la nouvelle orientation stratégique de la plateforme, privilégiant l'altruisme, la transparence et la valeur médicale sur les mécanismes de monétisation.

---

## 1. Nouveaux leviers d'engagement

Pour maintenir l'engagement des patients sans dénaturer l'éthique du soin, cinq piliers sont intégrés :

* **Feedback de recherche (valeur scientifique) :** Le patient reçoit un résumé vulgarisé de l'étude à laquelle il a contribué. Il voit l'utilité concrète de son geste (ex: corrélation entre activité physique et glycémie nocturne).
* **Score d'impact altruiste (gamification sociale) :** Accumulation d'un "Score de Contribution" symbolique (badges, niveaux) pour valoriser le rôle du patient dans l'avancée de la science.
* **Accès aux Données Agrégées (Le "Benchmark") :** Possibilité pour le patient de comparer anonymement ses propres indicateurs à une cohorte similaire pour mieux gérer sa pathologie.
* **Philanthropie (Don de Points) :** Les points générés ne sont pas rachetables par le patient mais convertis en dons réels vers des associations (ex: Fédération Française des Diabétiques).
* **Facilité de Suivi Médical (Valeur Pratique) :** Génération d'un tableau de bord structuré facilitant le dialogue et le gain de temps lors des consultations avec son médecin traitant.

---

## 2. Principes Directeurs
* **Éthique :** Non-marchandisation des données et respect total de l'autonomie (consentement révocable).
* **Transparence :** Auditabilité complète des accès chercheurs via la blockchain.
* **Gouvernance :** Modèle participatif incluant patients, médecins et chercheurs.
* **Conformité :** Sécurité HDS, respect strict du RGPD et minimisation des données.

---

## 3. Reconversion du Token ERC20 : Cercle

### 🎁 3.1 Tokens Philanthropiques
Les tokens accumulés par le patient sont **non-rachetables** mais convertibles en dons réels :
* Le patient accumule des `Cercle` via ses contributions de données
* Les tokens se convertissent en dons vers des associations de santé partenaires (ex: Fédération Française des Diabétiques, AFD, etc.)
* Le patient choisit l'association bénéficiaire de sa contribution
* Création d'une valeur altruiste sans gain financier personnel
* Tableau de bord "Mon Impact Philanthropique" avec historique des dons générés

### 🗳️ 3.2 Tokens de Gouvernance
Les tokens confèrent un **poids de vote** dans la plateforme :
* Vote sur l'approbation des études de recherche soumises
* Participation aux décisions de gouvernance de la plateforme
* Voix consultative au sein du Comité d'Éthique
* Plus de contributions = voix plus forte dans la communauté
* Principe : 1 token = 1 vote (plafond anti-concentration possible)

### 🔓 3.3 Tokens d'Accès / Déblocage
Les tokens débloquent des **avantages non-monétaires** :
* Accès anticipé aux résumés vulgarisés des résultats de recherche
* Accès aux comparaisons benchmark détaillées avec patients similaires
* Déblocage de contenus éducatifs sur la gestion du diabète
* Accès à des webinaires scientifiques ou sessions Q&A avec chercheurs
* Paliers progressifs : Bronze (50 tokens), Argent (200), Or (500), Platine (1000)

### 🏆 3.4 Tokens de Score d'Impact (Gamification)
Reconnaissance symbolique pure basée sur l'accumulation :
* Système de badges et niveaux ("Contributeur", "Ambassadeur", "Pioneer", etc.)
* Classement optionnel des "top contributeurs à la science" (opt-in uniquement)
* Certificat de contribution téléchargeable et partageable
* Timeline personnelle de l'impact sur la recherche
* Profil public anonymisé montrant les contributions (si le patient le souhaite)

### 🔬 3.5 Crédits de Priorisation de Recherche
Permettre aux patients d'**influencer la science** :
* Dépenser des tokens pour voter sur les sujets de recherche prioritaires
* Signaler les questions de santé qui comptent le plus pour eux
* Les chercheurs visualisent les priorités de la communauté
* Mécanisme de "crowdsourcing" des besoins de recherche
* Rapports trimestriels sur les orientations votées par la communauté

---

## 4. Modifications par Couche Système

### 🟦 Contrats & Blockchain
* **Conservation :** Maintien du `Cercle` (SBT) pour la preuve de consentement
* **Ajouts :**
  - Fonction de conversion tokens → dons (avec choix d'association)
  - Système de vote pondéré par tokens pour la gouvernance
  - Registre des paliers d'accès atteints par patient
  - Journal d'événements pseudonymisé (logs d'accès aux données)

### 🖥️ Frontend (UX/UI)
* **Suppression :** Interfaces de boutiques de récompenses et d'échange monétaire
* **Transformation :**
  - "Mon Solde" devient "Mon Impact" (visualisation des contributions)
  - "Mes Récompenses" devient "Ma Contribution à la Science"
* **Nouveautés :**
  - Tableau de bord "Mon Consentement" et journal de transparence
  - Interface de choix d'associations pour les dons
  - Module de vote pour les études et priorités de recherche
  - Galerie de badges et certificats de contribution
  - Intégration des flux de feedbacks scientifiques

### ⚙️ API & Base de Données
* **Mutation :**
  - Table "Récompenses" → "Contributions" (historique d'accumulation)
  - Ajout table "Dons" (conversions tokens → associations)
  - Ajout table "Votes" (participation gouvernance)
  - Module "Journal d'Accès Aux Données" (AAD)
* **Transparence :** Nouveaux endpoints pour les "Data Use Statements" (justificatifs d'usage des chercheurs)
* **Gouvernance :** API de soumission et vote sur les études

---

## 5. Gouvernance & Sécurité
* **Comité d'Éthique :** Instauration d'un conseil de patients pour l'habilitation des études, avec poids de vote basé sur les tokens.
* **Souveraineté :** Hash seul stocké on-chain, données brutes sur serveurs HDS avec pseudonymisation renforcée.
* **Audit :** Journal d'accès inviolable et mécanismes de plainte intégrés.
* **Anti-concentration :** Plafond de tokens votants pour éviter qu'un petit groupe ne domine les décisions.

---

## 6. Plan de Migration technique
1.  **Phase 0 :** Désactivation des fonctions de récompense monétaire via *feature flags*.
4.  **Phase 1 :** Déploiement des nouvelles interfaces (Impact, Gouvernance, Dons).
5.  **Phase 2 :** Déploiement du module AAD et des outils de feedback pédagogiques.
6.  **Phase 3 :** Activation du système de vote et partenariats avec associations.

---

## 📊 Indicateurs de Réussite
* **Éthique :** 0 mécanisme d'échange monétaire lié aux contributions.
* **Engagement :** Taux de participation aux votes de gouvernance > 30%.
* **Philanthropie :** Montant total des dons générés vers les associations partenaires.
* **Traçabilité :** 100% des accès chercheurs sont audités et consultables par le patient.
* **Conformité :** Validation des revues RGPD/HDS.
* **Satisfaction :** Score NPS des patients sur le nouveau système > 50.