//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "SurfaceStrategy.h"
#include <algorithm>

using namespace std;

class SurfaceStrategyC1 : public SurfaceStrategy {
public:
    vector<vector<shared_ptr<Point>>> creerSurfaces(
        const vector<Nuage>& nuages)  const override
    {
        vector<vector<shared_ptr<Point>>> surfaces;

        for (const auto& n : nuages) {
            auto pts = n.getPoints();
            sort(pts.begin(), pts.end(),
                [](auto& a, auto& b){ return a->id < b->id; });

            surfaces.push_back(pts);
        }

        return surfaces;
    }
};
