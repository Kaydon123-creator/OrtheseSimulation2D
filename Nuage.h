//
// Created by Kaydon Mohamed on 2025-11-19.
//

#ifndef TEST2400_NUAGE_H
#define TEST2400_NUAGE_H

#endif //TEST2400_NUAGE_H
#pragma once
#include <vector>
#include <memory>
#include "Element.h"

class Nuage : public Element {
public:
    Nuage(const int& id, const std::string& texture);

    int getId() const override;
    int getX() const override;
    int getY() const override;
    void setPosition(int x, int y) override;
    std::string getTexture() const override;

    void ajouterEnfant(const std::shared_ptr<Element>& p);
    const std::vector<std::shared_ptr<Element>>& getEnfants() const;
    std::vector<std::shared_ptr<Element>>& getEnfants();
    void supprimerEnfant(int id);
    void appliquerTextureEnfants(const std::string& texture) ;
    void mettreAJourEnfant(const std::shared_ptr<Element>& pNouveau) ;
private:
    int id_;
    std::string texture_;
    std::vector<std::shared_ptr<Element>> enfants_;
};