/*************************************************************************
Trajet  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( Trajet_H )
#define Trajet_H

//--------------------------------------------------- Interfaces utilisees
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <Trajet>
// La classe trajet represente un trajet ayant une ville de depart et une 
// ville d'arrivee.
// Il instancie un objet de cette classe uniquement via le constructeur de
// ses specialisations, TrajetSimple et TrajetCompose.
//
//------------------------------------------------------------------------



class Trajet
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Methodes publiques

	virtual void Afficher() const;
	// Mode d'emploi :
	// Affiche sur la console une description du trajet, c'est a dire son depart
	// et son arrivee.
	// Contrat :
	// Il faut que cette methode soit redefinie dans ses specialisations

	virtual Trajet* Copier();
	// Mode d'emploi :
	// Permet d'appeler le constructeur par copie de ses specialisations
	// Contrat :
	// Il faut que cette methode soit redefinie dans ses specialisations

	char* GetDepart() const;
	// Mode d'emploi :
	// Retourne la ville de depart d'une instance de la classe trajet, en tant
	// que pointeur sur une chaine de caracteres. 

	char* GetArrivee() const;
	// Mode d'emploi :
	// Retourne la ville d'arrivee d'une instance de la classe trajet, en tant
	// que pointeur sur une chaine de caracteres. 

	virtual std::string ToCSV();

	//-------------------------------------------- Constructeurs - destructeur


	virtual ~Trajet();
	// Mode d'emploi (destructeur) :
	// Destructeur d'une instance de la classe Trajet.
	// Contrat :
	// Il doit bien supprimer tous les attributs de l'instance

	//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Constructeurs proteges

	Trajet(const char* depart, const char* arrivee);
	// Mode d'emploi (constructeur) :
	// Construction d'une instance de Trajet a partir des parametres depart et
	// arrivee.
	// Contrat :
	// Doit etre appele depuis une des specialisations de Trajet.

	Trajet(Trajet const&);
	// Mode d'emploi (constructeur par copie) :
	// Permet de creer un nouveau trajet en copiant l'instance de trajet qui lui
	// est passe par reference.
	// Contrat :
	// Doit etre appele depuis une des specialisations de Trajet.

	//----------------------------------------------------- Methodes protegees

	void SetDepart(const char *);
	// Mode d'emploi :
	// Fonction qui permet de changer l'attribut m_depart d'une instance de la
	// classe Trajet qui prend en parametre le nouveau depart.

	void SetArrivee(const char *);
	// Mode d'emploi :
	// Fonction qui permet de changer l'attribut m_arrivee de Trajet qui prend en
	// parametre le nouveau depart.

	//----------------------------------------------------- Attributs proteges
	char* m_depart;
	char* m_arrivee;

};

//-------------------------------- Autres definitions dependantes de <Trajet>

#endif // TRAJET_H