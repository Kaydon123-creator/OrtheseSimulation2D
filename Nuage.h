//
// Created by Kaydon Mohamed on 2025-11-19.
//

#ifndef TEST2400_NUAGE_H
#define TEST2400_NUAGE_H

#endif //TEST2400_NUAGE_H
#pragma once
#include <vector>
#include <memory>
#include "Point.h"

class Nuage {
public:
    Nuage(std::string texture);

    void ajouterPoint(std::shared_ptr<Point> p);
    void enleverPoint(int pointId);

    std::string getTexture() const;
    std::vector<std::shared_ptr<Point>>  getPoints() ;
    std::vector<std::shared_ptr<Point>>  const getPoints() const ;

private:
    std::string texture_;
    std::vector<std::shared_ptr<Point>> points_;
};
