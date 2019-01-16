/*************************************************************************
Collection  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Realisation de la classe <Collection> (fichier Collection.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Collection.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques


void Collection::Afficher(const char prefixe) const
{
	for (uint i = 0; i < m_nbTrajet; ++i)
	{
		cout << prefixe ;
		cout << i+1 << ") ";
		m_listeTrajet[i]->Afficher();
	}
}// ---- fin de Afficher

void Collection::AjouterTrajet(Trajet * trajet)
{

	if (m_nbTrajet == m_cardMax)
	{
		//Creation d'une nouvelle Collection 
		m_cardMax *= 2;
		Trajet ** temp = new Trajet*[m_cardMax];
		//Copie des elements de la collection actuelle dans la nouvelle
		for (uint i = 0; i < m_nbTrajet; ++i)
		{
			temp[i] = m_listeTrajet[i];
		}
		m_listeTrajet = temp;
		delete[] temp;
	}
	//Ajout du trajet et incrementation du nombre de trajets
	m_listeTrajet[m_nbTrajet++] = trajet;
}// ---- fin de AjouterTrajet

void Collection::DepilerTrajet()
{
	--m_nbTrajet;
	delete m_listeTrajet[m_nbTrajet];
}// ---- fin de DepilerTrajet

bool Collection::isCityIn(const char * cityName) const
{
	for (uint i = 0; i < m_nbTrajet; ++i)
	{
		if (!strcmp(m_listeTrajet[i]->GetArrivee(), cityName) || !strcmp(m_listeTrajet[i]->GetDepart(), cityName))return true;
	}
	return false;
}// ---- fin de isCityIn

Collection* Collection::GetTrajetsFrom(const char * depart) const
{
	Collection* itineraires = new Collection();
	for (uint i = 0; i < m_nbTrajet; ++i) {
		if (!strcmp(m_listeTrajet[i]->GetDepart(), depart)) {
			itineraires->AjouterTrajet(m_listeTrajet[i]->Copier());
		}
	}
	return itineraires;
}// ---- fin de GetTrajetsFrom

Collection* Collection::RechercheSimple(const char * depart, const char * arrivee) const
{
	Collection* itineraires = new Collection();
	for (uint i = 0; i < m_nbTrajet; ++i)
	{
		if (!strcmp(m_listeTrajet[i]->GetDepart(), depart) && !strcmp(m_listeTrajet[i]->GetArrivee(), arrivee))
		{
			itineraires->AjouterTrajet(m_listeTrajet[i]->Copier());
		}
	}
	return itineraires;
}// ---- fin de RechercheSimple

uint Collection::GetNbTrajet() const
{
	return m_nbTrajet;
}// ---- fin de GetNbTrajet

Trajet ** Collection::GetListeTrajet()
{
	return m_listeTrajet;
}// ---- fin de GetListeTrajet

//-------------------------------------------- Constructeurs - destructeur

Collection::Collection(uint taille)

{
	m_nbTrajet = 0;
	m_cardMax = taille;
	m_listeTrajet = new Trajet*[m_cardMax];

#ifdef MAP
	cout << "Appel au constructeur de <Collection>" << endl;
#endif
}// ---- fin de Collection

Collection::Collection(Collection const& model)
{
	m_cardMax = model.m_cardMax;
	m_nbTrajet = model.m_nbTrajet;
	m_listeTrajet = new Trajet*[m_cardMax];
	
	for (uint i = 0; i < m_nbTrajet; ++i)m_listeTrajet[i] = model.m_listeTrajet[i]->Copier();

#ifdef MAP
	cout << "Appel au constructeur par copie de <Collection>" << endl;
#endif
}// ---- fin de Collection

Collection::~Collection()
{
	for (uint i = 0; i < m_nbTrajet; i++) 
	{
		delete m_listeTrajet[i];
	}
	delete[] m_listeTrajet;
#ifdef MAP
	cout << "Appel au destructeur de <Collection>" << endl;
#endif
}// ---- fin de ~Collection

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees

