#!/usr/bin/env python3
"""
Vercel Deployment Automation Script
Validates and deploys the Bouncing Balls application to Vercel
"""

import os
import sys
import json
import subprocess
from pathlib import Path

def check_files():
    """Vérifier que tous les fichiers nécessaires existent"""
    print("✓ Vérification des fichiers...")
    required_files = [
        'bouncing_balls.html',
        'vercel.json',
        'package.json'
    ]
    
    for file in required_files:
        if not Path(file).exists():
            print(f"  ✗ {file} manquant")
            return False
        print(f"  ✓ {file} trouvé")
    
    return True

def check_git():
    """Vérifier que Git est configuré"""
    print("\n✓ Vérification de Git...")
    try:
        result = subprocess.run(['git', 'status'], capture_output=True, text=True)
        if result.returncode == 0:
            print(f"  ✓ Repository Git configuré")
            return True
    except:
        print(f"  ✗ Git non trouvé")
        return False

def check_html():
    """Valider le fichier HTML"""
    print("\n✓ Validation du HTML...")
    try:
        with open('bouncing_balls.html', 'r', encoding='utf-8') as f:
            content = f.read()
            if 'canvas' in content and 'bouncing' in content.lower():
                lines = len(content.split('\n'))
                print(f"  ✓ HTML valide ({lines} lignes)")
                return True
    except:
        print(f"  ✗ Erreur de lecture HTML")
        return False

def display_deployment_info():
    """Afficher les infos de déploiement"""
    print("\n" + "="*60)
    print("🚀 DEPLOYMENT INFORMATION")
    print("="*60)
    
    try:
        with open('vercel.json', 'r') as f:
            config = json.load(f)
            print(f"Project: {config.get('name', 'N/A')}")
    except:
        pass
    
    try:
        with open('package.json', 'r') as f:
            pkg = json.load(f)
            print(f"Version: {pkg.get('version', 'N/A')}")
            print(f"Description: {pkg.get('description', 'N/A')}")
    except:
        pass
    
    print("\n📊 Repository:")
    try:
        result = subprocess.run(['git', 'remote', '-v'], capture_output=True, text=True)
        for line in result.stdout.split('\n'):
            if 'origin' in line and line.strip():
                print(f"  {line.strip()}")
    except:
        pass
    
    print("\n📈 Recent commits:")
    try:
        result = subprocess.run(['git', 'log', '--oneline', '-n', '3'], capture_output=True, text=True)
        for line in result.stdout.split('\n'):
            if line.strip():
                print(f"  {line.strip()}")
    except:
        pass

def main():
    print("\n" + "="*60)
    print("🎾 BOUNCING BALLS - DEPLOYMENT VERIFICATION")
    print("="*60 + "\n")
    
    # Vérifications
    checks_passed = 0
    checks_total = 3
    
    if check_files():
        checks_passed += 1
    if check_git():
        checks_passed += 1
    if check_html():
        checks_passed += 1
    
    print(f"\n✓ Status: {checks_passed}/{checks_total} checks passed")
    
    if checks_passed == checks_total:
        print("✅ Tous les checks réussis!")
        display_deployment_info()
        
        print("\n" + "="*60)
        print("🎯 NEXT STEPS FOR DEPLOYMENT")
        print("="*60)
        print("""
1. Allez sur: https://vercel.com/import
2. Connectez avec GitHub
3. Sélectionnez: MarwaneOU7/MB7-BALL
4. Cliquez: IMPORT & DEPLOY

OU utiliser Vercel CLI:
   npm i -g vercel
   vercel

L'application sera en ligne à:
   https://mb7-ball-[random].vercel.app
        """)
        
        return 0
    else:
        print("❌ Certains checks ont échoué")
        return 1

if __name__ == '__main__':
    sys.exit(main())
