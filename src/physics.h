/**
 * @file physics.h
 * @brief Définition des constantes et fonctions de physique
 */

#ifndef PHYSICS_H
#define PHYSICS_H

#include "ball.h"
#include <math.h>

// ==================== CONSTANTES PHYSIQUES ====================

/** @brief Accélération due à la gravité (pixels/frame²) */
#define GRAVITY 0.4f

/** @brief Coefficient de restitution (élasticité) lors des rebonds */
#define ELASTICITY 0.95f

/** @brief Coefficient de friction de l'air (ralentit les balles) */
#define AIR_FRICTION 0.999f

/** @brief Vitesse maximale pour éviter les instabilités */
#define MAX_VELOCITY 15.0f

// ==================== FONCTIONS PHYSIQUES ====================

/**
 * @brief Applique la gravité et met à jour la vélocité d'une balle
 * 
 * @param ball Pointeur vers la balle à mettre à jour
 * @note Applique aussi la friction de l'air
 */
void Physics_ApplyGravity(Ball* ball);

/**
 * @brief Met à jour la position d'une balle selon sa vélocité
 * 
 * @param ball Pointeur vers la balle
 * @note Cette fonction est appelée à chaque frame
 */
void Physics_UpdatePosition(Ball* ball);

/**
 * @brief Gère le rebond d'une balle sur les murs de la fenêtre
 * 
 * @param ball Pointeur vers la balle
 * @param window_width Largeur de la fenêtre
 * @param window_height Hauteur de la fenêtre
 * @note Inverse la vélocité appropriée et ajuste la position si besoin
 */
void Physics_BounceOnWalls(Ball* ball, float window_width, float window_height);

/**
 * @brief Calcule la distance entre deux balles
 * 
 * @param ball1 Pointeur vers la première balle
 * @param ball2 Pointeur vers la deuxième balle
 * @return float Distance entre les deux centres
 */
float Physics_DistanceBetweenBalls(const Ball* ball1, const Ball* ball2);

/**
 * @brief Vérifie et gère la collision élastique entre deux balles
 * 
 * @param ball1 Pointeur vers la première balle
 * @param ball2 Pointeur vers la deuxième balle
 * @return int 1 si collision détectée, 0 sinon
 * @note Modifie les vélocités des deux balles en cas de collision
 */
int Physics_CheckBallCollision(Ball* ball1, Ball* ball2);

#endif // PHYSICS_H
