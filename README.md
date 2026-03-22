# Simulation de Balles Rebondissantes - Raylib

## 📋 Description du Projet

Ce projet est une **simulation physique interactive** de balles rebondissantes développée en **C pur** avec la bibliothèque graphique **Raylib**.

### Objectif Pédagogique

Apprendre les concepts fondamentaux de:
- **Programmation en C**: organisation modulaire, gestion mémoire, pointeurs
- **Programmation objet**: structures, encapsulation, abstraction
- **Physique appliquée**: gravité, vélocité, élasticité, collisions
- **Graphique 2D**: rendu, animation, interactions utilisateur

---

## 🎯 Fonctionnalités

### ✓ Fonctionnalités Implémentées

- ✅ **Création dynamique de balles** - Cliquez pour ajouter des balles
- ✅ **Gravité réaliste** - Les balles tombent naturellement
- ✅ **Rebonds élastiques** - Rebonds sur les murs avec coefficient d'élasticité
- ✅ **Collisions entre balles** - Détection et gestion réaliste
- ✅ **Couleurs aléatoires** - Chaque balle a sa propre couleur
- ✅ **Mode debug** - Affichage des FPS et du nombre de balles
- ✅ **Gestion mémoire parfaite** - Tous les malloc ont leur free
- ✅ **Code bien structuré** - 4 modules séparés + main

---

## 🏗️ Architecture du Projet

```
bouncing_balls/
│
├── src/                          # Code source
│   ├── main.c                   # Point d'entrée du programme
│   ├── ball.h / ball.c          # Gestion des balles (structure + création/destruction)
│   ├── physics.h / physics.c    # Moteur physique (gravité, rebonds, collisions)
│   ├── game.h / game.c          # Logique du jeu et boucle principale
│   └── README_CODE.md           # Documentation du code
│
├── build/                        # (Créé après compilation)
│   ├── obj/                     # Fichiers objets (.o)
│   └── bin/                     # Exécutables
│
├── Makefile                      # Compilation multi-plateforme
├── .gitignore                    # Fichiers à ignorer pour Git
└── README.md                     # Ce fichier
```

### Structure Modulaire

#### 1. **ball.h / ball.c** - Gestion des Balles
Définit la structure `Ball` et les opérations de base:
```c
typedef struct {
    float x, y;           // Position
    float vx, vy;         // Vélocité
    float radius;         // Rayon
    float mass;           // Masse
    int color;            // Couleur RGB
} Ball;
```

- `Ball_Create(x, y, radius, color)` - Crée une balle
- `Ball_Destroy(ball)` - Libère la mémoire
- `Ball_PrintDebug(ball)` - Affiche les infos

#### 2. **physics.h / physics.c** - Moteur Physique
Implémente les lois de la physique:
- `Physics_ApplyGravity(ball)` - Applique la gravité
- `Physics_UpdatePosition(ball)` - Mise à jour de la position
- `Physics_BounceOnWalls(ball, w, h)` - Gestion des rebonds
- `Physics_CheckBallCollision(ball1, ball2)` - Collision élastique

#### 3. **game.h / game.c** - Logique du Jeu
Orchestration du jeu:
- `Game_Init()` - Initialisation
- `Game_AddBall()` - Ajouter une balle
- `Game_Update()` - Mises à jour (appelée chaque frame)
- `Game_Draw()` - Rendu graphique
- `Game_HandleInput()` - Gestion des entrées
- `Game_Run()` - Boucle principale

#### 4. **main.c** - Point d'Entrée
Lance simplement: Init → Run → Cleanup

---

## 🔬 Concepts Physiques Utilisés

### 1. Gravité
```
vy += GRAVITY (0.4 pixels/frame²)
```
- Accélération constante vers le bas
- Simule l'attraction terrestre

### 2. Vélocité et Position
```
x += vx
y += vy
```
- Mise à jour à chaque frame (60 FPS)
- Déplacement continu et fluide

### 3. Élasticité / Rebond
```
vx = -vx * ELASTICITY (0.95)
vy = -vy * ELASTICITY
```
- Inversion de la vélocité au rebond
- Perte d'énergie (coefficient < 1)

### 4. Friction de l'Air
```
vx *= AIR_FRICTION (0.999)
vy *= AIR_FRICTION
```
- Ralentit légèrement les balles
- Rend la simulation plus réaliste

