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

	// Verifie si le site cible existe deja dans la map qui contient tous les sites cibles
	if ( it == m_docInfo.end()) // Site non trouvee
	{
		// On cree un nouveau noeud qui contiendra tous les sites sources qui
		// ont referes le site cible avec le nombre d'occurence (par site source et au total)
		Noeud* noeud = new Noeud(source);

		m_docInfo.insert(make_pair(cible, noeud));
	}
	else // Site trouve
	{
		// On ajoute le site source au Noeud correspondant au site cible
		it->second->Ajouter(source);
	}

	// On ajoute une node
	AddNode(source, cible);
}

void Data::AddNode ( string source, string cible )
{
	static uint index = 0;

	// On verifie si le site cible existe deja dans la map qui contient toutes les nodes et leur index
	map<string, uint>::iterator it = m_nodes.find(cible);
	if ( it == m_nodes.end())
	{
		m_nodes.insert(make_pair(cible, index++));
	}

	// On verifie si le site source existe deja dans la map qui contient toutes les nodes et leur index
	it = m_nodes.find(source);
	if ( it == m_nodes.end())
	{
		m_nodes.insert(make_pair(source, index++));
	}

}

bool Data::GenerateGraph ( const string & fileName )
{

	ofstream fileOut(fileName.c_str(), ios::trunc);

	// Verification de l'ouverture du fichier
	if(!fileOut)
	{
		return false;
	}

	fileOut << "digraph {" << endl;

	// On parcourt la map qui contient tous les sites avec un numero associe
	for(auto it=m_nodes.begin(); it!=m_nodes.end(); it++)
	{
		fileOut << "\tnode" << it->second << " [label=\"" <<  it->first << "\"];" << endl;
	}

	// On parcourt la map qui contient tous les sites cible
	for(auto itCible = m_docInfo.begin(); itCible != m_docInfo.end(); ++itCible)
	{
		// On recupere pour chacun des sites cibles la map des sites Sources qui le refere, avec le nombre d'occurence
		map <std::string, uint> mapSource = itCible->second->GetMapSources();
		for ( auto itSource = mapSource.begin() ; itSource != mapSource.end() ; ++itSource )
		{
			fileOut << "\tnode" << m_nodes.find(itSource->first)->second << " -> node" << m_nodes.find(itCible->first)->second;
			fileOut << " [label=\"" << itSource->second << "\"];" << endl;
		}
	}

	fileOut << "}" << endl;

	// Fermeture du flux d'écriture
	fileOut.close();

	return true;
}

bool Data::Traiter ()
{
	// On ouvre un FileManager
	FileManager fileM(choix.logName);

	while(!fileM.eof())
	{
		bool keep = true; // Nous permet de savoir si on garde la ligne
		string line;

		// Recupere chaque ligne du fichier log
		getline(fileM,line);
		stringstream s(line);

		// Decoupe chaque ligne en un vecteur de mots
		vector <string> v = fileM.Decouper(s);

		if (!v.empty())
		{
		// Traitement type d'entrées (-e)
		if(choix.eOption == 1)
		{
				if((v[6].find(".css",0)!= string::npos) || (v[6].find(".js",0)!= string::npos) || (v[6].find(".png",0)!= string::npos) || (v[6].find(".bmp",0)!= string::npos) || (v[6].find(".jpg",0)!= string::npos) || (v[6].find(".jpeg",0)!= string::npos) || (v[6].find(".gif",0)!= string::npos) || (v[6].find(".ico",0)!= string::npos))
				{
					// La ligne correspond à un site qui ne correspond pas a ce qui est desire
					keep = false;
				}
		}

		// Traitement intervalle temporelle (-t)
		if(choix.tOption == 1)
		{
			if (!v.empty())
			{
				size_t pos = v[3].find(':',0);
				uint t = stoul(v[3].substr(pos+1, pos+2));

				if(!(t==choix.hour))
				{
					// La ligne correspond à un site qui ne correspond pas a ce qui est desire
					keep = false;
				}
			}

			// Ajout de la cible et de la source dans la map qui contient tous les sites cibles
		if(keep == true)
		{
			Ajouter(v[10], v[6]);
		}
	}

	// Traitement création graphe (-g)
	if(choix.gOption == 1)
	{
		GenerateGraph(choix.graphName);
	}

	AfficherTopTen();

	return true;
}

void Data::AfficherTopTen ( )
{
	cout << "La liste des dix meilleurs pages atteintes\n" << endl;

	multimap <uint,string> topTen;
	map<string, Noeud*>::iterator itCible;
	for ( itCible = m_docInfo.begin(); itCible != m_docInfo.end(); itCible++ )
	{
		topTen.insert(make_pair(itCible->second->GetNbOcc(),itCible->first));
	}

	multimap <uint,string> ::reverse_iterator itTopTen;
	uint nbTopTen = 0;
	for ( itTopTen = topTen.rbegin(); itTopTen != topTen.rend() && nbTopTen < 10; itTopTen++ )
	{
		++nbTopTen;
		cout << itTopTen->first << ", " << itTopTen->second << endl;
	}
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

