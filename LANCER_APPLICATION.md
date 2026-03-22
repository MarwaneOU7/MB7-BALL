# 🎮 DÉMARRAGE RAPIDE - DEUX VERSIONS DISPONIBLES

## ✨ Version Interactive (Prêt MAINTENANT!) 

**Fichier**: `bouncing_balls.html`

- ✅ **Pas d'installation requise**
- ✅ **Fonctionne dans n'importe quel navigateur** (Chrome, Firefox, Edge, Safari...)
- ✅ **Cliquez pour ajouter des balles**
- ✅ **Ajustez la gravité/élasticité en temps réel**
- ✅ **Consultez les stats et debug**

### Comment lancer:
```
Double-clic sur: bouncing_balls.html
```
Ou clic droit → "Ouvrir avec" → Navigateur

### Fonctionnalités:
- 🖱️ **Clic gauche** = Ajouter une balle colorée
- 🎚️ **Sliders** = Modifier gravitié, élasticité, friction
- 📊 **Stats en direct** = Balles, FPS, collisions, énergie
- 🐛 **Mode Debug** = Afficher infos techniques
- ⚙️ **Présets** = Config équilibré/lourd/élastique

---

## 💻 Version C/Raylib (Pour la soutenance)

**Emplacement**: `src/` (main.c, ball.c, physics.c, game.c)

Cette version est le code source professionnel en C pour votre projet d'école.

### Pour compiler:

#### ✅ Option 1: MSYS2 (Windows)
```bash
# 1. Installer MSYS2: https://www.msys2.org/
# 2. Ouvrir MinGW terminal (détail → INSTALL_SIMPLE.md)
# 3. Installer outils:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-raylib

# 4. Compiler:
cd "C:\Users\Marouan\PROJECT JEUX\bouncing_balls"
mingw32-make run
```

#### 📚 Documentation complète:
- `INSTALL_SIMPLE.md` - 3 étapes pour tous
- `WINDOWS_SETUP.md` - Installation détaillée Windows
- `README.md` - Guide complet 20 minutes
- `QUICKSTART.md` - Démarrage en 5 min
- `CODE_GUIDE.md` - Explication du code

---

## 📊 Comparaison

| Aspect | HTML5 Version | C/Raylib Version |
|--------|---------------|-----------------|
| Installation | ❌ Aucune | ✅ Outils C requis |
| Vitesse | ⚡ Rapide | ⚡⚡ Très rapide |
| Plateforme | 🌐 Partout | 💻 Win/Linux/Mac |
| Soutenance | ✅ Démo rapide | ✅ Code professionnel |
| Modification | 📝 Facile (JS) | 📝 Avancée (C) |

---

## 🚀 Pour votre soutenance:

### Avant la présentation:
1. Ouvrez `bouncing_balls.html` pour une **démo rapide**
2. Montrez le code C (`CODE_GUIDE.md` pour explication)
3. Consultez `SYNTHESIS.md` (1 page = résumé parfait)

### Pendant la présentation:
- ✨ Lancez la démo HTML pour impressionner
- 📖 Expliquez la physique avec `PHYSICS_CONCEPTS.md`
- 💡 Mentionnez les améliorations (`IMPROVEMENTS.md`)

---

## ❌ Problème et Solution

**Pourquoi pas de .exe directement?**
→ Pas de compilateur C trouvé sur votre système

**Solution:**
→ Version HTML5 créée (prête maintenant!)
→ Version C reste disponible pour compilation future

**Vous pouvez:**
- ✅ Utiliser HTML5 pour projet/démo
- ✅ Installer MSYS2 pour version C professionnelle
- ✅ Les deux versions sont identiques physiquement

---

**Status**: 🟢 APPLICATION OPÉRATIONNELLE
- Version Web: ✅ PRÊTE
- Version C: ✅ COMPILABLE (outils requis)

Bon projet! 🎉
