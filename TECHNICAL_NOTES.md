# 🔧 Notes Techniques - Développement C + Raylib

## Conseils de Programmation en C

### 1. Gestion de la Mémoire: La Règle d'Or

```c
// ❌ MAUVAIS
Ball* ball = Ball_Create(x, y, r, c);
// ... oublier le free = fuite mémoire!

// ✅ BON
Ball* ball = Ball_Create(x, y, r, c);
// ... utiliser ball ...
Ball_Destroy(ball);  // free() est dans Destroy()
```

**Règle:** À chaque `malloc` doit correspondre exactement un `free`

### 2. Pointeurs et Tableaux

```c
// Preallouer un tableau de pointeurs
Ball** balls = (Ball**)malloc(MAX_BALLS * sizeof(Ball*));

// Utiliser
balls[0] = Ball_Create(...);
balls[1] = Ball_Create(...);

// Itérer
for (int i = 0; i < count; i++)
{
    Ball* ball = balls[i];  // Déréférencer
    ball->x += ball->vx;    // Utiliser
}

// Libérer
for (int i = 0; i < count; i++)
    Ball_Destroy(balls[i]);
free(balls);
```

### 3. Structures et Encapsulation

```c
// ❌ MAUVAIS - Pas d'encapsulation
struct Ball {
    float x, y;
};
ball.x = 100;  // N'importe qui peut modifier

// ✅ BON - Interface claire
typedef struct {
    float x, y;
} Ball;

Ball* ball = Ball_Create(100, 50, 15, RED);
Ball_SetPosition(ball, 200, 100);  // Via fonction
```

### 4. Chaînes de Caractères

```c
// ❌ RISQUÉ
char name[10];
strcpy(name, input);  // Peut déborder!

// ✅ SÛR
char name[256];
strncpy(name, input, sizeof(name)-1);
name[sizeof(name)-1] = '\0';
```

### 5. Fonctions Rapides

```c
// Préférer les fonctions courtes et spécialisées
void PhysicsApplyGravity(Ball* ball) { /* 10 lignes */ }

// Au lieu de
void PhysicsUpdate(Ball* ball) { /* 50 lignes */ }
```

---

## Raylib: Patterns Courants

### 1. Initialisation/Fermeture

```c
int main()
{
    // Initialiser Raylib
    InitWindow(WIDTH, HEIGHT, "Title");
    SetTargetFPS(60);
    
    // ... jeu ...
    
    // Fermer proprement
    CloseWindow();
    return 0;
}
```

### 2. Boucle Principale

```c
while (!WindowShouldClose())  // ESC ou X pour fermer
{
    // Input
    if (IsKeyPressed(KEY_SPACE)) { action(); }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { drag(); }
    
    // Update
    update_game();
    
    // Draw
    BeginDrawing();
    ClearBackground(color);
    draw_stuff();
    EndDrawing();
}
```

### 3. Dessiner des Formes

```c
// Cercle
DrawCircle(x, y, radius, color);
DrawCircleLines(x, y, radius, color);

// Rectangle
DrawRectangle(x, y, width, height, color);
DrawRectangleLines(x, y, width, height, color);

// Ligne
DrawLineEx(start, end, thickness, color);

// Texte
DrawText("Hello", x, y, font_size, color);
```

### 4. Gestion des Couleurs

```c
// Couleurs prédéfinies
Color red = RED;
Color blue = BLUE;

// Couleurs perso
Color custom = (Color){255, 128, 64, 255};  // RGBA

// Convertir int en color
int color_int = 0xFF0000;  // Exemple rouge
Color c = (Color){(color_int >> 16) & 0xFF,
                   (color_int >> 8) & 0xFF,
                   color_int & 0xFF, 255};
```

### 5. Temps et FPS

```c
// FPS actuel
int fps = GetFPS();

// Temps delta (pas utilisé dans Euler simple)
float dt = GetFrameTime();

// Temps total
float t = GetTime();
```

---

## Patterns de Physique

### 1. Intégration Numérique (Euler)

```c
void update_physics(Ball* b)
{
    // Force (gravité)
    b->vy += GRAVITY;
    
    // Friction
    b->vx *= FRICTION;
    b->vy *= FRICTION;
    
    // Position
    b->x += b->vx;
    b->y += b->vy;
}
```

### 2. Détection de Collision

```c
// Cercle-Cercle
float dist = distance(b1, b2);
if (dist < b1->radius + b2->radius)  // Collision!

// Point-Cercle
if (distance(point, b1) < b1->radius)  // Dedans

// AABB (Rectangle)
if (x1 < x2 + w2 && x1 + w1 > x2 &&
    y1 < y2 + h2 && y1 + h1 > y2)  // Collision
```

### 3. Résilience aux Erreurs

```c
// Vérifier pointeurs
if (ball == NULL) return;

// Vérifier limites
if (index < 0 || index >= count) return;

// Vérifier divisions
if (distance < 0.01f) distance = 0.01f;  // Éviter division par 0

// Limiter valeurs
if (velocity > MAX_VEL) velocity = MAX_VEL;
```

---

## Compilation: Astuces

### 1. Flags Recommandés

