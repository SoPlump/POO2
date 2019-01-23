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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <FileManager>
//
//
//------------------------------------------------------------------------

class FileManager : public Ancetre
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
    FileManager & operator = ( const FileManager & unFileManager );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    FileManager ( const FileManager & unFileManager );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    FileManager ( );
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

