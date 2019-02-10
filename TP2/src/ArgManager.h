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

enum class Status { Good, Err_arg, Err_log, Err_t, Err_graphName, Err_gDup};
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
//
//
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

    Options getOptions ();

    void getMessage (Status etat);

    bool goodFilename(const string& filename, const string& fileext);

    bool goodFile(const string& filename);

//-------------------------------------------- Constructeurs - destructeur
    ArgManager (int argc, char **argv );
    // Mode d'emploi :
    //
    // Contrat :
    //

    ~ArgManager ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
int m_argc;
vector<string> m_argv;
};

//-------------------------------- Autres définitions dépendantes de <ArgManager>

#endif // ArgManager_H

