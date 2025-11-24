//
// Created by Kaydon Mohamed on 2025-11-19.
//

#ifndef TEST2400_POINT_H
#define TEST2400_POINT_H

#endif //TEST2400_POINT_H

#pragma once


#include <string>
#include <memory>
#include <iostream>

// 1. Component (Interface)
class Point {
    public:
        virtual ~Point() = default;

        // Méthodes virtuelles pures (Getters/Setters nécessaires)
        virtual int getId() const = 0;
        virtual int getX() const = 0;
        virtual int getY() const = 0;
        virtual void setPosition(int x, int y) = 0;
        virtual std::string getTexture() const = 0;

        // Permet de récupérer l'objet décoré (pour le "undo")
        virtual std::shared_ptr<Point> getBase() { return nullptr; }
};

// 2. Concrete Component (Le point de base)
class PointConcret : public Point {
    protected:
        int id;
        int x, y;
    public:
        PointConcret(int id, int x, int y) : id(id), x(x), y(y) {}

        int getId() const override { return id; }
        int getX() const override { return x; }
        int getY() const override { return y; }
        void setPosition(int nx, int ny) override { x = nx; y = ny; }

        std::string getTexture() const override { return "."; }
};

// 3. Decorator (Classe de base des décorateurs)
class PointDecorateur : public Point {
    protected:
        std::shared_ptr<Point> point_; // Le point emballé
    public:
        PointDecorateur(std::shared_ptr<Point> p) : point_(p) {}

        int getId() const override { return point_->getId(); }
        int getX() const override { return point_->getX(); }
        int getY() const override { return point_->getY(); }
        void setPosition(int x, int y) override { point_->setPosition(x, y); }

        // Retourne le parent pour permettre le retrait du décorateur
        std::shared_ptr<Point> getBase() override { return point_; }

        std::string getTexture() const override { return point_->getTexture(); }
};

// 4. Concrete Decorator (Texture spécifique)
class DecorateurTexture : public PointDecorateur {
    protected:
        std::string textureAjoutee_;
    public:
        DecorateurTexture(std::shared_ptr<Point> p, std::string t)
            : PointDecorateur(p), textureAjoutee_(t) {}

        std::string getTexture() const override {
            std::string baseTex = point_->getTexture();
            if (baseTex == ".") return textureAjoutee_;
            return baseTex + textureAjoutee_;
        }
};