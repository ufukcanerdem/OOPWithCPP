#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

bool is_number_valid( string _number ) {    //'is_number_valid function simply checks number and return boolean value
    int i,j;
    bool not_valid=false;                 //not_valid variable starts default as false. If any problem in number, it takes true value and returns.

    if( _number.length() > 9 ) {            //Checks the number length. If number length bigger than 9, not_valid variable takes true value.
        not_valid=true;
    }

    for( i=0 ; i<_number.length() ; i++ ) {     //This loop checks is there any repeating number.
        for( j=0 ; j<_number.length() ; j++ ) {
            if( i != j &&  _number[i] == _number[j] ) {     //If loop find same number, not_valid variable takes true value and breaks loop.
                not_valid=true;
                break;
            }
        }
        if( not_valid ) {     //This is just for the break the outer loop when not_valid is true.
            break;
        }
    }

    if( _number[0] == '0' ) {   //If is not there is any repeating number, this if statement checks is leftmost digit is 0 .
        not_valid=true;
    }

    if( _number[0] == '-') {
        cout << "E0" << endl;
        exit(0);
    } 

    for( i=0 ; i<_number.length() ; i++ ) {     //This loop checks is there any character without digist according to ASCII table.
        if( (int)_number[i] < 48 || (int)_number[i] > 57 ) {    //If there is any character without digits, it prints specific error message and exits.
            cout << "E2" << endl;   
            exit(0);
        }
    }

    return not_valid;
}

string create_random_number( int digitLeng ) {  //This function creates random numbers for '-r' parameter.
    int i,random_digit;                         //For better performance this function create number according to rules of game,it is just don't create random number
    bool isSame=false;                          //and send it to 'is_number_valid' function for check it.
    int randomNumberLeng=0;
    string randomNumber;
    
    random_digit = (rand() % 9) + 1 ;           //First digit creating in here out of the loop because to be sure it is not 0.
    randomNumber=to_string(random_digit);       //Then digit converted into string.
    randomNumberLeng++;

    while(digitLeng > 1 ) {                     //'digitleng' is lenght parameter. If user wants single digit number, loop passes.
        random_digit = (rand() % 10) ;          //Creats random digit between 0 to 9.
        for( i=0 ; i<randomNumberLeng ; i++ ) { //This loop checks the created random digit in the loop is repeating.
            if( random_digit == ( randomNumber[i] - '0' ) ) {   //If any repeating digit, 'isSame' variable takes true value.
                isSame=true;
            }
        }
        if( !isSame ) {                         //If there is any repeating digit, the created random digit is added to the number.
            randomNumber+=to_string(random_digit);
            randomNumberLeng++;
        }
        if( randomNumberLeng == digitLeng ) {   //This statement checks is random number reach to wanted lenght. If it reached, it breaks loop.
            break;
        }
        isSame=false;                           //'isSame' variable takes false value for the start of new loop.
    }
    return randomNumber;                        //After the loop, it returns created random number.
}

void guess_number( string _guess, string _answer ) {    //This function takes guess numbers from user and return hints and found or failed message.
    int i,j;
    static int iteration_count=0;                       //This static variable keeps iteration count.
    int c1=0;
    int c2=0;

    for( i=0 ; i<_answer.length() ; i++ ) {             //This loop checks the digits of the proposed number that match in place of the secret number(FirstCount).
        if( _guess[i] == _answer[i] ) {
            c1++;
        }
    }

    for( i=0 ; i<_answer.length() ; i++ ) {             //This loop just checks the secret number digits for all the guess number digits.(c2-c1 will gave us SecondCount).
        for( j=0 ; j<_answer.length() ; j++ ) {
            if( _guess[i] == _answer[j] ) {
                c2++;
            }
        }
    }
    
    iteration_count++;
    if( iteration_count >= 100 ) {                      //If iteration count reaches 100, it prints failed message and exits.
        cout << "FAILED" << endl;
        exit(0);
    }

    if( c1 == _answer.length() ) {                      //If firstcount and length of secred number are the same it prints found message and iteration count then exits.
        cout << "FOUND " << iteration_count << endl;
        exit(0);
    }
    else{                                               //Else it prints hint(c2-c1 is exactly gave us secondcount).
        cout << c1 << " " << c2-c1 << endl;
    }
    
}

