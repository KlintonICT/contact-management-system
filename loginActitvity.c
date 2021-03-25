#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "header.h"

/// A String for storing asterisks as part to conceal the actual keystroke of the user
char passwordAsterisk[60];
char userTemp_password[60];

/// This is a String variable for storing string of ID.
/// So why ID is stored as String? Because it has to be processed. (Checking for alphabets)
char userTemp_inputId[7];
int userTemp_id;        /// userTemp_id is an ID Integer, after checking through checkID() and get no error.

struct contact personnel[50];

/** \brief Compares two strings
 *
 * \param String one
 * \param String two
 * \return 0 if the strings are identical, otherwise return 1.
 */
int compare2Strings(char stringA[], char stringB[]){
   int count = 0;

   while(stringA[count] == stringB[count]) {
      if (stringA[count] == '\0' || stringB[count] == '\0')
         break;
      count++;
   }

   if(stringA[count] == '\0' && stringB[count] == '\0'){
        /** If the string is identical **/
        return 0;
   }else{
       /** If the string is NOT identical **/
        return -1;
   }
}

/** \brief Verifies user log in data by checking for ID first. If it is exists in database, check for its Password.
 *
 * \param User's ID
 * \param User's Password
 * \return 0 If there is no error.
 * \return -1 If there is an error.
 */
int loginVerificator(int Temp_id, char Temp_password[]){

    selectionSortByID_Ascending();

    int index, countError = 0;

    // If there is no registered user in the DATABASE
    if(TOTAL_NUMBER_ofPersonnel == 0){
        countError++;
    }

    // Search through ALL ENTRY IN DATABASE
    for(index = 0; index < TOTAL_NUMBER_ofPersonnel; index++){
        // If it found a matched ID
        if(personnel[index]._id == Temp_id){
            // If user password and the password of matched ID is actually identical
            if(compare2Strings(personnel[index].password, Temp_password) == 0){
                // Get session login id for referencing
                session_Login_id = index;
                temporarySessionID = index;

                // These variables store temporary login data.
                temporaryID = personnel[index]._id;
                strcpy(temporaryFirstName, personnel[index].firstName);
                strcpy(temporaryLastName, personnel[index].lastName);
                strcpy(temporaryEmail, personnel[index].email);
                //extern char temporaryLastName[30];
                // Get user to Profile Menu
                break;
            }else{
                countError++;
                break;
            }
        }
    }

    // If there is an error OR there is no match for ID
    if(countError == 0){
        /** If there is no error **/
        return 0;
    }
    /** If there is an error **/
    return -1;
}

/**
 *  \brief Hides USER INPUT password with asterisks!
 */
void takeInputPassword(){
	char c = ' ';
	int index = 0, countAster = 0, countBackSpace = 0;
	while(index < 60){
	    userTemp_password[index] = getch();
	    c = userTemp_password[index];

	    // c = 13 is the Value for Enter
	    if(c == 13){
	    	break;
		}else if(c == 8){
            // BACKSPACE
            userTemp_password[index] = '\0';
            index--;

            system("cls");
            print_LoginActivityHeader();
            printf("\n\t\t\t  * ID\n\t\t\t\t-->> ");
            printf("%07d\n", userTemp_id);
            printf("\n\t\t\t  * PASSWORD\n\t\t\t\t-->> ");

            countBackSpace++;
            passwordAsterisk[index] = '\0';
            for(index = 0; index < countAster - countBackSpace; index++){
                printf("%c", passwordAsterisk[index]);
            }
        }else{
	    	printf("*");
	    	passwordAsterisk[index] = '*';
	    	countAster++;
	    	index++;
		}
	}
	if(countBackSpace > 0){
        userTemp_password[countAster - countBackSpace] = '\0';
	}else{
	    userTemp_password[index] = '\0';
	}
	index = 0;
}

/**
 *  \brief The header for LOG IN SCREEN
 */
