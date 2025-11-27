//
// Created by Kaydon and Johnny on 2025-11-19.
//

#ifndef TEST2400_SCENE_H
#define TEST2400_SCENE_H

#endif //TEST2400_SCENE_H
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Element.h"
#include "Nuage.h"


class Display;
class SurfaceStrategy;

class Scene {
    public:
        explicit Scene(const std::string& input);

        void afficherListe();
        void afficherOrthese(const Display& strat) const;

        void fusionnerElements(const std::vector<int>& ids) ;
        void deplacerPoint(int id, int nx, int ny);
        void supprimerPoint(int id) ;
        void creerSurface();
        bool detecterNuage(int id);

        void creerLigne(std::vector<std::vector<char> > &grille) const ;

        const std::vector<std::shared_ptr<Element>>& getPoints() const;

        const std::vector<std::shared_ptr<Nuage>>& getNuages() const ;

        const std::vector<std::vector<std::shared_ptr<Element>>>& getSurfaces() const;
        void setStrategieCreationSurface(std::unique_ptr<SurfaceStrategy> strat);
        std::shared_ptr<Element> trouverElement(int id) ;
        void ajouterElement(const std::shared_ptr<Element>& e) ;
    private:
        std::vector<std::shared_ptr<Element>> elements_;
        std::vector<std::shared_ptr<Nuage>> nuages_;
        std::vector<std::vector<std::shared_ptr<Element>>> surfaces_;
        std::unique_ptr<SurfaceStrategy> startegieCreation_;

        void creerPoint(const std::string& line);
};
