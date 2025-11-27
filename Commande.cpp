//
// Created by Kaydon and Johnny on 2025-11-26.
//
#include "Commande.h"


using namespace std;



CommandeDeplacer::CommandeDeplacer(Scene& s, int id, int nx, int ny) 
    : scene(s), id(id), xApres(nx), yApres(ny) 
{

    auto el = scene.trouverElement(id);
    if (el) {
        xAvant = el->getX();
        yAvant = el->getY();
    } else {
        xAvant = 0; yAvant = 0; // securité
    }
}

void CommandeDeplacer::executer() {
    scene.deplacerPoint(id, xApres, yApres);
}

void CommandeDeplacer::annuler() {
    scene.deplacerPoint(id, xAvant, yAvant);
}




CommandeSupprimer::CommandeSupprimer(Scene& s, int id) 
    : scene(s), id(id) 
{

    elementSauvegarde = scene.trouverElement(id) ;
}

void CommandeSupprimer::executer()   {
    if (elementSauvegarde) {

        scene.supprimerPoint(id);
    }
}

void CommandeSupprimer::annuler() {

    if (elementSauvegarde)

        {
        scene.ajouterElement(elementSauvegarde);
    }
}




void Invocateur::executerCommande(shared_ptr<Commande> cmd) {
    cmd->executer() ;
    pileUndo.push(cmd) ;
    while (!pileRedo.empty()) {
        pileRedo.pop();
    }
}

void Invocateur::undo() {
    if (pileUndo.empty()) {
        return;
    }

    auto cmd = pileUndo.top();
    pileUndo.pop();
    
    cmd->annuler();
    
    pileRedo.push(cmd);

}

void Invocateur::redo() {
    if (pileRedo.empty()) {

        return;
    }

    auto cmd = pileRedo.top();
    pileRedo.pop();
    
    cmd->executer();
    
    pileUndo.push(cmd);

}