void print_LoginActivityHeader(){
    printf("\n\n\n\n\t\t=========================================================================================================\n\n");
    printf("\t\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ LOGIN\n");
    printf("\n\t\t=========================================================================================================\n\n");
    printf("\t\t\t-------------------------------------------------------------------------\n\t\t\t|\t\t\t\t\t\t\t\t\t|");
    printf("\n\t\t\t|\t(*) LOGIN\t\t\t\t\t\t\t|\n\t\t\t|\t- for A REGISTERED USER who want to use this program\t\t|\n");
    printf("\t\t\t|\t\t\t\t\t\t\t\t\t|\n\t\t\t-------------------------------------------------------------------------\n");
}

/**
 *  \brief The main activity for LOG IN SCREEN
 */
void loginActivity(){
    system("cls");

    int selection = 1;

    print_LoginActivityHeader();

    reEnterForm:
    // Prompt user to enter ID first
    printf("\n\t\t\t\t  * ID\n\t\t\t\t\t-->> ");
    scanf(" %[^\t\n]s", &userTemp_inputId);
    if(checkID(userTemp_inputId) != 0){
        printf("\n\t\t\t\t\t  \a*** INVALID ID: Make sure it is your 7-digits ID. ***");
        printf("\n\t\t\t\t\t  --> Please to re-enter your ID again\n");
        goto reEnterForm;
    }else{
        // If there is nothing wrong in input ID then store it as an INTEGER!
        userTemp_id = stringToInteger(userTemp_inputId);
    }

    // Prompt user to enter Password
    printf("\n\t\t\t\t  * PASSWORD\n\t\t\t\t\t-->> ");
    takeInputPassword();

    // Print Selection Menu
    printf("\n\n\t\t\t\t[*] CONTINUE\t\t[ ] CANCEL\t\t[ ] CLEAR\n");
    printf("\n\t\t=========================================================================================================\n");
    printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");

    while(1){
        switch(getch()){
            case 'A':
            case 'a':
                // code for arrow right
                selection--;
                if(selection < 1){
                    selection = 1;
                }
                break;
            case 'D':
            case 'd':
                // code for arrow left
                selection++;
                if(selection > 3){
                    selection = 3;
                }
                break;
            case 13:
                switch(selection){
                    case 1:
                        if(loginVerificator(userTemp_id, userTemp_password) == 0 && session_Login_id != -1){
                            // Loading Message
                            system("cls");
                            printf("\n\n\n\n\n\t\t\t\t\tLoading...");
                            printf("\n\n\n\n\n\t\t\t\t\t");
                            //system("pause");
                            // If there is no error, login.
                            welcomeActivity();
                        }else{
                            // If "CONTINUE" is selected then we verify it.
                            // If there is something wrong we tell the user and ask the user to re-enter it
                            system("cls");
                            print_LoginActivityHeader();
                            printf("\n\t\t\t\t\t  \a*** INVALID ID or PASSWORD: Make sure it is your 7-digits ID. ***");
                            printf("\n\t\t\t\t\t  --> Please to re-enter your Information again\n");
                            goto reEnterForm;
                        }
                        break;
                    case 2:
                        // If "CANCEL" is selected then return to Main menu.
                        system("cls");
                        main();
                        break;
                    case 3:
                        // If "CLEAR" is selected then CLEAR the entire form.
                        system("cls");
                        loginActivity();
                        break;
                }
                break;
            default:
                selection = 1;
        }
        system("cls");

        print_LoginActivityHeader();
        printf("\n\t\t\t\t  * ID\n\t\t\t\t\t-->> ");
        printf("%07d\n", userTemp_id);
        printf("\n\t\t\t\t  * PASSWORD\n\t\t\t\t\t-->> ");
        printf("%s\n", passwordAsterisk);

        switch(selection){
            case 1:
                printf("\n\t\t\t\t[*] CONTINUE\t\t[ ] CANCEL\t\t[ ] CLEAR\n");
                break;
            case 2:
                printf("\n\t\t\t\t[ ] CONTINUE\t\t[*] CANCEL\t\t[ ] CLEAR\n");
                break;
            case 3:
                printf("\n\t\t\t\t[ ] CONTINUE\t\t[ ] CANCEL\t\t[*] CLEAR\n");
                break;
        }

        printf("\n\t\t=========================================================================================================\n");
        printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");

    }
}
