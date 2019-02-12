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

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

vector <string> FileManager::Decouper (stringstream& s)
// Algorithme :
// Recupere une ligne du log et la retourne decoupee en plusieurs parties
{
	vector <string> elts;
	string word;

	// Recupere chaque mot
	while (std::getline(s, word,' ')) 
	{ 
		elts.push_back(word); 
	}

	// Verifie que la ligne n'est pas vide
	if (!elts.empty())
	{
		// Retire la base de l'URL quand elle est locale
		string localURL = "http://intranet-if.insa-lyon.fr";
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
} //----- Fin de Decouper

//-------------------------------------------- Constructeurs - destructeur
FileManager::FileManager ( string fileName ) : ifstream ( fileName.c_str() )
{
#ifdef MAP
	cout << "Appel au destructeur de <FileManager>" << endl;
#endif
} //----- Fin de ~FileManager

FileManager::~FileManager ( )
{
#ifdef MAP
	cout << "Appel au destructeur de <FileManager>" << endl;
#endif
} //----- Fin de ~FileManager
