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
#include "ArgManager.h"
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

    friend std::ostream & operator << (std::ostream & out, Data & data)
    {
        map<std::string, Noeud*>::iterator it;
        for ( it = data.m_docInfo.begin(); it != data.m_docInfo.end(); it++)
        {
            out << it->first << ", " << it->second->GetNbOcc() << endl;
            out << *(it->second) << endl;
        }
        out << endl;

        map<std::string, uint>::iterator itN;
        for ( itN = data.m_nodes.begin(); itN != data.m_nodes.end(); itN++)
        {
            out << itN->first << ", ";
            out << itN->second << endl;
        }

        return out;
    }

    void Ajouter ( std::string source, std::string cible );
    // Mode d'emploi :
    //
    // Contrat :
    // 
    
    void AddNode ( std::string source, std::string cible );

    bool GenerateGraph ( const std::string & fileName ) const;

    bool Traiter ();

    void AfficherTopTen ( );

//-------------------------------------------- Constructeurs - destructeur
    Data (Options opt);
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
    //w

    void Save();
    // Mode d'emploi :
    //
    // Contrat :
    
///----------------------------------------------------- Attributs protégés
    Options choix;
    std::map<std::string, Noeud*> m_docInfo;
    std::map<std::string, uint> m_nodes;
};

//-------------------------------- Autres définitions dépendantes de <Data>

#endif // DATA_H

