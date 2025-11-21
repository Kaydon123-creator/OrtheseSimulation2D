//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "Scene.h"
#include "DisplayStrategy.h"
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
                auto p = make_shared<Point>();
                p->id = id++;
                p->x = x;
                p->y = y;
                p->texture = '.';
                points_.push_back(p);
            }
        }
    }
}

shared_ptr<Point> Scene::trouverPoint(int id)
{
    for (auto& p : points_)
        if (p->id == id) return p;
    return nullptr;
}

void Scene::afficherListe()
{
    cout << "\nPoints:\n";
    for (auto& p : points_) {
        auto text = (p->texture == ".") ? "" : p->texture;
        cout << "ID " << p->id << " : (" << p->x << "," << p->y
             << "), textures=" <<"'" <<text <<"'" <<"\n";
    }
    if (!(nuages_.empty())) {
        cout << "\nNuages:\n";
        for (size_t i = 0; i < nuages_.size(); i++) {
            cout << "Nuage " << i << ", tex=" << nuages_[i].getTexture() << " : ";
            for (auto& p : nuages_[i].getPoints())
                cout << p->id << " ";
            cout << "\n";
        }
    }
}

void Scene::afficherOrthese(const DisplayStrategy& strat) const
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
        auto p = trouverPoint(id);
        if (p) {
            if (p->texture != ".") {
                p->texture += texture;
                p->ancienneTexture = texture.substr(1);
            }
            else {
                p->texture = texture;
                p->ancienneTexture = "." ;
            }

            n.ajouterPoint(p);
        }
    }

    nuages_.push_back(n);
}

void Scene::deplacerPoint(int id, int nx, int ny)
{
    auto p = trouverPoint(id);
    if (p) {
        p->x = nx;
        p->y = ny;
    }
}
void Scene::creerLigne(vector<vector<char> > &grille) const{

    for (int j = 0; j < surfaces_.size() ; j++) {
        auto points = surfaces_[j];
        for (int i = 0; i <points.size() - 1; i++) {
            tracerLigne(grille, points[i]->x, points[i]->y, points[i+1]->x, points[i+1]->y);
        }
        tracerLigne(grille, points[points.size() - 1]->x, points[points.size() - 1]->y, points[0]->x, points[0]->y);
    }

}

void Scene::supprimerPoint(int id)
{
    points_.erase(
        remove_if(points_.begin(), points_.end(),
                  [id](auto& p){ return p->id == id; }),
        points_.end());

    for (auto& n : nuages_)
        n.enleverPoint(id);
}
void Scene::undoTexture(std::shared_ptr<Point>& p) {
    enleverPointDansBonNuage(string(1,p->texture[0]), p->id) ;
    p->texture = p->ancienneTexture;

}
void Scene::ecraserTexture(std::shared_ptr<Point>& p) {
    for (auto
        & c : p->texture) {
        enleverPointDansBonNuage(string(1,c), p->id) ;
    }

    p->texture = ".";

}

void Scene::enleverPointDansBonNuage(
                              const std::string& textureRecherchee,
                              int pointId)
{
    for (Nuage& nuage : nuages_) {
        if (nuage.getTexture() == textureRecherchee) {
            for (auto it = nuage.getPoints().begin(); it != nuage.getPoints().end(); it++) {
                if ((*(it))->id == pointId) {
                    nuage.getPoints().erase(it);
                    return;
                }
            }
            return;
        }
    }
}


void Scene::creerSurface(const SurfaceStrategy& strat)
{
    surfaces_ = strat.creerSurfaces(nuages_);
}

const vector<shared_ptr<Point>>& Scene::getPoints() const { return points_; }
const vector<Nuage>& Scene::getNuages() const { return nuages_; }
const vector<vector<shared_ptr<Point>>>& Scene::getSurfaces() const { return surfaces_; }
