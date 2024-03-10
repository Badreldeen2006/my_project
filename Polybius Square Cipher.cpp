#include <iostream>
#include <string>
#include <cctype>
using namespace std ;

char matrix[6][6];
void do_matrix() {
    // first element (( not important ))
    matrix[0][0] = '0';
    while (true){
        cout << " Enter your key : ";
        string key = "";
        string fixed_key = "" ;
        cin >> key;                                         // to ignore any input not digit
        for ( char check : key ){
            if ( isdigit( check )){
                fixed_key += check ;
            }
        }
        // to make sure the key length is equal to 5
        if ( fixed_key.size() != 5 ){
            cout << "(( Enter a valid key *size* ))" << endl ;
            continue ;
        }
        // to check if key digits is between 1 ~ 5 or not
        int int_key_digt [ 5 ] ;
        bool end_while_1 = true ;
        for ( int i = 0 ; i < fixed_key.size() ; i ++ ){
            int_key_digt [i] = int ( fixed_key[i] ) - 48  ;
            if ( int_key_digt [i] > 5 || int_key_digt [i] < 1 ){
                cout << " (( Enter a valid key *range* ))" << endl ;
                end_while_1 = false ;
                break;
            }
        }
        bool end_while_2 = true ;
        for ( int i = 0 ; i < 5 ; i ++ ){
            if ( int_key_digt[i] == int_key_digt[i+1] ){
                cout << " (( Enter a valid key *contain all dgts 1 ~ 5* ))" << endl ;
                end_while_2 = false ;
                break;
            }
        }

        if ( end_while_1 == true && end_while_2 == true ) {
            // to fill the key in the matrix
            int dig_key = 0;
            for (int i = 1; i <= 5; i++) {
                matrix[0][i] = matrix[i][0] = fixed_key[dig_key];
                dig_key++;
            }
            //  fill the alphabet letters
            int ascii = 0;
            for (int i = 1; i <= 5; i++) {
                for (int j = 1; j <= 5; j++) {
                    matrix[i][j] = char(65 + ascii);
                    if (matrix[i][j] == 'J') {
                        ascii++;
                        matrix[i][j] = char(65 + ascii);

                    }
                    ascii++;
                }
            }
            cout << "The fixed key is : " << fixed_key << endl ;                 // to check the key
            break;
        }
        else{
            continue ;}
    }
}

void cipher_Polybius() {
    while (true){
        cout << "Enter the message :- " << endl;
        string message;
        string fixed_message;
        getline(cin, message);
        for (char check: message) {
            check = toupper(check);
            if (check == 'J') {         //  convert the J letter to I
                check = 'I';
            }
            if (isalpha(check)) {               // fill the fixed message
                fixed_message += check;
            }
        }

        if ( fixed_message == "" ){
            cout << "((Please Enter a valid message *letters* )) " << endl ;
            continue ;
        }
        else {
            cout << "The fixed message is : " << fixed_message << endl ;
            do_matrix() ;
            int len = fixed_message.size() ;
            string cipher_message = "" ;
            string  cipher_unit  = "" ;

            for ( int i = 0 ; i < len ; i ++ ) {                // to check all digit in the message
                for (int row = 1; row < 6; row++) {             // to check current digit in the message if in the current row or not
                    for (int col = 1; col < 6; col++) {         // to check current digit in the message if in the current row and col or not
                        if (fixed_message[i] == matrix[row][col]) {
                            cipher_unit = matrix[row][0] ;
                            cipher_unit += matrix[0][col];
                            cipher_message += cipher_unit + " ";
                        }
                    }
                }
            }
            cout << "The ciphered message is : " << cipher_message << endl;
        }
        break;
    }
}

void decipher_Polybius() {
    while (true) {
        cout << " Enter the message : -" << endl;
        string message = "";
        string fixed_message = "";
        getline(cin, message);

        for (char check: message) {                   // to fix the message and ignore any input not digit
            if (isdigit(check)) {
                fixed_message += check;
            }
        }

        if ( fixed_message == "" ) {
            cout << "((Please Enter a valid message *integrs* )) " << endl;
            continue;
        }

        if (fixed_message.size() % 2 != 0) {                          // to make sure the message digits is even number
            cout << " (( Please the number of message digits must be even )) " << endl ;
            continue;
        }

        else{
            cout << "The fixed message is : " << fixed_message <<endl ;
            do_matrix();
            int len = fixed_message.size();
            string rows;
            string cols;
            for (int i = 0; i < len; i += 2) {
                rows += fixed_message[i];
                cols += fixed_message[i + 1];
            }

            int row_digts[len / 2];
            for (int i = 0; i < (len / 2); i++) {
                for (int j = 0; j <= 5; j++) {            // j is equal to  matrix[i][0] that is the key
                    if (rows[i] == matrix[j][0]) {
                        row_digts[i] = j;                        // to store the digit of the key that represent element in message
                        break;
                    }
                }
            }

            int col_digts[len / 2];
            for (int i = 0; i < (len / 2); i++) {
                for (int j = 0; j <= 5; j++) {            // j is equal to  matrix[0][i] that is the key
                    if (cols[i] == matrix[0][j]) {
                        col_digts[i] = j;                        // to store the digit of the key that represent element in message
                        break;
                    }
                }
            }

            string dichphered_unit = "";
            string dichphered_message = "";
            for (int i = 0; i < (len / 2); i++) {
                dichphered_unit = matrix[row_digts[i]][col_digts[i]];
                dichphered_message += dichphered_unit;
            }
            cout << " Dichphered message is : " << dichphered_message << endl;
            break ;
        }
        break;
    }
}

int main() {
    while (true) {
        cout << "=====================================================\n"
                "Ahlan ya user ya habibi.\n"
                "What do you like to do today ?\n"
                "1- Cipher a message\n"
                "2- Decipher a message\n"
                "3- End\n";
        char input;
        cin >> input;
        cin.ignore();
        if (input == '1') {
            cipher_Polybius();
        } else if (input == '2') {
            decipher_Polybius();
        } else if (input == '3') {
            return 0;
        } else {
            cout << " (( enter a valid input )) " << endl ;
            continue;
        }
    }
    return 0;
}