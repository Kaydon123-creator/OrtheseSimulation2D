//
// Created by Kaydon and Johnny on 2025-11-26.
//
#pragma once

#include "Scene.h"
#include <stack>
#include <memory>

class Commande {
public:
    virtual ~Commande() = default;
    virtual void executer() = 0;
    virtual void annuler() = 0;
};


class CommandeDeplacer : public Commande {
    private:
        Scene& scene;
        int id;
        int xAvant, yAvant;
        int xApres, yApres;

    public:
        CommandeDeplacer(Scene& s, int id, int nx, int ny);
        void executer() override;
        void annuler() override;
};


class CommandeSupprimer : public Commande {
    private:
        Scene& scene;
        int id;
        std::shared_ptr<Element> elementSauvegarde ;

    public:
        CommandeSupprimer(Scene& s, int id) ;
        void executer()   override;


        void annuler() override ;
};


class Invocateur {
    private:
        std::stack<std::shared_ptr<Commande>> pileUndo;
        std::stack<std::shared_ptr<Commande>> pileRedo;

    public:
        void executerCommande(std::shared_ptr<Commande> cmd);
        void undo();
        void redo();
};