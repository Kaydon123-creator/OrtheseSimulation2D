//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "Display.h"
#include "affichage.h"
#include <vector>



using namespace std;

class DisplayTexture : public Display {
    protected:
        void afficherPoints(const Scene& scene,
                            vector<vector<char>>& grille) const override
        {
            for (auto& p : scene.getPoints()) {
                // Utilisez getX(), getY()
                if (p->getX() >= 0 && p->getX() < LARGEUR &&
                    p->getY() >= 0 && p->getY() < HAUTEUR)
                {
                    string tex = p->getTexture(); // Appel polymorphique
                    int L = tex.size();

                    for (int dx = 0; dx < L; dx++) {
                        int xx = p->getX() + dx;
                        if (xx >= LARGEUR) break;
                        grille[p->getY()][xx] = tex[dx];
                    }
                }
            }
        }
};