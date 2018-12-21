/*************************************************************************
Collection  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Collection> (fichier Collection.h) ----------------
#if ! defined ( Collection_H )
#define Collection_H

//--------------------------------------------------- Interfaces utilisees
#include "Trajet.h"
#include <cstring>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef unsigned int uint;

//------------------------------------------------------------------------
// Role de la classe <Collection>
// Structure de donnees permettant de stocker des Trajets
// L'ajout dynamique est possible et est gere
// Propose plusieurs services sur les Trajets
//------------------------------------------------------------------------

class Collection
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Methodes publiques

	void Afficher(const char prefixe = '\0') const;
	// Mode d'emploi :
	// Parcours tous les Trajets de la collection et appelle leur fonction Afficher()
	// -> prefixe peut servir a ajouter un character avant l'affichage de chaque Trajet , comme par exemple un \t

	void AjouterTrajet(Trajet*);
	// Mode d'emploi :
	// Ajoute un Trajet* a la Collection courante
	// Si la capacite maximale de la Collection est atteinte alors une nouvelle Collection de taille maximale egale au double
	// de la taille maximale de la premiere collection est creee. Dedans on copie la premiere Collection. Cette nouvelle Collection remplace la premiere.

	void DepilerTrajet();
	// Mode d'emploi :
	// Supprime le dernier trajet ajoute dans la Collection
	// Decremente le nombre de Trajets presents dans la Collection ( m_nbTrajet )
	// Contrat :
	// On suppose qu'on ne depile jamais une Collection vide (sans Trajets)

	bool isCityIn(const char * cityName) const;
	// Mode d'emploi :
	// Retourne True si la ville cityName est presente en tant que ville d'arrivee ou de depart d'un Trajet de la Collection
	// Sinon retourne False

	Collection* GetTrajetsFrom(const char * villeDepart) const;
	// Mode d'emploi :
	// Renvoie la liste des Trajets presents dans la Collection dont la ville de depart correspond a villeDepart


	Collection* RechercheSimple(const char * villeDepart, const char * villeArrivee) const;
	// Mode d'emploi :
	// Parcours la liste des Trajets de Collection, renvoie la liste des Trajets dont
	// -> la ville de depart correspond a villeDepart
	// -> la ville d'arrivee correspond a villeArrivee
	// La combinaison de Trajets n'est PAS permise

	uint GetNbTrajet() const;
	// Mode d'emploi :
	// Retourne la valeur de m_nbTrajet
	
	Trajet** GetListeTrajet();
	// Mode d'emploi :
	// Retourne m_listeTrajet

	//-------------------------------------------- Constructeurs - destructeur

	Collection(uint taille = 10);
	//Cree une Collection de taille initiale 'taille'

	Collection(Collection const& model);
	//Constructeur par copie

	virtual ~Collection();

	//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Methodes protegees

	//----------------------------------------------------- Attributs proteges
	Trajet** m_listeTrajet; // Liste de pointeurs de Trajets
	uint m_nbTrajet; // Nombre de Trajets dans la Collection
	uint m_cardMax; // Nombre de Trajets maximal pouvant etre dans la Collection

};

#endif // Collection_H
