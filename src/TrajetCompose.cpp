/*************************************************************************
TrajetCompose  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Realisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "trajetcompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques

void TrajetCompose::Afficher() const
// Algorithme :
// Appelle la methode Afficher de sa collection.
{
	cout << "Trajet compose : " << endl;
	m_collectionTrajet->Afficher('\t');
} //----- Fin de Afficher

bool TrajetCompose::AjouterTrajet(Trajet * trajet)
// Algorithme :
// Ajoute un trajet simple a la collection du trajet compose precedemment cree.
// Si le trajet compose ne possede encore aucun trajet simple, on modifie
// le depart et l'arrivee de ce trajet compose
// Si le trajet compose possede deja un/des trajet(s) simple(s), on verifie
// que le trajet est coherent. Si c'est le cas, on modifie uniquement l'arrivee.
{
	if (m_collectionTrajet->GetNbTrajet() == 0)
	{
		this->SetArrivee(trajet->GetArrivee());
		this->SetDepart(trajet->GetDepart());
		m_collectionTrajet->AjouterTrajet(trajet);
	}
	else
	{
		if (!strcmp(trajet->GetDepart(), m_collectionTrajet->GetListeTrajet()[m_collectionTrajet->GetNbTrajet() -1]->GetArrivee())) 
		{
			this->SetArrivee(trajet->GetArrivee());
			m_collectionTrajet->AjouterTrajet(trajet);
		}
		else {
			cout << "Trajet incoherent" << endl;
			return false;
		}
		
	}
	return true;
} //----- Fin de AjouterTrajet

TrajetCompose * TrajetCompose::Copier()
// Algorithme :
// Appelle le constructeur par copie de TrajetSimple en lui passant en
// parametre l'objet appelant.
{
	return new TrajetCompose(*this);
} //----- Fin de Copier

//-------------------------------------------- Constructeurs - destructeur

TrajetCompose::TrajetCompose(uint taille) : Trajet("", "")
// Algorithme :
// Constructeur qui initialise la collecion d'une instance de trajet
// compose a la taille passee en parametre.
{
	m_collectionTrajet = new Collection(taille);

#ifdef MAP
	cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
} //----- Fin de TrajetCompose (constructeur [par defaut])

TrajetCompose::TrajetCompose(TrajetCompose const& model) : Trajet(model.m_depart, model.m_arrivee)
// Algorithme :
// Constructeur par copie qui... copie une reference d'un TrajetCompose donne
// en parametre.
{
	m_collectionTrajet = new Collection(*model.m_collectionTrajet);

#ifdef MAP
	cout << "Appel au constructeur par copie de <TrajetCompose>" << endl;
#endif
} //----- Fin de TrajetCompose (constructeur par copie)

TrajetCompose::~TrajetCompose()
// Algorithme :
// Destructeur d'une instance de TrajetCompose. Appelle automatiquement le
// destructeur de sa generalisation.
{
	delete m_collectionTrajet;
#ifdef MAP
	cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
} //----- Fin de ~TrajetCompose