/*************************************************************************
TrajetSimple  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Realisation de la classe <trajetsimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques
void TrajetSimple::Afficher() const
// Algorithme :
// Appelle la methode Afficher de Trajet (pour afficher le depart et l'arrivee).
// Puis afficher dans la console le moyen de transport utilise.
{
	Trajet::Afficher();
	cout << ", Moyen de Transport : " << m_moyenTransport << endl;
} //----- Fin de Afficher

TrajetSimple* TrajetSimple::Copier() 
// Algorithme :
// Appelle le constructeur par copie de TrajetSimple en lui passant en
// parametre l'objet appelant.
{
	return new TrajetSimple(*this);
} //----- Fin de Copier

char* TrajetSimple::GetMoyenTransport() const
// Algorithme :
// Retourne le moyen de transport utilise dans une instance de TrajetSimple.
{
	return m_moyenTransport;
} //----- Fin de GetMoyenTransport


//-------------------------------------------- Constructeurs - destructeur

TrajetSimple::TrajetSimple(const char* depart, const char* arrivee, const char* moyenTransport) : Trajet(depart, arrivee)
// Algorithme :
// Constructeur qui prend comme argument un depart, une arrivee et un moyen
// de transport.
{
	int lg = strlen(moyenTransport);
	m_moyenTransport = new char[lg + 1];
	m_moyenTransport = strcpy(m_moyenTransport, moyenTransport);

#ifdef MAP
	cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
} //----- Fin de TrajetSimple (constructeur)

TrajetSimple::TrajetSimple(TrajetSimple const& model) : Trajet(model.m_depart, model.m_arrivee)
// Algorithme :
// Constructeur par copie qui... copie une reference d'un TrajetSimple donne
// en parametre.
{
	m_moyenTransport = new char[strlen(model.m_moyenTransport)+1];
	strcpy(m_moyenTransport,model.m_moyenTransport);
#ifdef MAP
	cout << "Appel au constructeur par copie de <TrajetSimple>" << endl;
#endif
} //----- Fin de TrajetSimple (constructeur de copie)

string TrajetSimple::ToCSV()
{
	string moyenT(m_moyenTransport);
	string info = "1," + Trajet::ToCSV() + "," + moyenT;
	return info;
}

TrajetSimple::~TrajetSimple()
// Algorithme :
// Destructeur d'une instance de TrajetSimple. Appelle automatiquement le
// destructeur de sa generalisation.
{
	delete[] m_moyenTransport;
#ifdef MAP
	cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
} //----- Fin de ~TrajetSimple

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees