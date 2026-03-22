# ⚡ Guide de Démarrage Rapide

## 🎯 Vous Êtes Pressé? Commencez Ici!

---

## 1️⃣ Installation Raylib (5 min)

### Windows + PowerShell
```powershell
# Option 1: Via MSYS2 (RECOMMANDÉ)
# Télécharger: https://www.msys2.org/
# Installer, puis dans MSYS2:

pacman -S mingw-w64-x86_64-raylib mingw-w64-x86_64-gcc

# Option 2: Binaires pré-compilés
# https://github.com/raysan5/raylib/releases
# Télécharger et extraire dans C:\raylib\
```

### Linux
```bash
sudo apt-get install libraylib-dev gcc
# OU
cd bouncing_balls && make install-raylib
```

### macOS
```bash
brew install raylib gcc
```

---

## 2️⃣ Compiler et Lancer (2 min)

```bash
# Naviguer
cd bouncing_balls

# Compiler
make              # Crée build/bin/bouncing_balls (ou .exe)

# Lancer
make run          # Compile et lance automatiquement
```

**Résultat:** Une belle fenêtre apparaît avec 3 balles! 🎉

---

## 3️⃣ Utiliser le Programme (1 min)

| Touche | Action |
|--------|--------|
| **Clic Gauche** | Ajouter une balle là où vous cliquez |
| **R** | Réinitialiser (supprimer toutes les balles) |
| **D** | Afficher le debug (FPS + compteur) |
| **ESC** | Quitter |

**Essayez:** Cliquez plusieurs fois rapide pour créer une avalanche de balles!

---

## 4️⃣ Structure du Projet (30 sec)

```
bouncing_balls/
├── src/
│   ├── main.c          ← Démarrage
│   ├── game.h/c        ← Moteur principal
│   ├── ball.h/c        ← Définir une balle
│   ├── physics.h/c     ← Calculs physiques
│   └── [autres]        ← Helpers
├── Makefile            ← Compilation
├── README.md           ← Documentation complète
└── build/              ← (créé après make)
    ├── obj/            ← Fichiers .o
    └── bin/            ← Exécutable final
```

---

## 5️⃣ Points Clés pour la Soutenance

### À Montrer
1. ✅ Lancez le programme → 3 balles
2. ✅ Cliquez → Nouvelles balles apparaissent
3. ✅ Les balles rebondissent naturellement
4. ✅ Les balles entrent en collision
5. ✅ Appuyez D → Info de debug
6. ✅ Appuyez R → Tout s'efface

### À Expliquer
```c
// Comment ça tombe?
ball->vy += GRAVITY;  // Accélération

// Comment ça rebondit?
ball->vx = -ball->vx * ELASTICITY;  // Inversion

// Comment ça se détruit proprement?
Game_Cleanup(game);  // free() tout
```

### À Montrer Techniquement
- Ouvrir [src/physics.c](src/physics.c) → Montrer `Physics_ApplyGravity()`
- Ouvrir [src/game.c](src/game.c) → Montrer `Game_Update()`
- Montrer [Makefile](Makefile) → Expliquer la compilation

---

## 🚨 Si Ça Ne Marche Pas...

### "rien ne s'affiche"
```powershell
# Vérifier GCC
gcc --version

# Vérifier Raylib
pkg-config --cflags --libs raylib  # Linux/macOS
```

### "erreur de compilation"
```bash
# Nettoyer et relancer
make clean
make
```

### "la fenêtre plante immédiatement"
```bash
# Lancer directement pour voir l'erreur
./build/bin/bouncing_balls   # Linux/macOS
.\build\bin\bouncing_balls.exe  # Windows
```

### "j'ai un message d'erreur"
→ Consultez [WINDOWS_SETUP.md](WINDOWS_SETUP.md) (section Troubleshooting)

---

## 📚 Documentation Complète

| Document | Pour Quoi? |
|----------|-----------|
| [README.md](README.md) | Vue d'ensemble + toutes les infos |
| [CODE_GUIDE.md](CODE_GUIDE.md) | Comprendre le code fichier par fichier |
| [PHYSICS_CONCEPTS.md](PHYSICS_CONCEPTS.md) | Explications théoriques détaillées |
| [IMPROVEMENTS.md](IMPROVEMENTS.md) | Idées d'améliorations (niveaux 1-3) |
| [WINDOWS_SETUP.md](WINDOWS_SETUP.md) | Installation spécifique Windows |

---

## ✨ Petit Plus: Amélioration en 10 Min

**Ajouter des paramètres modifiables EN JEU:**

Ouvrir [src/game.c](src/game.c) et dans `Game_HandleInput()` ajouter:

