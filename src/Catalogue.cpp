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

void Catalogue::RechercheSimple(const char * depart, const char * arrivee) const
//Algorithme :
//Regarde tous les trajets du catalogue , si les villes de depart et d'arrivee correspondent
//L'ajoute a la collection rendue en retour
{
	Collection* itineraires;
	itineraires = m_collectionTrajet->RechercheSimple(depart, arrivee);

	if (itineraires->GetNbTrajet() != 0)
		cout << "Voici la liste de(s) " << itineraires->GetNbTrajet() << " trajet(s) correspondant(s) a votre recherche : " << endl;
	else
		cout << "Aucun trajet ne correspond a votre recherche" << endl;

	itineraires->Afficher();
	delete itineraires;
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
	m_collectionTrajet->AjouterTrajet(ScanTrajetSimple());
}// ---- fin de AjouterTrajet

void Catalogue::AjouterTrajetCompose()
{
	m_collectionTrajet->AjouterTrajet(ScanTrajetCompose());
}// ---- fin de AjouterTrajet

TrajetSimple* Catalogue::ScanTrajetSimple() const
//Entrees :
//--ville de depart
//--ville d'arrivee
//--moyen de transport
//du nouveau TrajetSimple cree
{
	cin.ignore();
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
	uint iTrajets;
	cout << "Combien de trajets simples composent ce nouveau trajet ? ";
	cin >> iTrajets;
	//TODO: Modifier pour rentrer uniquement la ville suivante
	if (iTrajets > 1)
	{
		TrajetCompose* trajetC = new TrajetCompose();
		cin.ignore();
		char* depart = ScanString("Choisissez un depart : ");
		char* arrivee;
		char* transport;

		for (uint i = 0; i < iTrajets-1; ++i)
		{	
			arrivee = ScanString("Entrez la ville suivante : ");
			transport = ScanString("\nChoisissez un moyen de transport : ");
			TrajetSimple* ts = new TrajetSimple(depart, arrivee, transport);
			trajetC->AjouterTrajet(ts);

			strcpy(depart, arrivee);

			delete[] transport;
			delete[] arrivee;
		}
		arrivee = ScanString("Entrez la ville d'arrivee : ");
		transport = ScanString("\nChoisissez un moyen de transport : ");
		TrajetSimple* ts = new TrajetSimple(depart, arrivee, transport);
		trajetC->AjouterTrajet(ts);

		delete[]  depart;
		delete[] arrivee;
		delete[] transport;

		return trajetC;
	}
	return nullptr;
}// ---- fin de ScanTrajetCompose

char * Catalogue::ScanString(const char * message) const
//Entrees :
//--Chaine de char a retourner
//utilisee pour demander a l'utilisateur le nom des villes et les moyens de transports
{

	char* temp= new char [30];
	cout << message << endl;
	cin.getline(temp, 30); // TODO: Corriger le getline
	return temp;
}// ---- fin de ScanString

void Catalogue::Charger(fstream& file)
{
	uint iTrajet;

    // Read the Data from the file as String Vector 
	vector<string> row; 
	string line, word; 
	getline(file, line); // ignore les metadonnees

	// read an entire row and store it in a string variable 'line' 
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
		iTrajet = stoi(row[0]); 
		// Cas pour les trajets composes
		if(iTrajet != 1)
		{
			TrajetCompose* trajetC = new TrajetCompose();
			for (uint i = 0; i < iTrajet; ++i)
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

				//todo: supprimer trajet simple ? 
			}

			m_collectionTrajet->AjouterTrajet(trajetC);
		}
        // Compare the roll number 
		else 
		{ 
			TrajetSimple* trajet = new TrajetSimple(row[1].c_str(), row[2].c_str(), row[3].c_str());
			m_collectionTrajet->AjouterTrajet(trajet);
		}
	} 
}

