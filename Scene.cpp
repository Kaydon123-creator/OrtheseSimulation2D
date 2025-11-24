//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "Scene.h"
#include "Display.h"
#include "SurfaceStrategy.h"
#include <sstream>
#include <iostream>
#include <algorithm>


using namespace std;

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
        if (token.front() == '(' && token.back() == ')') {
            token = token.substr(1, token.size() - 2);
            replace(token.begin(), token.end(), ',', ' ');
            istringstream ps(token);
            int x, y;
            if (ps >> x >> y) {
               points_.push_back(make_shared<PointConcret>(id++, x, y));
            }
        }
    }
}

shared_ptr<Point> Scene::trouverPoint(int id)
{
    for (auto& p : points_)
        if (p->getId() == id) return p;
    return nullptr;
}

void Scene::afficherListe()
{
    cout << "\nPoints:\n";
    for (auto& p : points_) {

        cout << "ID " << p->getId() << " : (" << p->getX() << "," << p->getY()
             << "), textures=" <<"'" <<p->getTexture() <<"'" <<"\n";
    }
    if (!(nuages_.empty())) {
        cout << "\nNuages:\n";
        for (size_t i = 0; i < nuages_.size(); i++) {
            cout << "Nuage " << nuages_[i].getTexture() << " contient les points: ";


            const auto& points = nuages_[i].getPoints();

            for (size_t j = 0; j < points.size(); ++j) {
              
                if (j > 0) {
                    cout << ", ";
                }
                cout << points[j]->getId();
            }

            cout << "\n";
        }
    }
}

void Scene::afficherOrthese(const Display& strat) const
{
    strat.afficher(*this);
}

void Scene::fusionnerPoints(const vector<int>& ids)
{
    if (ids.empty()) return;

    string texture = (nuages_.empty() ? "o" :
                   (nuages_.size() == 1 ? "#" : "$"));
    Nuage n(texture);

    for (int id : ids) {
        // On cherche l'index pour pouvoir remplacer le pointeur dans le vecteur
        for (auto& pRef : points_) {
            if (pRef->getId() == id) {
                // On décore le point existant
                pRef = make_shared<DecorateurTexture>(pRef, texture);

                // On l'ajoute au nuage
                n.ajouterPoint(pRef);
                break;
            }
        }
    }
    nuages_.push_back(n);
}

void Scene::deplacerPoint(int id, int nx, int ny)
{
    auto p = trouverPoint(id);
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

void Scene::supprimerPoint(int id)
{
    points_.erase(
        remove_if(points_.begin(), points_.end(),
                  [id](auto& p){ return p->getId() == id; }), // getId()
        points_.end());

    for (auto& n : nuages_)
        n.enleverPoint(id);
}



void Scene::enleverPointDansBonNuage(
                              const std::string& textureRecherchee,
                              int pointId)
{
    for (Nuage& nuage : nuages_) {
        if (nuage.getTexture() == textureRecherchee) {
            for (auto it = nuage.getPoints().begin(); it != nuage.getPoints().end(); it++) {
                if ((*(it))->getId() == pointId) {
                    nuage.getPoints().erase(it);
                    return;
                }
            }
            return;
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

const vector<shared_ptr<Point>>& Scene::getPoints() const { return points_; }
const vector<Nuage>& Scene::getNuages() const { return nuages_; }
const vector<vector<shared_ptr<Point>>>& Scene::getSurfaces() const { return surfaces_; }
