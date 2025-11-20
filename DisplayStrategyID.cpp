//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "DisplayStrategy.h"
#include <iostream>
#include "affichage.h"
#include <vector>

using namespace std;

class DisplayStrategyID : public DisplayStrategy {
public:
    void afficher(const Scene& scene) const override {
        vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));
        scene.creerLigne(grille);

        for (auto& p : scene.getPoints()) {
            if (p->x >= 0 && p->x < LARGEUR &&
                p->y >= 0 && p->y < HAUTEUR)
            {
                grille[p->y][p->x] = '0' + (p->id % 10); // protection au cas ou id superieur à 10
            }
        }

        afficherGrille(grille);
    }
};
