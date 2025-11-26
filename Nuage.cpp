//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "Nuage.h"


using namespace std;



Nuage::Nuage(int id, string texture) : id_(id), texture_(texture) {}

int Nuage::getId() const {
    return id_;
}

int Nuage::getX() const {
    return -1;
}

int Nuage::getY() const {
    return -1;
}

void Nuage::setPosition(int x, int y) {
}

string Nuage::getTexture() const {
    return texture_;
}

void Nuage::ajouterEnfant(shared_ptr<Point> p) {
    enfants_.push_back(p);
}

const vector<shared_ptr<Point>>& Nuage::getEnfants() const {
    return enfants_;
}
vector<shared_ptr<Point>>& Nuage::getEnfants()  {
    return enfants_;
}
void Nuage::appliquerTextureEnfants(const string& texture) {
    for (auto& p : enfants_) {
        if (auto sousNuage = dynamic_pointer_cast<Nuage>(p)) {
            sousNuage->appliquerTextureEnfants(texture);
        }
        else {
            p = make_shared<DecorateurTexture>(p, texture);
        }
    }
}
void Nuage::mettreAJourEnfant(shared_ptr<Point> pNouveau) {
    for (auto& enfant : enfants_) {

        // 1. C'est le point qu'on cherche ? On le remplace !
        if (enfant->getId() == pNouveau->getId()) {
            enfant = pNouveau; // Synchronisation effectuée
        }


        else {
            shared_ptr<Point> courant = enfant;

            while(auto deco = dynamic_pointer_cast<PointDecorateur>(courant)) courant = deco->getBase();

            if (auto sousNuage = dynamic_pointer_cast<Nuage>(courant)) {
                sousNuage->mettreAJourEnfant(pNouveau);
            }
        }
    }
}
void Nuage::supprimerEnfant(int id) {

    enfants_.erase(
        remove_if(enfants_.begin(), enfants_.end(),
            [id](shared_ptr<Point> p) { return p->getId() == id; }),
        enfants_.end());

    // Propagation aux sous-nuages
    for (auto& p : enfants_) {
        if (auto sousNuage = dynamic_pointer_cast<Nuage>(p)) {
            sousNuage->supprimerEnfant(id);
        }
    }
}