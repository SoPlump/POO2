/*************************************************************************
Interface  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Interface> (fichier Interface.h) ----------------
#if ! defined ( Interface_H )
#define Interface_H

//--------------------------------------------------- Interfaces utilisees
#include "Catalogue.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <Interface>
//Le role de la classe Interface est de realiser une UI. 
//Elle propose trois types de services a l'utilisateur :
//- l'affichage du Interface courant : affiche tous les trajets enregistres dans le Interface
//- ajout de trajets : permet de hum... euh... a l'utilisateur de creer de nouveaux trajets simples ou composes
//- la recherche de trajets : l'utilisateur peut chercher la liste des parcours menant d'une ville de depart a une ville d'arrivee saisies en entree
//------------------------------------------------------------------------

class Interface
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Methodes publiques
	static Interface* GetInstance();

	void Menu();
	// Mode d'emploi :
	// Interface avec l'utilisateur , boucle jusqu'a l'ecriture de "bye"
	//--numero de la commande a realiser
	//1. Ajouter un trajet simple
	//2. Ajouter un trajet compose
	//3. Chercher un trajet
	//4. Afficher tout le Interface
	
	//-------------------------------------------- Constructeurs - destructeur

	virtual ~Interface();
	// Mode d'emploi : Fonction recursive appelant les destructeurs des objets qu'il contient
private:
	static Interface* m_instance;

	Interface();
	// Mode d'emploi :
	// Constructeur d'un Interface en donnant une taille initiale 'tailleDeBase' a la Collection 'm_collectionTrajet' du Interface

protected:
	//----------------------------------------------------- Methodes protegees

	void Afficher() const;
	// Mode d'emploi :
	// Affiche l'ensemble des trajets contenus dans le Interface
	// Un trajet composants un trajet compose sont precedes d'une tabulation pour les differencier des autres trajets du Interface
	// Contrat :
	// Il est suppose qu'un TrajetCompose n'est compose QUE de trajets simples

	void AjouterTrajet();
	// Mode d'emploi :
	// Permet d'ajouter un Trajet au Interface
	// -> dans le cas d'un TrajetCompose , une verification de validite sera appliquee a chaque trajets simples le composant
	// afin de s'assurer que le TrajetCompose soit valide dans son integralite (ville de depart d'un trajet = ville d'arrivee du trajet le precedent) 

	void Rechercher() const;

	void Charger();

	void Sauvegarder() const;

	//----------------------------------------------------- Attributs proteges
	Catalogue* m_catalogue;

};

//-------------------------------- Autres definitions dependantes de <Interface>

#endif // Interface_H