void Catalogue::Charger(fstream& file, bool isSimple)
{
	// Get the roll number 
    // of which the data is required 
	uint nbTrajet;

    // Read the Data from the file 
    // as String Vector 
	vector<string> row; 
	string line, word; 

	getline(file, line); // ignore les metadonnees

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
		if (!isSimple && nbTrajet !=1)
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

				//todo: supprimer trajet simple ? 
			}
			m_collectionTrajet->AjouterTrajet(trajetC);
		} 
		else if (isSimple && nbTrajet != 1)
		{
			for (uint i = 0; i < nbTrajet; ++i)
			{
				getline(file, line);
			}	
		} else if (isSimple && nbTrajet == 1)
		{
			TrajetSimple* trajet = new TrajetSimple(row[1].c_str(), row[2].c_str(), row[3].c_str());
			m_collectionTrajet->AjouterTrajet(trajet);
		}
	}
}

void Catalogue::Charger(std::fstream& file, bool isDep, string ville)
{	
	uint indexVille;
	if(isDep) indexVille = 1; //Le critere est sur la ville de depart
	else indexVille = 2; //Le critere est sur la ville d'arrivee
	
	uint iTrajet;

    // Read the Data from the file as String Vector 
	vector<string> row; 
	string line, word; 
	getline(file, line); // ignore les metadonnees

	// read an entire row and store it in a string variable 'line' 
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
		iTrajet = stoi(row[0]); 
		// Cas pour les trajets composes
		if(iTrajet != 1)
		{
			if(row[indexVille] == ville)
			{
				TrajetCompose* trajetC = new TrajetCompose();
				for (uint i = 0; i < iTrajet; ++i)
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

				//todo: supprimer trajet simple ? 
				}

				m_collectionTrajet->AjouterTrajet(trajetC);
			}
			else
			{
				for (uint i = 0; i < iTrajet; ++i)
					getline(file, line);
			}
		}
		else 
		{
			if(row[indexVille] == ville)
			{
				TrajetSimple* trajet = new TrajetSimple(row[1].c_str(), row[2].c_str(), row[3].c_str());
				m_collectionTrajet->AjouterTrajet(trajet);
			}
		}
	}
}

void Catalogue::Charger(std::fstream& file, string depart, string arrivee)
{	
	uint iTrajet;

    // Read the Data from the file as String Vector 
	vector<string> row; 
	string line, word;
	getline(file, line); // ignore les metadonnees 

	// read an entire row and store it in a string variable 'line' 
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
		iTrajet = stoi(row[0]); 
		// Cas pour les trajets composes
		if(iTrajet != 1)
		{
			if((row[1] == depart)&&(row[2] == arrivee))
			{
				TrajetCompose* trajetC = new TrajetCompose();
				for (uint i = 0; i < iTrajet; ++i)
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

				//todo: supprimer trajet simple ? 
				}

				m_collectionTrajet->AjouterTrajet(trajetC);
			}
			else
			{
				for (uint i = 0; i < iTrajet; ++i)
					getline(file, line);
			}
		}
		else 
		{
			if((row[1] == depart)&&(row[2] == arrivee))
			{
				TrajetSimple* trajet = new TrajetSimple(row[1].c_str(), row[2].c_str(), row[3].c_str());
				m_collectionTrajet->AjouterTrajet(trajet);
			}
		}
	}
}

bool Catalogue::Charger(std::fstream& file, int begin, int end)
{
	// m - n > 0
	uint iTrajet, nbTrajet;

    // Read the Data from the file as String Vector 
	vector<string> row; 
	string line, word; 

	getline(file, line); // ignore les metadonnees
	nbTrajet = stoi(line);

		// Les bornes ne sont pas inversees // Les indices designe un trajet existant
	if((end - begin >= 0)&&(1 <= begin)&&((uint)begin <= nbTrajet)&&(1 <= end)&&((uint)end<= nbTrajet))
	{
		int x;
		for(x=0; x<begin-1;++x)
		{
			getline(file, line);
		}
		for (x=begin; x<=end;++x)
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

        // convert string to integer for comparison 
			iTrajet = stoi(row[0]); 
		// Cas pour les trajets composes
			if(iTrajet != 1)
			{
				TrajetCompose* trajetC = new TrajetCompose();
				for (uint i = 0; i < iTrajet; ++i)
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

				//todo: supprimer trajet simple ? 
				}

				m_collectionTrajet->AjouterTrajet(trajetC);
			}
			// Cas des trajets simples
			else 
			{ 
				TrajetSimple* trajet = new TrajetSimple(row[1].c_str(), row[2].c_str(), row[3].c_str());
				m_collectionTrajet->AjouterTrajet(trajet);
			}
		} 
		return true;
	}
	else 
	{
		cout << "Intervalles incorrectes" << endl;
		return false;
	}
}

