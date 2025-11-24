//
// Created by Kaydon Mohamed on 2025-11-19.
//

#ifndef TEST2400_DISPLAYSTATEGY_H
#define TEST2400_DISPLAYSTATEGY_H

#endif //TEST2400_DISPLAYSTATEGY_H

#pragma once

#include "Scene.h"

class Display {
    public:
        virtual ~Display() = default;

        //  TEMPLATE METHOD
        void afficher(const Scene& scene) const {
            std::vector<std::vector<char>> grille(HAUTEUR, std::vector<char>(LARGEUR, ' '));

            // étape 1 : tracer les lignes
            scene.creerLigne(grille);

            // étape 2 : afficher les points selon la stratégie
            afficherPoints(scene, grille);

            // étape 3 : afficher la grille finale
            afficherGrille(grille);
        }

    protected:
        virtual void afficherPoints(const Scene& scene,
                                    std::vector<std::vector<char>>& grille) const = 0;
};

