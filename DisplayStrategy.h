//
// Created by Kaydon Mohamed on 2025-11-19.
//

#ifndef TEST2400_DISPLAYSTATEGY_H
#define TEST2400_DISPLAYSTATEGY_H

#endif //TEST2400_DISPLAYSTATEGY_H

#pragma once

#include "Scene.h"

class DisplayStrategy {
public:
    virtual ~DisplayStrategy() = default;
    virtual void afficher(const Scene& scene) const = 0;
};