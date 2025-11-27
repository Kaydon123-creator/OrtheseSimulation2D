//
// Created by Kaydon and Johnny on 2025-11-19.
//
#include "SurfaceStrategy.h"
#include "Nuage.h"
#include <algorithm>

using namespace std;

class SurfaceStrategyC1 : public SurfaceStrategy {
    private:
        void static extrairePoints(const shared_ptr<Element>& p, vector<shared_ptr<Element>>& res)  {
            shared_ptr<Element> courant = p;
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
        vector<vector<shared_ptr<Element>>> creerSurfaces(
            const vector<shared_ptr<Nuage>>& nuages) const override
        {
            vector<vector<shared_ptr<Element>>> surfaces;


            for (const auto& n : nuages) {
                vector<shared_ptr<Element>> pointsDuNuage;
                extrairePoints(n, pointsDuNuage);

                if (pointsDuNuage.empty()) continue;

                sort(pointsDuNuage.begin(), pointsDuNuage.end(),
                    [](const shared_ptr<Element>& a, const shared_ptr<Element>& b){
                        return a->getId() < b->getId();
                    });

                surfaces.push_back(pointsDuNuage);
            }

            return surfaces;
        }
};
