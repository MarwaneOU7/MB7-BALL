/**
 * @file game.h
 * @brief Définition de la structure du jeu et des fonctions principales
 */

#ifndef GAME_H
#define GAME_H

#include "ball.h"

// Paramètres de la fenêtre
#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 700
#define WINDOW_TITLE  "Simulation de Balles Rebondissantes - Raylib"
#define TARGET_FPS    60

// Limite du nombre de balles
#define MAX_BALLS 100

/**
 * @struct GameState
 * @brief Tient à jour l'état global de la simulation
 * 
 * @var balls Tableau de pointeurs vers les balles
 * @var ball_count Nombre de balles actuellement en jeu
 * @var running Drapeau pour arrêter la boucle de jeu
 * @var show_debug Affichage des informations de debug
 */
typedef struct
{
    Ball** balls;
    int ball_count;
    int running;
    int show_debug;
} GameState;

/**
 * @brief Initialise l'état du jeu
 * 
 * @return GameState* Pointeur vers le nouvel état du jeu
 * @note Le pointeur retourné doit être libéré avec Game_Cleanup()
 */
GameState* Game_Init(void);

/**
 * @brief Libère toutes les ressources du jeu
 * 
 * @param state Pointeur vers l'état du jeu
 * @note Doit être appelé avant de quitter le programme
 */
void Game_Cleanup(GameState* state);

/**
 * @brief Ajoute une balle à la simulation
 * 
 * @param state Pointeur vers l'état du jeu
 * @param x Position X initiale
 * @param y Position Y initiale
 * @param radius Rayon de la balle
 * @param color Couleur RGB
 * @return int 1 si succès, 0 si la limite de balles est atteinte
 */
int Game_AddBall(GameState* state, float x, float y, float radius, int color);

/**
 * @brief Supprime une balle à l'index spécifié
 * 
 * @param state Pointeur vers l'état du jeu
 * @param index Index de la balle à supprimer
 */
void Game_RemoveBall(GameState* state, int index);

/**
 * @brief Met à jour la logique du jeu (une frame)
 * 
 * @param state Pointeur vers l'état du jeu
 * @note Gère:
 *       - Application de la gravité
 *       - Mise à jour des positions
 *       - Rebonds sur les murs
 *       - Collisions entre balles
 *       - Interactions utilisateur
 */
void Game_Update(GameState* state);

/**
 * @brief Dessine l'état actuel du jeu
 * 
 * @param state Pointeur vers l'état du jeu
 */
void Game_Draw(const GameState* state);

/**
 * @brief Traite les entrées utilisateur
 * 
 * @param state Pointeur vers l'état du jeu
 */
void Game_HandleInput(GameState* state);

/**
 * @brief Lance la boucle principale du jeu
 * 
 * @param state Pointeur vers l'état du jeu
 */
void Game_Run(GameState* state);

#endif // GAME_H
