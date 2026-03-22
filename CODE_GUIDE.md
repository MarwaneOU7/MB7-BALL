# 📚 Guide du Code Source

## 🎯 Vue d'Ensemble

Ce document explique comment chaque fichier fonction et comment ils interagissent ensemble.

```
main.c
  ↓
  ├─→ Game_Init()      [Initialise l'état du jeu]
  ├─→ Game_Run()       [Boucle principale]
  │    ├─→ Game_HandleInput()    [Gère clics/touches]
  │    ├─→ Game_Update()         [Logique physique]
  │    │    ├─→ Physics_ApplyGravity()
  │    │    ├─→ Physics_UpdatePosition()
  │    │    ├─→ Physics_BounceOnWalls()
  │    │    └─→ Physics_CheckBallCollision()
  │    └─→ Game_Draw()           [Rendu graphique]
  └─→ Game_Cleanup()   [Libère mémoire]
```

---

## 📄 main.c - Point d'Entrée

### Responsabilité
- Afficher les infos de démarrage
- Initialiser le jeu
- Exécuter la boucle principale
- Nettoyer les ressources

### Flux
```
main()
  ├─ Afficher le banner
  ├─ Game_Init()
  │  └─ Allocation mémoire de GameState
  ├─ Game_Run()
  │  └─ Boucle 60 FPS jusqu'à ESC
  ├─ Game_Cleanup()
  │  └─ Libérer toute la mémoire
  └─ return 0
```

### Points Clés
```c
GameState* game = Game_Init();  // Allocation
Game_Run(game);                  // Boucle principale
Game_Cleanup(game);              // Libération
```

✅ **Code simple et propre** - La complexité est cachée dans game.c

---

## 🎮 game.h / game.c - Orchestration du Jeu

### Responsabilité Principale
- **Gérer l'état global** du jeu
- **Boucle principale** 60 FPS
- **Rendering** avec Raylib
- **Gestion des entrées** souris/clavier

### Structures Clés

```c
typedef struct {
    Ball** balls;        // Tableau de pointeurs
    int ball_count;      // Nombre de balles
    int running;         // Pour continuer la boucle
    int show_debug;      // Mode debug
} GameState;
```

### Fonctions Principales

#### 1. `Game_Init()`
```c
GameState* game = Game_Init();

// Alloue:
// - GameState lui-même
// - Tableau de MAX_BALLS pointeurs Ball*
// - Initialise les valeurs

// Vérifie:
// - malloc réussies
// - Pas de NULL
```

**Gestion Erreur:**
```c
if (state == NULL) return NULL;  // Vérification imbriquée
```

#### 2. `Game_AddBall(state, x, y, radius, color)`
```c
// Crée une nouvelle balle
Ball* new_ball = Ball_Create(x, y, radius, color);

// L'ajoute au tableau
state->balls[state->ball_count] = new_ball;
state->ball_count++;

// Retourne 1 = succès, 0 = échec
```

**Entrée souris:**
```c
if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
{
    int mouse_x = GetMouseX();
    int mouse_y = GetMouseY();
    Game_AddBall(state, mouse_x, mouse_y, 15, random_color);
}
```

#### 3. `Game_Update(state)`

C'est le **cœur de la simulation**:

```c
void Game_Update(GameState* state)
{
    // PHASE 1: Appliquer les forces
    for (int i = 0; i < state->ball_count; i++)
    {
        Physics_ApplyGravity(state->balls[i]);     // +0.4 vy
        Physics_UpdatePosition(state->balls[i]);   // x+=vx, y+=vy
        Physics_BounceOnWalls(...);                // Rebonds parois
    }
    
    // PHASE 2: Déterminer les collisions
    for (int i = 0; i < state->ball_count; i++)
    {
        for (int j = i+1; j < state->ball_count; j++)
        {
            Physics_CheckBallCollision(ball_i, ball_j);
        }
    }
}
```

**Appelée 60 fois par seconde!**

#### 4. `Game_Draw(state)`
```c
BeginDrawing();
ClearBackground(RAYWHITE);  // Fond blanc

// Dessiner chaque balle
for (int i = 0; i < state->ball_count; i++)
{
    Ball* ball = state->balls[i];
    
    // Cercle rempli
    DrawCircle((int)ball->x, (int)ball->y, ball->radius, color);
    
    // Contour noir
    DrawCircleLines((int)ball->x, (int)ball->y, ball->radius, BLACK);
}

// Infos debug
if (state->show_debug)
{
    DrawText("Nombre de balles: " + count, 10, 40, 20, BLACK);
    DrawText("FPS: " + GetFPS(), 10, 70, 20, BLACK);
}

EndDrawing();
```

