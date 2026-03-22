# 🔬 Documentation Détaillée - Concepts Physiques

## Résumé Exécutif

Ce document explique comment les lois de la physique sont implémentées dans le moteur de simulation.

---

## 1️⃣ Gravité

### Concept Physique
La gravité est l'accélération due à la force d'attraction terrestre. Elle agit verticalement vers le bas avec une valeur constante (≈ 9.81 m/s² sur Terre).

### Implémentation Simplifiée
```c
// Dans Physics_ApplyGravity()
ball->vy += GRAVITY;  // où GRAVITY = 0.4 pixels/frame²
```

### Équation Mathématique
```
vy(t+1) = vy(t) + GRAVITY
```

### Effet Visuel
- Les balles **accélèrent** vers le bas
- Plus elles tombent longtemps, plus elles vont vite
- Jusqu'à atteindre une vitesse "terminale" (voir friction)

### Paramètres à Ajuster
```c
#define GRAVITY 0.4f
```
- **Valeur faible** (0.1): Les balles tombent lentement → sensation "lunaire"
- **Valeur normale** (0.4): Sensation réaliste
- **Valeur forte** (0.8): Les balles chutent rapidement → sensation "Jupiter"

---

## 2️⃣ Vélocité et Position

### Concept Physique
La **vélocité** est la **vitesse avec direction** (vecteur).
La **position** change chaque frame selon la vélocité.

### Équations du Mouvement (Cinématique)
```
Position (t+1) = Position(t) + Vélocité(t) * Δt

Où Δt = 1 frame à 60 FPS = 1/60 secondes
```

### Implémentation
```c
// Mise à jour de la position
void Physics_UpdatePosition(Ball* ball)
{
    ball->x += ball->vx;  // Déplacement horizontal
    ball->y += ball->vy;  // Déplacement vertical
}
```

### Exemple Numérique
```
Frame 0:  x=100,  vx=5   → x=105
Frame 1:  x=105,  vx=5   → x=110
Frame 2:  x=110,  vx=5   → x=115
...
Résultat: Mouvement lisse et prévisible
```

### Import de Raylib
```c
#include "raylib.h"
```

---

## 3️⃣ Rebond sur les Murs

### Concept Physique
Quand un objet frappe un obstacle, sa vélocité s'inverse.
L'**élasticité** détermine combien d'énergie est conservée.

### Types de Rebond

#### A) Élastique Parfait (ELASTICITY = 1.0)
```
v_après = -v_avant
```
- L'énergie est TOTALEMENT conservée
- Résultat: La balle rebondit indéfiniment
- Rare dans la vraie vie

#### B) Élastique Partiel (ELASTICITY = 0.95)
```
v_après = -v_avant * 0.95
```
- L'énergie DIMINUE de 5% à chaque rebond
- Résultat: La balle ralentit progressivement
- **Réaliste et recommandé**

#### C) Inélastique (ELASTICITY = 0.0)
```
v_après = 0
```
- Pas de rebond du tout
- La balle s'arrête instantanément
- Effet de collision collante

### Implémentation
```c
void Physics_BounceOnWalls(Ball* ball, float window_width, float window_height)
{
    // Mur GAUCHE (x = 0)
    if (ball->x - ball->radius < 0)
    {
        ball->x = ball->radius;              // Ajustement position
        ball->vx = -ball->vx * ELASTICITY;   // Rebond
    }
    
    // Mur DROIT (x = window_width)
    else if (ball->x + ball->radius > window_width)
    {
        ball->x = window_width - ball->radius;
        ball->vx = -ball->vx * ELASTICITY;
    }
    
    // Mur HAUT (y = 0)
    if (ball->y - ball->radius < 0)
    {
        ball->y = ball->radius;
        ball->vy = -ball->vy * ELASTICITY;
    }
    
    // Mur BAS (y = window_height)
    else if (ball->y + ball->radius > window_height)
    {
        ball->y = window_height - ball->radius;
        ball->vy = -ball->vy * ELASTICITY;
    }
}
```

