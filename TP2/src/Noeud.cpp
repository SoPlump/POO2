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

//----------------------------------------------------- Méthodes publiques
/*uint GetNbOcc ( )
// Algorithme :
//
{
	return m_nbOcc;
} //----- Fin de GetNbOcc*/


void Noeud::Ajouter ( string source )
{	
	map<string, uint>::iterator it = m_mapSources.find(source);
	if ( it == m_mapSources.end())
	{
		// not found
		m_mapSources.insert(make_pair(source, 1));
	}
	else
	{
		// found
		++(it->second);
	}
}

map <string, uint> Noeud::GetMapSources ( )
{
	return m_mapSources;
}

//-------------------------------------------- Constructeurs - destructeur
Noeud::Noeud ( string source )
// Algorithme :
//
{

	m_mapSources.insert(make_pair(source, 1));
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