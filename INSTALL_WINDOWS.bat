@echo off
REM ╔══════════════════════════════════════════════════════════════╗
REM ║  Script d'Installation Automatisée - Windows                ║
REM ║  Installe MinGW + Raylib pour le projet bouncing_balls      ║
REM ║  Exécutez comme administrateur!                             ║
REM ╚══════════════════════════════════════════════════════════════╝

setlocal enabledelayedexpansion
color 0A
title Installation Raylib - Bouncing Balls Project

echo.
echo ╔════════════════════════════════════════════════════════════╗
echo ║     INSTALLATION AUTOMATISÉE - RAYLIB + GCC                ║
echo ║     Pour: Simulation de Balles Rebondissantes             ║
echo ╚════════════════════════════════════════════════════════════╝
echo.

REM Vérifier si l'utilisateur est administrateur
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo ⚠️  ERREUR: Ce script doit s'exécuter en administrateur!
    echo.
    echo Solution:
    echo 1. Clic droit sur ce fichier
    echo 2. Sélectionner "Exécuter en tant qu'administrateur"
    pause
    exit /b 1
)

echo ✓ Exécution en mode administrateur confirmée
echo.

REM ═══════════════════════════════════════════════════════════════
REM Étape 1: Vérifier MSYS2
REM ═══════════════════════════════════════════════════════════════

echo [1/4] Vérification MSYS2...
echo.

if exist "C:\msys64\msys2_shell.cmd" (
    echo ✓ MSYS2 détecté à C:\msys64
) else (
    echo ⚠️  MSYS2 n'est pas trouvé
    echo.
    echo TÉLÉCHARGER MSYS2:
    echo 1. Allez sur: https://www.msys2.org/
    echo 2. Téléchargez msys2-x86_64-latest.exe
    echo 3. Installez dans C:\msys64\
    echo 4. Relancez ce script
    echo.
    pause
    exit /b 1
)

echo.

REM ═══════════════════════════════════════════════════════════════
REM Étape 2: Installer MinGW GCC via MSYS2
REM ═══════════════════════════════════════════════════════════════

echo [2/4] Installation MinGW GCC (peut prendre 5 min)...
echo.

REM Lancer MSYS2 et installer gcc
C:\msys64\msys2_shell.cmd -defterm -no-start -c "pacman -S --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-make"

if %errorLevel% neq 0 (
    echo ⚠️  Erreur lors de l'installation de GCC
    pause
    exit /b 1
)

echo ✓ GCC installé avec succès!
echo.

REM ═══════════════════════════════════════════════════════════════
REM Étape 3: Installer Raylib
REM ═══════════════════════════════════════════════════════════════

echo [3/4] Installation Raylib (peut prendre 3 min)...
echo.

C:\msys64\msys2_shell.cmd -defterm -no-start -c "pacman -S --noconfirm mingw-w64-x86_64-raylib"

if %errorLevel% neq 0 (
    echo ⚠️  Erreur lors de l'installation de Raylib
    pause
    exit /b 1
)

echo ✓ Raylib installé avec succès!
echo.

REM ═══════════════════════════════════════════════════════════════
REM Étape 4: Vérifier l'installation
REM ═══════════════════════════════════════════════════════════════

echo [4/4] Vérification de l'installation...
echo.

REM Ajouter MSYS2 au PATH temporaire
set PATH=C:\msys64\mingw64\bin;%PATH%

echo Vérification GCC...
gcc --version
if %errorLevel% neq 0 (
    echo ⚠️  GCC n'a pas pu être testé
    echo Vérifiez manuellement: C:\msys64\mingw64\bin\gcc.exe
    timeout /t 5
)

echo.
echo ✓ Installation terminée avec succès!
echo.

REM ═══════════════════════════════════════════════════════════════
REM Étape 5: Compiler le projet
REM ═══════════════════════════════════════════════════════════════

echo [BONUS] Tentative de compilation du projet...
echo.

cd /d "C:\Users\Marouan\PROJECT JEUX\bouncing_balls"

REM Windows utilise mingw32-make et non make
REM Essayer de compiler avec le PATH modifié
call C:\msys64\msys2_shell.cmd -defterm -no-start -c "cd /c/Users/Marouan/PROJECT\ JEUX/bouncing_balls && mingw32-make clean && mingw32-make"

if %errorLevel% equ 0 (
    echo.
    echo ╔════════════════════════════════════════════════════════════╗
    echo ║  ✅ COMPILATION RÉUSSIE!                                  ║
    echo ╚════════════════════════════════════════════════════════════╝
    echo.
    echo Pour lancer le programme:
    echo   mingw32-make run
    echo.
) else (
    echo.
    echo ⚠️  Compilation n'a pas abouti en automatique
    echo Procédure manuelle:
    echo.
    echo 1. Ouvrir "MSYS2 MinGW 64-bit" depuis le menu Démarrer
    echo 2. Taper:
    echo    cd /c/Users/Marouan/PROJECT\ JEUX/bouncing_balls
    echo    mingw32-make run
    echo.
)

echo.
echo ╔════════════════════════════════════════════════════════════╗
echo ║  Installation terminée!                                    ║
echo ║  Appuyez sur une touche pour quitter...                   ║
echo ╚════════════════════════════════════════════════════════════╝
pause

exit /b 0
