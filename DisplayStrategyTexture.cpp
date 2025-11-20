//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "DisplayStrategy.h"
#include "affichage.h"
#include <vector>



using namespace std;

class DisplayStrategyTexture : public DisplayStrategy {
public:
    void afficher(const Scene& scene) const override {
        vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));
        scene.creerLigne(grille);
        for (auto& p : scene.getPoints()) {
            if (p->x >= 0 && p->x < LARGEUR &&
                p->y >= 0 && p->y < HAUTEUR)
            {
                const int LARGEUR = 30;
                string tex = p->texture;
                int L = tex.size();

                for (int dx = 0; dx < L; dx++) {
                    int xx = p->x + dx;

                    if (xx >= LARGEUR)
                        break;  // on dépasse, on arrête proprement

                    grille[p->y][xx] = tex[dx];
                }
            }
        }

        afficherGrille(grille);
    }
};