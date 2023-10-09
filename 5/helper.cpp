#include"helper.h"

using namespace std;

//Every function is works like functions of template book class.
//There is only small changes like different variable names etc.

Movie::Movie() {
    ifstream file("data.txt");
    ofstream _out("output.txt");
    _out << "Catalog Read: movie" << endl;
    int i=0;
    int y=0;
    string line;
    string temp="";
    int temp_size=99;

    getline(file, line);    
    while(getline(file, line)) {
        i=0;
        if( getlineelementnumber(line) != 10 ) {
            _out << "Exception: missing field" << endl;
            _out << line << endl;
        }
        line+=" ";
        while( i != line.size()-1 && getlineelementnumber(line) == 10 ) {
        if( line[i] == '\"') {
            while(1) {
                i++;
                if( line[i] == '\"') {
                    if(temp.empty()) {
                        temp="emptychar";
                    }
                    break;
                }
                temp+=line[i];
            }
        }
        if( y == 5) {
            y=0;
        }
        if( temp != "" ) {
            if(temp == "emptychar") {
                temp="";
            }
                if( y == 0 ) { 
                    moviename.push_back(temp);
                }

                if( y == 1 ) {
                    directorname.push_back(temp);
                }

                if( y == 2 ) {
                    date.push_back(temp);
                }

                if( y == 3 ) {
                    types.push_back(temp);
                }

                if( y == 4 ) {
                    actors.push_back(temp);
                }
                y++;
        }
        temp = "";
        i++;
    }
        int temp_totalentries = moviename.size()-2;
        while( temp_totalentries > -1 ) {
            if(moviename[moviename.size()-1] == moviename[temp_totalentries] && temp_totalentries != temp_size) {
                _out << "Exception: duplicate entry" << endl;
                _out << "\"" << moviename[temp_totalentries] << "\" " << "\"" << directorname[temp_totalentries] << "\" " << "\"" << date[temp_totalentries] << "\" " << "\"" << types[temp_totalentries] << "\" " << "\"" << actors[temp_totalentries] << "\" " << endl;
                _out << "Exception: duplicate entry" << endl;
                _out << "\"" << moviename[moviename.size()-1] << "\" " << "\"" << directorname[moviename.size()-1] << "\" " << "\"" << date[moviename.size()-1] << "\" " << "\"" << types[moviename.size()-1] << "\" " << "\"" << actors[moviename.size()-1] << "\" " << endl;
                temp_size=temp_totalentries;
            }
            temp_totalentries--;
        }
        y=0;
    }
    
    if(moviename.size() >= directorname.size() ) {
        TotalCount=moviename.size();
    }
    else{
        TotalCount=directorname.size();
    }

    _out << TotalCount << " unique entries" << endl;

    file.close();
    _out.close();
}

