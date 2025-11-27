//
// Created by Kaydon and Johnny on 2025-11-19.
//

#pragma once


#include <string>
#include <memory>
#include <iostream>

class Element {
    public:
        virtual ~Element() = default;

        virtual int getId() const = 0;
        virtual int getX() const = 0;
        virtual int getY() const = 0;
        virtual void setPosition(int x, int y) = 0;
        virtual std::string getTexture() const = 0;

        virtual std::shared_ptr<Element> getBase();
};

class PointConcret : public Element {
    protected:
        int id;
        int x, y;
    public:
        PointConcret(int id, int x, int y);

        int getId() const override;
        int getX() const override;
        int getY() const override;
        void setPosition(int nx, int ny) override;

        std::string getTexture() const override;
};

class PointDecorateur : public Element {
    protected:
        std::shared_ptr<Element> point_;
    public:
        explicit PointDecorateur(const std::shared_ptr<Element>& p);

        int getId() const override;
        int getX() const override;
        int getY() const override;
        void setPosition(int x, int y) override;

        std::shared_ptr<Element> getBase() override;

        std::string getTexture() const override;
};

class DecorateurTexture : public PointDecorateur {
    protected:
        std::string textureAjoutee_;
    public:
        DecorateurTexture(const std::shared_ptr<Element>& p, const std::string& t);

        std::string getTexture() const override;
};