int main(int argc,char **argv) {
    if( argc != 3 ) {                                    //It checks is there any argument more or less than 3.
        cout << "E0" << endl;
        exit(0);
    }
    
    string u_or_r=argv[1];
    string guessNumber;
    string str_u = "-u";
    string str_r = "-r";
    srand (time(NULL));
    
    if( str_u.compare(u_or_r) == 0 ) {              //Checks argv[1] which is 'u_or_r' is '-u'.
        string answer=argv[2];                      //'answer' variable keeps argv[2] which is user secred number.
        int i;
        for( i=0 ; i<answer.length() ; i++ ) {     		    		    //This loop checks is there any character without digist according to ASCII table.
            if( (int)answer[i]< 48 || (int)answer[i] > 57 ) {       //If there is any character without digits, it prints specific error message and exits.
        	    cout << "E0" << endl;   
        	    exit(0);
        	}
        }
        if( !is_number_valid(answer) ) {            //This statement just checks the secred number the user entered.
            while(1) {                              
                cin >> guessNumber;
                if( guessNumber.length() != answer.length() ) {     //This statement compare the lengths of input number and secred number.
                    cout << "E1" << endl;
                    exit(0);
                }
                if( !is_number_valid(guessNumber) ) {               //This statement sends the input number to 'is_number_valid' function.
                    guess_number( guessNumber,answer );             //If number is valid then it's sending to 'guess_number' function.
                }
                else{                                               //If guess number is not valid error message prints and exits.
                    cout << "E1" << endl;
                    exit(0);
                }
            }
        }
        else{                                                       //If secred number which is user entered is not valid error message prints and exits.
            cout << "E0" << endl;
            exit(0);
        }
    }

    else if( str_r.compare(u_or_r) == 0 ) {                         //Checks argv[1] which is 'u_or_r' is '-r'.
	string temp_argv2=argv[2];
	int i;
    if( temp_argv2[0] == '-' || temp_argv2[0] == '0' ) {
        cout << "E0" << endl;
        exit(0);
    }
	for( i=0 ; i<temp_argv2.length() ; i++ ) {     		    		    //This loop checks is there any character without digist according to ASCII table.
        if( (int)temp_argv2[i]< 48 || (int)temp_argv2[i] > 57 ) {       //If there is any character without digits, it prints specific error message and exits.
        	cout << "E0" << endl;   
        	exit(0);
        	}
    }
        if( is_number_valid(temp_argv2) ) {
            cout << "E0" << endl;
            exit(0);
        }
        int digit_leng=stoi(argv[2]);                               //It converts the length argument to integer. 
        if( digit_leng < 1 || digit_leng > 9 ) {                    //If length smaller than one or bigger than nine, it prints error message and exits.
            cout << "E0" << endl;
            exit(0);
        }
        string answer = create_random_number(digit_leng);           //'answer' variable keeps randomly generated secred number.
        
        if( !is_number_valid(answer) ) {                            //It checks is created random number is valid (Random secred number is also created according to the rules. It is just to be sure).
            while(1) {                                              //Infinite loop starts until the game finish.
                cin >> guessNumber;
                if( !is_number_valid(guessNumber) && guessNumber.length() == answer.length() ) { //This statement sends the input number to 'is_number_valid' function and compare lengths of input number and secred number.
                    guess_number( guessNumber,answer );             //If number is valid then it's sending to 'guess_number' function.
                }
                else{                                               //If guess number is not valid error message prints and exits.
                    cout << "E1" << endl;
                    exit(0);
                }
            }
        }
        else{                                                       //If the created secred is not valid it prints error message and exits but most likely the created
            cout << "E1" << endl;                                   //secred number will always be valid.
            exit(0);
        }
    }

    else {                                                          //If argv[1] is not '-u' or '-r' it prints error message and exits.
        cout << "E0" << endl;
        exit(0);
    }
    return 0;
}
