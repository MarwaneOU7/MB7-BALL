/**
 * @file ball.h
 * @brief Définition de la structure Ball et des fonctions associées
 * @author Étudiant Ingénierie
 * @date 2026
 */

#ifndef BALL_H
#define BALL_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @struct Ball
 * @brief Représente une balle dans la simulation physique
 * 
 * @var x Position X du centre de la balle (pixels)
 * @var y Position Y du centre de la balle (pixels)
 * @var vx Vélocité horizontale (pixels/frame)
 * @var vy Vélocité verticale (pixels/frame)
 * @var radius Rayon de la balle (pixels)
 * @var mass Masse de la balle (pour les collisions)
 * @var color Couleur RGB de la balle (stockée comme entier HSL converti)
 */
typedef struct
{
    float x;        // Position X
    float y;        // Position Y
    float vx;       // Vélocité X
    float vy;       // Vélocité Y
    float radius;   // Rayon de la balle
    float mass;     // Masse
    int color;      // Couleur (RGB encodée)
} Ball;

/**
 * @brief Crée une nouvelle balle avec les paramètres spécifiés
 * 
 * @param x Position X initiale
 * @param y Position Y initiale
 * @param radius Rayon de la balle
 * @param color Couleur de la balle (RGB)
 * @return Ball* Pointeur vers la nouvelle balle allouée dynamiquement
 * @note Le pointeur retourné doit être libéré avec free()
 */
Ball* Ball_Create(float x, float y, float radius, int color);

/**
 * @brief Libère la mémoire allouée pour une balle
 * 
 * @param ball Pointeur vers la balle à libérer
 * @note Cette fonction doit être appelée pour chaque Ball_Create()
 */
void Ball_Destroy(Ball* ball);

/**
 * @brief Affiche les informations de debug d'une balle en console
 * 
 * @param ball Pointeur vers la balle
 */
void Ball_PrintDebug(const Ball* ball);

#endif // BALL_H
