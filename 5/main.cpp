/*
UFUKCAN
ERDEM
1901042686
*/


#include <iostream>
#include <sstream>
#include"helper.h"

using namespace std;

int find_datatxt_type();                //Returns catalog name of data.txt
void read_commands_book(Book<string>*); //Gets pointer for book class. Create object for book pointer and reads commands.txt and do things according to commands.txt
void read_commands_music(Music*);       //Gets pointer for music class. Create object for music pointer and reads commands.txt and do things according to commands.txt
void read_commands_movie(Movie*);       //Gets pointer for movie class. Create object for movie pointer and reads commands.txt and do things according to commands.txt
int getquotesnumber(string s);          //Returns quotes mark count for any string


int main() {

    int _type = find_datatxt_type();    //For identify to which catalog

    Book<string> *ptr_book;
    Music *ptr_music;
    Movie *ptr_movie;

    if( _type == 0 ) {
        ptr_book = new Book<string>;
        read_commands_book(ptr_book);
        delete ptr_book;
    }

    else if( _type == 1 ) {
        ptr_music = new Music;
        read_commands_music(ptr_music);
        delete ptr_music;
    }

    else if( _type == 2 ) {
        ptr_movie = new Movie;
        read_commands_movie(ptr_movie);
        delete ptr_movie;
    }

    return 0;
}

int find_datatxt_type() {
    ifstream file("data.txt");
    char x;
    string temp="";
    for(int i=0 ; i<3 ; i++ ) {
        file >> x;
        temp+=x;
    }
    if( temp == "boo" ) { return 0;}
    else if( temp == "mus" ) { return 1;}
    else if( temp == "mov" ) { return 2;}
    else{ return 99;}
}

int getquotesnumber(string s) {
    string::size_type pos = s.find("\"");
    stringstream  stream(s);
    string        word;
    int count2 = 0;

    while(stream >> word) { 
        count2++;
    }

    int count=0;
    while (pos != string::npos) {
        count++;
        pos = s.find("\"", pos + 1);
    }
    return count*count2;
}

void read_commands_book(Book<string> *ptr) {
    ifstream _cmd("commands.txt");

    int j=0;
    int k=0;
    string line;
    string temp="";
    vector<string> temp_commands;   //Holds lines of commands.txt
    vector<string> throwed_commands;    //Holds throwed commands
    int is_command_correct;
    
    string::size_type found_seach;
    string::size_type found_sort;
    bool find_search=false;
    bool find_sort=false;
    string search_word;

    while(getline(_cmd, line)) {
        temp_commands.push_back(line);
    }
    for( int i=0 ; i<temp_commands.size() ; i++ ) {

        found_seach = temp_commands[i].find("search");  //Look in the line for is there search word.
        if (found_seach != string::npos ) {
            find_search=true;
        }
        
        found_sort = temp_commands[i].find("sort");     //Look in the line for is there sort word.
        if (found_sort != string::npos ) {
            find_sort=true;
        }
        is_command_correct=getquotesnumber(temp_commands[i]);
    try{
        if( find_search ) {             //If line has search word statement works.
            j=0;
            temp.clear();
            while( j != temp_commands[i].size()-1 && is_command_correct == 16) {   //Reads and holds the search word and field.
                if( temp_commands[i][j] == '\"') {
                    while(1) {
                        j++;
                            if( temp_commands[i][j] == '\"') {
                                break;
                            }
                    temp+=temp_commands[i][j];
                    }
                }
                if( temp != "" ) {
                    if( k==0 ) {
                        search_word=temp;
                        k++;
                    }
                    else if( k==1 ) {   //According to the field sends search word to function.
                        if( temp == "title" ) { ptr->searchwords(search_word,0); k++; }
                        else if( temp == "authors" ) { ptr->searchwords(search_word,1); k++; }
                        else if( temp == "year" ) { ptr->searchwords(search_word,2); k++; }
                        else if( temp == "tags" ) { ptr->searchwords(search_word,3); k++; }
                        else {      //Throws line of command if field name is unknown.
                            throw(temp_commands[i]);
                            break;
                        }
                    }
                    else if( k==2 ) {
                        break;
                    }
                }
                temp.clear();
                j++;
            }
            if( is_command_correct != 16 ) {        //Throws line of command if there is more than 4 word and 4 quotes.
                throw(temp_commands[i]);
            }
        }
    }
    catch(string x){            //Prints error message to output.txt
        int ch=0;
        bool _ch=false;
        while(ch != throwed_commands.size()) {
            if(throwed_commands[ch] == x ) {
                _ch=true;
            }
            ch++;
        }
        if(!_ch) {
            ofstream _out("output.txt", std::ios_base::app);
            _out << "Exception: command is wrong" << endl;
            _out << x << endl;
            _out.close();
        }
    }

    k=0;
    
    try{
        if( find_sort ) {       //If line has sort word statement works.
            j=0;
            temp.clear();
            while( j != temp_commands[i].size()-1 && is_command_correct == 4) {   //Read and holds the field name.
                if( temp_commands[i][j] == '\"') {
                    while(1) {
                        j++;
                            if( temp_commands[i][j] == '\"') {
                                break;
                            }
                    temp+=temp_commands[i][j];
                    }
                }
                if( temp != "" && k==0 ) {      //According to the field name sends to related function.
                    if( temp == "title") { ptr->sortTitle(); k++; }
                    else if( temp == "authors") { ptr->sortAuthors(); k++; }
                    else if( temp == "year") { ptr->sortYear(); k++; }
                    else if( temp == "tags") { ptr->sortTags(); k++; }
                    else {      //Throws line of command if field name is unknown.
                            throw(temp_commands[i]);
                            break;
                        }
                }
                else if (k==1) {
                    break;
                }
                temp.clear();
                j++;
            }
            if( is_command_correct != 4 ) {        //Throws line of command if there is more than 4 word and 4 quotes.
                throw(temp_commands[i]);
            }
        }
    }
    catch(string x){            //Prints error message to output.txt
        int ch=0;
        bool _ch=false;
        while(ch != throwed_commands.size()) {
            if(throwed_commands[ch] == x ) {
                _ch=true;
            }
            ch++;
        }
        if(!_ch) {
            ofstream _out("output.txt", std::ios_base::app);
            _out << "Exception: command is wrong" << endl;
            _out << x << endl;
            _out.close();
        }
    }    
        k=0;
        temp.clear();
        find_search=false;
        find_sort=false;
    }

    _cmd.close();
}

