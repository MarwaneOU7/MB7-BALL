#!/bin/bash
# ╔══════════════════════════════════════════════════════════════╗
# ║  Script d'Installation - Linux                              ║
# ║  Installe Raylib + GCC pour le projet bouncing_balls        ║
# ╚══════════════════════════════════════════════════════════════╝

set -e  # Exit on error

echo ""
echo "╔════════════════════════════════════════════════════════════╗"
echo "║     INSTALLATION AUTOMATISÉE - RAYLIB + GCC                ║"
echo "║     Pour: Simulation de Balles Rebondissantes             ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo ""

# Déterminer le gestionnaire de paquets
if command -v apt-get &> /dev/null; then
    PACKAGE_MANAGER="apt-get"
    INSTALL_CMD="sudo apt-get install -y"
    UPDATE_CMD="sudo apt-get update"
elif command -v yum &> /dev/null; then
    PACKAGE_MANAGER="yum"
    INSTALL_CMD="sudo yum install -y"
    UPDATE_CMD="sudo yum update"
elif command -v pacman &> /dev/null; then
    PACKAGE_MANAGER="pacman"
    INSTALL_CMD="sudo pacman -S --noconfirm"
    UPDATE_CMD="sudo pacman -Syu"
else
    echo "⚠️  Gestionnaire de paquets non reconnu"
    exit 1
fi

echo "[1/3] Mise à jour des paquets ($PACKAGE_MANAGER)..."
$UPDATE_CMD

echo ""
echo "[2/3] Installation GCC et outils de compilation..."
$INSTALL_CMD build-essential

echo ""
echo "[3/3] Installation Raylib..."

if [ "$PACKAGE_MANAGER" = "apt-get" ]; then
    $INSTALL_CMD libraylib-dev
elif [ "$PACKAGE_MANAGER" = "yum" ]; then
    $INSTALL_CMD raylib-devel
elif [ "$PACKAGE_MANAGER" = "pacman" ]; then
    $INSTALL_CMD raylib
fi

echo ""
echo "✓ Installation terminée!"
echo ""
echo "Pour compiler le projet:"
echo "  cd c:/Users/Marouan/PROJECT\ JEUX/bouncing_balls"
echo "  make run"
echo ""
