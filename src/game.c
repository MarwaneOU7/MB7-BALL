/**
 * @file game.c
 * @brief Implémentation des fonctions principales du jeu
 */

#include "game.h"
#include "physics.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Initialise l'état du jeu
 */
GameState* Game_Init(void)
{
    GameState* state = (GameState*)malloc(sizeof(GameState));
    
    if (state == NULL)
    {
        fprintf(stderr, "Erreur: Impossible d'allouer la mémoire pour GameState\n");
        return NULL;
    }
    
    // Allocation du tableau de balles
    state->balls = (Ball**)malloc(MAX_BALLS * sizeof(Ball*));
    
    if (state->balls == NULL)
    {
        fprintf(stderr, "Erreur: Impossible d'allouer la mémoire pour le tableau de balles\n");
        free(state);
        return NULL;
    }
    
    state->ball_count = 0;
    state->running = 1;
    state->show_debug = 0;
    
    // Créer une graine aléatoire pour les balles initiales
    srand((unsigned int)time(NULL));
    
    return state;
}

/**
 * @brief Libère les ressources du jeu
 */
void Game_Cleanup(GameState* state)
{
    if (state == NULL) return;
    
    // Libérer toutes les balles
    for (int i = 0; i < state->ball_count; i++)
    {
        Ball_Destroy(state->balls[i]);
    }
    
    // Libérer le tableau de balles
    if (state->balls != NULL)
    {
        free(state->balls);
    }
    
    // Libérer l'état du jeu
    free(state);
}

/**
 * @brief Ajoute une balle à la simulation
 */
int Game_AddBall(GameState* state, float x, float y, float radius, int color)
{
    if (state == NULL) return 0;
    
    // Vérifier si on a atteint le maximum de balles
    if (state->ball_count >= MAX_BALLS)
    {
        fprintf(stderr, "Avertissement: Limite de %d balles atteinte\n", MAX_BALLS);
        return 0;
    }
    
    // Créer une nouvelle balle
    Ball* new_ball = Ball_Create(x, y, radius, color);
    
    if (new_ball == NULL)
    {
        fprintf(stderr, "Erreur: Impossible de créer une nouvelle balle\n");
        return 0;
    }
    
    state->balls[state->ball_count] = new_ball;
    state->ball_count++;
    
    return 1;
}

/**
 * @brief Supprime une balle à l'index spécifié
 */
void Game_RemoveBall(GameState* state, int index)
{
    if (state == NULL || index < 0 || index >= state->ball_count) return;
    
    // Libérer la balle
    Ball_Destroy(state->balls[index]);
    
    // Décaler les autres balles
    for (int i = index; i < state->ball_count - 1; i++)
    {
        state->balls[i] = state->balls[i + 1];
    }
    
    state->ball_count--;
}

/**
 * @brief Met à jour la logique du jeu
 */
void Game_Update(GameState* state)
{
    if (state == NULL) return;
    
    // Appliquer la physique à chaque balle
    for (int i = 0; i < state->ball_count; i++)
    {
        Physics_ApplyGravity(state->balls[i]);
        Physics_UpdatePosition(state->balls[i]);
        Physics_BounceOnWalls(state->balls[i], WINDOW_WIDTH, WINDOW_HEIGHT);
    }
    
    // Déterminer les collisions entre balles
    for (int i = 0; i < state->ball_count; i++)
    {
        for (int j = i + 1; j < state->ball_count; j++)
        {
            Physics_CheckBallCollision(state->balls[i], state->balls[j]);
        }
    }
}

/**
 * @brief Dessine le jeu
 */
void Game_Draw(const GameState* state)
{
    if (state == NULL) return;
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // Dessiner les balles
    for (int i = 0; i < state->ball_count; i++)
    {
        Ball* ball = state->balls[i];
        DrawCircle((int)ball->x, (int)ball->y, ball->radius, (Color){
            (ball->color >> 16) & 0xFF,
            (ball->color >> 8) & 0xFF,
            ball->color & 0xFF,
            255
        });
        
        // Dessiner un contour negro pour mieux voir les balles
        DrawCircleLines((int)ball->x, (int)ball->y, ball->radius, BLACK);
    }
    
    // Afficher les informations de debug
    if (state->show_debug)
    {
        DrawText("Mode DEBUG - Appuyez sur D pour désactiver", 10, 10, 20, RED);
        DrawText(TextFormat("Nombre de balles: %d", state->ball_count), 10, 40, 20, BLACK);
        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 70, 20, BLACK);
    }
    
    // Afficher les instructions
    DrawText("CLIC GAUCHE: Ajouter balle | R: Réinitialiser | D: Debug | ESC: Quitter", 10, WINDOW_HEIGHT - 30, 16, DARKGRAY);
    
    EndDrawing();
}

/**
 * @brief Traite les entrées utilisateur
 */
void Game_HandleInput(GameState* state)
{
    if (state == NULL) return;
    
    // Clic souris pour ajouter une balle
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int mouse_x = GetMouseX();
        int mouse_y = GetMouseY();
        
        // Générer une couleur aléatoire
        int color = (rand() % 256) << 16 | (rand() % 256) << 8 | (rand() % 256);
        
        // Créer une balle avec une taille aléatoire (10-20 pixels)
        float radius = 10.0f + (rand() % 11);
        
        Game_AddBall(state, (float)mouse_x, (float)mouse_y, radius, color);
    }
    
    // Touche R pour réinitialiser
    if (IsKeyPressed(KEY_R))
    {
        for (int i = state->ball_count - 1; i >= 0; i--)
        {
            Game_RemoveBall(state, i);
        }
        printf("Jeu réinitialisé\n");
    }
    
    // Touche D pour le mode debug
    if (IsKeyPressed(KEY_D))
    {
        state->show_debug = !state->show_debug;
        printf("Mode DEBUG: %s\n", state->show_debug ? "Activé" : "Désactivé");
    }
    
    // Touche ESC pour quitter
    if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose())
    {
        state->running = 0;
    }
}

/**
 * @brief Lance la boucle principale du jeu
 */
void Game_Run(GameState* state)
{
    if (state == NULL) return;
    
    // Initialiser la fenêtre Raylib
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);
    
    printf("=== Simulation de Balles Rebondissantes ===\n");
    printf("Fenêtre: %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("FPS Max: %d\n", TARGET_FPS);
    printf("Max balles: %d\n", MAX_BALLS);
    printf("Commandes:\n");
    printf("  - CLIC GAUCHE: Ajouter une balle\n");
    printf("  - R: Réinitialiser le jeu\n");
    printf("  - D: Afficher le debug\n");
    printf("  - ESC: Quitter\n");
    printf("\n");
    
    // Créer quelques balles pour démarrer
    Game_AddBall(state, 200, 100, 15, 0xFF0000);  // Rouge
    Game_AddBall(state, 600, 150, 12, 0x00FF00);  // Vert
    Game_AddBall(state, 900, 120, 18, 0x0000FF);  // Bleu
    
    // Boucle principale
    while (state->running && !WindowShouldClose())
    {
        Game_HandleInput(state);
        Game_Update(state);
        Game_Draw(state);
    }
    
    // Fermar la fenêtre Raylib
    CloseWindow();
}
