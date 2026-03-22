/**
 * @file ball.c
 * @brief Implémentation des fonctions de gestion des balles
 */

#include "ball.h"

/**
 * @brief Crée une nouvelle balle avec les paramètres spécifiés
 */
Ball* Ball_Create(float x, float y, float radius, int color)
{
    // Allocation mémoire pour une nouvelle balle
    Ball* ball = (Ball*)malloc(sizeof(Ball));
    
    // Vérification de l'allocation
    if (ball == NULL)
    {
        fprintf(stderr, "Erreur: Impossible d'allouer la mémoire pour Ball\n");
        return NULL;
    }
    
    // Initialisation des propriétés
    ball->x = x;
    ball->y = y;
    ball->vx = 0.0f;  // Pas de vélocité initiale
    ball->vy = 0.0f;
    ball->radius = radius;
    ball->mass = radius * radius;  // Masse proportionnelle à la surface
    ball->color = color;
    
    return ball;
}

/**
 * @brief Libère la mémoire allouée pour une balle
 */
void Ball_Destroy(Ball* ball)
{
    if (ball != NULL)
    {
        free(ball);
    }
}

/**
 * @brief Affiche les informations de debug d'une balle en console
 */
void Ball_PrintDebug(const Ball* ball)
{
    if (ball != NULL)
    {
        printf("Ball Debug Info:\n");
        printf("  Position: (%.2f, %.2f)\n", ball->x, ball->y);
        printf("  Vélocité: (%.2f, %.2f)\n", ball->vx, ball->vy);
        printf("  Rayon: %.2f\n", ball->radius);
        printf("  Masse: %.2f\n", ball->mass);
        printf("---\n");
    }
}
