/*************************************************************************
TrajetCompose  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H

//--------------------------------------------------- Interfaces utilisees
#include "trajet.h"
#include "collection.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef unsigned int uint;

//------------------------------------------------------------------------
// Role de la classe <TrajetCompose>
// La classe TrajetCompose est une specification de la classe Trajet.
// Elle a comme attribut, en plus de ceux de Trajet, une instance de la
// classe collection.
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Methodes publiques

	void Afficher() const;
	// Mode d'emploi :
	// Affiche sur la console une description du trajet compose. Pour cela, cette
	// methode appelle aussi la methode Afficher sa generalisation.

	bool AjouterTrajet(Trajet *);
	// Mode d'emploi :
	// Methode qui ajoute un trajet simple dans la collection de l'instance du
	// trajet compose. 	

	TrajetCompose* Copier();
	// Mode d'emploi :
	// Methode appelee par la generalisation de cette classe (ie Trajet). Elle
	// appelle le constructeur par copie de la classe TrajetCompose, en lui donnant
	// en parametre l'objet appelant cette methode.

	//-------------------------------------------- Constructeurs - destructeur

	TrajetCompose(uint taille = 10);
	// Mode d'emploi (constructeur) :
	// Construit une nouvelle instance de TrajetCompose a partir d'une taille,
	// mise par defaut a 10 si elle n'est pas renseignee.

	TrajetCompose(TrajetCompose const&);
	// Mode d'emploi (constructeur par copie) :
	// Construit une nouvelle instance de la classe TrajetCompose en copiant 
	// l'instance de TrajetCompose qui lui est passe par reference.

	std::string ToCSV();

	virtual ~TrajetCompose();
	// Mode d'emploi (destructeur) :
	// Destructeur d'une instance de la classe TrajetCompose.
	// Contrat :
	// Il doit bien supprimer tous les attributs de l'instance

	//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Methodes protegees

	//----------------------------------------------------- Attributs proteges
	Collection *m_collectionTrajet;
};

//-------------------------------- Autres definitions dependantes de <TrajetCompose>

#endif // TRAJETCOMPOSE_H
