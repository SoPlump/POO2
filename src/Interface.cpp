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
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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
//} //----- fin de Methode


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
	cout << "\n\n\n";
	cout << "Bienvenue !" << endl;
	cout << "****************************" << endl;
	cout << "ajouter : Ajouter un Trajet" << endl;
	cout << "chercher : Chercher un Trajet" << endl;
	cout << "afficher : Afficher tous les Trajets du Catalogue" << endl;
	cout << "charger : Charger un Catalogue pre existant" << endl;
	cout << "sauvegarder : Sauvegarder un Catalogue" << endl;
	cout << "****************************" << endl;
	cout << "\n\n\n"; 

	fscanf(stdin, "%99s", lecture);
	while (strcmp(lecture, "bye") != 0)
	{
		if (strcmp(lecture, "ajouter") == 0)
		{
			AjouterTrajet();
		}
		if (strcmp(lecture, "chercher") == 0)
		{
			Rechercher();
		}
		if (strcmp(lecture, "afficher") == 0)
		{
			Afficher();
		}
		if (strcmp(lecture, "charger") == 0)
		{
			Charger();
		}

		if (strcmp(lecture, "sauvegarder") == 0)
		{
			Sauvegarder();
		}


		cout << "\n\n\n";
		cout << "****************************" << endl;
		cout << "ajouter : Ajouter un Trajet" << endl;
		cout << "chercher : Chercher un Trajet" << endl;
		cout << "afficher : Afficher tous les Trajets du Catalogue" << endl;
		cout << "charger : Charger un Catalogue pre existant" << endl;
		cout << "sauvegarder : Sauvegarder un Catalogue" << endl;
		cout << "****************************" << endl;
		cout << "\n\n\n";
		fscanf(stdin, "%99s", lecture);
	}
}// ---- file de Menu

void Interface::Afficher() const
{
	m_catalogue->Afficher();
}// ---- fin de Afficher


void Interface::AjouterTrajet()
{
	char lecture[100];

	cout << "simple : Ajouter un Trajet Simple" << endl;
	cout << "compose : Ajouter un Trajet Compose" << endl;
	cout << "exit : Vous ne voulez pas ajouter de trajet" << endl;

	fscanf(stdin, "%99s", lecture);
	while ((strcmp(lecture, "simple") != 0)&&(strcmp(lecture, "compose") != 0)&&(strcmp(lecture, "exit") != 0))
	{
		fscanf(stdin, "%99s", lecture);
	}

	if (strcmp(lecture, "simple") == 0)
	{
		m_catalogue->AjouterTrajetSimple();
	}
	if (strcmp(lecture, "compose") == 0)
	{
		m_catalogue->AjouterTrajetCompose();
	}

}// ---- fin de AjouterTrajet

void Interface::Rechercher() const
{
	char lecture[100];
	string depart, arrivee;

	cout << "simple : Recherche Simple" << endl;
	cout << "complexe : Recherche Complexe" << endl;
	cout << "exit : Vous ne voulez pas ajouter de trajet" << endl;

	fscanf(stdin, "%99s", lecture);
	while ((strcmp(lecture, "simple") != 0)&&(strcmp(lecture, "complexe") != 0)&&(strcmp(lecture, "exit") != 0))
	{
		fscanf(stdin, "%99s", lecture);
	}

	cout << "Choisissez un Depart" << endl;
	cin >> depart;
	cout << "Choisissez une Arrivee" << endl;
	cin >> arrivee;

	if (strcmp(lecture, "simple") == 0)
	{
		m_catalogue->RechercheSimple(depart.c_str(), arrivee.c_str());
	}
	if (strcmp(lecture, "complexe") == 0)
	{
		m_catalogue->RechercheComplexe(depart.c_str(), arrivee.c_str());
	}
}// ---- fin de Rechercher