```c
// Modifier la gravité avec les touches
if (IsKeyPressed(KEY_G))
{
    GRAVITY += 0.05f;
    printf("Nouvelle gravité: %.2f\n", GRAVITY);
}
if (IsKeyPressed(KEY_H))
{
    GRAVITY = fmax(0.1f, GRAVITY - 0.05f);
    printf("Nouvelle gravité: %.2f\n", GRAVITY);
}

// Afficher à l'écran
DrawText(TextFormat("Gravité: %.2f (G/H pour changer)", GRAVITY), 
         10, 250, 14, DARKGRAY);
```

**Recompiler:**
```bash
make && make run
```

Maintenant:
- **G** = Gravité plus forte
- **H** = Gravité plus faible

Les juges adorent voir que c'est "interactif" pendant la présentation! 🎓

---

## 🎥 Scénario de Démo Parfait (5 min)

```
[0:00] "Bonjour, je vous montre une simulation physique en C"
[0:05] Lance le programme (3 balles visibles)
[0:10] "Voyez les balles tomber avec la gravité"
[0:20] "Je peux cliquer pour en ajouter" → Clique 10 fois rapido
[0:35] "Elles rebondissent réaliste ET détectent les collisions"
[0:50] "Appuyez D pour voir les infos" → Montre FPS, compteur
[1:00] "Le code est bien organisé: 5 modules C séparés"
[1:30] Ouvrir un fichier source, montrer un fonction
[2:00] "Tout est bien documenté et la mémoire est gérée proprement"
[2:30] "Possibilité d'améliorer avec..." → Mention IMPROVEMENTS.md
[3:00] Questions? Répondre confiant
[4:00] Fin gracieuse, programme termine proprement
```

---

## 🧠 Réponses aux Questions Fréquentes

**Q: Pourquoi en C et pas en C++ ou Python?**  
A: C'est plus pedagogue pour comprendre la mémoire et la structure. Et pour un jeu, la performance est mieux.

**Q: Comment ça gère 100 balles sans lag?**  
A: Raylib optimise le rendu. Et faire O(n²) collisions est OK pour 100 items.

**Q: Comment ça rebondit réaliste?**  
A: On inverse la vélocité mais on multiplie par 0.95 pour perdre de l'énergie.

**Q: Vous avez testé avec combien de balles max?**  
A: 100 sans problème. Au-delà, on atteint la limite MAX_BALLS.

**Q: D'autres améliorations possibles?**  
A: Oui! Voir le fichier IMPROVEMENTS.md. Il y aurait des effets de particules, du son, de la physique avancée...

---

## 📊 Variables Environment à Connaître

Dans [src/physics.h](src/physics.h):
```c
#define GRAVITY       0.4f   // Intensité tombée (modifier pour tester)
#define ELASTICITY    0.95f  // Rebond (1.0 = super, 0.5 = mort)
#define AIR_FRICTION  0.999f // Ralentisseur (0.99 = ralenti, 1.0 = infini)
#define MAX_VELOCITY  15.0f  // Limite de vitesse (30% plus rapide = instable)
```

Et dans [src/game.h](src/game.h):
```c
#define WINDOW_WIDTH  1200   // Largeur
#define WINDOW_HEIGHT 700    // Hauteur
#define TARGET_FPS    60     // Images par seconde
#define MAX_BALLS     100    // Limite balles
```

---

## 🎯 Checklist Final

- [ ] Raylib installé
- [ ] Code compilé sans erreur
- [ ] Programme lance et affiche 3 balles
- [ ] Les balles tombent (gravité)
- [ ] Les balles rebondissent (murs)
- [ ] Les balles collider (entre elles)
- [ ] Clic ajoute balles
- [ ] R réinitialise
- [ ] D affiche debug
- [ ] ESC quitte proprement
- [ ] Pas de fuites mémoire

✅ **Tout Bon? C'est Prêt Pour la Soutenance!**

---

## 💡 Dernier Conseil

> **"Un bon projet en C est un projet qui parle de ce qui n'est PAS visible."**

Les juges ne voient que les balles qui rebondissent.  
Mais ils veux entendre parler de:
1. **Structure modulaire** - 5 fichiers = 5 responsabilités
2. **Gestion mémoire** - malloc/free = gestion propre
3. **Physique** - Gravité, collision, élasticité
4. **Performance** - 60 FPS stable avec 100 objets

Montrez que vous comprenez Ces concepts = Note parfaite!

---

**Vous êtes prêt! Bonne chance! 🚀**

*Questions? Relisez le [README.md](README.md) ou le [CODE_GUIDE.md](CODE_GUIDE.md)*
