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
#include <string>
#include <cstring>

//------------------------------------------------------------------------
// Rôle de la classe <FileManager>
// La classe FileManager permet d'ouvrir un fichier et de decouper ses lignes
// en vector de string.
// Cette classe herite de ifstream.
//------------------------------------------------------------------------

class FileManager : public ifstream
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    std::vector < std::string > Decouper (std::stringstream& s);
    // Mode d'emploi :
    // Fonction appelee par Data::Traiter pour decouper une ligne en un vecteur de mots

//-------------------------------------------- Constructeurs - destructeur
    FileManager ( std::string fileName );
    // Mode d'emploi :
    // Construit un FileManager a partir d'un nom de fichier .log

    virtual ~FileManager ( );
};

#endif // FileManager_H