void Interface::Charger()
{    
	// File pointer 
	fstream file; 

	string path = "saves/";

	//TODO: Verifier les actions de l'utilisateur et boucler si il faut
	string fileName;
	cout << "Quel fichier voulez vous charger ?" << endl;
	cin >> fileName;

    // Open an existing file 
	file.open((path + fileName + ".csv").c_str(), ios::in);
	while(!file.is_open())
	{
		cout << "Impossible d'ouvrir ce fichier." << endl;
		string answer;
		cout << "Voulez vous reellement charger un fichier ? y/n" << endl;
		cin >> answer;

		if(answer == "n") return;


		string fileName;
		cout << "Quel fichier voulez vous charger ? Numero attenu" << endl;
		cin >> fileName;

    // Open an existing file 
		file.open((path + fileName + ".csv").c_str(), ios::in);
	}

	/* Lecture du choix de chargement de l'utilisateur*/
	//TODO: pas beau (faire des fonctions)
	char lecture[100];
	string depart, arrivee;

	cout << "none : Chargement sans criteres de selection" << endl;
	cout << "type : Chargement selon le type de trajets" << endl;
	cout << "ville : Chargement selon la ville de depart et/ou la ville d'arrivee" << endl;
	cout << "selection : Chargement selon un intervalle de selection" << endl;
	cout << "exit : Vous ne voulez pas charger de fichier" << endl;

	fscanf(stdin, "%99s", lecture);
	while ((strcmp(lecture, "none") != 0)&&(strcmp(lecture, "type") != 0)&&(strcmp(lecture, "ville") != 0)&&(strcmp(lecture, "selection") != 0)&&(strcmp(lecture, "exit") != 0))
	{
		fscanf(stdin, "%99s", lecture);
	}

	if (strcmp(lecture, "none") == 0)
	{	
		m_catalogue->Charger(file);
	}
	if (strcmp(lecture, "type") == 0)
	{
		bool isSimple = true;
		cout << "simple : chargement des trajets simples" << endl;
		cout << "compose : chargement des trajets composés" << endl;
		fscanf(stdin, "%99s", lecture);
		while ((strcmp(lecture, "simple") != 0)&&(strcmp(lecture, "compose") != 0))
		{
			fscanf(stdin, "%99s", lecture);
		}
		if (strcmp(lecture, "compose") == 0)
		{
			isSimple = false;
		}
		m_catalogue->Charger(file,isSimple);
	}
	if (strcmp(lecture, "ville") == 0)
	{
		cout << "both : Critere sur les deux villes" << endl;
		cout << "depart : Critere sur la ville de depart" << endl;
		cout << "arrivee : Critere sur la ville d'arrivee" << endl;

		fscanf(stdin, "%99s", lecture);
		while ((strcmp(lecture, "both") != 0)&&(strcmp(lecture, "depart") != 0)&&(strcmp(lecture, "arrivee") != 0))
		{
			fscanf(stdin, "%99s", lecture);
		}

		if (strcmp(lecture, "both") == 0)
		{
			cout << "Choisissez un Depart" << endl;
			cin >> depart;
			cout << "Choisissez une Arrivee" << endl;
			cin >> arrivee;

			m_catalogue->Charger(file, depart, arrivee);
		}
		if (strcmp(lecture, "depart") == 0)
		{
			cout << "Choisissez un Depart" << endl;
			cin >> depart;

			m_catalogue->Charger(file, true, depart);
		}
		if (strcmp(lecture, "arrivee") == 0)
		{
			cout << "Choisissez une Arrivee" << endl;
			cin >> arrivee;

			m_catalogue->Charger(file, false, arrivee);
		}
		//m_catalogue->Charger(file);
	}
	if (strcmp(lecture, "selection") == 0)
	{
		//m_catalogue->Charger(file);
	}

	m_catalogue->Charger(file);
}// ---- fin de Charger

void Interface::Sauvegarder()
{
    // file pointer 
	fstream file; 

	string path = "saves/";

	string fileName;
	cout << "Dans quel fichier voulez vous sauvegarder ?" << endl;
	cin >> fileName;

    // opens an existing csv file or creates a new file. 
	file.open((path + fileName + ".csv").c_str(), ios::out | ios::app);

	m_catalogue->Sauvegarder(file);
}// ---- fin de Sauvegarder

Interface::Interface()
{
	m_catalogue = new Catalogue();
#ifdef MAP
	cout << "Appel au constructeur de <Interface>" << endl;
#endif
}

Interface::~Interface()
{
#ifdef MAP
	cout << "Appel au destructeur de <Interface>" << endl;
#endif
}// ---- file de ~Interface

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees


