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