```bash
# Production (optimisé)
gcc -O2 -Wall -Wextra -std=c99 *.c -o prog -lraylib

# Debug (plus lent, plus infos)
gcc -g -O0 -Wall -Wextra -std=c99 *.c -o prog -lraylib

# C stricte
gcc -std=c99 -pedantic -Wall *.c -o prog
```

### 2. Warnings à Ignorer

```bash
# Certains warnings n'importent pas
gcc -Wno-unused-variable *.c ...  # Ignorer "unused"
gcc -Wno-unused-parameter *.c ... # Ignorer paramètres inutilisés
```

### 3. Makefile Patterns

```makefile
# Cible de debug
debug: CFLAGS += -g -O0
debug: clean $(TARGET)

# Cible run
run: $(TARGET)
	./$(TARGET)

# Cible clean
clean:
	rm -f *.o $(TARGET)
```

---

## Débogage en C

### 1. Avec printf() (Simple)

```c
printf("Debug: x=%.2f, y=%.2f, v=%.2f\n", ball->x, ball->y, speed);
```

### 2. Avec GDB (Pro)

```bash
gcc -g -o prog main.c  # Compiler avec -g
gdb ./prog
(gdb) break main       # Point d'arrêt
(gdb) run              # Lancer
(gdb) print variable   # Afficher var
(gdb) step             # Étape par étape
(gdb) continue         # Continuer jusqu'au breakpoint suivant
```

### 3. Avec Valgrind (Mémoire)

```bash
valgrind --leak-check=full ./prog
# Affiche toutes les fuites mémoire
```

### 4. Assertions

```c
#include <assert.h>

assert(ball != NULL);      // Crash si false
assert(radius > 0);        // Crash si false
```

---

## Patterns de Code Propre

### 1. Noms de Variables

```c
// ❌ Mauvais
int x, y, v;
float d;

// ✅ Bon
int ball_x, ball_y;
float current_velocity;
float time_delta;
```

### 2. Constantes

```c
// ❌ Mauvais (magic numbers)
ball->vy += 0.4f;

// ✅ Bon
#define GRAVITY 0.4f
ball->vy += GRAVITY;
```

### 3. Commentaires Utiles

```c
// ❌ Commentaire superflu
x += 1;  // Ajouter 1 à x

// ✅ Commentaire utile
// Appliquer la gravité terrestre (pixels/frame²)
ball->vy += GRAVITY;
```

### 4. Fonction Courtes

```c
// ❌ Trop long
void do_everything() {
    // 100 lignes...
}

// ✅ Bon
void add_ball(...) { /* 10 lignes */ }
void update_physics() { /* 15 lignes */ }
void draw_scene() { /* 20 lignes */ }
```

---

## Performance: Tips & Tricks

### 1. Éviter les Allocations dans la Boucle

```c
// ❌ LENT (malloc 60 fois par seconde)
while (running)
{
    Ball* temp = malloc(sizeof(Ball));
    free(temp);
}

// ✅ RAPIDE (allocate once)
Ball* pool[MAX_PARTICLES];
for (int i = 0; i < frame; i++)
{
    pool[i % MAX_PARTICLES]->x += ...;  // Réutiliser
}
```

### 2. Éviter les Allocations Dynamiques Inutiles

```c
// ❌ Pour une struct locale
typedef struct {
    float* data;  // Pointeur = malloc
} Temp;
Temp t;
t.data = malloc(...);
// ...
free(t.data);

// ✅ Stack allocation
float data[100];
```

### 3. Utiliser le Calcul Vectoriel

```c
// ❌ Lent
float dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
if (dist < radius) { }

// ✅ Rapide (pas de sqrt)
float dist_sq = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
if (dist_sq < radius*radius) { }
```

---

## Erreurs Communes à Éviter

| Erreur | Problème | Solution |
|--------|----------|----------|
| `malloc` sans `free` | Fuite mémoire | Toujours libérer |
| Pointeur NULL | Crash | Vérifier != NULL |
| Déborder de tableau | Corruption | Vérifier index < size |
| Division par zéro | Crash/NaN | Ajouter epsilon |
| Vitesse trop haute | Instabilité numérique | Limiter MAX_VEL |
| Code dans main() | Pas modulaire | Extraire fonctions |
| Pas de commentaires | Code illisible | Commenter logique |
| Variables globales | Dépendances cachées | Passer paramètres |

---

## Checklist Code Quality

- [ ] Tous les `malloc` ont un `free`
- [ ] Tous les imports sont utilisés
- [ ] Pas de warnings à la compilation
- [ ] Pas de code mort
- [ ] Noms variables explicites
- [ ] Fonctions < 50 lignes
- [ ] Commentaires sur logique complexe
- [ ] Pas de magic numbers (utiliser #define)
- [ ] Gestion d'erreur (vérifier NULL, etc)
- [ ] Pas de dépendances circulaires

---

## Ressources Utiles

| Sujet | Lien |
|-------|------|
| Raylib Docs | https://www.raylib.com/ |
| C Reference | https://en.cppreference.com/w/c |
| GDB Tutorial | https://www.gnu.org/software/gdb/ |
| Valgrind Guide | https://valgrind.org/docs/manual/ |
| Data Structures | Sedgewick: Algorithms in C |

---

**Bonne programmation! 🚀**
