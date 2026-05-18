# Conformité Réglementaire - Cercle Bleu

## 📋 Vue d'ensemble

Ce document détaille la stratégie de conformité réglementaire de Cercle Bleu, incluant les certifications HDS, la conformité CNIL/RGPD, et les jalons de mise en œuvre.

## 🏥 Certification HDS (Hébergeur de Données de Santé)

### Stratégie retenue : OVHcloud HDS

**Décision** : Utilisation d'OVHcloud HDS plutôt que l'acquisition de serveurs privés.

**Avantages** :
- ✅ Certification HDS déjà obtenue
- ✅ Réduction des coûts (70% d'économie sur 3 ans)
- ✅ Expertise technique et juridique incluse
- ✅ Maintenance et sécurité assurées
- ✅ Conformité continue garantie
- ✅ Support français spécialisé santé

**Architecture recommandée** :
- **Hébergement** : OVHcloud Public Cloud HDS
- **Base de données** : PostgreSQL managée HDS
- **Stockage** : Object Storage HDS pour les données sensibles
- **Réseau** : vRack privé avec chiffrement end-to-end
- **Sauvegarde** : Backup automatisé multi-zones

**Coût estimé** : 800-1200€/mois selon la charge

## ✅ État d’implémentation actuel (RGPD/CNIL & technique)

- Consentement granulaire on-chain (SBT ERC721) avec validité, révocation en temps réel, comptage des consentements actifs et études autorisées (contrat de consentement).
- Interface patient: affichage statut (Actif/Expiré/Révoqué) et bouton de révocation, lecture des consentements depuis la blockchain (frontend: listes, hooks, composants).
- Récompenses SBT ERC20: mint automatique à chaque téléchargement de données, burn pour échange avec traçabilité par événements (contrat de jeton).
- Listes d’autorisation présentes pour patients/chercheurs; à durcir par contrôle d’accès administrateur (propriétaire/roles).
- Pause d’urgence: non implémentée actuellement; à ajouter via Pausable/AccessControl.
- Chiffrement/pseudonymisation (API/DB/HDS): à mettre en œuvre côté backend et base gérée OVHcloud HDS.
- Hébergement HDS: décision prise (OVHcloud HDS), mise en place de l’architecture en cours de planification.

## 🔒 Conformité CNIL et RGPD

### Jalons de mise en œuvre (4-5 mois)

#### **Phase 1 : Analyse et Préparation (Mois 1)**
**Durée** : 4 semaines

**Semaine 1-2 : Audit de conformité**
- [ ] Cartographie des traitements de données personnelles
- [ ] Identification des bases légales (consentement, intérêt légitime)
- [ ] Analyse des flux de données (collecte, traitement, transfert)
- [ ] Évaluation des risques sur les droits et libertés

**Semaine 3-4 : Documentation juridique**
- [ ] Rédaction du registre des traitements (Art. 30 RGPD)
- [ ] Politique de confidentialité détaillée
- [ ] Mentions d'information (Art. 13-14 RGPD)
- [ ] Procédures d'exercice des droits (accès, rectification, effacement)

**Livrables** :
- Registre des traitements complet
- Politique de confidentialité
- Procédures RGPD documentées

---

#### **Phase 2 : Implémentation Technique (Mois 2)**
**Durée** : 4 semaines

**Semaine 1-2 : Sécurité et chiffrement**
- [ ] Implémentation du chiffrement en transit (TLS) et au repos (DB)
- [ ] Pseudonymisation des données sensibles (modèle et pipelines backend)
- [ ] Sécurisation des API et bases de données (OVHcloud HDS)
- [ ] Mise en place des logs d'audit applicatifs (hors chaîne)

**Semaine 3-4 : Gestion des consentements (déjà en place côté on-chain/frontend)**
- [x] Interface de gestion granulaire des consentements (par étude/dataset)
- [x] Mécanisme de révocation en temps réel (contrat + UI)
- [x] Traçabilité blockchain des consentements
- [x] Intégration avec les smart contracts

**Durcissement smart contracts (sécurité additionnelle)**
- [ ] Ajouter des contrôles d’accès (propriétaire/roles) sur les fonctions admin
- [ ] Ajouter un mécanisme de pause d’urgence (Pausable) sur contrats critiques
- [ ] Journaliser les événements et relayer vers SIEM (hors chaîne)

**Livrables** :
- Système de consentement opérationnel (on-chain + UI)
- Chiffrement et pseudonymisation implémentés
- Logs d'audit configurés
- Contrats durcis (contrôles d’accès, pause)

---

#### **Phase 3 : Documentation et Procédures (Mois 3)**
**Durée** : 4 semaines 

**Semaine 1-2 : Procédures opérationnelles**
- [ ] Procédure de gestion des violations de données
- [ ] Plan de réponse aux demandes d'exercice des droits
- [ ] Procédure de Data Protection Impact Assessment (DPIA)
- [ ] Formation des équipes aux obligations RGPD

**Semaine 3-4 : Contrats et partenariats**
- [ ] Contrats de sous-traitance conformes (Art. 28 RGPD)
- [ ] Accords de transfert de données avec les chercheurs
- [ ] Clauses contractuelles types pour les partenaires
- [ ] Validation juridique des contrats

**Livrables** :
- Procédures opérationnelles RGPD
- Contrats de sous-traitance conformes
- Plan de formation équipes

---

#### **Phase 4 : Déclaration CNIL et Validation (Mois 4)**
**Durée** : 4 semaines 

**Semaine 1-2 : Préparation déclaration CNIL**
- [ ] Finalisation du dossier de déclaration
- [ ] Analyse d'impact (DPIA) si nécessaire
- [ ] Validation par un avocat spécialisé données personnelles
- [ ] Préparation des éléments techniques

**Semaine 3-4 : Soumission et suivi**
- [ ] Dépôt de la déclaration CNIL
- [ ] Réponse aux éventuelles questions de la CNIL
- [ ] Ajustements selon les retours
- [ ] Obtention de l'accusé de réception

**Livrables** :
- Déclaration CNIL déposée
- Accusé de réception CNIL
- Conformité RGPD validée

---

#### **Phase 5 : Maintenance et Amélioration Continue (Mois 5+)**
**Durée** : Ongoing

**Actions récurrentes** :
- [ ] Audit de conformité trimestriel
- [ ] Mise à jour des procédures selon évolutions réglementaires
- [ ] Formation continue des équipes
- [ ] Veille juridique et technologique
- [ ] Tests de sécurité réguliers (incl. audits smart contracts annuels)

**Livrables** :
- Rapports d'audit trimestriels
- Mise à jour continue de la conformité
- Formation équipes maintenue


## 🎯 Objectifs de Conformité

### Conformité RGPD
- ✅ **Licéité** : Base légale claire (consentement explicite)
- ✅ **Transparence** : Information complète des patients
- ✅ **Minimisation** : Collecte limitée aux données nécessaires
- ✅ **Exactitude** : Mécanismes de correction et mise à jour
- ✅ **Limitation de conservation** : Durées définies et respectées
- ✅ **Sécurité** : Chiffrement et mesures techniques appropriées
- ✅ **Responsabilité** : Documentation et preuves de conformité

### Droits des personnes
- **Droit d'accès** : Interface patient pour consulter ses données
- **Droit de rectification** : Modification des données inexactes
- **Droit à l'effacement** : Suppression sur demande (avec exceptions recherche)
- **Droit à la portabilité** : Export des données dans un format structuré
- **Droit d'opposition** : Refus du traitement pour motifs légitimes
- **Droit à la limitation** : Restriction temporaire du traitement

## 🔍 Points de Vigilance Spécifiques

### Blockchain et RGPD
- **Immutabilité vs droit à l'effacement** : Seuls les hash sont stockés on-chain
- **Pseudonymisation** : Données personnelles hors blockchain
- **Consentement granulaire** : Smart contracts pour gestion fine
- **Révocation** : Mécanisme technique de désactivation

### Données de santé
- **Sensibilité particulière** : Mesures de sécurité renforcées
- **Hébergement HDS** : Obligation légale respectée via OVHcloud
- **Finalités recherche** : Base légale intérêt public/scientifique
- **Anonymisation** : Processus technique documenté

## 📞 Contacts et Ressources

### Partenaires juridiques recommandés
- **Cabinet spécialisé RGPD** : Pour validation finale
- **DPO externe** : Accompagnement continu
- **Avocat données personnelles** : Conseil stratégique

### Organismes de référence
- **CNIL** : Commission Nationale de l'Informatique et des Libertés
- **ANSSI** : Agence Nationale de la Sécurité des Systèmes d'Information
- **ANS** : Agence du Numérique en Santé

---

*Document mis à jour le : 13/11/2025*  
*Version : 1.2*  
*Responsable : Équipe Cercle Bleu*