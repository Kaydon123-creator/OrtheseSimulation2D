//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "SurfaceStrategy.h"
#include "Nuage.h"
#include <algorithm>

using namespace std;

class SurfaceStrategyC1 : public SurfaceStrategy {
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
                vector<shared_ptr<Point>> pointsDuNuage;
                extrairePoints(n, pointsDuNuage);

                if (pointsDuNuage.empty()) continue;

                sort(pointsDuNuage.begin(), pointsDuNuage.end(),
                    [](const shared_ptr<Point>& a, const shared_ptr<Point>& b){
                        return a->getId() < b->getId();
                    });

                surfaces.push_back(pointsDuNuage);
            }

            return surfaces;
        }
};
