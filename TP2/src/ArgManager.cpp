/*************************************************************************
                           ArgManager  -  description
                             -------------------
    début                : 23/01/2019
    copyright            : (C) 3IF par ABDEL RAHMAN Ahmed - RAUDRANT Sophie
    e-mail               : 
*************************************************************************/

//---------- Réalisation de la classe <ArgManager> (fichier ArgManager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "ArgManager.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type ArgManager::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
ArgManager & ArgManager::operator = ( const ArgManager & unArgManager )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
ArgManager::ArgManager ( const ArgManager & unArgManager )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <ArgManager>" << endl;
#endif
} //----- Fin de ArgManager (constructeur de copie)


ArgManager::ArgManager ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <ArgManager>" << endl;
#endif
} //----- Fin de ArgManager


ArgManager::~ArgManager ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ArgManager>" << endl;
#endif
} //----- Fin de ~ArgManager


//------------------------------------------------------------------ PRIVE



//----------------------------------------------------- Méthodes protégées