### Graphique Énergétique
```
Énergie
   |     Frame 1      Frame 2      Frame 3       Frame 4
   |        ▲            ▲            ▲            ▲
100|        |            |            |            |
   |    ✓───┘        ✓───┘        ✓───┘        ✓───┘
 95|                                               (95% restant)
   |___|___|___|___|___|___|___|___|___|___|___|___|___
```

---

## 4️⃣ Friction de l'Air

### Concept Physique
L'air oppose une résistance au mouvement (traînée aérodynamique).
Dans une simulation simplifie: **tout ralentit légèrement chaque frame**.

### Formule
```
vx(t+1) = vx(t) * AIR_FRICTION
vy(t+1) = vy(t) * AIR_FRICTION

Où AIR_FRICTION = 0.999 (99.9% conservé)
```

### Implémentation
```c
void Physics_ApplyGravity(Ball* ball)
{
    // ...
    ball->vx *= AIR_FRICTION;  // Ralentit vx
    ball->vy *= AIR_FRICTION;  // Ralentit vy
}
```

### Effet Visuel
- Les balles qui rebondissent perdent progressivement de la hauteur
- Finissent par s'arrêter complètement
- Donnent un effet **réaliste et naturel**

### Impact sur les Dynamics
```
Quand AIR_FRICTION = 0.999:
  → Après 1000 frames (≈17 secondes): vitesse ≈ 37% de l'initiale
  → Après 3000 frames (≈50 secondes): vitesse ≈ 5% de l'initiale
  
La balle s'arrête graduellement, jamais instantanément.
```

---

## 5️⃣ Collision Entre Balles

### Concept Physique
Quand deux balles se touchent, elles doivent s'échanger une partie de leur énergie.
Dans une collision en ligne (1D), les formules de momentum conservation s'appliquent.

### Détection de Collision
```c
float distance = sqrt((ball2->x - ball1->x)² + (ball2->y - ball1->y)²)

if (distance < ball1->radius + ball2->radius)
{
    // COLLISION!
}
```

### Problème: Comment Gérer 2 Balles en Collision?

#### Cas Simple: Balles de Même Masse
```
Avant: ball1->vx=5,  ball2->vx=-5
Après: ball1->vx=-5, ball2->vx=5  (inversion)
```

#### Cas Général: Masses Différentes
Si une balle est plus lourde, elle affecte moins la légère.

```
Formule de conservation du momentum:
m1*v1 + m2*v2 = m1*v1' + m2*v2'
```

### Implémentation Complexe
```c
int Physics_CheckBallCollision(Ball* ball1, Ball* ball2)
{
    // 1. Calculer la distance
    float distance = Physics_DistanceBetweenBalls(ball1, ball2);
    float min_distance = ball1->radius + ball2->radius;
    
    if (distance < min_distance)
    {
        // 2. Calculer la NORMALE de collision (direction)
        float nx = (ball2->x - ball1->x) / distance;  // Composante X
        float ny = (ball2->y - ball1->y) / distance;  // Composante Y
        
        // 3. Vélocité RELATIVE (une par rapport à l'autre)
        float dvx = ball2->vx - ball1->vx;
        float dvy = ball2->vy - ball1->vy;
        
        // 4. Produit scalaire: vitesse relative · direction
        float dot = dvx * nx + dvy * ny;
        
        // 5. Échangeimpulsion selon les masses
        float total_mass = ball1->mass + ball2->mass;
        float factor1 = 2.0f * ball2->mass / total_mass;
        float factor2 = 2.0f * ball1->mass / total_mass;
        
        ball1->vx += factor1 * dot * nx;
        ball1->vy += factor1 * dot * ny;
        
        ball2->vx -= factor2 * dot * nx;
        ball2->vy -= factor2 * dot * ny;
        
        // 6. Séparer les balles (évite qu'elles restent collées)
        float overlap = min_distance - distance;
        float separation = overlap / 2.0f + 0.1f;
        
        ball1->x -= separation * nx;
        ball1->y -= separation * ny;
        ball2->x += separation * nx;
        ball2->y += separation * ny;
        
        return 1;  // Collision détectée
    }
    
    return 0;
}
```

