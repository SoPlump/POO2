/*************************************************************************
Trajet  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Realisation de la classe <Trajet> (fichier Trajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

//------------------------------------------------------ Include personnel
#include "trajet.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques

void Trajet::Afficher() const
// Algorithme :
// Affiche les attributs de Trajet
{
	cout << "Depart : " << m_depart << ", Arrivee : " << m_arrivee;
} //----- Fin de Afficher

Trajet * Trajet::Copier()
// Algorithme :
// Methode virtuelle donc va chercher la fonction Copier de la specialisation
// correspondante.
{
	return nullptr;
} //----- Fin de Copier

char* Trajet::GetDepart() const
// Algorithme :
// Retourne le depart d'une instance de TrajetSimple.
{
	return m_depart;
} //----- Fin de GetDepart

char* Trajet::GetArrivee() const
// Algorithme :
// Retourne l'arrivee d'une instance de TrajetSimple.
{
	return m_arrivee;
} //----- Fin de GetArrivee

string Trajet::ToCSV()
{
	string depart (m_depart);
	string arrivee(m_arrivee);
	string info = depart + "," + arrivee;
	return info;
}

//-------------------------------------------- Destructeur

Trajet::~Trajet()
// Algorithme :
// Destructeur d'une instance de Trajet.
{
	delete[] m_depart;
	delete[] m_arrivee;
#ifdef MAP
	cout << "Appel au destructeur de <Trajet>" << endl;
#endif
} //----- Fin de ~TrajetSimple

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees

void Trajet::SetDepart(const char * depart)
// Algorithme :
// Modifie l'attribut m_depart par le parametre formel. 
{
	int lg = strlen(depart);
	if (m_depart != nullptr) delete[] m_depart;
	m_depart = new char[lg + 1];
	m_depart = strcpy(m_depart, depart);
} //----- Fin de SetDepart

void Trajet::SetArrivee(const char * arrivee)
// Algorithme :
// Modifie l'attribut m_arrivee par le parametre formel. 
{
	int lg = strlen(arrivee);
	if (m_arrivee != nullptr)delete[] m_arrivee;
	m_arrivee = new char[lg + 1];
	m_arrivee = strcpy(m_arrivee, arrivee);
} //----- Fin de SetArrivee

//-------------------------------------------- Constructeurs

Trajet::Trajet(const char* depart, const char* arrivee)
// Algorithme :
// Constructeur qui prend comme argument un depart, une arrivee.
{
	int lg = strlen(depart);
	m_depart = new char[lg + 1];
	m_depart = strcpy(m_depart, depart);


	lg = strlen(arrivee);
	m_arrivee = new char[lg + 1];
	m_arrivee = strcpy(m_arrivee, arrivee);

#ifdef MAP
	cout << "Appel au constructeur de <Trajet>" << endl;
#endif
} //----- Fin de Trajet (constructeur)

Trajet::Trajet(Trajet const& model)
// Algorithme :
// Constructeur par copie qui... copie une reference d'un Trajet donne
// en parametre.
{
	m_arrivee = model.m_arrivee;
	m_depart = model.m_depart;

#ifdef MAP
	cout << "Appel au constructeur par copie de <Trajet>" << endl;
#endif
} //----- Fin de Trajet (constructeur de copie)







