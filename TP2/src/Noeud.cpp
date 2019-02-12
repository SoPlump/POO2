/*************************************************************************
                           Noeud  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Noeud> (fichier Noeud.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Noeud.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

std::ostream & operator << (std::ostream & out, Noeud & noeud)
{
	map<string, uint>::iterator it;
	for ( it = noeud.m_mapSources.begin(); it != noeud.m_mapSources.end(); it++)
	{
		out << " | " << it->first << ", " << it->second << endl;
	}
	return out;
}

//----------------------------------------------------- Méthodes publiques

void Noeud::Ajouter ( const string source )
// Algorithme :
// Ajoute a m_mapSources une source supplementaire ou incremente le nombre
// de hit provenant de ce site
{	
	// Verifie si le site source existe deja dans la map qui contient tous les sites sources
	// d'un meme site cible
	map<string, uint>::iterator it = m_mapSources.find(source);
	if ( it == m_mapSources.end()) // Site non trouve
	{
		// On ajoute le site source dans m_mapSources avec 1 hit
		m_mapSources.insert(make_pair(source, 1));
	}
	else // Site trouve
	{
		// On incremente de 1 le nombre de hit lie au site source
		++(it->second);
	}
	// Augmente le nombre de hit total lie a un site cible
	++m_nbOcc;
}

map <string, uint> Noeud::GetMapSources ( )
{
	return m_mapSources;
}

uint Noeud::GetNbOcc() const
{
	return m_nbOcc;
}

//-------------------------------------------- Constructeurs - destructeur
Noeud::Noeud ( string source )
{

	m_mapSources.insert(make_pair(source, 1));
	m_nbOcc = 1;
#ifdef MAP
	cout << "Appel au constructeur de <Noeud>" << endl;
#endif
} //----- Fin de Noeud


Noeud::~Noeud ( )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <Noeud>" << endl;
#endif
} //----- Fin de ~Noeud


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées