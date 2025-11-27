//
// Created by Kaydon and Johnny on 2025-11-19.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Scene.h"
#include "Commande.h"
// #include "DisplayStrategy.h"
#include "DisplayID.cpp"
#include "DisplayTexture.cpp"
#include "SurfaceStrategyC1.cpp"
#include "SurfaceStrategyC2.cpp"



using namespace std;

int main(int argc, char* argv[]) {
    string args;
    // On accepte des points en entrée.
    if (argc > 1) {
        ostringstream oss;
        for (int i = 1; i < argc; ++i) oss << argv[i] << " ";
        args = oss.str();
    } else {
        cout << "Entrez les points au format (x,y) :\n> ";
        getline(cin, args);
    }
    
    // Voici des fonctions utiles pour réaliser le TP.
    // TODO: Il faudrait les placer dans des classes appropriées.
    Scene scene(args);
    DisplayTexture o1;
    DisplayID o2;
    SurfaceStrategyC1 c1;
    SurfaceStrategyC2 c2;
    Invocateur historique;
    
    // Ce sont différentes textures possibles. Seules les 2 premières sont utilisées dans les scénarios du TP.
    vector<char> texturesNuages = {'o', '#', '$'};
    string cmd;
    
    // Menu
    while (true) {
        cout << "\nCommandes:\n"
                  << "a  - Afficher les points et les nuages\n"
                  << "o1 - Afficher l'orthèse avec les textures des points\n"
                  << "o2 - Afficher l'orthèse avec les IDs des points\n"
                  << "f  - Fusionner des points/nuages dans un nuage (et appliquer texture)\n"
                  << "d  - Deplacer un point (ID)\n"
                  << "s  - Supprimer un point (ID)\n"
        << "u - Annuler la dernière commande (undo)\n"
        << "r - Réappliquer la dernière commande annulée(redo)\n"
                  << "c1 - Créer les surfaces selon l'ordre des IDs\n"
                  << "c2 - Créer les surfaces selon la distance minimale\n"
                  << "q  - Quitter\n> ";
        getline(std::cin, cmd);

        if (cmd == "q") break;
        else if (cmd == "a") scene.afficherListe();
        else if (cmd == "o1") scene.afficherOrthese(o1);
        else if (cmd == "o2") scene.afficherOrthese(o2);
        else if (cmd == "c1") {
            scene.setStrategieCreationSurface(std::make_unique<SurfaceStrategyC1>());
            scene.creerSurface();
        }
        else if (cmd == "c2") {
            scene.setStrategieCreationSurface(std::make_unique<SurfaceStrategyC2>());
            scene.creerSurface();
        }

        else if (cmd == "d") {
            cout << "ID : "; int id; cin >> id;
            cout << "x y : "; int x,y; cin >> x >> y;
            cin.ignore();
            auto deplacement = make_shared<CommandeDeplacer>(scene, id, x, y);
            historique.executerCommande(deplacement);
        }
        else if (cmd == "s") {
            cout << "ID : "; int id; cin >> id;
            cin.ignore();
            auto suppression = make_shared<CommandeSupprimer>(scene, id);
            historique.executerCommande(suppression);
        }
        else if (cmd == "f") {
            cout << "IDs (ex: 0 2 4): ";
            string line; getline(cin,line);
            istringstream iss(line);
            vector<int> ids; int v;
            while (iss >> v) ids.push_back(v);
            scene.fusionnerElements(ids);
        }
        else if (cmd == "u") {
            historique.undo();
        }
        else if (cmd == "r") {
            historique.redo();
        }
        else {
            cout << "Commands incorrect.\n";
        }
    }

    return 0;
}