//
// Created by Kaydon Mohamed and Johnny on 2025-11-19.
//

#pragma once
#include <vector>
#include <memory>
#include "Nuage.h"

class SurfaceStrategy {
    public:
        virtual ~SurfaceStrategy() = default;

        virtual std::vector<std::vector<std::shared_ptr<Element>>>
        creerSurfaces(const std::vector<std::shared_ptr<Nuage>>& nuagess) const = 0;
};
