//
// Created by Kaydon Mohamed on 2025-11-19.
//

#ifndef TEST2400_NUAGE_H
#define TEST2400_NUAGE_H

#endif //TEST2400_NUAGE_H
#pragma once
#include <vector>
#include <memory>
#include "Point.h"

class Nuage : public Point {
public:
    Nuage(int id, std::string texture);

    int getId() const override;
    int getX() const override;
    int getY() const override;
    void setPosition(int x, int y) override;
    std::string getTexture() const override;

    void ajouterEnfant(std::shared_ptr<Point> p);
    const std::vector<std::shared_ptr<Point>>& getEnfants() const;
    std::vector<std::shared_ptr<Point>>& getEnfants();
    void supprimerEnfant(int id);
    void appliquerTextureEnfants(const std::string& texture) ;
    void mettreAJourEnfant(std::shared_ptr<Point> pNouveau) ;
private:
    int id_;
    std::string texture_;
    std::vector<std::shared_ptr<Point>> enfants_;
};