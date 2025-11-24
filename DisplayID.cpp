//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "Display.h"
#include <iostream>
#include "affichage.h"
#include <vector>

using namespace std;
class DisplayID : public Display {
    protected:
        void afficherPoints(const Scene& scene,
                            vector<vector<char>>& grille) const override
        {
            for (auto& p : scene.getPoints()) {
                if (p->getX() >= 0 && p->getX() < LARGEUR &&
                    p->getY() >= 0 && p->getY() < HAUTEUR)
                {
                    grille[p->getY()][p->getX()] = '0' + (p->getId() % 10);
                }
            }
        }
};
