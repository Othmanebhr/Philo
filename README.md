# 🧘‍♂️ Philosophers - École 42

Projet réalisé dans le cadre du cursus de l’École 42.  
**Philosophers** explore la **programmation concurrente** à travers le célèbre problème des *philosophes mangeurs*, illustrant la gestion des threads, des mutex et des accès concurrents à la mémoire.

---

## 🎯 Objectifs
- Comprendre la **concurrence** et les **threads** en C.  
- Utiliser les **mutex** pour éviter les conditions de compétition.  
- Synchroniser correctement les actions entre plusieurs philosophes.  
- Respecter les contraintes de temps et d’ordre d’exécution.  

---

## ⚙️ Fonctionnalités
- Création d’un thread par philosophe.  
- Gestion des états : manger 🍝, dormir 😴, penser 🤔.  
- Protection des ressources (fourchettes) via mutex.  
- Fin propre du programme et détection de la mort d’un philosophe.  

---

## 🧱 Compilation
```bash
make
./philo [nb_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (optional [nb_meals])
