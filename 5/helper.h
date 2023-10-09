#ifndef HELPER_H_
#define HELPER_H_

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

template<typename T>        
class Book{                 //Template Book class
    private:                //Private data of Book class
        vector<T> title;
        vector<T> authors;
        vector<T> year;
        vector<T> tags;
        int TotalCount=0;   //Total entry count
    public:
        Book();  
        const vector<T> &getTitle() const { return title; }
        const vector<T> &getDirectorNames() const { return authors; }
        const vector<T> &getDates() const { return year; }
        const vector<T> &getTypes() const { return tags; }
        void sortTitle();       //Sort functions
        void sortAuthors();
        void sortYear();
        void sortTags();
        void searchwords(T search_word, int k); //Search word function. k for the search in which field.
        int getlineelementnumber(string s);     //This is helper function for exception handling.
        string getelement(int k);               //Helper function for write to output.txt
};

template<typename T>
string Book<T>::getelement(int k) {     //Just a helper function. Returns string by number.
    if(k==0) {return "title";}
    if(k==1) {return "authors";}
    if(k==2) {return "year";}
    if(k==3) {return "tags";}
    else{return "unknown";}
}

template<typename T>
int Book<T>::getlineelementnumber(string s) {   //Just helper function for exception handling. Returns quotes count in specific line.
    string::size_type pos = s.find("\"");
    int count=0;
    while (pos != string::npos) {
        count++;
        pos = s.find("\"", pos + 1);
    }
    return count;
}

