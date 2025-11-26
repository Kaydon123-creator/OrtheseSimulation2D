//
// Created by Kaydon Mohamed on 2025-11-19.
//
#include "Element.h"

std::shared_ptr<Element> Element::getBase() { return nullptr; }

PointConcret::PointConcret(int id, int x, int y) : id(id), x(x), y(y) {}

int PointConcret::getId() const { return id; }

int PointConcret::getX() const { return x; }

int PointConcret::getY() const { return y; }

void PointConcret::setPosition(int nx, int ny) { x = nx; y = ny; }

std::string PointConcret::getTexture() const { return "."; }

PointDecorateur::PointDecorateur(const std::shared_ptr<Element>& p) : point_(p) {}

int PointDecorateur::getId() const { return point_->getId(); }

int PointDecorateur::getX() const { return point_->getX(); }

int PointDecorateur::getY() const { return point_->getY(); }

void PointDecorateur::setPosition(int x, int y) { point_->setPosition(x, y); }

std::shared_ptr<Element> PointDecorateur::getBase() { return point_; }

std::string PointDecorateur::getTexture() const { return point_->getTexture(); }

DecorateurTexture::DecorateurTexture(const std::shared_ptr<Element>& p, const std::string& t)
    : PointDecorateur(p), textureAjoutee_(t) {}

std::string DecorateurTexture::getTexture() const {
    std::string baseTex = point_->getTexture();
    if (baseTex == ".") return textureAjoutee_;
    return baseTex + textureAjoutee_;
}