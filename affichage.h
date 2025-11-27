
#pragma once
#include <vector>

const int LARGEUR = 30;
const int HAUTEUR = 20;

void tracerLigne(std::vector<std::vector<char>>& grille,
                 int x0, int y0, int x1, int y1);

void afficherGrille(const std::vector<std::vector<char>>& grille);

