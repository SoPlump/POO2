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

Interface* Interface::m_instance = NULL;

Interface* Interface::GetInstance()
{
	if (m_instance == 0)
		m_instance = new Interface();
	return m_instance;
}

void Interface::Menu()
//Entrees :
//--numero de la commande a realiser
//1. Ajouter un trajet simple
//2. Ajouter un trajet compose
//3. Chercher un trajet
//4. Afficher tout le Interface
{
	string lecture;
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

	getline(cin, lecture);
	while (lecture != "bye")
	{
		if (lecture == "ajouter")
		{
			AjouterTrajet();
		}
		if (lecture == "chercher")
		{
			Rechercher();
		}
		if (lecture == "afficher")
		{
			Afficher();
		}
		if (lecture == "charger")
		{
			Charger();
		}

		if (lecture == "sauvegarder")
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
		getline(cin, lecture);
	}
}// ---- file de Menu

void Interface::Afficher() const
{
	m_catalogue->Afficher();
}// ---- fin de Afficher


void Interface::AjouterTrajet()
{
	string lecture;

	cout << "simple : Ajouter un Trajet Simple" << endl;
	cout << "compose : Ajouter un Trajet Compose" << endl;
	cout << "exit : Vous ne voulez pas ajouter de trajet" << endl;

	getline(cin,lecture);
	while ((lecture != "simple")&&(lecture != "compose")&&(lecture != "exit"))
	{
		getline(cin, lecture);
	}

	if (lecture == "simple")
	{
		m_catalogue->AjouterTrajetSimple();
	}
	if (lecture == "compose")
	{
		m_catalogue->AjouterTrajetCompose();
	}

}// ---- fin de AjouterTrajet

void Interface::Rechercher() const
{
	string lecture, depart, arrivee;

	cout << "simple : Recherche Simple" << endl;
	cout << "complexe : Recherche Complexe" << endl;
	cout << "exit : Vous ne voulez pas ajouter de trajet" << endl;

	getline(cin, lecture);
	while ((lecture != "simple")&&(lecture != "complexe")&&(lecture != "exit"))
	{
		getline(cin, lecture);
	}

	cout << "Choisissez un Depart" << endl;
	getline(cin,depart);
	cout << "Choisissez une Arrivee" << endl;
	getline(cin,arrivee);

	if (lecture == "simple")
	{
		m_catalogue->RechercheSimple(depart.c_str(), arrivee.c_str());
	}
	if (lecture == "complexe")
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
	getline(cin,fileName);

    // Open an existing file 
	file.open((path + fileName + ".csv").c_str(), ios::in);
	while(!file.is_open())
	{
		cout << "Impossible d'ouvrir ce fichier." << endl;
		string answer;
		cout << "Voulez vous reellement charger un fichier ? y/n" << endl;
		getline(cin,answer);

		if(answer == "n") return;


		string fileName;
		cout << "Quel fichier voulez vous charger ?" << endl;
		getline(cin,fileName);

    // Open an existing file 
		file.open((path + fileName + ".csv").c_str(), ios::in);
	}

	/* Lecture du choix de chargement de l'utilisateur*/
	//TODO: pas beau (faire des fonctions)
	string lecture, depart, arrivee;
	int begin, end;

	cout << "none : Chargement sans criteres de selection" << endl;
	cout << "type : Chargement selon le type de trajets" << endl;
	cout << "ville : Chargement selon la ville de depart et/ou la ville d'arrivee" << endl;
	cout << "selection : Chargement selon un intervalle de selection" << endl;
	cout << "exit : Vous ne voulez pas charger de fichier" << endl;

		getline(cin, lecture);
	while ((lecture != "none")&&(lecture !=, "type")&&(lecture != "ville")&&(lecture != "selection")&&(lecture != "exit"))
	{
		getline(cin, lecture);
	}

	if (lecture == "none")
	{	
		m_catalogue->Charger(file);
	}
	if (lecture == "type")
	{
		bool isSimple = true;
		cout << "\n\nSauvegarde selon le type de trajet :" << endl;
		cout << "simple : chargement des trajets simples" << endl;
		cout << "compose : chargement des trajets composés" << endl;
		getline(cin, lecture);
		while ((lecture != "simple")&&(lecture != "compose"))
		{
		getline(cin, lecture);
		}
		if ((lecture == "compose"))
		{
			isSimple = false;
		}
		m_catalogue->Charger(file,isSimple);
	}
	if (lecture == "ville")
	{
		cout << "both : Critere sur les deux villes" << endl;
		cout << "depart : Critere sur la ville de depart" << endl;
		cout << "arrivee : Critere sur la ville d'arrivee" << endl;

		getline(cin, lecture);
		while ((lecture != "both")&&(lecture != "depart")&&(lecture != "arrivee"))
		{
			getline(cin, lecture);
		}

		if (lecture == "both")
		{
			cout << "Choisissez un Depart" << endl;
			getline(cin,depart);
			cout << "Choisissez une Arrivee" << endl;
			getline(cin,arrivee);

			m_catalogue->Charger(file, depart, arrivee);
		}
		if (lecture == "depart")
		{
			cout << "Choisissez un Depart" << endl;
			getline(cin,depart);

			m_catalogue->Charger(file, true, depart);
		}
		if (lecture == "arrivee")
		{
			cout << "Choisissez une Arrivee" << endl;
			getline(cin,arrivee);

			m_catalogue->Charger(file, false, arrivee);
		}
	}
	if (lecture == "selection")
	{
		string temp;
		bool valide;
		do
		{
			cout << "Soit l'intervalle [n, m]. Choisissez l'indice n (supérieur ou égal à 1)" << endl;
			getline(cin,temp);
			begin=stoi(temp);
			cout << "Choisissez l'indice m" << endl;
			getline(cin,temp);
			end=stoi(temp);
			valide = m_catalogue->Charger(file, begin, end);
		} while (!valide);
	}
}// ---- fin de Charger

