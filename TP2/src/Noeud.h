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

//------------------------------------------------------------------ Types
typedef unsigned int uint;
//------------------------------------------------------------------------
// Rôle de la classe <Noeud>
// La classe Noeud a pour principal attribut une map m_mapSources qui
// contient une liste de site referer a un site cible ainsi que leur nombre
// de hit pour chacun.
// Son deuxieme attribut permet de compatabiliser le nombre total de hits
// effectues.
//------------------------------------------------------------------------

class Noeud
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------- Surcharge d'opérateurs
    
    friend std::ostream & operator << ( std::ostream & out, Noeud & noeud );
    // Mode d'emploi :
    // Operateur uniquement utilise pour le debug du programme
    // Fonction appelee par Data::operator << 

//----------------------------------------------------- Méthodes publiques

    void Ajouter ( const std::string source );
    // Mode d'emploi :
    // Fonction appelee par Data::Ajouter
    // Ajoute a m_mapSources une source supplementaire ou incremente le nombre
    // de hit provenant de ce site

    std::map <std::string, uint> GetMapSources ( );
    // Mode d'emploi :
    // Retourne la map des sources d'un site cible

    uint GetNbOcc() const;
    // Mode d'emploi :
    // Retourne le nombre de hit total lie a un site cible

//-------------------------------------------- Constructeurs - destructeur

    Noeud ( std::string source );

    virtual ~Noeud ( );

//------------------------------------------------------------------ PRIVE

protected:

//----------------------------------------------------- Attributs protégés

    // Map contenant les sites sources d'un meme site cible avec le nombre de hit
    // par site source
    std::map <std::string, uint> m_mapSources;

    // Nombre de hit total lie a un site cible
    uint m_nbOcc;
};

#endif // NOEUD_H