void read_commands_music(Music *ptr) {  //Works like read_commands_book function.
    ifstream _cmd("commands.txt");
    
    int j=0;
    int k=0;
    string line;
    string temp="";
    vector<string> temp_commands;
    vector<string> throwed_commands;
    int is_command_correct;
    
    string::size_type found_seach;
    string::size_type found_sort;
    bool find_search=false;
    bool find_sort=false;
    string search_word;

    while(getline(_cmd, line)) {
        temp_commands.push_back(line);
    }
    for( int i=0 ; i<temp_commands.size() ; i++ ) {

        found_seach = temp_commands[i].find("search");
        if (found_seach != string::npos) {
            find_search=true;
        }
        
        found_sort = temp_commands[i].find("sort");
        if (found_sort != string::npos) {
            find_sort=true;
        }
        is_command_correct=getquotesnumber(temp_commands[i]);
    try{
        if( find_search ) {
            j=0;
            temp.clear();
            while( j != temp_commands[i].size()-1 && is_command_correct == 16) {
                if( temp_commands[i][j] == '\"') {
                    while(1) {
                        j++;
                            if( temp_commands[i][j] == '\"') {
                                break;
                            }
                    temp+=temp_commands[i][j];
                    }
                }
                if( temp != "" ) {
                    if( k==0 ) {
                        search_word=temp;
                        k++;
                    }
                    else if( k==1 ) {
                        if( temp == "title" ) { ptr->searchwords(search_word,0); k++; }
                        else if( temp == "artists" ) { ptr->searchwords(search_word,1); k++; }
                        else if( temp == "year" ) { ptr->searchwords(search_word,2); k++; }
                        else if( temp == "genre" ) { ptr->searchwords(search_word,3); k++; }
                        else {      //Throws line of command if field name is unknown.
                            throw(temp_commands[i]);
                            break;
                        }
                    }
                    else if( k==2 ) {
                        break;
                    }
                }
                temp.clear();
                j++;
            }
            if( is_command_correct != 16 ) {        //Throws line of command if there is more than 4 word and 4 quotes.
                throw(temp_commands[i]);
            } 
        }
    }
    catch(string x){            //Prints error message to output.txt
        int ch=0;
        bool _ch=false;
        while(ch != throwed_commands.size()) {
            if(throwed_commands[ch] == x ) {
                _ch=true;
            }
            ch++;
        }
        if(!_ch) {
            ofstream _out("output.txt", std::ios_base::app);
            _out << "Exception: command is wrong" << endl;
            _out << x << endl;
            _out.close();
        }
    }

        k=0;
    try{
        if( find_sort ) {
            j=0;
            temp.clear();
            while( j != temp_commands[i].size()-1 && is_command_correct == 4) {
                if( temp_commands[i][j] == '\"') {
                    while(1) {
                        j++;
                            if( temp_commands[i][j] == '\"') {
                                break;
                            }
                    temp+=temp_commands[i][j];
                    }
                }
                if( temp != "" && k==0 ) {
                    if( temp == "title") { ptr->sortTitle(); k++; }
                    else if( temp == "artists") { ptr->sortArtists(); k++; }
                    else if( temp == "year") { ptr->sortYear(); k++; }
                    else if( temp == "genre") { ptr->sortGenre(); k++; }
                    else {      //Throws line of command if field name is unknown.
                            throw(temp_commands[i]);
                            break;
                        }  
                }
                else if (k==1) {
                    break;
                }
                temp.clear();
                j++;
            }
            if( is_command_correct != 4 ) {        //Throws line of command if there is more than 4 word and 4 quotes.
                throw(temp_commands[i]);
            }
        }
    }
    catch(string x){            //Prints error message to output.txt
        int ch=0;
        bool _ch=false;
        while(ch != throwed_commands.size()) {
            if(throwed_commands[ch] == x ) {
                _ch=true;
            }
            ch++;
        }
        if(!_ch) {
            ofstream _out("output.txt", std::ios_base::app);
            _out << "Exception: command is wrong" << endl;
            _out << x << endl;
            _out.close();
        }
    }    
        k=0;
        temp.clear();
        find_search=false;
        find_sort=false;
    }

    _cmd.close();
}