### 5. Collision Élastique entre Balles
```
1. Détecte si distance < (r1 + r2)
2. Calcule la normale de collision
3. Échange les vélocités selon les masses
4. Sépare les balles pour éviter le chevauchement
```

**Formule de collision**:
- Conservation du momentum
- Échange de vélocité selon direction et masse
- Élasticité conservée

---

## 🛠️ Installation et Compilation

### Prérequis

- **Compilateur C**: GCC ou Clang (C99/C11 minimum)
- **Raylib**: Bibliothèque graphique

### 1. Installer Raylib

#### **Windows (MinGW)**
```bash
# Télécharger depuis https://github.com/raysan5/raylib/releases
# Extraire dans C:\raylib\

# Ou avec vcpkg:
vcpkg install raylib:x64-windows
```

#### **Linux (Debian/Ubuntu)**
```bash
sudo apt-get install libraylib-dev
# Ou via Makefile:
make install-raylib
```

#### **macOS (Homebrew)**
```bash
brew install raylib
# Ou via Makefile:
make install-raylib
```

### 2. Compiler le Projet

#### **Méthode 1: Avec Makefile (Recommandé)**
```bash
cd bouncing_balls
make              # Compilation normale
make run          # Compiler et exécuter
make debug        # Compilation en mode debug
make clean        # Nettoyer les fichiers
```

#### **Méthode 2: Compilation Manuelle**

**Windows (MinGW)**:
```bash
gcc -o build/bin/bouncing_balls.exe src/*.c -IC:\raylib\include -LC:\raylib\lib -lraylib -lwinmm -Wall -std=c99
```

**Linux**:
```bash
gcc -o build/bin/bouncing_balls src/*.c -lraylib -lm -Wall -std=c99
```

**macOS**:
```bash
gcc -o build/bin/bouncing_balls src/*.c -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL -Wall -std=c99
```

### 3. Exécuter

```bash
./build/bin/bouncing_balls        # Linux/macOS
./build/bin/bouncing_balls.exe    # Windows
```

---

## 🎮 Commandes d'Utilisation

| Commande | Action |
|----------|--------|
| **Clic Gauche** | Ajouter une balle à la position du curseur |
| **R** | Réinitialiser le jeu (supprimer toutes les balles) |
| **D** | Activer/désactiver le mode debug |
| **ESC** | Quitter le programme |

---

## 💾 Gestion de la Mémoire

### Allocation
```c
Ball* ball = Ball_Create(x, y, radius, color);   // malloc dans Ball_Create()
GameState* game = Game_Init();                    // malloc dans Game_Init()
```

### Libération
```c
Ball_Destroy(ball);       // free() dans Ball_Destroy()
Game_Cleanup(game);       // Libère toutes les balles + état
```

### Vérifications
- ✅ Tous les `malloc` ont un `free` correspondant
- ✅ Pas de fuites mémoire (testée avec Valgrind)
- ✅ Vérifications de NULL après allocation
- ✅ Nettoyage au quitter du programme

---

## 📊 Constantes Configurables

Dans [physics.h](src/physics.h):
```c
#define GRAVITY          0.4f    // Intensité de la gravité
#define ELASTICITY       0.95f   // Rebond (1.0 = parfait, 0 = absorbant)
#define AIR_FRICTION     0.999f  // Résistance de l'air
#define MAX_VELOCITY     15.0f   // Vitesse maximale autorisée
```

Dans [game.h](src/game.h):
```c
#define WINDOW_WIDTH     1200    // Largeur fenêtre
#define WINDOW_HEIGHT    700     // Hauteur fenêtre
#define TARGET_FPS       60      // FPS cible
#define MAX_BALLS        100     // Limite de balles
```

---

## 📈 Améliorations Possibles

### Niveau 1: Améliorations Simples (pour la soutenance)

1. **Statistiques en temps réel**
   - Énergie totale du système
   - Vitesse moyenne des balles
   - Nombre de collisions par frame

2. **Interactions Supplémentaires**
   - Clic droit: Supprimer une balle
   - Glisser-déposer: Déplacer une balle
   - Espace: Lancer les balles en l'air

3. **Paramètres Modifiables en Jeu**
   - Touches numériques pour changer la gravité
   - + / - pour augmenter/réduire l'élasticité
   - Affichage des paramètres actuels

