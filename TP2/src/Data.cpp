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

//----------------------------------------------------------------- PUBLIC

//------------------------------------------------- Surcharge d'opérateurs

std::ostream & operator << ( std::ostream & out, Data & data )
{
	map<std::string, Noeud*>::iterator it;
	for ( it = data.m_docInfo.begin(); it != data.m_docInfo.end(); it++)
	{
		out << it->first << ", " << it->second->GetNbOcc() << endl;
		out << *(it->second) << endl;
	}
	out << endl;

	map<std::string, uint>::iterator itN;
	for ( itN = data.m_nodes.begin(); itN != data.m_nodes.end(); itN++)
	{
		out << itN->first << ", ";
		out << itN->second << endl;
	}

	return out;
}

//----------------------------------------------------- Méthodes publiques

bool Data::Traiter ()
// Algorithme :
// La fonction ouvre un fichier .log puis recupere chaque ligne decoupee par partie
// S'occupe de garder ou non la ligne selon les parametres d'execution gere par Option
// Ensuite elle :
// - Ajoute a m_docInfo les lignes
// - Genere un graph si il le faut
// - Appelle l'affichage du Top Dix
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

	}

			// Traitement création graphe (-g)
	if(choix.gOption == 1)
	{
		GenerateGraph(choix.graphName);
	}

	AfficherTopTen();
	return true;
} //----- Fin de Traiter

//-------------------------------------------- Constructeurs - destructeur

Data::Data (Options opt)
// Algorithme :
// Genere les bonnes options qui ont precedemment ete activee dans ArgManager
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
// Il est necessaire de supprimer les Noeuds stockes dans m_docInfo
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

void Data::Ajouter ( const string source, const string cible )
// Algorithme :
// Ajoute les informations sur une ligne d'un .log 
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

} //----- Fin de Ajouter

void Data::AddNode ( const string source, const string cible )
// Algorithme :
// Cette fonction permet d'ajouter tous les sites a une map qui les fera correspondre avec des index
// La variable static index permet de cibler chaque site avec des index distinctifs
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
} //----- Fin de AddNode

bool Data::GenerateGraph ( const string & fileName ) const
// Algorithme :
// Genere un .dot a partir de m_docInfo et m_nodes
// construit precedemment
{
	const string path = "dots/"; 
	ofstream fileOut(path + fileName.c_str(), ios::trunc);

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
} //----- Fin de GenerateGraph

void Data::AfficherTopTen ( )
// Algorithme :
// Cree une liste des sites selon leur popularite et en affiche les 10 meilleurs
{
	cout << "Liste des dix meilleurs pages atteintes\n" << endl;

	// Insere dans une nouvelle multimap les sites selon leur popularite
	multimap <uint,string> topTen;
	map<string, Noeud*>::iterator itCible;
	for ( itCible = m_docInfo.begin(); itCible != m_docInfo.end(); itCible++ )
	{
		topTen.insert(make_pair(itCible->second->GetNbOcc(),itCible->first));
	}

	// Affiche dans l'ordre decroissant les 10 sites les plus populaires
	multimap <uint,string> ::reverse_iterator itTopTen;
	uint nbTopTen = 0;
	for ( itTopTen = topTen.rbegin(); itTopTen != topTen.rend() && nbTopTen < 10; itTopTen++ )
	{
		++nbTopTen;
		cout << itTopTen->first << ", " << itTopTen->second << endl;
	}
} //----- Fin de AfficherTopTen
