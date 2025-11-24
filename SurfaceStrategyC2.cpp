//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "SurfaceStrategy.h"
#include <cmath>
#include <algorithm>

using namespace std;

static double dist(shared_ptr<Point> a, shared_ptr<Point> b) {
    double dx = a->getX() - b->getX();
    double dy = a->getY() - b->getY();
    return sqrt(dx*dx + dy*dy);
}

class SurfaceStrategyC2 : public SurfaceStrategy {
public:
    vector<vector<shared_ptr<Point>>> creerSurfaces(
        const vector<Nuage>& nuages) const override
    {
        vector<vector<shared_ptr<Point>>> surfaces;

        for (auto& nuage : nuages) {
            auto restants = nuage.getPoints();
            if (restants.empty()) continue;

            vector<shared_ptr<Point>> ordre;

            auto courant = restants[0];
            ordre.push_back(courant);

            restants.erase(restants.begin());

            while (!restants.empty()) {
                auto it = min_element(restants.begin(), restants.end(),
                    [&](auto& p1, auto& p2){
                        return dist(courant, p1) < dist(courant, p2);
                    }
                );

                courant = *it;
                ordre.push_back(courant);
                restants.erase(it);
            }

            surfaces.push_back(ordre);
        }

        return surfaces;
    }
};
