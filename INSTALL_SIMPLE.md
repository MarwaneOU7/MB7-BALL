# 🚀 GUIDE D'INSTALLATION WINDOWS - 3 ÉTAPES

## Étape 1️⃣: Installer MSYS2

**C'est la partie la plus importante!**

1. Télécharger: **https://www.msys2.org/**
2. Installer dans: `C:\msys64\`
3. Laisser les options par défaut
4. **Vérifier:** Un dossier `C:\msys64\` doit exister

---

## Étape 2️⃣: Installer GCC + Raylib

**Ouvrir "MSYS2 MinGW 64-bit" depuis le Menu Démarrer** (NON "MSYS2 MSYS")

Puis exécuter ces commandes UNE PAR UNE:

```bash
# Mettre à jour les paquets
pacman -Syu

# Installer GCC et Make
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make

# Installer Raylib
pacman -S mingw-w64-x86_64-raylib
```

**Répondre `y` (yes) à toutes les questions**

---

## Étape 3️⃣: Compiler et Lancer

**Dans MSYS2 MinGW 64-bit:**

```bash
cd /c/Users/Marouan/PROJECT\ JEUX/bouncing_balls

mingw32-make run
```

**Résultat:** Une fenêtre apparaît avec 3 balles qui rebondissent! 🎉

---

## ⚡ Commandes Rapides

```bash
# Compiler seulement
mingw32-make

# Compiler et lancer
mingw32-make run

# Nettoyer les fichiers compilés
mingw32-make clean

# Compiler en mode debug
mingw32-make debug
```

---

## ✅ Vérifications

Après installation, tester que tout fonctionne:

```bash
# Vérifier GCC
gcc --version
# Doit afficher: gcc (Rev...) ...

# Vérifier Raylib
pkg-config --cflags --libs raylib
# Doit afficher des chemins
```

---

## 🐛 Troubleshooting

### "gcc: command not found"
→ MSYS2 n'est pas installé ou au mauvais chemin
→ Réinstaller dans `C:\msys64\`

### "raylib not found"
→ Raylib n'a pas été installé
→ Relancer: `pacman -S mingw-w64-x86_64-raylib`

### "mingw32-make not found"
→ Make n'est pas installé
→ Relancer: `pacman -S mingw-w64-x86_64-make`

### Le programme se ferme immédiatement
→ Une erreur s'affiche
→ Vérifier Raylib est bien installé
→ Recompiler: `mingw32-make clean && mingw32-make`

---

## 🎯 Résumé (5 minutes)

1. Télécharger + installer MSYS2
2. Ouvrir "MSYS2 MinGW 64-bit"
3. Copier-coller les 3 commandes pacman
4. Taper: `mingw32-make run`
5. **DONE!** 🎉

---

## 📚 Pour Plus de Détails

Voir: [WINDOWS_SETUP.md](WINDOWS_SETUP.md) dans le projet

---

**Besoin d'aide supplémentaire? Consultez les fichiers documentation du projet!**
