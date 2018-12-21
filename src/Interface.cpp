/*************************************************************************
Interface  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Realisation de la classe <Interface> (fichier Interface.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Interface.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques
// type Interface::Methode ( liste des parametres )
// Algorithme :
//
//{
//} //----- Fin de Methode


//-------------------------------------------- Constructeurs - destructeur

void Interface::Menu()
//Entrees :
//--numero de la commande a realiser
//1. Ajouter un trajet simple
//2. Ajouter un trajet compose
//3. Chercher un trajet
//4. Afficher tout le Interface
{
	char lecture[100];
	cout << "Bienvenue !" << endl;
	cout << "****************************" << endl;
	cout << "1. Ajouter un trajet simple" << endl;
	cout << "2. Ajouter un trajet compose" << endl;
	cout << "3. Chercher un Trajet Complexe" << endl;
	cout << "4. Chercher un Trajet Simple" << endl;
	cout << "5. Afficher tout le Interface" << endl;
	cout << "****************************" << endl;

	fscanf(stdin, "%99s", lecture);
	while (strcmp(lecture, "bye") != 0)
	{
		if (strcmp(lecture, "ajout") == 0)
		{
			AjouterTrajet();
		}

		if (strcmp(lecture, "recherche") == 0)
		{
			Rechercher();
		}
		if (strcmp(lecture, "affichage") == 0)
		{
			Afficher();
		}

		fscanf(stdin, "%99s", lecture);
	}
}// ---- fin de Menu

void Interface::Afficher() const
{
	m_collectionTrajet->Afficher();
}// ---- fin de Afficher


void Interface::AjouterTrajet(Trajet * trajet)
{
	m_collectionTrajet->AjouterTrajet(trajet);
}// ---- fin de AjouterTrajet

void Rechercher() const
{

}

Interface::~Interface()
{
	delete m_collectionTrajet;
#ifdef MAP
	cout << "Appel au destructeur de <Interface>" << endl;
#endif
}// ---- fin de ~Interface

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees


