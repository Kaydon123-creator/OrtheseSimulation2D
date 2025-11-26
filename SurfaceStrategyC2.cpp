//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "SurfaceStrategy.h"
#include "Nuage.h"
#include <cmath>
#include <algorithm>

using namespace std;

static double dist(shared_ptr<Point> a, shared_ptr<Point> b) {
    double dx = a->getX() - b->getX();
    double dy = a->getY() - b->getY();
    return sqrt(dx*dx + dy*dy);
}

class SurfaceStrategyC2 : public SurfaceStrategy {
    private:
        void extrairePoints(shared_ptr<Point> p, vector<shared_ptr<Point>>& res) const {
            shared_ptr<Point> courant = p;
            while(auto deco = dynamic_pointer_cast<PointDecorateur>(courant)) {
                courant = deco->getBase();
            }

            if (auto nuage = dynamic_pointer_cast<Nuage>(courant)) {
                for(const auto& enfant : nuage->getEnfants()) {
                    extrairePoints(enfant, res);
                }
            } else {
                res.push_back(p);
            }
        }

    public:
        vector<vector<shared_ptr<Point>>> creerSurfaces(
            const vector<shared_ptr<Nuage>>& nuages) const override
        {
            vector<vector<shared_ptr<Point>>> surfaces;

            for (const auto& n : nuages) {
                // 1. Récupérer tous les points (feuilles) de ce nuage spécifique
                vector<shared_ptr<Point>> restants;
                extrairePoints(n, restants);

                if (restants.empty()) continue;
                vector<shared_ptr<Point>> ordre;

                auto courant = restants[0];
                ordre.push_back(courant);
                restants.erase(restants.begin());

                while (!restants.empty()) {
                    auto it = min_element(restants.begin(), restants.end(),
                        [&](shared_ptr<Point> p1, shared_ptr<Point> p2){
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
