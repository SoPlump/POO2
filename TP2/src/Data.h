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

//------------------------------------------------------------------ Types
typedef unsigned int uint;

//------------------------------------------------------------------------
// Rôle de la classe <Data>
// La classe Data permet de stocker les donnees relatives a un fichier log
// Il stockera chaque site cible atteint en tant que cle de son attribut
// m_docInfo. La valeur associe est un Noeud qui regroupe les informations
// quant aux sites sources.
// Ca sera egalement a partir de la classe Data qu'un fichier dot peut etre
// genere, grace a ses attributs m_docInfo et m_nodes. Cette derniere map
// associe a chaque site traite un index.
//------------------------------------------------------------------------

class Data
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------- Surcharge d'opérateurs

    friend std::ostream & operator << ( std::ostream & out, Data & data );
    // Mode d'emploi :
    // Operateur uniquement utilise pour le debug du programme

//----------------------------------------------------- Méthodes publiques

    bool Traiter ( );
    // Mode d'emploi :
    // Fonction appelee par le main. Lance la decoupe des lignes d'un .log
    // Puis selon les parametres passes a l'execution, appelle les fonctions :
    // - Ajouter
    // - GenerateGraph
    // La fonction appelera toujours la fonction AfficherTopTen
    // Contrat :
    // Les parametres passes a l'execution doivent etre traite avant, ce qui
    // est gere dans l'ArgManager

//-------------------------------------------- Constructeurs - destructeur

    Data ( Options opt );

    virtual ~Data ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

    void Ajouter ( const std::string source, const std::string cible );
    // Mode d'emploi :
    // Fonction appelee par la fonction Traiter a chaque ligne 
    // correspondante aux options d'execution.
    // Ajoute les informations necessaires a la m_docInfo

    void AddNode ( const std::string source, const std::string cible );
    // Mode d'emploi :
    // Fonction appelee par la fonction Ajouter. Ajoute a m_nodes les
    // sites qui n'ont jamais ete ajoute auparavant.

    bool GenerateGraph ( const std::string & fileName ) const;
    // Mode d'emploi :
    // Fonction appelee par Traiter. Genere un .dot correspondant
    // au .log et aux parametres d'execution
    // Contrat :
    // Le nom de fichier ne doit pas exister. Condition verifiee par
    // l'ArgManager donc ok

    void AfficherTopTen ( );
    // Mode d'emploi :
    // Affiche sous forme textuelle la liste des 10 documents les plus consultes
    // par ordre decroissant de popularite. 
    
///----------------------------------------------------- Attributs protégés

    // Contient toutes les options choisies ou non par l'utilisateur
    Options choix;

    // Map contenant toutes les infos importantes (cible, source, occurence) du .log passe en parametre
    std::map<std::string, Noeud*> m_docInfo;

    // Map associant chaque site avec un index different 
    std::map<std::string, uint> m_nodes;
};

#endif // DATA_H