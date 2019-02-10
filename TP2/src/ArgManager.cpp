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
using namespace std;

//------------------------------------------------------ Include personnel
#include "ArgManager.h"

//------------------------------------------------------------- Constantes
const string path ="logs/";
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type ArgManager::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

Options ArgManager::getOptions ()
{
	Options options;

	//Pas assez d'arguments
	if (m_argc<2)
	{
		options.etat = Status::Err_arg;
		return options;
	}

	//Nom du log
	if(!goodFilename(m_argv[m_argc-1],".log"))
	{
		options.etat = Status::Err_log;
		return options;
	}
	else
	{
		options.logName = path + m_argv[m_argc-1];
	}

	//Options choisies
	for(int i = 1;i<m_argc-1;i++)
	{
		cout << m_argv[i] << endl;

		if(m_argv[i].compare("-e")==0)
		{
			options.eOption = true;
		}
		if(m_argv[i].compare("-g")==0)
		{
			options.gOption = true;
			if (!goodFilename(m_argv[i+1],".dot"))
			{
				options.etat = Status::Err_graphName;
				return options;
			} 
			else
			{
				options.graphName = m_argv[i+1];
			}
		}
		if(m_argv[i].compare("-t")==0)
		{
			try{
				if(stoi(m_argv[i+1])<0 || stoi(m_argv[i+1])>23)
				{
					options.etat = Status::Err_t;
					return options;
				}
				else
				{
					options.tOption = true;
					options.hour = stoi(m_argv[i+1]);	
				}
			}
			catch(exception e)
			{
				options.etat = Status::Err_t;
				return options;
			}
		}
	}

	return options;
}

void ArgManager::getMessage(Status etat)
{
	switch(etat)
	{
		case Status::Good:
		default:
			cerr << "Lancement du traitement" << endl;
			break;
		case Status::Err_arg :
			cerr << "Arguments manquants" << endl;
			break;
		case Status::Err_log :
			cerr << "Erreur nom fichier log" << endl;
			break;
		case Status::Err_graphName :
			cerr << "Erreur nom graphViz de sortie" << endl;
			break;
		case Status::Err_t :
			cerr << "Erreur heure indiquée" << endl;
			break;
	}
}

bool ArgManager::goodFilename(const string& filename, const string& fileext)
{
	//Verification des caractères illicites
	if(find_if(filename.begin(), filename.end(), InvalidChar()) != filename.end())
	{
		return false;
	}

	//Verification de l'extension
	if(filename.size() <= fileext.size())
    {
        return false;
    }
    if(filename.compare(filename.size() - fileext.size(), fileext.size(), fileext) != 0)
    {
        return false;
    }
    return true;
}

bool ArgManager::goodFile (const string& filename)
{
	//Vérification que le fichier existe
	ifstream test(filename.c_str());
	if(!test.is_open())
	{
		return false;
	}

	//Vérification que le fichier n'est pas vide
	if (test)
	{
		test.get();
		return test.eof();
	}
	return false;
}
//-------------------------------------------- Constructeurs - destructeur
ArgManager::ArgManager (int argc, char **argv)
// Algorithme :
//
{
	m_argc = argc;
	for(int i = 0; i<argc;i++)
	{
		m_argv.push_back(string(argv[i]));
	}	

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

