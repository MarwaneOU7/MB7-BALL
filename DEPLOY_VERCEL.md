# 🚀 Déployer sur Vercel en 2 minutes

## Option 1: Déploiement automatique via GitHub (RECOMMANDÉ ✨)

### Étape 1: Allez sur Vercel
```
https://vercel.com
```

### Étape 2: Connectez-vous avec GitHub
- Cliquez **"Sign Up"** ou **"Log In"**
- Choisissez **"Continue with GitHub"**

### Étape 3: Autorisez Vercel
- Cliquez **"Authorize Vercel"**
- Sélectionnez vos repositories (ou "All repositories")

### Étape 4: Déployez
- Cherchez **"MB7-BALL"** dans la liste
- Cliquez **"Import"**
- Cliquez **"Deploy"**

### C'est fini! ✅
L'application sera disponible à:
```
https://mb7-ball.<votre-vercel-id>.vercel.app
```

---

## Option 2: Déploiement via CLI (si Node.js est installé)

### Étape 1: Installer Node.js
```
https://nodejs.org/
```

### Étape 2: Installer Vercel CLI
```powershell
npm install -g vercel
```

### Étape 3: Se connecter à Vercel
```powershell
vercel login
```

### Étape 4: Déployer
```powershell
cd "C:\Users\Marouan\PROJECT JEUX\bouncing_balls"
vercel
```

### Étape 5: Répondre aux questions
```
? Set up and deploy "C:\Users\Marouan\PROJECT JEUX\bouncing_balls"? [Y/n] y
? Which scope do you want to deploy to? [votre-scope]
? Link to existing project? [y/N] n
? What's your project's name? bouncing-balls
? In which directory is your code located? . (current)
```

---

## 🎉 Après le déploiement

Votre application sera:
- ✅ Accessible en ligne 24/7
- ✅ Auto-scalable (Vercel gère la charge)
- ✅ Avec HTTPS gratuit
- ✅ Déploiements automatiques à chaque push sur GitHub

### URL en direct:
```
https://mb7-ball-<random>.vercel.app
```

### Domaine personnel (optionnel):
- Allez sur dashboard Vercel
- Settings → Domains
- Connectez votre domaine personnalisé

---

## 📊 Variables d'environnement

Si vous avez besoin de variables secrets:

1. Vercel Dashboard → Settings → Environment Variables
2. Ajoutez vos variables
3. Les futures versions utiliseront auto

---

## 🔄 Mises à jour futures

Une fois déployé:
- Chaque **push sur GitHub** = déploiement automatique
- Pas besoin de commandes supplémentaires
- Vercel fait tout automatiquement

---

## ❌ Troubleshooting

**Le déploiement échoue?**
- Vérifiez que `bouncing_balls.html` existe et est valide
- Assurez-vous que `vercel.json` est configuré correctement
- Vérifiez les logs dans Vercel Dashboard → Deployments

**La page affiche 404?**
- Vérifiez que le fichier HTML est au root
- Vercel doit servir `bouncing_balls.html` par défaut

**Problèmes de permissions?**
- GitHub et Vercel doivent être connectés
- Vérifiez les paramètres d'accès Vercel

---

## 📚 Resources

- Vercel Docs: https://vercel.com/docs
- GitHub Integration: https://vercel.com/docs/concepts/git
- Static Sites: https://vercel.com/docs/frameworks/static

---

**Status**: Application prête pour Vercel ✅
- vercel.json créé ✅
- package.json créé ✅  
- Code pushé sur GitHub ✅
