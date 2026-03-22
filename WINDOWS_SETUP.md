# 🪟 Guide de Compilation et Installation - Windows

## Table des Matières
1. [Méthode Cheat Rapide](#méthode-rapide)
2. [Méthode Complète avec MinGW](#méthode-complète)
3. [Troubleshooting](#troubleshooting)

---

## 🚀 Méthode Rapide (5 minutes)

### Étape 1: Télécharger MinGW + GCC
1. Visiter: https://www.mingw-w64.org/
2. Télécharger le compilateur (gcc)
3. Installer dans `C:\mingw64\`
4. Ajouter `C:\mingw64\bin` au PATH Windows

Vérifier l'installation:
```powershell
gcc --version
```

### Étape 2: Installer Raylib via MSYS2 (Recommandé)
```powershell
# Installer MSYS2: https://www.msys2.org/
# Puis dans le terminal MSYS2:

pacman -S mingw-w64-x86_64-raylib
```

### Étape 3: Compiler
```powershell
cd C:\Users\Marouan\PROJECT JEUX\bouncing_balls
mingw32-make          # Si vous avez mingw-make
# OU
gcc -o build/bin/bouncing_balls.exe src/*.c -lraylib -lwinmm -Wall -std=c99
```

### Étape 4: Exécuter
```powershell
.\build\bin\bouncing_balls.exe
```

---

## 🔧 Méthode Complète avec MinGW

### Partie 1: Installer les Outils

#### Option A: MSYS2 (Recommandé)
```powershell
# 1. Télécharger MSYS2: https://www.msys2.org/
# 2. Installer
# 3. Ouvrir "MSYS2 MinGW 64-bit"
# 4. Exécuter:

pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-raylib
pacman -S mingw-w64-x86_64-cmake
```

#### Option B: MinGW Standalone
1. Télécharger de https://www.mingw-w64.org/
2. Extraire dans `C:\mingw64`
3. Ajouter à PATH

Vérifier:
```powershell
gcc --version
# Output: gcc (rev5, Built by MinGW-W64 project) 8.1.0
```

### Partie 2: Installer Raylib

#### Méthode 1: Via Pacman (MSYS2)
```bash
# Dans terminal MSYS2
pacman -Syu
pacman -S mingw-w64-x86_64-raylib
```

#### Méthode 2: Compiler Raylib localement
```bash
cd C:\
git clone https://github.com/raysan5/raylib.git
cd raylib/src
mingw32-make PLATFORM=WINDOWS
# Raylib compilé!
```

#### Méthode 3: Télécharger Binaire Pré-compilé
1. Aller sur: https://github.com/raysan5/raylib/releases
2. Télécharger: `raylib-x.x.x_Win64_msvc16.zip`
3. Extraire dans `C:\raylib\`

### Partie 3: Compiler le Projet

#### Si Raylib est Installé Globalement (MSYS2)
```powershell
cd C:\Users\Marouan\PROJECT JEUX\bouncing_balls
mingw32-make              # Utilise le Makefile
# OU manuellement:
gcc -o build/bin/bouncing_balls.exe src/*.c -lraylib -lwinmm -Wall -std=c99
```

#### Si Raylib est Local (`C:\raylib\`)
```powershell
gcc -o build/bin/bouncing_balls.exe src/*.c `
  -IC:\raylib\include -LC:\raylib\lib `
  -lraylib -lwinmm -luser32 -Wall -std=c99
```

### Partie 4: Valider la Compilation
```powershell
ls build\bin\
# Doit afficher: bouncing_balls.exe
```

### Partie 5: Exécuter
```powershell
.\build\bin\bouncing_balls.exe
```

---

## 📋 Commandes PowerShell Complètes

### Configuration en 1-2-3
```powershell
# 1. Naviguer
cd 'C:\Users\Marouan\PROJECT JEUX\bouncing_balls'

# 2. Compiler
mingw32-make

# 3. Exécuter
mingw32-make run
```

### Nettoyage
```powershell
mingw32-make clean
```

### Compilation Debug
```powershell
mingw32-make debug
```

---

## 🐛 Troubleshooting

### Problème: "gcc: command not found"
**Solution:**
1. Installer MinGW: https://www.mingw-w64.org/
2. Ajouter `C:\mingw64\bin` au PATH Windows
3. Redémarrer PowerShell

Tester:
```powershell
gcc --version
```

### Problème: "Raylib not found"
**Solution 1 (Via MSYS2):**
```bash
pacman -S mingw-w64-x86_64-raylib
```

**Solution 2 (Compiler Raylib):**
```bash
git clone https://github.com/raysan5/raylib.git
cd raylib/src
mingw32-make PLATFORM=WINDOWS
```

**Solution 3 (Indiquer le chemin):**
```powershell
gcc -IC:\raylib\include -LC:\raylib\lib src/*.c -lraylib -lwinmm -Wall -std=c99
```

### Problème: "make: command not found"
**Solution:**
- MSYS2 inclut Make automatiquement
- OU télécharger GnuWin32: http://gnuwin32.sourceforge.net/

```powershell
# Vérifier où est Make
where make
# Ajouter son dossier au PATH si nécessaire
```

### Problème: "undefined reference to `InitWindow@16'"
**Raison:** Raylib n'est pas linkée correctement

**Solution:** Ajouter les flags Windows
```powershell
gcc src/*.c -lraylib -lwinmm -luser32 -lgdi32 -Wall -std=c99
```

### Problème: La fenêtre se ferme immédiatement
**Raison:** Le programme plante probablement

**Solution:** Lancer depuis PowerShell pour voir l'erreur
```powershell
.\build\bin\bouncing_balls.exe
# Attendre le message d'erreur
```

---

## ✅ Checklist de Succès

- [ ] GCC est installé (`gcc --version` fonctionne)
- [ ] Raylib est trouvée par le compilateur
- [ ] Le Makefile local fonctionne (`mingw32-make` réussit)
- [ ] L'exécutable est créé dans `build\bin\bouncing_balls.exe`
- [ ] Le programme démarre correctement
- [ ] Les balles apparaissent et rebondissent
- [ ] Les clics souris ajoutent des balles
- [ ] Pas de warnings à la compilation

---

## 🎯 Configuration Finale Recommandée

### Outils à Installer
- ✅ MSYS2 + MinGW (gcc, make)
- ✅ Raylib via pacman
- ✅ Git pour version control

### Commandes à Connaître
```powershell
mingw32-make              # Compiler
mingw32-make run          # Compiler + exécuter
mingw32-make clean        # Nettoyer
mingw32-make debug        # Debug
```

### Pour Aller Plus Loin
- VSCode + Extension "C/C++"
- Raylib Documentation: https://www.raylib.com/
- C Reference: https://en.cppreference.com/w/c

---

**Windows Setup Complete! 🎉**