#### 5. `Game_HandleInput(state)`
```c
// Clic gauche → ajouter balle
if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
{
    Game_AddBall(state, GetMouseX(), GetMouseY(), radius, color);
}

// R → réinitialiser
if (IsKeyPressed(KEY_R))
{
    for (int i = state->ball_count - 1; i >= 0; i--)
        Game_RemoveBall(state, i);
}

// D → toggle debug
if (IsKeyPressed(KEY_D))
    state->show_debug = !state->show_debug;

// ESC → quitter
if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose())
    state->running = 0;
```

#### 6. `Game_Run(state)`
```c
InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
SetTargetFPS(TARGET_FPS);

// Créer balles initiales
Game_AddBall(state, 200, 100, 15, RED);
Game_AddBall(state, 600, 150, 12, GREEN);

// BOUCLE PRINCIPALE
while (state->running && !WindowShouldClose())
{
    Game_HandleInput(state);  // Lire clavier/souris
    Game_Update(state);        // Calculer la physique
    Game_Draw(state);          // Afficher à l'écran
}
```

**C'est la boucle 60 FPS!**

---

## 🎾 ball.h / ball.c - Gestion des Balles

### Structure
```c
typedef struct {
    float x, y;      // Position
    float vx, vy;    // Vélocité
    float radius;    // Rayon
    float mass;      // Masse (pour collisions)
    int color;       // Couleur RGB
} Ball;
```

### Fonctions

#### 1. `Ball_Create(x, y, radius, color)`
```c
Ball* ball = Ball_Create(100, 50, 15, 0xFF0000);

// Alloue la mémoire
Ball* ball = (Ball*)malloc(sizeof(Ball));

// Initialise
ball->x = 100;
ball->y = 50;
ball->vx = 0;      // Pas de vitesse initiale
ball->vy = 0;
ball->radius = 15;
ball->mass = 15*15 = 225;  // Proportional à la surface
ball->color = 0xFF0000;

return ball;
```

**Important:** Les balles créées comme ceci **se lèvent debout** (vx=vy=0). Elles commencent à tomber sous la gravité.

#### 2. `Ball_Destroy(ball)`
```c
Ball_Destroy(ball);  // free(ball);

// JAMAIS appeler deux fois sur la même balle!
// JAMAIS oublier de l'appeler (fuite mémoire)
```

#### 3. `Ball_PrintDebug(ball)` 
Pour le debugging:
```c
Ball_PrintDebug(ball);
/* Output:
  Ball Debug Info:
    Position: (234.50, 120.30)
    Vélocité: (2.10, 5.40)
    Rayon: 15.00
    Masse: 225.00
  ---
*/
```

---

## ⚙️ physics.h / physics.c - Moteur Physique

### Constantes
```c
#define GRAVITY 0.4f        // Gravité
#define ELASTICITY 0.95f    // Élasticité rebond
#define AIR_FRICTION 0.999f // Friction de l'air
#define MAX_VELOCITY 15.0f  // Vitesse max
```

### Fonctions

#### 1. `Physics_ApplyGravity(ball)`
```c
void Physics_ApplyGravity(Ball* ball)
{
    // Appliquer gravité
    ball->vy += GRAVITY;  // = 0.4
    
    // Friction de l'air
    ball->vx *= AIR_FRICTION;  // *= 0.999
    ball->vy *= AIR_FRICTION;
    
    // Limiter la vitesse max
    float speed = sqrt(vx² + vy²);
    if (speed > MAX_VELOCITY)
    {
        // Normaliser et réappliquer
        ball->vx = (vx / speed) * MAX_VELOCITY;
        ball->vy = (vy / speed) * MAX_VELOCITY;
    }
}
```

**Appelée chaque frame!**

#### 2. `Physics_UpdatePosition(ball)`
```c
void Physics_UpdatePosition(Ball* ball)
{
    ball->x += ball->vx;
    ball->y += ball->vy;
}
```

**Simple cinématique!**

#### 3. `Physics_BounceOnWalls(ball, w, h)`
```c
// Mur GAUCHE (x < 0)
if (ball->x - ball->radius < 0)
{
    ball->x = ball->radius;           // Ajuster position
    ball->vx = -ball->vx * ELASTICITY; // Inverser + atténuer
}

// Mur BAS (y > height)
else if (ball->y + ball->radius > height)
{
    ball->y = height - ball->radius;
    ball->vy = -ball->vy * ELASTICITY;  // Inverser + atténuer
}
```

