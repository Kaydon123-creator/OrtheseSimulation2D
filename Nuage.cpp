//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "Nuage.h"
#include <algorithm>

using namespace std;

Nuage::Nuage(string texture) : texture_(texture) {}

void Nuage::ajouterPoint(shared_ptr<Point> p) {
    points_.push_back(p);
}

void Nuage::enleverPoint(int pointId) {
    points_.erase(
        remove_if(points_.begin(), points_.end(),
                  [pointId](const shared_ptr<Point>& p) {
                      return p->id == pointId;
                  }),
        points_.end());
}

string Nuage::getTexture() const {
    return texture_;
}

vector<shared_ptr<Point>>  Nuage::getPoints()  {
    return points_;
}

vector<shared_ptr<Point>> const Nuage::getPoints() const {
    return points_;
}