template<typename T>
Book<T>::Book() {           //Consturctor of Book class.
    ifstream file("data.txt");
    ofstream _out("output.txt");
    _out << "Catalog Read: book" << endl;
    int i=0;
    int y=0;
    string line;
    string temp="";
    int temp_size=99;
    
    getline(file, line);    
    while(getline(file, line)) {
        i=0;
        if( getlineelementnumber(line) != 8 ) {     //If quotes count is not 8 (8 quotes for 4 field) outputs error message.
            _out << "Exception: missing field" << endl;
            _out << line << endl;
        }
        line+=" ";
        while( i != line.size()-1 && getlineelementnumber(line) == 8 ) {    //If there is missing field without quotes, loop is not works so that informations never hold by memory.
        if( line[i] == '\"') {          //temp variable holds word between quotes mark 
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
        if( y == 4) {
            y=0;
        }
        if( temp != "" ) {          //According to y variable. Word coming from upper loop is holds by related vector.
            if(temp == "emptychar") {
                temp="";
            }    
                if( y == 0 ) {
                    title.push_back(temp);
                }

                if( y == 1 ) {
                    authors.push_back(temp);
                }

                if( y == 2 ) {
                    year.push_back(temp);
                }

                if( y == 3 ) {
                    tags.push_back(temp);
                }
                y++;
        }
        temp = "";
        i++;
    }
        int temp_totalentries = title.size()-2;
        while( temp_totalentries > -1 ) {      //Check algorithm for duplivate entry.
            if(title[title.size()-1] == title[temp_totalentries] && temp_size!=temp_totalentries ) {
                _out << "Exception: duplicate entry" << endl;
                _out << "\"" << title[temp_totalentries] << "\" " << "\"" << authors[temp_totalentries] << "\" " << "\"" << year[temp_totalentries] << "\" " << "\"" << tags[temp_totalentries] << "\" " << endl;
                _out << "Exception: duplicate entry" << endl;
                _out << "\"" << title[title.size()-1] << "\" " << "\"" << authors[title.size()-1] << "\" " << "\"" << year[title.size()-1] << "\" " << "\"" << tags[title.size()-1] << "\" " << endl;
                temp_size=temp_totalentries;
            }
            temp_totalentries--;
        }
        y=0;
        temp_totalentries++;
    }

    if(title.size() >= authors.size() ) {
        TotalCount=title.size();
    }
    else{
        TotalCount=authors.size();
    }

    _out << TotalCount << " unique entries" << endl;

    file.close();
    _out.close();
}

template<typename T>
void Book<T>::sortTitle() {     //Sort algorithm for title. Every sort function works with same algorithm.
    vector<string> temp = title;    //temp vector holds title vector.
    sort(temp.begin(), temp.end()); //temp vector holds title vector because after the sorting places of sorting of vector is changes.
    bool is_checked=false;
    vector<string> checked_names;   //Holds name of already checked and sorted titles.
    int k=0;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"title\"" << endl;

    for(auto sortedTitles : temp ) {    //Checks the is title already checked and sorted.
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedTitles )  {
                is_checked=true;
            }
        }
        while(k<title.size() && !is_checked) {  //if it's not sorted, it's prints to output.txt
            if( title[k] == sortedTitles ) {
                _out << "\"" << title[k] << "\" " << "\"" << authors[k] << "\" " << "\"" << year[k] << "\" " << "\"" << tags[k] << "\" " << endl;
                checked_names.push_back(sortedTitles); //checked_names vector holds name of printed title.
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

template<typename T>
void Book<T>::sortAuthors() {   //Works like sortTitle algorithm.
    vector<string> temp = authors;
    sort(temp.begin(), temp.end());
    bool is_checked=false;      
    vector<string> checked_names;      
    int k=0;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"authors\"" << endl;

    for(auto sortedAuthors : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedAuthors )  {
                is_checked=true;
            }
        }
        while(k<title.size() && !is_checked) {  
            if( sortedAuthors == authors[k] ) {
                _out << "\"" << title[k] << "\" " << "\"" << authors[k] << "\" " << "\"" << year[k] << "\" " << "\"" << tags[k] << "\" " << endl;
                checked_names.push_back(sortedAuthors); 
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

template<typename T>
void Book<T>::sortYear() {  //Works like sortTitle algorithm.
    vector<string> temp = year;
    sort(temp.begin(), temp.end());
    bool is_checked=false;      
    vector<string> checked_names;      
    int k=0;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"year\"" << endl;

    for(auto sortedYears : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedYears )  {
                is_checked=true;
            }
        }
        while(k<title.size() && !is_checked) {  
            if( sortedYears == year[k] ) {
                _out << "\"" << title[k] << "\" " << "\"" << authors[k] << "\" " << "\"" << year[k] << "\" " << "\"" << tags[k] << "\" " << endl;
                checked_names.push_back(sortedYears); 
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

template<typename T>
void Book<T>::sortTags() { //Works like sortTitle algorithm.
    vector<string> temp = tags;
    sort(temp.begin(), temp.end());
    bool is_checked=false;      
    vector<string> checked_names;      
    int k=0;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "sort \"tags\"" << endl;

    for(auto sortedTags : temp ) {
        for ( int j=0 ; j<checked_names.size() ; j++ ) {
            if(checked_names[j] == sortedTags )  {
                is_checked=true;
            }
        }
        while(k<title.size() && !is_checked) {  
            if( sortedTags == tags[k] ) {
                _out << "\"" << title[k] << "\" " << "\"" << authors[k] << "\" " << "\"" << year[k] << "\" " << "\"" << tags[k] << "\" " << endl;
                checked_names.push_back(sortedTags); 
            }
            k++;
        }
        k=0;
        is_checked=false;
    }
    _out.close();
}

template<typename T>
void Book<T>::searchwords(T search_word, int k) {   //Search word in fields according to parameters.
    int i=0;
    string::size_type pos;
    ofstream _out("output.txt", std::ios_base::app);
    _out << "search \"" << search_word << "\" in \"" << getelement(k) << "\"" << endl;  //prints command to output.txt

    if( k == 0 ) {  //Searchs word in the title field and if finds prints it to output.txt.
        while( i < TotalCount ) {   
            pos = title[i].find(search_word); 

            while (pos != string::npos) {
                _out << "\"" << title[i] << "\" " << "\"" << authors[i] << "\" " << "\"" << year[i] << "\" " << "\"" << tags[i] << "\" " << endl;
                pos = title[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    if( k == 1 ) {  //Searchs word in the authors field and if finds prints it to output.txt.
        while( i < TotalCount ) {   
            pos = authors[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << title[i] << "\" " << "\"" << authors[i] << "\" " << "\"" << year[i] << "\" " << "\"" << tags[i] << "\" " << endl;
                pos = authors[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    if( k == 2 ) {  //Searchs word in the year field and if finds prints it to output.txt.
        while( i < TotalCount ) {   
            pos = year[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << title[i] << "\" " << "\"" << authors[i] << "\" " << "\"" << year[i] << "\" " << "\"" << tags[i] << "\" " << endl;
                pos = year[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    if( k == 3 ) {  //Searchs word in the tags field and if finds prints it to output.txt.
        while( i < TotalCount ) {   
            pos = tags[i].find(search_word);

            while (pos != string::npos) {
                _out << "\"" << title[i] << "\" " << "\"" << authors[i] << "\" " << "\"" << year[i] << "\" " << "\"" << tags[i] << "\" " << endl;
                pos = tags[i].find(search_word, pos + 1);
            }
            i++;   
        }
    }

    _out.close();
}


class Movie{    //Works like book class. Different is book class is template class.
    private:    //Private data members of movie class.
        vector<string> moviename;
        vector<string> directorname;
        vector<string> date;
        vector<string> types;
        vector<string> actors;
        int TotalCount=0;
    public:
        const vector<string> &getMovieNames() const { return moviename; }
        const vector<string> &getDirectorNames() const { return directorname; }
        const vector<string> &getDates() const { return date; }
        const vector<string> &getTypes() const { return types; }
        const vector<string> &getActors() const { return actors; }
        void sortTitle();   //Sorting functions.
        void sortDirector();
        void sortYear();
        void sortGenre();
        void sortStarring();
        void searchwords(string search_word, int k);
        int getlineelementnumber(string s);
        string getelement(int k);
        Movie();
};

class Music{    //Works like book and movie classes.
    private:
        string is_music="music";
        vector<string> title;
        vector<string> artists;
        vector<string> year;
        vector<string> genre;
        int TotalCount=0;
    public:
        const string get_check() const { return is_music; }
        const vector<string> &getTitle() const { return title; }
        const vector<string> &getArtists() const { return artists; }
        const vector<string> &getYear() const { return year; }
        const vector<string> &getGenre() const { return genre; }
        void sortTitle();
        void sortArtists();
        void sortYear();
        void sortGenre();
        void searchwords(string search_word, int k);
        int getlineelementnumber(string s);
        string getelement(int k);
        Music();
};

#endif