4. **Présets de Scènes**
   - Touche 1: Scène équilibrée
   - Touche 2: Forte gravité
   - Touche 3: Très élastique (antigravité)

### Niveau 2: Améliorations Intermédiaires

5. **Types de Balles Différentes**
   - Balles légères vs lourdes
   - Balles collantes vs élastiques
   - Balles magnétiques

6. **Obstacles et Décor**
   - Murs immobiles à divers angles
   - Plateformes mobiles
   - Trampoline (augmente l'élasticité)

7. **Effets Visuels**
   - Traînée des balles (trail effect)
   - Particules au collision
   - Glow effect sur les balles

### Niveau 3: Améliorations Avancées

8. **Physique Avancée**
   - Rotation des balles + friction de roulement
   - Forces externes (vent, magnétisme)
   - Déformation des balles au collision

9. **Sauvegarde/Chargement**
   - Enregistrer une configuration
   - Charger une scène prédéfinie
   - Export en fichier de configuration

10. **Optimisation Performace**
    - Algorithme broad-phase (quadtree, spatial hashing)
    - Multi-threading pour les collisions
    - Culling (ne pas calculer les objets hors écran)

### Niveau 4: Idées Créatives

11. **Modes de Jeu**
    - Mode sandbox libre
    - Mode objectif (faire tomber dans des trous)
    - Mode temps (scores = balles + durée)

12. **Intégration Audio**
    - Son du rebond
    - Musique de fond
    - Feedbackaudio au collision

13. **Simulation Avancée**
    - Liquide (mouvement dans l'eau)
    - Feu (particules, physique différente)
    - Câbles élastiques entre balles

---

## 🐛 Débogage

### Mode Debug
Appuyez sur **D** pour activer le mode debug qui affiche:
- FPS en temps réel
- Nombre de balles
- Position de la souris

### Avec Valgrind (Linux)
```bash
valgrind --leak-check=full ./build/bin/bouncing_balls
```

### Avec GDB (débogueur)
```bash
gdb ./build/bin/bouncing_balls
(gdb) run
(gdb) break main
(gdb) print variable_name
```

---

## 📝 Code Quality

- ✅ **Standard C99**: Compatible avec tous les compilateurs modernes
- ✅ **Documentation**: Chaque fonction a un commentaire Doxygen
- ✅ **Lisibilité**: Indentation 4 espaces, variables explicites
- ✅ **Modularité**: Chaque module = une responsabilité unique
- ✅ **Absence de Warnings**: Compilé avec `-Wall -Wextra`
- ✅ **Pas de Code Mort**: Tout le code est utilisé

---

## 👨‍💻 Auteur et Licence

**Auteur**: Étudiant Ingénieria  
**Année**: Projet de Première Année  
**Licence**: MIT (usage libre)

---

## 🔗 Ressources Utiles

- **Raylib Documentation**: https://www.raylib.com/
- **C Reference**: https://en.cppreference.com/w/c
- **Physique des Collisions**: https://en.wikipedia.org/wiki/Collision_detection
- **Doxygen (documentation)**: https://www.doxygen.nl/

---

## ✨ Conseils pour la Soutenance

1. **Démo en temps réel**: Montrez comment ajouter des balles et les voir interagir
2. **Expliquez l'architecture**: Montrez comment le code est organisé en modules
3. **Parlez physique**: Explique les constantes (gravité, élasticité, friction)
4. **Montrez le code**: Ouvrez un fichier source et expliquez les fonctions principales
5. **Discutez améliorations**: Mentionnez les possibilités d'extension
6. **Stress test**: Ajoutez 50+ balles pour montrer la stabilité
7. **Performance**: Montrez que le programme tourne à 60 FPS stable

---

### 🎓 Compétences Évaluées

Ce projet démontre votre maîtrise de:
- ✅ Programmation modulaire et réutilisable
- ✅ Gestion correcte de la mémoire en C
- ✅ Structures de données (arrays, structs)
- ✅ Algorithmes (collision, physique)
- ✅ Compréhension de la physique appliquée
- ✅ Utilisation de bibliothèques externes
- ✅ Documentation et commentaires
- ✅ Compilation multi-plateforme

**Bon projet! 🚀**
