//
// Created by Kaydon Mohamed on 2025-11-19.
//

#ifndef TEST2400_SURFACESTRATEGY_H
#define TEST2400_SURFACESTRATEGY_H

#endif //TEST2400_SURFACESTRATEGY_H

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
