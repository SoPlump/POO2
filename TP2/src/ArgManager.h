/*************************************************************************
                           ArgManager  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <ArgManager> (fichier ArgManager.h) ----------------
#if ! defined ( ArgManager_H )
#define ArgManager_H

//--------------------------------------------------- Interfaces utilisées
#include <memory>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cctype>
#include <utility>
using namespace std;
//------------------------------------------------------------- Constantes

enum class Status { Good, Err_arg, Err_log, Err_t, Err_graphName, Err_gDup };
//------------------------------------------------------------------ Types
struct Options
{
    Status etat = Status::Good;
    bool eOption = false;
    bool gOption = false;
    bool tOption = false;
    unsigned int hour = 0;
    string logName;
    string graphName;

};

struct InvalidChar
{
    bool operator() ( const char& car ) const
    {
        return !isalnum(car) && car != '_' && car != '.' && car != '/' && car != '-';
    }
};


//------------------------------------------------------------------------
// Rôle de la classe <ArgManager>
// La classe ArgManager permet de verifier la coherence des arguments passes
// lors de l'execution et de ne pas lancer la lecture d'un log si ils ne
// sont pas bons.
// ArgManager met a jour les elements d'une instance d'une structure
// option.
//------------------------------------------------------------------------

class ArgManager
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Options getOptions ( );
    // Mode d'emploi :
    // Verifie la validite de chaque argument et met a jour option selon

    void getMessage ( Status etat );
    // Mode d'emploi :
    // Affiche l'etat du programme

    bool goodFile( const string& filename );
    // Mode d'emploi :
    // Verifie si le fichier log existe et n'est pas vide

//-------------------------------------------- Constructeurs - destructeur
    ArgManager ( int argc, char **argv );
    // Contrat :
    // Doit recevoir tous les arguments passes lors de l'execution

    ~ArgManager ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    
    bool goodFilename( const string& filename, const string& fileext ) const;
    // Mode d'emploi :
    // Verifie si le nom du fichier est valide. Que ce soit pour le log
    // ou pour le dot

//----------------------------------------------------- Attributs protégés
    int m_argc;
    vector<string> m_argv;
};

//-------------------------------- Autres définitions dépendantes de <ArgManager>

#endif // ArgManager_H

