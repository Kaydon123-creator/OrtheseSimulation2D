//
// Created by Kaydon and Johnny on 2025-11-19.
//

#pragma once

#include "Scene.h"
#include "affichage.h"

class Display {
    public:
        virtual ~Display() = default;

        //  TEMPLATE METHOD
        void afficher(const Scene& scene) const {
            std::vector<std::vector<char>> grille(HAUTEUR, std::vector<char>(LARGEUR, ' '));

            scene.creerLigne(grille);

            afficherPoints(scene, grille);

            afficherGrille(grille);
        }

    protected:
        virtual void afficherPoints(const Scene& scene,
                                    std::vector<std::vector<char>>& grille) const = 0;
};