void Movie::sortTitle() {
    vector<string> temp = moviename;
    sort(temp.begin(), temp.end());
    bool is_checked=false;      //
    vector<string> checked_names;      //
    int k=0;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"title\"" << endl;

    for(auto sortedTitles : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedTitles )  {
                is_checked=true;
            }
        }
        while(k<moviename.size() && !is_checked) {  //
            if( sortedTitles == moviename[k] ) {
                _out << "\"" << moviename[k] << "\" " << "\"" << directorname[k] << "\" " << "\"" << date[k] << "\" " << "\"" << types[k] << "\" " << "\"" << actors[k] << "\" " << endl;
                checked_names.push_back(sortedTitles); //
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

void Movie::sortDirector() {
    vector<string> temp = directorname;        
    sort(temp.begin(), temp.end());
    bool is_checked=false;      //
    vector<string> checked_names;      //
    int k=0;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"director\"" << endl;

    for(auto sortedDirectorname : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedDirectorname )  {
                is_checked=true;
            }
        }
        while(k<directorname.size() && !is_checked) {
            if( sortedDirectorname == directorname[k] ) {
                _out << "\"" << moviename[k] << "\" " << "\"" << directorname[k] << "\" " << "\"" << date[k] << "\" " << "\"" << types[k] << "\" " << "\"" << actors[k] << "\" " << endl;
                checked_names.push_back(sortedDirectorname);
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

void Movie::sortYear() {
    vector<string> temp = date;
    sort(temp.begin(), temp.end());
    int k=0;
    bool is_checked=false;      //
    vector<string> checked_names;      //
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"year\"" << endl;

    for(auto sortedDates : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedDates )  {
                is_checked=true;
            }
        }
        while(k<date.size() && !is_checked ) {
            if( sortedDates == date[k] ) {
                _out << "\"" << moviename[k] << "\" " << "\"" << directorname[k] << "\" " << "\"" << date[k] << "\" " << "\"" << types[k] << "\" " << "\"" << actors[k] << "\" " << endl;
                checked_names.push_back(sortedDates);
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

void Movie::sortGenre() {
    vector<string> temp = types;
    sort(temp.begin(), temp.end());
    int k=0;
    bool is_checked=false;      //
    vector<string> checked_names;      //
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"genre\"" << endl;

    for(auto sortedGenres : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedGenres )  {
                is_checked=true;
            }
        }
        while(k<types.size() && !is_checked) {
            if( sortedGenres == types[k] ) {
                _out << "\"" << moviename[k] << "\" " << "\"" << directorname[k] << "\" " << "\"" << date[k] << "\" " << "\"" << types[k] << "\" " << "\"" << actors[k] << "\" " << endl;
                checked_names.push_back(sortedGenres);
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

void Movie::sortStarring() {
    vector<string> temp = actors;
    sort(temp.begin(), temp.end());
    int k=0;
    bool is_checked=false;      //
    vector<string> checked_names;      //
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"starring\"" << endl;

    for(auto sortedActors : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedActors )  {
                is_checked=true;
            }
        }
        while(k<actors.size() && !is_checked ) {
            if( sortedActors == actors[k] ) {
                _out << "\"" << moviename[k] << "\" " << "\"" << directorname[k] << "\" " << "\"" << date[k] << "\" " << "\"" << types[k] << "\" " << "\"" << actors[k] << "\" " << endl;
                checked_names.push_back(sortedActors);
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

string Movie::getelement(int k) {
    if(k==0) {return "title";}
    if(k==1) {return "director";}
    if(k==2) {return "year";}
    if(k==3) {return "genre";}
    if(k==4) {return "starring";}
    else{return "unknown";}
}

void Movie::searchwords(string search_word, int k) {
    int i=0;
    string::size_type pos;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "search \"" << search_word << "\" in \"" << getelement(k) << "\"" << endl;

    if( k == 0 ) {
        while( i < TotalCount ) {   
            pos = moviename[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << moviename[i] << "\" " << "\"" << directorname[i] << "\" " << "\"" << date[i] << "\" " << "\"" << types[i] << "\" " << "\"" << actors[i] << "\" " << endl;
                pos = moviename[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    if( k == 1 ) {
        while( i < TotalCount ) {   
            pos = directorname[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << moviename[i] << "\" " << "\"" << directorname[i] << "\" " << "\"" << date[i] << "\" " << "\"" << types[i] << "\" " << "\"" << actors[i] << "\" " << endl;
                pos = directorname[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    if( k == 2 ) {
        while( i < TotalCount ) {   
            pos = date[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << moviename[i] << "\" " << "\"" << directorname[i] << "\" " << "\"" << date[i] << "\" " << "\"" << types[i] << "\" " << "\"" << actors[i] << "\" " << endl;
                pos = date[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    if( k == 3 ) {
        while( i < TotalCount ) {   
            pos = types[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << moviename[i] << "\" " << "\"" << directorname[i] << "\" " << "\"" << date[i] << "\" " << "\"" << types[i] << "\" " << "\"" << actors[i] << "\" " << endl;
                pos = types[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    if( k == 4 ) {
        while( i < TotalCount ) {   
            pos = actors[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << moviename[i] << "\" " << "\"" << directorname[i] << "\" " << "\"" << date[i] << "\" " << "\"" << types[i] << "\" " << "\"" << actors[i] << "\" " << endl;
                pos = actors[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }
    _out.close();
}

int Movie::getlineelementnumber(string s) { 
    string::size_type pos = s.find("\"");
    int count=0;
    while (pos != string::npos) {
        count++;
        pos = s.find("\"", pos + 1);
    }
    return count;
}

void Music::sortTitle() {
    vector<string> temp = title;
    sort(temp.begin(), temp.end());
    bool is_checked=false;      //
    vector<string> checked_names;      //
    int k=0;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"title\"" << endl;

    for(auto sortedTitles : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedTitles )  {
                is_checked=true;
            }
        }
        while(k<title.size() && !is_checked) {  //
            if( title[k] == sortedTitles ) {
                _out << "\"" << title[k] << "\" " << "\"" << artists[k] << "\" " << "\"" << year[k] << "\" " << "\"" << genre[k] << "\" " << endl;
                checked_names.push_back(sortedTitles); //
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

void Music::sortArtists() {
    vector<string> temp = artists;
    sort(temp.begin(), temp.end());
    bool is_checked=false;      //
    vector<string> checked_names;      //
    int k=0;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"artists\"" << endl;

    for(auto sortedArtists : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedArtists )  {
                is_checked=true;
            }
        }
        while(k<title.size() && !is_checked) {  //
            if( artists[k] == sortedArtists ) {
                _out << "\"" << title[k] << "\" " << "\"" << artists[k] << "\" " << "\"" << year[k] << "\" " << "\"" << genre[k] << "\" " << endl;
                checked_names.push_back(sortedArtists); //
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

void Music::sortYear() {
    vector<string> temp = year;
    sort(temp.begin(), temp.end());
    bool is_checked=false;      //
    vector<string> checked_names;      //
    int k=0;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"year\"" << endl;

    for(auto sortedYear : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedYear )  {
                is_checked=true;
            }
        }
        while(k<title.size() && !is_checked) {  //
            if( year[k] == sortedYear ) {
                _out << "\"" << title[k] << "\" " << "\"" << artists[k] << "\" " << "\"" << year[k] << "\" " << "\"" << genre[k] << "\" " << endl;
                checked_names.push_back(sortedYear); //
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

void Music::sortGenre() {
    vector<string> temp = genre;
    sort(temp.begin(), temp.end());
    bool is_checked=false;      //
    vector<string> checked_names;      //
    int k=0;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"genre\"" << endl;

    for(auto sortedGenres : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedGenres )  {
                is_checked=true;
            }
        }
        while(k<title.size() && !is_checked) {  //
            if( genre[k] == sortedGenres ) {
                _out << "\"" << title[k] << "\" " << "\"" << artists[k] << "\" " << "\"" << year[k] << "\" " << "\"" << genre[k] << "\" " << endl;
                checked_names.push_back(sortedGenres); //
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

void Music::searchwords(string search_word, int k) {
    int i=0;
    string::size_type pos;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "search \"" << search_word << "\" in \"" << getelement(k) << "\"" << endl;

    if( k == 0 ) {
        while( i < TotalCount ) {   
            pos = title[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << title[i] << "\" " << "\"" << artists[i] << "\" " << "\"" << year[i] << "\" " << "\"" << genre[i] << "\" " << endl;
                pos = title[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    if( k == 1 ) {
        while( i < TotalCount ) {   
            pos = artists[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << title[i] << "\" " << "\"" << artists[i] << "\" " << "\"" << year[i] << "\" " << "\"" << genre[i] << "\" " << endl;
                pos = artists[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    if( k == 2 ) {
        while( i < TotalCount ) {   
            pos = year[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << title[i] << "\" " << "\"" << artists[i] << "\" " << "\"" << year[i] << "\" " << "\"" << genre[i] << "\" " << endl;
                pos = year[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    if( k == 3 ) {
        while( i < TotalCount ) {   
            pos = genre[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << title[i] << "\" " << "\"" << artists[i] << "\" " << "\"" << year[i] << "\" " << "\"" << genre[i] << "\" " << endl;
                pos = genre[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    _out.close();
}

int Music::getlineelementnumber(string s) {   //exception wrong yardımcı
    string::size_type pos = s.find("\"");
    int count=0;
    while (pos != string::npos) {
        count++;
        pos = s.find("\"", pos + 1);
    }
    return count;
}

Music::Music() {
    ifstream file("data.txt");
    ofstream _out("output.txt");
    _out << "Catalog Read: music" << endl;
    int i=0;
    int y=0;
    string line;
    string temp="";
    int temp_size=99;

    getline(file, line); 
    while(getline(file, line) ) {
        i=0;
        if( getlineelementnumber(line) != 8 ) {     //If quotes count is not 8 (8 quotes for 4 field) outputs error message.
            _out << "Exception: missing field" << endl;
            _out << line << endl;
        }
        line+=" ";
        while( i != line.size()-1 && getlineelementnumber(line) == 8 ) {
        if( line[i] == '\"') {
            while(1) {
                i++;
                if( line[i] == '\"' ) {
                    if(temp.empty()) {
                        temp="emptychar";
                    }
                    break;
                }
                temp+=line[i];
            }
        }
        if( y == 4) {
            y=0;
        }
        if( temp != "" ) {
            if(temp == "emptychar") {
                temp="";
            }
                if( y == 0 ) { 
                    title.push_back(temp);
                }

                if( y == 1 ) {
                    artists.push_back(temp);
                }

                if( y == 2 ) {
                    year.push_back(temp);
                }

                if( y == 3 ) {
                    genre.push_back(temp);
                }
                y++;
        }
        temp = "";
        i++;
    }
        int temp_totalentries = title.size()-2;
        while( temp_totalentries > -1 ) {
            if(title[title.size()-1] == title[temp_totalentries] && temp_totalentries != temp_size) {
                _out << "Exception: duplicate entry" << endl;
                _out << "\"" << title[temp_totalentries] << "\" " << "\"" << artists[temp_totalentries] << "\" " << "\"" << year[temp_totalentries] << "\" " << "\"" << genre[temp_totalentries] << "\" " << endl;
                _out << "Exception: duplicate entry" << endl;
                _out << "\"" << title[title.size()-1] << "\" " << "\"" << artists[title.size()-1] << "\" " << "\"" << year[title.size()-1] << "\" " << "\"" << genre[title.size()-1] << "\" " << endl;
                temp_size=temp_totalentries;
            }
            temp_totalentries--;
        }
        y=0;
    }
    if(title.size() >= artists.size() ) {
        TotalCount=title.size();
    }
    else{
        TotalCount=artists.size();
    }

    _out << TotalCount << " unique entries" << endl;

    file.close();
    _out.close();
    
}

string Music::getelement(int k) {
    if(k==0) {return "title";}
    if(k==1) {return "artists";}
    if(k==2) {return "year";}
    if(k==3) {return "genre";}
    else{return "unknown";}
}