### Visualisation d'une Collision

```
Avant collision:
  ball1 (m=100)    ball2 (m=50)
    [●═════]  →       [●]
     vx=3           vx=-2

Calcul:
  - Normal de collision: vers la droite (1, 0)
  - Vélocité relative: -2 - 3 = -5 (elle se rapproche)
  - Factor1 = 2*50/150 = 0.67 (la lourde subit peu)
  - Factor2 = 2*100/150 = 1.33 (la légère subit beaucoup)

Après collision:
    [●═════] →       [●]→
     vx=2            vx=1 (inversé mais modérée)
```

---

## 6️⃣ Intégration Numérique (Euler Explicite)

### Concept
La simulation met à jour l'état en **petits pas discrets** plutôt que de résoudre les équations analytiquement.

### Algorithme d'Euler Explicite (utilisé ici)
```
Pour chaque frame (Δt = 1):
  1. Appliquer les forces externes (gravité)
  2. Mettre à jour la vélocité
  3. Mettre à jour la position
  4. Vérifier les collisions
  5. Appliquer les réactions (rebonds)
```

### Code dans la Boucle Principale
```c
void Game_Update(GameState* state)
{
    for (int i = 0; i < state->ball_count; i++)
    {
        Physics_ApplyGravity(state->balls[i]);      // Étape 1 & 2
        Physics_UpdatePosition(state->balls[i]);    // Étape 3
        Physics_BounceOnWalls(...);                 // Étape 5
    }
    
    for (int i = 0; i < state->ball_count; i++)
    {
        for (int j = i + 1; j < state->ball_count; j++)
        {
            Physics_CheckBallCollision(...);        // Étape 4
        }
    }
}
```

### Avantages et Limitations
| Aspect | Euler Explicite |
|--------|-----------------|
| Complexité | ✅ Simple à implémenter |
| Vitesse | ✅ Très rapide |
| Stabilité | ⚠️ Peut devenir instable pour des gros Δt |
| Précision | ⚠️ Accumule des erreurs |

**Pour ce projet: c'est suffisant et recommandé!**

---

## 🎯 Résumé des Formules Clés

| Phénomène | Formule | Constante |
|-----------|---------|-----------|
| Gravité | `vy += GRAVITY` | 0.4 |
| Friction | `v *= AIR_FRICTION` | 0.999 |
| Rebond | `v = -v * ELASTICITY` | 0.95 |
| Collision | `v = -v * factor * dot` | Conservation |
| Position | `pos += vel` | Intégration |

---

## 🔧 Comment Ajuster la Simulation

### Je veux que... → Changez...

| Besoin | Paramètre | Valeur Actuelle | Suggestion |
|--------|-----------|-----------------|-----------|
| Les balles tombent plus vite | `GRAVITY` | 0.4 | 0.6 → 0.8 |
| Les balles tombent plus lentement | `GRAVITY` | 0.4 | 0.1 → 0.2 |
| Plus de rebonds (super balls) | `ELASTICITY` | 0.95 | 0.98 → 1.0 |
| Moins de rebonds (balle mouillée) | `ELASTICITY` | 0.95 | 0.7 → 0.85 |
| Les balles ralentissent plus vite | `AIR_FRICTION` | 0.999 | 0.99 → 0.98 |
| Les balles ralentissent plus lentement | `AIR_FRICTION` | 0.999 | 0.9999 |

---

## ✅ Points Clés pour la Soutenance

1. **Expliquez la gravité** - "C'est une accélération constante vers le bas"
2. **Parlez de l'élasticité** - "On inverse la vélocité mais on la multiplie par 0.95"
3. **Mentionnez la friction** - "Chaque frame, la vitesse est multipliée par 0.999"
4. **Décrivez les collisions** - "On échange de l'énergie selon les masses"
5. **Soulignez la stabilité** - "On limite la vélocité max pour éviter les bugs"

---

**Document pédagogique | Compréhension physique garantie! 🎓**