void Catalogue::Sauvegarder(fstream& file)
{
	file << m_collectionTrajet->GetNbTrajet() << "\n";
	for (uint i = 0; i < m_collectionTrajet->GetNbTrajet(); ++i)
	{
		file << m_collectionTrajet->GetListeTrajet()[i]->ToCSV() << "\n";
	}
}

void Catalogue::Sauvegarder(fstream& file, bool isDep, string ville)
{	
	uint nbTrajet = 0;
	std::vector<string> info;

	for (uint i = 0; i < m_collectionTrajet->GetNbTrajet(); ++i)
	{
		if(((isDep)&&(m_collectionTrajet->GetListeTrajet()[i]->GetDepart() == ville))||((!isDep)&&(m_collectionTrajet->GetListeTrajet()[i]->GetArrivee() == ville)))
		{
			++nbTrajet;
			info.push_back(m_collectionTrajet->GetListeTrajet()[i]->ToCSV());
		}
	}

	file << nbTrajet << "\n";
	for (uint i = 0; i < nbTrajet; ++i)
	{
		file << info[i] << "\n";
	}

}

void Catalogue::Sauvegarder(fstream& file, string depart, string arrivee)
{
	uint nbTrajet = 0;
	std::vector<string> info;

	for (uint i = 0; i < m_collectionTrajet->GetNbTrajet(); ++i)
	{
		if((m_collectionTrajet->GetListeTrajet()[i]->GetDepart() == depart)&&(m_collectionTrajet->GetListeTrajet()[i]->GetArrivee() == arrivee))
		{
			++nbTrajet;
			info.push_back(m_collectionTrajet->GetListeTrajet()[i]->ToCSV());
		}
	}

	file << nbTrajet << "\n";
	for (uint i = 0; i < nbTrajet; ++i)
	{
		file << info[i] << "\n";
	}
}

void Catalogue::Sauvegarder(fstream& file, bool isSimple)
{
	uint nbTrajet = 0;
	std::vector<string> info;

	for (uint i = 0; i < m_collectionTrajet->GetNbTrajet(); ++i)
	{
		// Recupere le type de trajet
		string typeTrajet;
		stringstream s(m_collectionTrajet->GetListeTrajet()[i]->ToCSV()); 
		getline(s, typeTrajet, ',');
		cout << stoi(typeTrajet) << endl;

		if(isSimple && stoi(typeTrajet)==1)
		{
			++nbTrajet;
			info.push_back(m_collectionTrajet->GetListeTrajet()[i]->ToCSV());
		} 
		else if (!isSimple && stoi(typeTrajet) !=1)
		{
			++nbTrajet;
			info.push_back(m_collectionTrajet->GetListeTrajet()[i]->ToCSV());
		}
	}
	
	file << nbTrajet << "\n";
	for (uint i = 0; i < nbTrajet; ++i)
	{
		file << info[i] << "\n";
	}
}

bool Catalogue::Sauvegarder(fstream& file, int begin, int end)
{
	int nbTrajet = m_collectionTrajet->GetNbTrajet();

	if((end - begin >= 0)&&(1 <= begin)&&(begin <= nbTrajet)&&(1 <= end)&&(end<= nbTrajet))
	{
		file << end-begin+1 << "\n";
		for (int i = begin-1; i <= end-1; ++i)
		{
			// Recupere le type de trajet
			string typeTrajet;
			stringstream s(m_collectionTrajet->GetListeTrajet()[i]->ToCSV()); 
			getline(s, typeTrajet, ',');
			cout << stoi(typeTrajet) << endl;

			file << m_collectionTrajet->GetListeTrajet()[i]->ToCSV() << "\n";
		}
		return true;
	}
	else 
	{
		cout << "Intervalles incorrectes" << endl;
		return false;
	}
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees

