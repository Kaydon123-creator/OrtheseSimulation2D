//
// Created by Kaydon Mohamed on 2025-11-19.
//

#ifndef TEST2400_SCENE_H
#define TEST2400_SCENE_H

#endif //TEST2400_SCENE_H
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Point.h"
#include "Nuage.h"
#include "affichage.h"

class Display;
class SurfaceStrategy;

class Scene {
public:
    Scene(const std::string& input);

    void afficherListe() ;
    void afficherOrthese(const Display& strat) const;

    void fusionnerPoints(const std::vector<int>& ids);
    void deplacerPoint(int id, int nx, int ny);
    void supprimerPoint(int id);
    void creerSurface();

    void creerLigne(std::vector<std::vector<char> > &grille) const;

    const std::vector<std::shared_ptr<Point>>& getPoints() const;

    const std::vector<std::shared_ptr<Nuage>>& getNuages() const;

    const std::vector<std::vector<std::shared_ptr<Point>>>& getSurfaces() const;
    void setStrategieCreationSurface(std::unique_ptr<SurfaceStrategy> strat);
    void enleverPointDansBonNuage(
                              const std::string& textureRecherchee,
                              int pointId) ;

private:
    std::vector<std::shared_ptr<Point>> points_;
    std::vector<std::shared_ptr<Nuage>> nuages_;
    std::vector<std::vector<std::shared_ptr<Point>>> surfaces_;
    std::unique_ptr<SurfaceStrategy> startegieCreation_;
    std::shared_ptr<Point> trouverPoint(int id);
    void creerPoint(const std::string& line);
};
