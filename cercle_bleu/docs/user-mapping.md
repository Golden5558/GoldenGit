# User Mapping — Cercle Bleu

---

## 1. Patient

### Profil

- Personne atteinte de diabète (type 1, 2, gestationnel ou LADA)
- Niveau de littératie numérique variable
- Motivations : mieux gérer sa maladie, contribuer à la recherche, garder le contrôle de ses données

### Besoins

**Contrôle et transparence**

- Savoir qui accède à ses données, quand et pour quelle étude
- Pouvoir révoquer un consentement à tout moment
- Comprendre ce que chaque accord implique concrètement

**Suivi médical**

- Visualiser ses indicateurs glycémiques et leur évolution
- Comparer ses données à une cohorte de patients similaires (benchmark anonyme)
- Partager un tableau de bord structuré avec son médecin lors des consultations

**Engagement et reconnaissance**

- Voir l'impact concret de sa contribution scientifique
- Recevoir des résumés vulgarisés des études auxquelles il a participé
- Accumuler un score altruiste et débloquer des contenus éducatifs
- Convertir ses tokens en dons vers des associations de patients

**Gouvernance**

- Voter sur les études soumises à la plateforme
- Influencer les priorités de recherche qui le concernent

### Parcours dans l'application

```
Inscription (wallet + profil médical)
    ↓
Tableau de bord personnel (glycémie, indicateurs, benchmark)
    ↓
Réception d'une demande d'étude → Lecture du protocole → Consentement (ou refus)
    ↓
Journal d'accès : consultation des accès effectués par les chercheurs
    ↓
Feedback scientifique : résumé vulgarisé des résultats de l'étude
    ↓
Accumulation de tokens → Dons, vote, contenus éducatifs
```

### Frustrations actuelles (sans Cercle Bleu)

- Signe des formulaires sans comprendre les implications réelles
- Ne sait jamais si ses données ont été utilisées
- Ne reçoit aucun retour sur les études auxquelles il a contribué
- Ses données sont éparpillées entre appareils, médecins et hôpitaux
- Se sent spectateur passif de sa propre maladie

---

## 2. Chercheur

### Profil

- Équipe académique (INSERM, universités, Institut Pasteur), laboratoire pharmaceutique ou MedTech
- Objectif : accéder à des données réelles de qualité pour mener des études cliniques ou fondamentales
- Contrainte principale : recrutement long, coûteux et peu représentatif dans les études classiques

### Besoins

**Accès aux données**

- Constituer des cohortes de patients rapidement et à moindre coût
- Accéder à des données longitudinales du quotidien (glycémie continue, alimentation, activité)
- Filtrer les patients selon des critères précis (type de diabète, âge, traitements, comorbidités)

**Conformité et traçabilité**

- Prouver que chaque accès aux données est consenti, tracé et conforme au RGPD
- Disposer d'une preuve d'audit inviolable pour les publications et les régulateurs
- Recevoir des données pseudonymisées et structurées, prêtes à l'analyse

**Publication et visibilité**

- Soumettre des protocoles d'étude à la communauté de patients
- Publier des résultats vulgarisés en retour vers les patients contributeurs
- Valoriser les études auprès d'une communauté engagée

### Parcours dans l'application

```
Inscription et vérification de l'institution
    ↓
Soumission d'un protocole d'étude (objectif, données requises, durée, critères)
    ↓
Validation par le Comité d'Éthique (patients + médecins)
    ↓
Diffusion de l'appel à participation auprès des patients éligibles
    ↓
Collecte des consentements → Accès aux données pseudonymisées
    ↓
Analyse → Publication des résultats vulgarisés sur la plateforme
    ↓
Facturation (frais d'accès à la plateforme + volume de données)
```

### Frustrations actuelles (sans Cercle Bleu)

- Recrutement classique : 2 à 5 ans pour constituer une cohorte
- Données hétérogènes, mal structurées, difficiles à agréger
- Prouver la conformité RGPD est un processus administratif lourd
- Aucun retour possible vers les patients participants

---

## 3. Médecin

### Profil

- Médecin traitant, endocrinologue ou diabétologue
- Suivi régulier de patients diabétiques en consultation
- Contrainte principale : manque de temps, données éparpillées, peu de vision longitudinale entre les consultations

