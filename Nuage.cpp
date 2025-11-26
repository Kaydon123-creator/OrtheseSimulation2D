//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "Nuage.h"


using namespace std;
Nuage::Nuage(const int& id,  const string& texture) : id_(id), texture_(texture) {}

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

void Nuage::ajouterEnfant(const shared_ptr<Element>& p) {
    enfants_.push_back(p);
}

const vector<shared_ptr<Element>>& Nuage::getEnfants() const {
    return enfants_;
}
vector<shared_ptr<Element>>& Nuage::getEnfants()  {
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
void Nuage::mettreAJourEnfant(const shared_ptr<Element>& pNouveau) {
    for (auto& enfant : enfants_) {
        if (enfant->getId() == pNouveau->getId()) {
            enfant = pNouveau;
        }


        else {
            shared_ptr<Element> courant = enfant;

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
            [id](const shared_ptr<Element>& p) { return p->getId() == id; }),
        enfants_.end());

    // Propagation aux sous-nuages
    for (auto& p : enfants_) {
        if (auto sousNuage = dynamic_pointer_cast<Nuage>(p)) {
            sousNuage->supprimerEnfant(id);
        }
    }
}