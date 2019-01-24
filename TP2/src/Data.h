/*************************************************************************
                           Data  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Data> (fichier Data.h) ----------------
#if ! defined ( DATA_H )
#define DATA_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <map>
#include <string>
#include "FileManager.h"
#include "Noeud.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef unsigned int uint;

//------------------------------------------------------------------------
// Rôle de la classe <Data>
//
//
//------------------------------------------------------------------------

class Data
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Ajouter ( std::string source, std::string cible );
    // Mode d'emploi :
    //
    // Contrat :
    // 

//-------------------------------------------- Constructeurs - destructeur
    Data ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Data ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void Afficher();
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Save();
    // Mode d'emploi :
    //
    // Contrat :
    
///----------------------------------------------------- Attributs protégés
    std::map<std::string, Noeud*> m_docInfo;
};

//-------------------------------- Autres définitions dépendantes de <Data>

#endif // DATA_H

