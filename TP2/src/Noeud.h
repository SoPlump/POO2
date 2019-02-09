/*************************************************************************
                           Noeud  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Noeud> (fichier Noeud.h) ----------------
#if ! defined ( NOEUD_H )
#define NOEUD_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <map>
#include <ostream>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef unsigned int uint;
//------------------------------------------------------------------------
// Rôle de la classe <Noeud>
//
//
//------------------------------------------------------------------------

class Noeud
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    //uint GetNbOcc ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    friend std::ostream & operator << (std::ostream & out, Noeud & noeud)
    {
        map<string, uint>::iterator it;
        for ( it = noeud.m_mapSources.begin(); it != noeud.m_mapSources.end(); it++)
        {
            out << " | " << it->first << ", " << it->second << endl;
        }
        return out;
    }

    void Ajouter ( std::string source );

    std::map <std::string, uint> GetMapSources ( );
//-------------------------------------------- Constructeurs - destructeur
    Noeud ( std::string source );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Noeud ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::map <std::string, uint> m_mapSources;
    uint m_nbOcc;

};

//-------------------------------- Autres définitions dépendantes de <Noeud>

#endif // NOEUD_H

