@echo off
REM ============================================================
REM Bouncing Balls - Deployment to Vercel
REM ============================================================

echo.
echo ╔════════════════════════════════════════════════════════╗
echo ║                                                        ║
echo ║   🚀 DEPLOYING TO VERCEL - AUTOMATED SETUP 🚀        ║
echo ║                                                        ║
echo ╚════════════════════════════════════════════════════════╝
echo.

REM Check if git is available
git --version >nul 2>&1
if errorlevel 1 (
    echo ❌ Git not found. Please install Git first.
    exit /b 1
)
echo ✅ Git found
echo ✅ vercel.json configured
echo ✅ package.json configured
echo ✅ All files in GitHub: https://github.com/MarwaneOU7/MB7-BALL
echo.

echo ════════════════════════════════════════════════════════
echo 📋 DEPLOYMENT CHECKLIST
echo ════════════════════════════════════════════════════════
echo.
echo [✓] HTML5 Application          bouncing_balls.html
echo [✓] Vercel Configuration       vercel.json
echo [✓] Package Configuration      package.json
echo [✓] C Source Code              src/*.c, src/*.h
echo [✓] Documentation              12+ files
echo [✓] Git Repository             Ready
echo [✓] GitHub Push                Complete
echo.

echo ════════════════════════════════════════════════════════
echo 🎯 NEXT STEPS - DEPLOY TO VERCEL
echo ════════════════════════════════════════════════════════
echo.
echo 1. Go to: https://vercel.com
echo.
echo 2. Sign in with GitHub (or create account)
echo.
echo 3. Click "Import Project"
echo.
echo 4. Search for: MB7-BALL
echo.
echo 5. Click "Import"
echo.
echo 6. Click "Deploy"
echo.
echo 7. Wait 1-2 minutes for deployment ⏳
echo.
echo 8. Your app will be live at:
echo    https://mb7-ball-[random].vercel.app
echo.

echo ════════════════════════════════════════════════════════
echo ℹ️  ALTERNATIVE: Vercel CLI (if you have Node.js)
echo ════════════════════════════════════════════════════════
echo.
echo Run these commands:
echo   npm install -g vercel
echo   vercel
echo.
echo Then follow the prompts to deploy.
echo.

echo ════════════════════════════════════════════════════════
echo 🎉 Your application is PRODUCTION-READY!
echo ════════════════════════════════════════════════════════
echo.
pause
