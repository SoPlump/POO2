/*************************************************************************
                           FileManager  -  description
                             -------------------
    début                : 23/01/2019
    copyright            : (C) 3IF par ABDEL RAHMAN Ahmed - RAUDRANT Sophie
    e-mail               : 
*************************************************************************/

//---------- Réalisation de la classe <FileManager> (fichier FileManager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "FileManager.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type FileManager::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

vector <string> FileManager::Decoupage (stringstream s)
// Algorithme :
//
{
	vector <string> elts;
	string word;

	while (std::getline(s, word,' ')) 
	{ 
		elts.push_back(word); 
	}

	return elts;
} //----- Fin de Méthode



//-------------------------------------------- Constructeurs - destructeur
FileManager::~FileManager ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <FileManager>" << endl;
#endif
} //----- Fin de ~FileManager


//------------------------------------------------------------------ PRIVE



//----------------------------------------------------- Méthodes protégées

