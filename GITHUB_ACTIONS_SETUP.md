# 🚀 AUTOMATIC DEPLOYMENT SETUP

Your GitHub Actions workflow is ready for automatic Vercel deployment!

## ⚙️ ONE-TIME SETUP (5 minutes):

### Step 1: Get Your Vercel Tokens
1. Go to: https://vercel.com/account/tokens
2. Click: "Create Token"
3. Name it: `VERCEL_TOKEN`
4. Copy the token

### Step 2: Get Your Vercel Project ID
1. Go to: https://vercel.com/dashboard
2. Select: "bouncing-balls" project (after first deploy)
3. Go to: Settings → General
4. Find: "Project ID"
5. Copy it

### Step 3: Get Your Vercel Org ID
1. Go to: https://vercel.com/account
2. Find: "Team ID" (in account settings)
3. Copy it

### Step 4: Add Secrets to GitHub
1. Go to: https://github.com/MarwaneOU7/MB7-BALL
2. Settings → Secrets and variables → Actions
3. Click: "New repository secret"

Create 3 secrets:
- **Name:** `VERCEL_TOKEN`     **Value:** [paste token from Step 1]
- **Name:** `VERCEL_ORG_ID`    **Value:** [paste org ID from Step 3]  
- **Name:** `VERCEL_PROJECT_ID` **Value:** [paste project ID from Step 2]

### Step 5: Enable Automatic Deployment
- Workflow is already configured in: `.github/workflows/deploy.yml`
- Next `git push` will auto-deploy to Vercel!

## ✨ AFTER SETUP - HOW IT WORKS:

Every time you push to GitHub:
```bash
git add .
git commit -m "Update"
git push
```

→ GitHub Actions automatically builds and deploys to Vercel! 🎉

## 📊 DEPLOYMENT FLOW:

```
You push to GitHub
        ↓
GitHub Actions triggers
        ↓
Vercel deploys your app
        ↓
https://mb7-ball-xxx.vercel.app goes LIVE! ✨
```

## 🔍 MONITOR DEPLOYMENTS:

- GitHub: Actions tab → See workflows running/completed
- Vercel: Dashboard → Deployments tab → See live updates
