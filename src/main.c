/**
 * @file main.c
 * @brief Point d'entrée du programme - Simulation de Balles Rebondissantes avec Raylib
 * 
 * @author Étudiant Ingénierie - Année 1
 * @date Mars 2026
 * @version 1.0
 * 
 * Projet: Simulation physique interactive de balles rebondissantes
 * 
 * Description:
 * Ce programme simule plusieurs balles affectées par la gravité, rebondissant
 * sur les murs et entrant en collision les unes avec les autres.
 * 
 * Fonctionnalités:
 * - Création dynamique de balles par clic souris
 * - Gravité réaliste
 * - Rebonds élastiques sur les murs
 * - Collisions élastiques entre balles
 * - Mode debug pour visualiser les états
 * - Gestion complète de la mémoire
 * 
 * Compilation:
 * - Sur Windows: gcc -o bouncing_balls.exe *.c -lraylib -lwinmm -Wall -std=c99
 * - Sur Linux: gcc -o bouncing_balls *.c -lraylib -Wall -std=c99
 * - Sur macOS: gcc -o bouncing_balls *.c -lraylib -Wall -std=c99
 * 
 * Usage:
 * ./bouncing_balls
 */

#include "game.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Fonction principale - Point d'entrée du programme
 * 
 * @return int Code de sortie (0 = succès, 1 = erreur)
 */
int main(void)
{
    printf("╔════════════════════════════════════════════╗\n");
    printf("║  Simulation de Balles Rebondissantes v1.0  ║\n");
    printf("║  Langage: C99 | Gaphique: Raylib         ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    
    // Initialiser le jeu
    GameState* game = Game_Init();
    
    if (game == NULL)
    {
        fprintf(stderr, "ERREUR CRITIQUE: Impossible d'initialiser le jeu\n");
        return 1;
    }
    
    // Lancer la boucle principale
    Game_Run(game);
    
    // Nettoyer et libérer les ressources
    Game_Cleanup(game);
    
    printf("\nProgramme terminé avec succès\n");
    return 0;
}
