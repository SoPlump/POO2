/*************************************************************************
Catalogue  -  description
-------------------
debut                : 14 decembre 2018
copyright            : (C) 2018 par CERBA, RAUDRANT
e-mail               : guilhem.cerba@insa-lyon.fr, sophie.raudrant@insa-lyon.fr
*************************************************************************/

//---------- Realisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques
// type Catalogue::Methode ( liste des parametres )
// Algorithme :
//
//{
//} //----- Fin de Methode


//-------------------------------------------- Constructeurs - destructeur


void Catalogue::Afficher() const
{
	m_collectionTrajet->Afficher();
}// ---- fin de Afficher


void Catalogue::AjouterTrajet(Trajet * trajet)
{
	m_collectionTrajet->AjouterTrajet(trajet);
}// ---- fin de AjouterTrajet

void Catalogue::RechercheSimple(const char * depart, const char * arrivee) const
//Algorithme :
//Regarde tous les trajets du catalogue , si les villes de depart et d'arrivee correspondent
//L'ajoute a la collection rendue en retour
{
	Collection* itineraires = new Collection();
	itineraires = m_collectionTrajet->RechercheSimple(depart, arrivee);

	if (itineraires->GetNbTrajet() != 0)
		cout << "Voici la liste de(s) " << itineraires->GetNbTrajet() << " trajet(s) correspondant(s) a votre recherche : " << endl;
	else
		cout << "Aucun trajet ne correspond a votre recherche" << endl;

	itineraires->Afficher();
}// ---- fin de RechercheSimple


void Catalogue::RechercheComplexe(const char * depart, const char * arrivee) const
{
	Collection* chemins = new Collection();
	Chemin(depart, arrivee, *chemins);
	delete chemins;
}// ---- fin de RechercheComplexe


void Catalogue::Chemin(const char * depart, const char * arrivee, Collection & wayToHere) const
//Algorithme :
//Algorithme recursif de parcours en profondeur // backtracking
// Creation d'une Collection contenant l'ensemble des trajets partants de depart
// Pour chacun de ces trajets : 
// 		si la ville d'arrivee est la ville de destination souhaitee : on met a jour wayToHere , on l'affiche puis depile le dernier trajet ajoute
// 		sinon on relance la recherche en mettant comme nouveau depart la ville d'arrivee du trajet , et on met a jour wayToHere que l'on envoie par reference
// On libere cette collection
{
	Collection* departs = m_collectionTrajet->GetTrajetsFrom(depart);
	for (uint i = 0; i < departs->GetNbTrajet(); ++i) 
	{
		if (!strcmp(departs->GetListeTrajet()[i]->GetArrivee(), arrivee)) 
		{
			wayToHere.AjouterTrajet(departs->GetListeTrajet()[i]->Copier());
			wayToHere.Afficher();
			wayToHere.DepilerTrajet();
		}
		else if(!wayToHere.isCityIn(departs->GetListeTrajet()[i]->GetArrivee()))
		{
			wayToHere.AjouterTrajet(departs->GetListeTrajet()[i]->Copier());
				
			Chemin(departs->GetListeTrajet()[i]->GetArrivee(), arrivee, wayToHere);
			wayToHere.DepilerTrajet();
		}
	}
	delete departs;
}// ---- fin de Chemin

Catalogue::Catalogue(uint taille)
{
	m_collectionTrajet = new Collection(taille);
#ifdef MAP
	cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
}// ---- fin de Catalogue

Catalogue::~Catalogue()
{
	delete m_collectionTrajet;
#ifdef MAP
	cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
}// ---- fin de ~Catalogue

void Catalogue::AjouterTrajet(int selection)
{
	if (selection == 1) 
	{
		AjouterTrajet(ScanTrajetSimple());
	}
	else 
	{
		AjouterTrajet(ScanTrajetCompose());
	}
}// ---- fin de AjouterTrajet

TrajetSimple* Catalogue::ScanTrajetSimple() const
//Entrees :
//--ville de depart
//--ville d'arrivee
//--moyen de transport
//du nouveau TrajetSimple cree
{
	const char* depart = ScanString("Choisissez un depart : ");
	const char* arrivee = ScanString("\nChoisissez une arrivee : ");
	const char* transport = ScanString("\nChoisissez un moyen de transport : ");

	TrajetSimple* unTrajetSimple = new TrajetSimple(depart, arrivee, transport);
	
	delete[] depart;
	delete[] arrivee;
	delete[] transport;

	return unTrajetSimple;
}// ---- fin de ScanTrajetSimple

TrajetCompose * Catalogue::ScanTrajetCompose() const
//Entrees :
//--nombre de trajets composant le trajet composee
//Appel a ScanTrajetSimple()
{
	uint nbTrajets;
	cout << "Combien de trajets simples composent ce nouveau trajet ? ";
	cin >> nbTrajets;
	if (nbTrajets != 0)
	{
		TrajetCompose* trajetC = new TrajetCompose();
		for (uint i = 0; i < nbTrajets; ++i)
		{
			TrajetSimple* ts = ScanTrajetSimple();
			while (!trajetC->AjouterTrajet(ts))
			{
				delete ts;
				ts = ScanTrajetSimple();
			}	
		}
		return trajetC;
	}
	return nullptr;
}// ---- fin de ScanTrajetCompose

void Catalogue::ChercherTrajet(int selection) const
//Entrees :
//--nom de la ville de depart
//--nom de la ville d'arrivee
// de l'itineraire recherche dans le catalogue
{
	const char* depart = ScanString("Choisissez un depart : ");
	const char* arrivee = ScanString("\nChoisissez une arrivee : ");

	if (selection == 3)
	{
		RechercheComplexe(depart, arrivee);
	}
	else
	{
		RechercheSimple(depart, arrivee);
	}
		
	delete[] depart;
	delete[] arrivee;
} // ---- fin de ChercherTrajet


char * Catalogue::ScanString(const char * message) const
//Entrees :
//--Chaine de char a retourner
//utilisee pour demander a l'utilisateur le nom des villes et les moyens de transports
{
	char * temp = new char[20];
	cout << message << endl;
	cin.getline(temp, 20);
	return temp;
}// ---- fin de ScanString

void Catalogue::Interface()
//Entrees :
//--numero de la commande a realiser
//1. Ajouter un trajet simple
//2. Ajouter un trajet compose
//3. Chercher un trajet
//4. Afficher tout le catalogue
{
	char lecture[100];
	cout << "Bienvenue !" << endl;
	cout << "****************************" << endl;
	cout << "1. Ajouter un trajet simple" << endl;
	cout << "2. Ajouter un trajet compose" << endl;
	cout << "3. Chercher un Trajet Complexe" << endl;
	cout << "4. Chercher un Trajet Simple" << endl;
	cout << "5. Afficher tout le catalogue" << endl;
	cout << "****************************" << endl;

	fscanf(stdin, "%99s", lecture);
	while (strcmp(lecture, "bye") != 0)
	{
		if (strcmp(lecture, "1") == 0 || strcmp(lecture, "2") == 0)
		{
			AjouterTrajet(atoi(lecture));
		}

		if ((strcmp(lecture, "3") == 0) || strcmp(lecture, "4") == 0)
		{
			ChercherTrajet(atoi(lecture));
		}
		if (strcmp(lecture, "5") == 0)
		{
			Afficher();
		}

		fscanf(stdin, "%99s", lecture);
	}
}// ---- fin de Interface

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees


