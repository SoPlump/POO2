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

vector <string> FileManager::Decouper (stringstream& s)
// Algorithme :
//
{
	vector <string> elts;
	string word;

	while (std::getline(s, word,' ')) 
	{ 
		elts.push_back(word); 
	}

	// Retire la base de l'URL quand elle est locale
	string localURL = "http://intranet-if.insa-lyon.fr";

	if (!elts.empty())
	{
		size_t pos = elts[10].find(localURL);
		if (pos != string::npos) //Adresse locale
		{
			elts[10] = elts[10].substr(localURL.size() + 1, elts[10].size() - (localURL.size() + 2));
		}
		else // Adresse non locale -> On retire quand meme les guillemets
		{
			elts[10] = elts[10].substr(1, elts[10].size() - 2);
		}
	}

	return elts;
}//----- Fin de Méthode



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

