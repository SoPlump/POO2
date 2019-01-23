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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ArgManager>
//
//
//------------------------------------------------------------------------

class ArgManager : public Ancetre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    ArgManager & operator = ( const ArgManager & unArgManager );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    ArgManager ( const ArgManager & unArgManager );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    ArgManager ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~ArgManager ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <ArgManager>

#endif // ArgManager_H

