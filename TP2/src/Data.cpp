/*************************************************************************
                           Data  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Data> (fichier Data.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Data.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Data::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void Data::Ajouter ( string source, string cible )
{
	map<string, Noeud*>::iterator it = m_docInfo.find(cible);
	if ( it == m_docInfo.end())
	{
		// not found
		Noeud* noeud = new Noeud(source);
		m_docInfo.insert(make_pair(cible, noeud));
	}
	else
	{
		// found
		it->second->Ajouter(source);
	}
}

void Data::AddNode ( string source, string cible )
{
	static uint index = 0;

	map<string, uint>::iterator it = m_nodes.find(cible);
	if ( it == m_nodes.end())
	{
		m_nodes.insert(make_pair(cible, index++));
	}
	it = m_nodes.find(source);
	if ( it == m_nodes.end())
	{
		m_nodes.insert(make_pair(source, index++));
	}

}

bool Data::GenerateGraph ( const string & fileName )
{

	ofstream fileOut(fileName.c_str(), ios::trunc);
	// Vérification de l'ouverture du fichier en écriture
	if(!fileOut)
	{
		return false;
	}

    // Ouverture de la description du graphe
	fileOut << "digraph {" << endl;

	// Déclaration de l'ensemble des sites
	// On parcours la table nodes contenant l'ensemble des sites
	for(auto it=m_nodes.begin(); it!=m_nodes.end(); it++)
	{
		fileOut << "\tnode" << it->second << " [label=\"" <<  it->first << "\"];" << endl;
	}

	// Ecriture des arcs entre les sites
	// On parcours la table edges contenant l'ensemble des arcs

	map<string, uint> mapSource;
	map<string, uint>::iterator itSource;

	map<string, Noeud*>::iterator itCible;
	map<string, uint>::iterator itNode;
	for ( itCible = m_docInfo.begin(); itCible != m_docInfo.end(); itCible++ )
	{
		itNode = m_nodes.find(itCible->first);
		mapSource = itCible->second->GetMapSources();
		//fileOut << "\tnode" << itNode->second << " -> node" << pos->first.second;
	}

	/*for(auto pos=edges.begin(); pos!=edges.end(); pos++)
	{
		fileOut << "\tnode" << pos->first.first << " -> node" << pos->first.second;
		fileOut << " [label=\"" << pos->second << "\"];" << endl;
	}*/

    // Fermeture de la description du graphe
	fileOut << "}" << endl;

	// Fermeture du flux d'écriture
	fileOut.close();
	return true;
}

bool Data::Traiter ()
{
	FileManager fileM(choix.logName);
	int i=0;

	while(!fileM.eof())
	{
		bool keep = true;
		string line;
		getline(fileM,line);
		stringstream s(line);
		vector <string> v = fileM.Decouper(s);

		// Traitement type d'entrées (-e)
		if(choix.eOption == 1)
		{
			if((v[6].find(".css",0)!= string::npos) || (v[6].find(".js",0)!= string::npos) || (v[6].find(".png",0)!= string::npos) || (v[6].find(".bmp",0)!= string::npos) || (v[6].find(".jpg",0)!= string::npos) || (v[6].find(".jpeg",0)!= string::npos) || (v[6].find(".gif",0)!= string::npos) || (v[6].find(".ico",0)!= string::npos))
			{
				keep = false;
			}
		}

		// Traitement intervalle temporelle (-t)
		if(choix.tOption == 1)
		{
			size_t pos = v[3].find(':',0);
			uint t = stoul(v[3].substr(pos+1, pos+2));

			if(!(t==choix.hour))
			{
				keep = false;
			}
		}

		// Prise en compte dans le résultat
		if(keep == true)
		{
			//TODO : insérer dans les maps
			cout << i++ << endl;
		}
	}

	// Affichage du Top 10

	// Traitement création graphe (-g)
	if(choix.gOption == 1)
	{
		//TODO : Générer graphe
	}

	return true;
}

//-------------------------------------------- Constructeurs - destructeur

Data::Data (Options opt)
// Algorithme :
//
{
	// Récupération des choix
	choix.etat = opt.etat;
    choix.eOption = opt.eOption;
    choix.gOption = opt.gOption;
    choix.tOption = opt.tOption;
    choix.hour = opt.hour;
    choix.logName = opt.logName;
    choix.graphName = opt.graphName;

#ifdef MAP
	cout << "Appel au constructeur de <Data>" << endl;
#endif
} //----- Fin de Data

Data::~Data ( )
// Algorithme :
//
{
	map<string, Noeud*>::iterator it;
	for ( it = m_docInfo.begin(); it != m_docInfo.end(); it++)
	{
		delete (it->second);
	}
#ifdef MAP
	cout << "Appel au destructeur de <Data>" << endl;
#endif
} //----- Fin de ~Data


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

