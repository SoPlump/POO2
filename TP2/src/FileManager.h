/*************************************************************************
                           FileManager  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <FileManager> (fichier FileManager.h) ----------------
#if ! defined ( FileManager_H )
#define FileManager_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <FileManager>
//
//
//------------------------------------------------------------------------

class FileManager : public ifstream
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector <string> Decouper (stringstream& s);

//------------------------------------------------- Surcharge d'opérateurs
    FileManager & operator = ( const FileManager & unFileManager );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    FileManager (string fileName) : ifstream(fileName.c_str()) {}
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~FileManager ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <FileManager>

#endif // FileManager_H

