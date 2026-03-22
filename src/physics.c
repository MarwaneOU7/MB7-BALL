/**
 * @file physics.c
 * @brief Implémentation des fonctions physiques de la simulation
 */

#include "physics.h"

/**
 * @brief Applique la gravité et la friction de l'air
 * 
 * Formules utilisées:
 * - vy += GRAVITY (accélération vers le bas)
 * - vx *= AIR_FRICTION (perte d'énergie)
 * - vy *= AIR_FRICTION (perte d'énergie)
 * - Limite la vélocité maximale pour éviter les instabilités numériques
 */
void Physics_ApplyGravity(Ball* ball)
{
    if (ball == NULL) return;
    
    // Application de la gravité (accélération vers le bas)
    ball->vy += GRAVITY;
    
    // Application de la friction de l'air (résistance du milieu)
    ball->vx *= AIR_FRICTION;
    ball->vy *= AIR_FRICTION;
    
    // Limitation de la vélocité maximale pour la stabilité
    float speed = sqrtf(ball->vx * ball->vx + ball->vy * ball->vy);
    if (speed > MAX_VELOCITY)
    {
        ball->vx = (ball->vx / speed) * MAX_VELOCITY;
        ball->vy = (ball->vy / speed) * MAX_VELOCITY;
    }
}

/**
 * @brief Met à jour la position d'une balle selon sa vélocité
 * 
 * Formule utilisée:
 * - x += vx
 * - y += vy
 */
void Physics_UpdatePosition(Ball* ball)
{
    if (ball == NULL) return;
    
    ball->x += ball->vx;
    ball->y += ball->vy;
}

/**
 * @brief Gère les rebonds sur les murs avec coefficient de restitution
 * 
 * Logique:
 * - Si la balle touche le mur gauche ou droit: inverser vx et multiplier par ELASTICITY
 * - Si la balle touche le mur haut ou bas: inverser vy et multiplier par ELASTICITY
 * - Ajuster la position pour éviter que la balle passe à travers les murs
 */
void Physics_BounceOnWalls(Ball* ball, float window_width, float window_height)
{
    if (ball == NULL) return;
    
    // Rebond sur les murs gauche et droit
    if (ball->x - ball->radius < 0)
    {
        ball->x = ball->radius;
        ball->vx = -ball->vx * ELASTICITY;
    }
    else if (ball->x + ball->radius > window_width)
    {
        ball->x = window_width - ball->radius;
        ball->vx = -ball->vx * ELASTICITY;
    }
    
    // Rebond sur les murs haut et bas
    if (ball->y - ball->radius < 0)
    {
        ball->y = ball->radius;
        ball->vy = -ball->vy * ELASTICITY;
    }
    else if (ball->y + ball->radius > window_height)
    {
        ball->y = window_height - ball->radius;
        ball->vy = -ball->vy * ELASTICITY;
    }
}

/**
 * @brief Calcule la distance euclidienne entre deux balles
 * 
 * Formule: distance = sqrt((x2-x1)² + (y2-y1)²)
 */
float Physics_DistanceBetweenBalls(const Ball* ball1, const Ball* ball2)
{
    if (ball1 == NULL || ball2 == NULL) return 0.0f;
    
    float dx = ball2->x - ball1->x;
    float dy = ball2->y - ball1->y;
    
    return sqrtf(dx * dx + dy * dy);
}

/**
 * @brief Détecte et gère les collisions élastiques entre deux balles
 * 
 * Processus:
 * 1. Calcule la distance entre les deux balles
 * 2. Compare avec la somme des rayons (distance de collision)
 * 3. Si collision: échange les vélocités en fonction des masses
 * 4. Applique le coefficient d'élasticité
 * 
 * @return 1 si collision, 0 sinon
 */
int Physics_CheckBallCollision(Ball* ball1, Ball* ball2)
{
    if (ball1 == NULL || ball2 == NULL) return 0;
    
    // Distance entre les centres des deux balles
    float distance = Physics_DistanceBetweenBalls(ball1, ball2);
    float min_distance = ball1->radius + ball2->radius;
    
    // Vérifier s'il y a collision
    if (distance < min_distance)
    {
        // Éviter la division par zéro
        if (distance < 0.1f) distance = 0.1f;
        
        // Direction de collision (vecteur normalisé)
        float nx = (ball2->x - ball1->x) / distance;
        float ny = (ball2->y - ball1->y) / distance;
        
        // Vitesse relative
        float dvx = ball2->vx - ball1->vx;
        float dvy = ball2->vy - ball1->vy;
        
        // Produit scalaire vitesse relative · normale
        float dot = dvx * nx + dvy * ny;
        
        // Si les balles s'éloignent, pas besoin de faire quelque chose
        if (dot >= 0) return 1;
        
        // Échange de vélocité avec conservation du momentum
        // Formule pour collision élastique en 1D selon la normale
        float total_mass = ball1->mass + ball2->mass;
        float factor1 = 2.0f * ball2->mass / total_mass * ELASTICITY;
        float factor2 = 2.0f * ball1->mass / total_mass * ELASTICITY;
        
        ball1->vx += factor1 * dot * nx;
        ball1->vy += factor1 * dot * ny;
        
        ball2->vx -= factor2 * dot * nx;
        ball2->vy -= factor2 * dot * ny;
        
        // Séparer les balles pour éviter qu'elles restent coincer
        float overlap = min_distance - distance;
        float separation = overlap / 2.0f + 0.1f;
        
        ball1->x -= separation * nx;
        ball1->y -= separation * ny;
        ball2->x += separation * nx;
        ball2->y += separation * ny;
        
        return 1;  // Collision détectée
    }
    
    return 0;  // Pas de collision
}
