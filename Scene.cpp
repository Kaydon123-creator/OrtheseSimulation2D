//
// Created by Kaydon and Johnny on 2025-11-19.
//
#include "Scene.h"
#include "Display.h"
#include "SurfaceStrategy.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <affichage.h>


using namespace std;

void trouverIdsReels(const shared_ptr<Element>& p, vector<int>& listeIds) {
    shared_ptr<Element> courant = p;

    while(auto deco = dynamic_pointer_cast<PointDecorateur>(courant)) courant = deco->getBase();

    if (auto n = dynamic_pointer_cast<Nuage>(courant)) {
        for(auto& enfant : n->getEnfants()) trouverIdsReels(enfant, listeIds);
    } else {
        listeIds.push_back(p->getId());
    }
}
bool estTrieParId(const std::vector<std::shared_ptr<Element>>& elements) {
    // std::is_sorted retourne true si la plage est triée selon le comparateur fourni
    return is_sorted(elements.begin(), elements.end(),
        [](const std::shared_ptr<Element>& a, const std::shared_ptr<Element>& b) {
            return a->getId() < b->getId();
        });
}

Scene::Scene(const string& input)
{
    creerPoint(input);
}

void Scene::creerPoint(const string& line)
{
    string token;
    istringstream iss(line);
    int id = 0;
    while (iss >> token) {
        bool formatCorrect = false;
        if (token.size() >= 3 && token.front() == '(' && token.back() == ')') {

            string content = token.substr(1, token.size() - 2);

            replace(content.begin(), content.end(), ',', ' ');

            istringstream ps(content);
            int x, y;


            if (ps >> x >> y) {
                char reste;
                if (!(ps >> reste)) {
                    elements_.push_back(make_shared<PointConcret>(id++, x, y));
                    formatCorrect = true;
                }
            }
        }

        if (!formatCorrect) {
            throw runtime_error("Erreur : Entrée invalide. Le format doit être (x,y) séparé par des espaces.");
        }
    }
}

shared_ptr<Element> Scene::trouverElement(int id)
{
    for (auto& p : elements_)
        if (p->getId() == id) return p;
    return nullptr;
}

void Scene::afficherListe() {
    cout << "Liste:\n";
    if (!(estTrieParId(elements_))) {
        sort(elements_.begin(), elements_.end(), [](const shared_ptr<Element>& a, const shared_ptr<Element>& b) {
    return a->getId() < b->getId();});
    }
    for (const auto& p : elements_) {
        auto nuage = dynamic_pointer_cast<Nuage>(p);

        if (nuage ) {
            if (!(nuage->getEnfants().empty())) {
                cout << nuage->getId() << ": Nuage '" << nuage->getTexture()
                     << "' contient les éléments:";

                for (const auto& enfant : nuage->getEnfants()) {
                    cout << " " << enfant->getId();
                }
                cout << "\n";
            }
        }
        else {
            string texture = p->getTexture() == "." ? " " : p->getTexture();
            cout << p->getId() << ": (" << p->getX() << "," << p->getY()
                 << ") textures: '" << texture << "'\n";
        }
    }
}

void Scene::afficherOrthese(const Display& strat) const
{
    strat.afficher(*this);
}


void Scene::fusionnerElements(const vector<int>& ids) {
    if (ids.empty()) return;


    int maxId = 0;
    int nbNuages = 0;
    for (const auto& p : elements_) {
        if (p->getId() > maxId) maxId = p->getId();
        if (dynamic_pointer_cast<Nuage>(p)) nbNuages++;
    }

    string texture = string(1, "o#$%&"[nbNuages % 5]);
    auto nouveauNuage = make_shared<Nuage>(maxId + 1, texture);
    vector<int> idsATexturer;

    for (auto& p : elements_) {
        bool estDansLaDemande = false;
        for(int id : ids) {
            if(p->getId() == id) {
                estDansLaDemande = true;
            }


        }
        if (estDansLaDemande) {

            nouveauNuage->ajouterEnfant(p);
            trouverIdsReels(p, idsATexturer);
        }
    }


    for (auto& p : elements_) {


        bool aTexturer = false;
        for(int id : idsATexturer) if(p->getId() == id) aTexturer = true;

        if (aTexturer) {

            shared_ptr<Element> check = p;

            if (!dynamic_pointer_cast<Nuage>(check)) {


                p = make_shared<DecorateurTexture>(p, texture);


                for (auto& n : nuages_) {
                    n->mettreAJourEnfant(p);
                }

                nouveauNuage->mettreAJourEnfant(p);
            }
        }
    }

    if (!nouveauNuage->getEnfants().empty()) {
        elements_.push_back(nouveauNuage);
        nuages_.push_back(nouveauNuage);
    }
}
void Scene::deplacerPoint(int id, int nx, int ny)
{
    if (detecterNuage(id)) {
        std::cout << "Opération annulée car le deplacement de nuages n'est pas autorisée." << std::endl;
        return;
    }
    auto p = trouverElement(id);
    if (p) {
        p->setPosition(nx, ny);
    }
}
void Scene::creerLigne(vector<vector<char> > &grille) const{

    for (int j = 0; j < surfaces_.size() ; j++) {
        auto points = surfaces_[j];
        for (int i = 0; i <points.size() - 1; i++) {
            tracerLigne(grille, points[i]->getX(), points[i]->getY(), points[i+1]->getX(), points[i+1]->getY());
        }
        tracerLigne(grille, points[points.size() - 1]->getX(), points[points.size() - 1]->getY(), points[0]->getX(), points[0]->getY());
    }

}
bool Scene::detecterNuage(int id) {
    std::shared_ptr<Element> elementASupprimer = nullptr;
    auto it = elements_.begin();
    while (it != elements_.end()) {
        if ((*it)->getId() == id) {
            elementASupprimer = *it;
            break;
        }
        ++it;
    }
    if (!elementASupprimer) {
        return true;
    }
    if (std::dynamic_pointer_cast<Nuage>(elementASupprimer)) {
        return true;
    }
    return false;
}
void Scene::ajouterElement(const std::shared_ptr<Element>& e) {
    elements_.push_back(e);
}
void Scene::supprimerPoint(int id)
{   //TODO:   effecture undo et redo
    // 1. Suppression au premier niveau
    //tcheck rapide pour voir si on essaye pas de supprimer un nuage entier
    if (detecterNuage(id)) {
        std::cout << "Opération annulée car la suppression de nuages n'est pas autorisée." << std::endl;
        return;
    }

    elements_.erase(
        remove_if(elements_.begin(), elements_.end(),
            [id](const shared_ptr<Element>& p) { return p->getId() == id; }),
        elements_.end());

    // 2. Propagation aux nuages restants
    for (auto& p : elements_) {
        // Comme les nuages ne sont plus décorés, le cast est direct
        if (auto nuage = dynamic_pointer_cast<Nuage>(p)) {
            nuage->supprimerEnfant(id);
        }
    }

}




void Scene::setStrategieCreationSurface(std::unique_ptr<SurfaceStrategy> strat) {
    startegieCreation_ = std::move(strat);
}

void Scene::creerSurface()
{
    surfaces_ = startegieCreation_->creerSurfaces(nuages_);
}

const vector<shared_ptr<Element>>& Scene::getPoints() const { return elements_; }
const std::vector<std::shared_ptr<Nuage>>& Scene::getNuages() const { return nuages_; }
const vector<vector<shared_ptr<Element>>>& Scene::getSurfaces() const { return surfaces_; }
