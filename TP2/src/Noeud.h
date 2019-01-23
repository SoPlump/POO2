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
    uint GetNbOcc ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Noeud ( );
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
    std::map < std::string source, uint nbOcc >;
    uint m_nbOcc;

};

//-------------------------------- Autres définitions dépendantes de <Noeud>

#endif // NOEUD_H

