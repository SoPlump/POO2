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

#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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

void Catalogue::AjouterTrajetSimple()
{
	AjouterTrajet(ScanTrajetSimple());
}// ---- fin de AjouterTrajet

void Catalogue::AjouterTrajetCompose()
{
	AjouterTrajet(ScanTrajetCompose());
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
	//TODO: Modifier pour rentrer uniquement la ville suivante
	if (nbTrajets > 1)
	{
		TrajetCompose* trajetC = new TrajetCompose();
		const char* depart = ScanString("Choisissez un depart : ");
		const char* arrivee;
		const char* transport;

		for (uint i = 0; i < nbTrajets-1; ++i)
		{	
			arrivee = ScanString("Entrez la ville suivante : ");
			transport = ScanString("\nChoisissez un moyen de transport : ");
			TrajetSimple* ts = new TrajetSimple(depart, arrivee, transport);

			depart = arrivee;
			while (!trajetC->AjouterTrajet(ts))
			{
				delete ts;
			}



			/*TrajetSimple* ts = ScanTrajetSimple();
			while (!trajetC->AjouterTrajet(ts))
			{
				delete ts;
				ts = ScanTrajetSimple();
			}*/	
		}
		arrivee = ScanString("Entrez la ville d'arrivee : ");
		transport = ScanString("\nChoisissez un moyen de transport : ");
		TrajetSimple* ts = new TrajetSimple(depart, arrivee, transport);

		while (!trajetC->AjouterTrajet(ts))
		{
			delete ts;
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
	cin >> temp;
	//cin.getline(temp, 20); // TODO: Corriger le getline
	return temp;
}// ---- fin de ScanString

void Catalogue::Charger(fstream& file)
{
	// Get the roll number 
    // of which the data is required 
	uint nbTrajet;

    // Read the Data from the file 
    // as String Vector 
	vector<string> row; 
	string line, word; 

	// read an entire row and 
    // store it in a string variable 'line' 
	while(getline(file, line))
	{ 
		row.clear(); 

        // used for breaking words 
		stringstream s(line); 

        // read every column data of a row and 
        // store it in a string variable, 'word' 
		while (getline(s, word, ',')) 
		{ 
            // add all the column data 
            // of a row to a vector 
			row.push_back(word); 
		} 

        // convert string to integer for comparison 
		nbTrajet = stoi(row[0]); 
		// Cas pour les trajets composes
		if(nbTrajet != 1)
		{
			TrajetCompose* trajetC = new TrajetCompose();
			for (uint i = 0; i < nbTrajet; ++i)
			{
				getline(file, line);

				row.clear(); 

        		// used for breaking words 
				stringstream s(line); 

        		// read every column data of a row and 
        		// store it in a string variable, 'word' 
				while (getline(s, word, ',')) 
				{ 
           		// add all the column data 
            	// of a row to a vector 
					row.push_back(word); 
				} 


				TrajetSimple* trajet = new TrajetSimple(row[1].c_str(), row[2].c_str(), row[3].c_str());
				trajetC->AjouterTrajet(trajet);

			}

			m_collectionTrajet->AjouterTrajet(trajetC);
		}

  		// TODO: Faire en sorte d'Afficher toutes les lignes
        // Compare the roll number 
		else 
		{ 
			TrajetSimple* trajet = new TrajetSimple(row[1].c_str(), row[2].c_str(), row[3].c_str());
			m_collectionTrajet->AjouterTrajet(trajet);
		}
	} 
}

/*void Catalogue::Sauvegarder(fstream& file)
{
	Trajet** liste = new Trajet*[m_collectionTrajet->GetNbTrajet()];
	liste = m_collectionTrajet->GetListeTrajet();
	for (uint i = 0; i < m_collectionTrajet->GetNbTrajet(); ++i)
	{
		if()
		file << liste[0]->GetDepart() << ","
			 << liste[0]->GetDepart() << ","
			 << liste[0]->GetDepart() << ","
	}
	delete liste;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees

/***********************************/
// Affichage d'un csv
/*
// Get the roll number 
    // of which the data is required 
	uint nbTrajet;

    // Read the Data from the file 
    // as String Vector 
	vector<string> row; 
	string line, word; 

	// read an entire row and 
    // store it in a string variable 'line' 
	while(getline(file, line))
	{ 
		row.clear(); 

        // used for breaking words 
		stringstream s(line); 

        // read every column data of a row and 
        // store it in a string variable, 'word' 
		while (getline(s, word, ',')) 
		{ 
            // add all the column data 
            // of a row to a vector 
			row.push_back(word); 
		} 

        // convert string to integer for comparison 
		nbTrajet = stoi(row[0]); 
		// Cas pour les trajets composes
		if(nbTrajet != 1)
		{
			cout << "Trajet " << row[1] << " " << row[2] << "\n";
			cout << "Compose de " << row[0] << " Trajets : \n"; 
			for (uint i = 0; i < nbTrajet; ++i)
			{
				getline(file, line);

				row.clear(); 

        		// used for breaking words 
				stringstream s(line); 

        		// read every column data of a row and 
        		// store it in a string variable, 'word' 
				while (getline(s, word, ',')) 
				{ 
           		// add all the column data 
            	// of a row to a vector 
					row.push_back(word); 
				} 
            	// Print the found data 
				cout << "Departs : " << row[1] << "\n"; 
				cout << "Arrivee : " << row[2] << "\n"; 
				cout << "Moyen de Transport : " << row[3] << "\n\n"; 

			}
		}

  		// TODO: Faire en sorte d'Afficher toutes les lignes
        // Compare the roll number 
		else 
		{ 
            // Print the found data 
			cout << "Trajet Simple\n";
			cout << "Departs : " << row[1] << "\n"; 
			cout << "Arrivee : " << row[2] << "\n"; 
			cout << "Moyen de Transport : " << row[3] << "\n\n"; 
		}
	} 
*/



/*        // read an entire row and 
        // store it in a string variable 'line' 
	while(getline(file, line))
	{ 
		row.clear(); 

        // used for breaking words 
		stringstream s(line); 

        // read every column data of a row and 
        // store it in a string variable, 'word' 
		while (getline(s, word, ',')) 
		{ 
            // add all the column data 
            // of a row to a vector 
			row.push_back(word); 
		} 

        // convert string to integer for comparison 
		nbTrajet = stoi(row[0]); 
		if(nbTrajet == 2)
			getline(file, line);

  		// TODO: Faire en sorte d'Afficher toutes les lignes
        // Compare the roll number 
		if (true) 
		{ 
            // Print the found data 
			count = 1; 
			cout << "Details of Roll " << row[0] << " : \n"; 
			cout << "Name: " << row[1] << "\n"; 
			cout << "Maths: " << row[2] << "\n"; 
			cout << "Physics: " << row[3] << "\n"; 
			cout << "Chemistry: " << row[4] << "\n"; 
			cout << "Biology: " << row[5] << "\n\n"; 
		} 
	} 
	if (count == 0) 
		cout << "Record not found\n"; */