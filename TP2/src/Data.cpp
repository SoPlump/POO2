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
	Noeud* noeud = new Noeud();
	//m_fileM = new FileManager( logFile );
	/*uint nbLine = 0;
	string element = "dest";
	string res;
	do
	{
			//res = m_fileM->GetFragLine( nbLine, element );
		if (m_docInfo.find("res") == m_docInfo.end())
		{
			cout << "insere" << endl;
			m_docInfo.insert(make_pair("res", 0));
		}
		else 
		{
			cout << "remplace" << endl;
			m_docInfo["res"] = 1;
		}
		++nbLine;
		// TODO : Vérifier avec regex si le fichier ne termine pas avec .css ou .jpg ou .js
	} while ( nbLine != 3 );*/
}
//-------------------------------------------- Constructeurs - destructeur

Data::Data (   )
// Algorithme :
//
{

#ifdef MAP
	cout << "Appel au constructeur de <Data>" << endl;
#endif
} //----- Fin de Data

Data::~Data ( )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <Data>" << endl;
#endif
} //----- Fin de ~Data


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