void read_commands_movie(Movie *ptr) {  //Works like read_commands_book function.
    ifstream _cmd("commands.txt");
    
    int j=0;
    int k=0;
    string line;
    string temp="";
    vector<string> temp_commands;
    vector<string> throwed_commands;
    int is_command_correct;
    
    string::size_type found_seach;
    string::size_type found_sort;
    bool find_search=false;
    bool find_sort=false;
    string search_word;

    while(getline(_cmd, line)) {
        temp_commands.push_back(line);
    }
    for( int i=0 ; i<temp_commands.size() ; i++ ) {

        found_seach = temp_commands[i].find("search");
        if (found_seach != string::npos) {
            find_search=true;
        }
        
        found_sort = temp_commands[i].find("sort");
        if (found_sort != string::npos) {
            find_sort=true;
        }
        is_command_correct=getquotesnumber(temp_commands[i]);
    try{
        if( find_search ) {
            j=0;
            temp.clear();
            while( j != temp_commands[i-1].size()-1 && is_command_correct == 16) {
                if( temp_commands[i][j] == '\"') {
                    while(1) {
                        j++;
                            if( temp_commands[i][j] == '\"') {
                                break;
                            }
                    temp+=temp_commands[i][j];
                    }
                }
                if( temp != "" ) {
                    if( k==0 ) {
                        search_word=temp;
                        k++;
                    }
                    else if( k==1 ) {
                        if( temp == "title" ) { ptr->searchwords(search_word,0); k++; }
                        else if( temp == "director" ) { ptr->searchwords(search_word,1); k++; }
                        else if( temp == "year" ) { ptr->searchwords(search_word,2); k++; }
                        else if( temp == "genre" ) { ptr->searchwords(search_word,3); k++; }
                        else if( temp == "starring" ) { ptr->searchwords(search_word,4); k++; }
                        else {      //Throws line of command if field name is unknown.
                            throw(temp_commands[i]);
                            break;
                        }
                    }
                    else if( k==2 ) {
                        break;
                    }
                }
                temp.clear();
                j++;
            }
            if( is_command_correct != 16 ) {        //Throws line of command if there is more than 4 word and 4 quotes.
                throw(temp_commands[i]);
            } 
        }
    }
    catch(string x){            //Prints error message to output.txt
        int ch=0;
        bool _ch=false;
        while(ch != throwed_commands.size()) {
            if(throwed_commands[ch] == x ) {
                _ch=true;
            }
            ch++;
        }
        if(!_ch) {
            ofstream _out("output.txt", std::ios_base::app);
            _out << "Exception: command is wrong" << endl;
            _out << x << endl;
            _out.close();
        }
    }
        k=0;
    try{
        if( find_sort ) {
            j=0;
            temp.clear();
            while( j != temp_commands[i].size()-1 && is_command_correct == 4 ) {
                if( temp_commands[i][j] == '\"') {
                    while(1) {
                        j++;
                            if( temp_commands[i][j] == '\"') {
                                break;
                            }
                    temp+=temp_commands[i][j];
                    }
                }
                if( !temp.empty() && k==0 ) {
                    if( temp == "title") { ptr->sortTitle(); k++;}
                    else if( temp == "director") { ptr->sortStarring(); k++; }
                    else if( temp == "year") { ptr->sortYear(); k++; }
                    else if( temp == "genre") { ptr->sortGenre(); k++; }
                    else if( temp == "starring") { ptr->sortStarring(); k++; }
                    else {      //Throws line of command if field name is unknown.
                            throw(temp_commands[i]);
                            break;
                        }
                }
                else if (k==1) {
                    break;
                }
                temp.clear();
                j++;
            }
            if( is_command_correct != 4 ) {        //Throws line of command if there is more than 4 word and 4 quotes.
                throw(temp_commands[i]);
            }
        }
    }
    catch(string x){            //Prints error message to output.txt
        int ch=0;
        bool _ch=false;
        while(ch != throwed_commands.size()) {
            if(throwed_commands[ch] == x ) {
                _ch=true;
            }
            ch++;
        }
        if(!_ch) {
            ofstream _out("output.txt", std::ios_base::app);
            _out << "Exception: command is wrong" << endl;
            _out << x << endl;
            _out.close();
        }
    }
        k=0;
        temp.clear();
        find_search=false;
        find_sort=false;
    }

    _cmd.close();
}