void Interface::Sauvegarder() const
{
    // file pointer 
	fstream file; 

	string path = "saves/";

	string fileName;
	cout << "Dans quel fichier voulez vous sauvegarder ?" << endl;
	getline(cin,fileName);

    // opens an existing csv file or creates a new file. 
	remove((path + fileName + ".csv").c_str());
	file.open((path + fileName + ".csv").c_str(), ios::out | ios::app);

	/* Lecture du choix de chargement de l'utilisateur*/
	//TODO: pas beau (faire des fonctions)
	string lecture, depart, arrivee, temp;
	int begin, end;

	cout << "none : Sauvegarde sans criteres de selection" << endl;
	cout << "type : Sauvegarde selon le type de trajets" << endl;
	cout << "ville : Sauvegarde selon la ville de depart et/ou la ville d'arrivee" << endl;
	cout << "selection : Sauvegarde selon un intervalle de selection" << endl;
	cout << "exit : Vous ne voulez pas sauvegarder de fichier" << endl;

		getline(cin, lecture);
	while ((lecture != "none")&&(lecture != "type")&&(lecture != "ville")&&(lecture != "selection")&&(lecture != "exit"))
	{
		getline(cin, lecture);
	}

	if (lecture == "none")
	{	
		m_catalogue->Sauvegarder(file);
	}
	if (lecture == "type")
	{
		bool isSimple = true;
		cout << endl;
		cout << endl;
		cout << "Sauvegarde selon le type de trajets :" << endl;
		cout << "simple : sauvegarde des trajets simples" << endl;
		cout << "compose : sauvegarde des trajets composés" << endl;

		getline(cin, lecture);
		while ((lecture != "simple")&&(lecture != "simple"))
		{
		getline(cin, lecture);
		}
		if (slecture == "compose")
		{
			isSimple = false;
		}
		m_catalogue->Sauvegarder(file,isSimple);
	}
	if (lecture == "ville")
	{
		cout << "both : Critere sur les deux villes" << endl;
		cout << "depart : Critere sur la ville de depart" << endl;
		cout << "arrivee : Critere sur la ville d'arrivee" << endl;

		getline(cin, lecture);
		while ((lecture != "both")&&(lecture != "depart")&&(lecture != "arrivee"))
		{
		getline(cin, lecture);
		}

		if (lecture == "both")
		{
			cout << "Choisissez un Depart" << endl;
			getline(cin,depart);
			cout << "Choisissez une Arrivee" << endl;
			getline(cin,arrivee);

			m_catalogue->Sauvegarder(file, depart, arrivee);
		}
		if (lecture == "depart")
		{
			cout << "Choisissez un Depart" << endl;
			getline(cin,depart);

			m_catalogue->Sauvegarder(file, true, depart);
		}
		if (lecture == "arrivee")
		{
			cout << "Choisissez une Arrivee" << endl;
			getline(cin,arrivee);

			m_catalogue->Sauvegarder(file, false, arrivee);
		}
	}
	if (lecture == "selection")
	{
		bool valide;
		do
		{

			cout << "Soit l'intervalle [n, m]. Choisissez l'indice n (supérieur ou égal à 1)" << endl;
			getline(cin,temp);
			begin=stoi(temp);
			cout << "Choisissez l'indice m" << endl;
			getline(cin,temp);
			end=stoi(temp);
			valide = m_catalogue->Sauvegarder(file, begin, end);
		} while (!valide);
	}
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
	delete m_catalogue;
#ifdef MAP
	cout << "Appel au destructeur de <Interface>" << endl;
#endif
}// ---- file de ~Interface

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees


