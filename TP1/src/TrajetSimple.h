/*************************************************************************
TrajetSimple  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TrajetSimple_H )
#define TrajetSimple_H

//--------------------------------------------------- Interfaces utilisees
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <TrajetSimple>
// La classe TrajetSimple est une specification de la classe Trajet.
// Elle a comme attribut, en plus de ceux de Trajet, m_moyenTransport qui
// precise quel moyen de transport est utilise pour un trajet.
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Methodes publiques

	void Afficher() const;
	// Mode d'emploi :
	// Affiche sur la console une description du trajet simple. Pour cela, cette
	// methode appelle aussi la methode Afficher sa generalisation.

	TrajetSimple* Copier();
	// Mode d'emploi :
	// Methode appelee par la generalisation de cette classe (ie Trajet). Elle
	// appelle le constructeur par copie de la classe TrajetSimple, en lui donnant
	// en parametre l'objet appelant cette methode.
	
	char* GetMoyenTransport() const;
	// Mode d'emploi :
	// Retourne le moyen de transport d'une instance de la classe trajet simple, 
	// en tant que pointeur sur une chaîne de caracteres.

	//-------------------------------------------- Constructeurs - destructeur

	TrajetSimple(const char* depart, const char* arrivee, const char* moyenTransport);
	// Mode d'emploi (constructeur):
	// Construit une nouvelle instance de TrajetSimple a partir d'un depart, d'une
	// arrivee et d'un moyen de transport.

	TrajetSimple(TrajetSimple const& model);
	// Mode d'emploi (constructeur par copie) :
	// Construit une nouvelle instance de la classe TrajetSimple en copiant l'instance
	// de TrajetSimple qui lui est passe par reference.

	std::string ToCSV();

	virtual ~TrajetSimple();
	// Mode d'emploi (destructeur) :
	// Destructeur d'une instance de la classe TrajetSimple.
	// Contrat :
	// Il doit bien supprimer tous les attributs de l'instance


	//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Methodes protegees

	//----------------------------------------------------- Attributs proteges
	char* m_moyenTransport;
};

//-------------------------------- Autres definitions dependantes de <Xxx>

#endif // TRAJETSIMPLE_H