### Besoins

**Coordination des soins**

- Accéder à un tableau de bord patient unifié lors des consultations
- Visualiser l'évolution des indicateurs entre deux visites (glycémie, HbA1c, poids, activité)
- Recevoir des alertes sur des tendances préoccupantes en dehors des consultations

**Gain de temps**

- Éviter de reconstituer l'historique médical à chaque consultation
- Disposer d'un résumé structuré et lisible, généré à partir des données patient

**Contribution à la recherche**

- Orienter ses patients vers des études pertinentes sur la plateforme
- Consulter les résultats agrégés de cohortes similaires pour affiner ses pratiques
- Participer au Comité d'Éthique pour la validation des protocoles d'études

### Parcours dans l'application

```
Inscription (vérification RPPS)
    ↓
Accès au tableau de bord de ses patients (sur autorisation explicite du patient)
    ↓
Consultation des indicateurs, alertes et évolutions entre les visites
    ↓
Orientation du patient vers une étude pertinente
    ↓
Participation optionnelle au Comité d'Éthique pour la validation des protocoles
```

### Frustrations actuelles (sans Cercle Bleu)

- Les données du patient sont silotées entre le CGM, l'application mobile, le laboratoire et le dossier médical
- Le temps de consultation est gaspillé à reconstituer l'historique
- Aucun outil pour suivre l'évolution entre deux visites sans que le patient appelle

---

## 4. Interactions entre les acteurs

```
                        ┌──────────────────────────────┐
                        │        CERCLE BLEU           │
                        │   (plateforme + blockchain)  │
                        └──────────┬──────────┬────────┘
                                   │          │
              ┌────────────────────┘          └───────────────────────┐
              │                                                       │
              ▼                                                       ▼
     ┌────────────────┐                                    ┌──────────────────┐
     │    PATIENT     │                                    │    CHERCHEUR     │
     │                │◄── Résumé vulgarisé des études ─── │                  │
     │ Donne accès    │                                    │ Soumet protocole │
     │ à ses données  │──── Consentement tracé ──────────► │ Accède aux data  │
     │                │                                    │ pseudonymisées   │
     └───────┬────────┘                                    └──────────────────┘
             │                                                       ▲
             │ Partage tableau                          Validation   │
             │ de bord                                  protocole    │
             ▼                                                       │
     ┌────────────────┐                                    ┌──────────────────┐
     │    MÉDECIN     │────── Oriente vers une étude ─────►│  COMITÉ ÉTHIQUE  │
     │                │                                    │ (patients +      │
     │ Consulte les   │                                    │  médecins)       │
     │ indicateurs    │                                    └──────────────────┘
     │ du patient     │
     └────────────────┘
```

### Tableau des interactions clés

| Interaction | De | Vers | Canal |
|---|---|---|---|
| Consentement à une étude | Patient | Chercheur | Smart contract (blockchain) |
| Journal d'accès aux données | Plateforme | Patient | Dashboard |
| Résumé vulgarisé d'étude | Chercheur | Patient | Notification + Dashboard |
| Partage du tableau de bord | Patient | Médecin | Autorisation explicite |
| Orientation vers une étude | Médecin | Patient | Recommandation in-app |
| Soumission d'un protocole | Chercheur | Comité d'Éthique | Workflow de validation |
| Vote sur une étude | Patient | Comité d'Éthique | Token de gouvernance |
| Alerte de tendance glycémique | Plateforme | Médecin | Notification |
| Don philanthropique | Patient | Association partenaire | Conversion de tokens |

---

## 5. Synthèse des valeurs par acteur

| | Patient | Chercheur | Médecin |
|---|---|---|---|
| **Valeur principale** | Contrôle et impact altruiste | Données réelles éthiques | Gain de temps et coordination |
| **Ce qu'il donne** | Ses données et son consentement | Son protocole et ses résultats | Son expertise et sa validation |
| **Ce qu'il reçoit** | Outils de suivi, feedback, reconnaissance | Cohortes qualifiées, traçabilité RGPD | Dashboard unifié, alertes, insights |
| **Son levier d'engagement** | Tokens, badges, dons, vote | Accès simplifié, conformité garantie | Meilleure qualité de soin |
