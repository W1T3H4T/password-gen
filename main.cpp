//  File    :   password-gen.cc
//  Function:   Generate one or more passwords
//  Caveats :   This application does not use a secure random number generator for
//          :   production of random characters.
//  Authors :   Hritik Raj, on June 21, 2018
//          :       https://www.includehelp.com/cpp-programs/generate-random-password.aspx
//          :   (c) 2021 David C. Means
//          :       https://www.W1T3H4T.com 
//  ===========================================================================
// The MIT License (MIT)
//
//  Copyright © 2021 David Means <w1t3h4t@gmail.com>
//
//  Permission is hereby granted, free of charge, to any person obtaining
//  a copy of this software and associated documentation files 
//  (the “Software”), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish, 
//  distribute, sublicense, and/or sell copies of the Software, and to permit 
//  persons to whom the Software is furnished to do so, subject to the following 
//  conditions:
//
//  The above copyright notice and this permission notice shall be included in all 
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//  ===========================================================================
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

static bool isSeeded = false;
bool autoGen = false;
int  autoGenCount = 0;
string password;

void seedRandom()
{
    if ( !isSeeded ) { 
        isSeeded = true;
        srand((unsigned int) time(NULL));
    }
}  

//selectArray is  a utility function that is used to
//randomly generate a integer in the range 1 to 4 (both inclusive)
int selectArray()
{
    seedRandom();
    int i = rand() % 5;
    if (i == 0)
        i++;
    return i;
}

//getKey() is another utility function that is used to randomly generate
//an integer in the range 0 to 25 (both inclusive)
int getKey()
{
    seedRandom();

    int key = rand() % 26;
    return key;
}

void generate_password(int length)
{
    if ( autoGen == true ) { 
        autoGenCount++;
    }
    
    //Intializing result string password as NULL.
    password.clear();

    //Strings whose characters will be used to build password
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string s_symbol = "!@#$%&";
    string number = "0123456789";

    //initializing local variables
    int key, count_alphabet = 0, count_ALPHABET = 0, count_number = 0, count_s_symbol = 0;

    //Count will store the length of the password being created,
    //initially this will be zero(0)
    int count = 0;
    while (count < length) {
        // selectArray() function will return a number 1 to 4
        // and will use to select one of the above defined string
        //(i.e alphabet or ALPHABET or s_symbol or number )
        // 1 is for string alphabet
        // 2 is for string ALPHABET
        // 3 is for string number
        // and 4 is for string s_symbol

        int k = selectArray();

        //for the first character of password it is mentioned that,
        //it should be a letter
        //so the string that should be selected is either alphabet or 
        //ALPHABET (i.e 1 or 2)
        //following if condition will take care of it.
        if (count == 0) {
            k = k % 3;
            if (k == 0)
                k++;
        }
        switch (k) {
        case 1:
            // following if condition will check if minimum requirement of alphabet
            // character has been fulfilled or not
            // in case it has been fulfilled and minimum requirements of other
            // characters is still left then it will break ;
            if ((count_alphabet == 2) && (count_number == 0 || count_ALPHABET == 0 || count_ALPHABET == 1 || count_s_symbol == 0))
                break;

            key = getKey();
            password += (const char) alphabet[key];
            count_alphabet++;
            count++;
            break;

        case 2:
            // following if condition will check if minimum requirement of
            // ALPHABET character has been fulfilled or not
            // in case it has been fulfilled and minimum requirements of
            // other characters is still left then it will break ;
            if ((count_ALPHABET == 2) && (count_number == 0 || count_alphabet == 0 || count_alphabet == 1 || count_s_symbol == 0))
                break;
            key = getKey();
            password += (const char) ALPHABET[key];
            count_ALPHABET++;
            count++;
            break;

        case 3:
            // following if condition will check if minimum requirement
            // of Numbers  has been fulfilled or not
            // in case it has been fulfilled and minimum requirements of
            // other characters is still left then it will break ;
            if ((count_number == 1) && (count_alphabet == 0 || count_alphabet == 1 || count_ALPHABET == 1 || count_ALPHABET == 0 || count_s_symbol == 0))
                break;

            key = getKey();
            key = key % 10;
            password += (const char) number[key];
            count_number++;
            count++;
            break;

        case 4:
            // following if condition will check if minimum requirement of
            // Special symbol character has been fulfilled or not
            // in case it has been fulfilled and minimum requirements of
            // other characters is still left then it will break ;
            if ((count_s_symbol == 1) && (count_alphabet == 0 || count_alphabet == 1 || count_ALPHABET == 0 || count_ALPHABET == 1 || count_number == 0))
                break;

            key = getKey();
            key = key % 6;
            password += (const char) s_symbol[key];
            count_s_symbol++;
            count++;
            break;
        }
    }

    if ( autoGen == false  ) { 
        cout << "\n-----------------------------\n";
        cout << "         Password             \n";
        cout << "------------------------------\n\n";

    }
    else { 
        cout << autoGenCount << ") ";
    }

    cout << " " << password << endl;

    if ( autoGen == false  ) { 
        cout << "\nPress any key continue \n";
        getchar();
    }
}

//  -------------------------
//  MAIN is here
//  -------------------------
int main(int argc, char** argv)
{
    int opt, length, count;
    opt = length = count = 0;

    // If we have cmd line arguments, then
    // create passwords automagically

    if ( argc >= 2 && argc <= 3 ) {
        autoGen = true;

        length = atoi(argv[1]);

        if ( argc == 3 ) 
            count = atoi(argv[2]);
        else 
            count = 1;
               
        while (  count > 0 ) {
            generate_password( length );
            --count;
        }
        return 0;
    }

    //  Otherwise, present the menu
    do {
        cout << "\n-----------------------------\n";
        cout << "  Random Password Generator\n";
        cout << "------------------------------\n\n";
        cout << "    1. Generate Password"
             << "\n";
        cout << "    2. Exit"
             << "\n\n";
        cout << "Press key 1 to Generate Password and key 2 to exit  : ";
        cin >> opt;

        switch (opt) {
        case 1:
            cout << "Enter Length :  ";
            cin >> length;
            //if length is less than 7 , program  will show error
            if (length < 7) {
                cout << "\nError : Password Length Should be atleast 7\n";
                cout << "Press any key to try again \n";
                getchar();
            }
            // Length should not exceed 100 , program should show error if it exceeds
            else if (length > 100) {
                cout << "\nError : Maximum length of password should be 100\n";
                cout << "Press any key to try again \n";
                getchar();
            }
            //Otherwise call generate_password() function to generate password
            else
                generate_password(length);
            break;

        default:
            // If invalid option is chosen by user it will also show error
            if (opt != 2) {
                printf("\nInvalid choice\n");
                printf("Please Press ( 1 ) to generate password and ( 2 ) to exit.\n");
                cout << "Press any key to try again \n";
                getchar();
            }
            break;
        }
    } while (opt != 2);

    if ( autoGen == false  ) { 
        cerr << endl << "Usage: " << argv[0] << " [ length ] [ count ]" << endl << endl << endl;
    }

    return 0;
}