#### 4. `Physics_CheckBallCollision(ball1, ball2)`

C'est la **fonction complexe**:

```c
// 1. Déterminer la distance
float distance = Physics_DistanceBetweenBalls(ball1, ball2);
float min_distance = ball1->radius + ball2->radius;

if (distance < min_distance)  // COLLISION!
{
    // 2. Vecteur collision (normal)
    float nx = (ball2->x - ball1->x) / distance;
    float ny = (ball2->y - ball1->y) / distance;
    
    // 3. Vélocité relative
    float dvx = ball2->vx - ball1->vx;
    float dvy = ball2->vy - ball1->vy;
    
    // 4. Produit scalaire (approche-t-on?)
    float dot = dvx * nx + dvy * ny;
    if (dot >= 0) return 1;  // S'éloignent déjà
    
    // 5. Conservation du momentum avec masses
    float total_mass = ball1->mass + ball2->mass;
    float factor1 = 2.0f * ball2->mass / total_mass;
    float factor2 = 2.0f * ball1->mass / total_mass;
    
    ball1->vx += factor1 * dot * nx;
    ball1->vy += factor1 * dot * ny;
    
    ball2->vx -= factor2 * dot * nx;
    ball2->vy -= factor2 * dot * ny;
    
    // 6. Séparer les balles
    float overlap = min_distance - distance;
    float separation = overlap / 2.0f + 0.1f;
    
    ball1->x -= separation * nx;
    ball1->y -= separation * ny;
    ball2->x += separation * nx;
    ball2->y += separation * ny;
    
    return 1;
}

return 0;
```

**Équation complexe mais très importante!**

---

## 🔄 Flux d'Exécution Complet

### Frame 1
```
Game_HandleInput()
  ├─ Utilisateur clique à (500, 300)
  └─ Game_AddBall(state, 500, 300, 15, color)
     └─ Ball_Create() → malloc

Game_Update()
  └─ Pour chaque balle:
     ├─ Physics_ApplyGravity() → vy += 0.4
     ├─ Physics_UpdatePosition() → y += vy
     └─ Physics_BounceOnWalls() → vérifier murs

Game_Draw()
  └─ DrawCircle(500, 300, 15, color)
```

### Frame 2
```
// Même chose, mais la balle est maintenant à y=300.4
// Et vy=0.4 (elle tombe plus vite)
```

### Frame 60 (1 seconde plus tard)
```
// La balle a parcouru une certaine distance
// vy ≈ 0.4 * 60 = 24 (très vite!)
// Mais AIR_FRICTION ralentit et elle rebondit aux murs
```

---

## 🧠 Points Mémoriser

### 1. Allocation/Libération
- `Game_Init()` → `malloc(GameState)` + `malloc(Ball*[])`
- `Ball_Create()` → `malloc(Ball)`
- **TOUJOURS** faire le `free()` correspondant!

### 2. Boucle Principale
```
WHILE running:
  1. Handle Input (lecture clavier/souris)
  2. Update (calculs physiques)
  3. Draw (affichage)
  REPEAT 60 fois par seconde
```

### 3. Physique
```
À chaque frame:
  vy += GRAVITY
  x += vx, y += vy
  Inverser vx/vy aux murs
  Échanger vélocité en collision
```

### 4. Limite des Balles
```c
#define MAX_BALLS 100

if (state->ball_count >= MAX_BALLS)
    return 0;  // Impossible d'en ajouter plus
```

---

## 🎯 Pour les Questions de Soutenance

**Q: Comment se faites-vous que les balles ne passent pas à travers?**
A: Dans `Physics_BounceOnWalls()`, on vérifie si position < mur, et si c'est le cas on remet la position au bord et on inverse la vélocité.

**Q: Comment détectez-vous les collisions?**
A: On calcule la distance entre les deux centres. Si elle est < (r1 + r2), c'est une collision. Puis on échange les vélocités.

**Q: Combien de balles pouvez-vous gérer?**
A: Jusqu'à 100 (MAX_BALLS). Au-delà, c'est un message d'erreur.

**Q: Comment la mémoire est-elle gérée?**
A: Chaque malloc a un free correspondant. Au quitter, `Game_Cleanup()` libère tout.

**Q: Pourquoi la gravité vaut 0.4?**
A: C'est une calibration pour que l'animation soit fluide et réaliste à 60 FPS.

---

**Code understanding: 100%! 🎓**
