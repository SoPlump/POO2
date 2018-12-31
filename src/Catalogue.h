/*************************************************************************
Catalogue  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( Catalogue_H )
#define Catalogue_H

#include <iostream>
#include <fstream>
//--------------------------------------------------- Interfaces utilisees
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Collection.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <Catalogue>
//Le role de la classe catalogue est de realiser une UI. 
//Elle propose trois types de services a l'utilisateur :
//- l'affichage du catalogue courant : affiche tous les trajets enregistres dans le catalogue
//- ajout de trajets : permet de hum... euh... a l'utilisateur de creer de nouveaux trajets simples ou composes
//- la recherche de trajets : l'utilisateur peut chercher la liste des parcours menant d'une ville de depart a une ville d'arrivee saisies en entree
//------------------------------------------------------------------------

class Catalogue
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Methodes publiques
	
	void Afficher() const;
	// Mode d'emploi :
	// Affiche l'ensemble des trajets contenus dans le catalogue
	// Un trajet composants un trajet compose sont precedes d'une tabulation pour les differencier des autres trajets du catalogue
	// Contrat :
	// Il est suppose qu'un TrajetCompose n'est compose QUE de trajets simples
	
	//-------------------------------------------- Constructeurs - destructeur

	Catalogue(uint tailleDeBase = 10);
	// Mode d'emploi :
	// Constructeur d'un catalogue en donnant une taille initiale 'tailleDeBase' a la Collection 'm_collectionTrajet' du Catalogue


	virtual ~Catalogue();
	// Mode d'emploi : Fonction recursive appelant les destructeurs des objets qu'il contient

	void Charger(std::fstream& file);
	//void Sauvegarder(std::fstream& file);

	void AjouterTrajetSimple();
	void AjouterTrajetCompose();
	// Mode d'emploi :
	// Ajoute un Trajet au Catalogue en precisant via selection de quel type de trajet il s'agit
	// Les verifications de coherence des trajets seront effectuees dans les classes des Trajets
	// -> selection = 1 : TrajetSimple
	// -> selection = 2 : TrajetCompose

	void RechercheSimple(const char* depart, const char* arrivee) const;
	// Mode d'emploi :une ville de depart et d'arrivee sont donnees en entree
	// la fonction affiche la liste des trajets (simples ou composes) qui vont de la ville de depart a celle d'arrivee
	// la composition de trajets n'est PAS prise en compte dans cette fonction
	// Cette fonction gere l'affichage des resultats

	void RechercheComplexe(const char*, const char*) const;
	// Mode d'emploi :
	//une ville de depart et d'arrivee sont donnees en entree
	// la fonction affiche la liste des trajets (simples ou composes) qui vont de la ville de depart a celle d'arrivee
	// la composition de trajets EST prise en compte dans cette fonction
	// Contrat :
	// -> les cycles ne sont pas consideres comme de protentielles solutions
	// -> un trajet (simple ou compose) ne peut etre emprunte qu'une seule fois dans une meme solution

	//------------------------------------------------------------------ PRIVE

	//----------------------------------------------------- Methodes privees
private:
	void Chemin(const char * depart, const char * arrivee, Collection & wayToHere) const;
	// Mode d'emploi : Fonction recursive
	// Fonction appelee lors de la RechercheComplexe
	// Retourne toutes les combinaisons des trajets du catalogue permettant de relier la ville de depart a celle d'arrivee
	// wayToHere permet d'enregistrer le chemin parcouru par l'algorithme , pour le premier appel , lui donner une collection vide

protected:
	//----------------------------------------------------- Methodes protegees


	void AjouterTrajet(Trajet*);
	// Mode d'emploi :
	// Permet d'ajouter un Trajet au Catalogue
	// -> dans le cas d'un TrajetCompose , une verification de validite sera appliquee a chaque trajets simples le composant
	// afin de s'assurer que le TrajetCompose soit valide dans son integralite (ville de depart d'un trajet = ville d'arrivee du trajet le precedent) 




	TrajetSimple* ScanTrajetSimple() const;
	// Mode d'emploi :
	// Affiche les phrases d'interactions avec l'utilisateur
	// Cree et renseigne un nouveau TrajetSimple et le retourne en sortie

	TrajetCompose* ScanTrajetCompose() const;
	// Mode d'emploi :
	// Affiche les phrases d'interactions avec l'utilisateur
	// Cree et renseigne un nouveau TrajetCompose et le retourne en sortie

	void ChercherTrajet(int selection) const;
	// Mode d'emploi :
	// Demande a l'utilisateur de rentrer le nom de la ville de depart et d'arrivee de l'itineraire qu'il recherche
	// Appelle ensuite une fonction de recherche

	char* ScanString(const char*) const;
	// Mode d'emploi :
	//Demande a l'utilisateur le nom des villes et les moyens de transports des trajets qu'il insere dans le catalogue

	//----------------------------------------------------- Attributs proteges
	Collection* m_collectionTrajet;

};

//-------------------------------- Autres definitions dependantes de <Catalogue>

#endif // Catalogue_H
