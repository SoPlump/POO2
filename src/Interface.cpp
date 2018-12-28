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
	std::cout << "Bienvenue !" << endl;
	std::cout << "****************************" << endl;
	std::cout << "1. Ajouter un trajet simple" << endl;
	std::cout << "2. Ajouter un trajet compose" << endl;
	std::cout << "3. Chercher un Trajet Complexe" << endl;
	std::cout << "4. Chercher un Trajet Simple" << endl;
	std::cout << "5. Afficher tout le Interface" << endl;
	std::cout << "****************************" << endl;

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
}// ---- file de Menu

void Interface::Afficher() const
{

}// ---- fin de Afficher


void Interface::AjouterTrajet()
{
}// ---- fin de AjouterTrajet

void Interface::Rechercher() const
{

}// ---- fin de Rechercher

void Interface::Charger()
{    
	// File pointer 
    fstream file; 
  
    // Open an existing file 
    file.open("test.csv", ios::in); 
  
    // Get the roll number 
    // of which the data is required 
    int rollnum, roll2, count = 0; 
    cout << "Enter the roll number "
         << "of the student to display details: "; 
    cin >> rollnum; 
  
    // Read the Data from the file 
    // as String Vector 
    vector<string> row; 
    string line, word, temp; 
  
    while (file >> temp) 
    { 
  
        row.clear(); 
  
        // read an entire row and 
        // store it in a string variable 'line' 
        getline(file, line); 
  
        // used for breaking words 
        stringstream s(line); 
  
        // read every column data of a row and 
        // store it in a string variable, 'word' 
        while (getline(s, word, ',')) 
        { 
  
            // add all the column data 
            // of a row to a vector 
            row.push_back(word); 
        } 
  
        // convert string to integer for comparison 
        roll2 = stoi(row[0]); 
  		

  		// TODO: Faire en sorte d'Afficher toutes les lignes
        // Compare the roll number 
        if (roll2 == rollnum) 
        { 
  
            // Print the found data 
            count = 1; 
            cout << "Details of Roll " << row[0] << " : \n"; 
            cout << "Name: " << row[1] << "\n"; 
            cout << "Maths: " << row[2] << "\n"; 
            cout << "Physics: " << row[3] << "\n"; 
            cout << "Chemistry: " << row[4] << "\n"; 
            cout << "Biology: " << row[5] << "\n"; 
            break; 
        } 
    } 
    if (count == 0) 
        cout << "Record not found\n"; 

}// ---- file de Charger

void Interface::Sauvegarder()
{

}// ---- file de Sauvegarder

Interface::Interface()
{

}

Interface::~Interface()
{
#ifdef MAP
	cout << "Appel au destructeur de <Interface>" << endl;
#endif
}// ---- file de ~Interface

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees


