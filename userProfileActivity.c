#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "header.h"

/**
 * \brief The header for WELCOME SCREEN. It shows different messages depends on user privilege.
 */
void print_userProfileMenuActivityHeader(){
	system("cls");
    printf("\n\n\n\n\t\t=========================================================================================================\n\n");
    printf("\t\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ YOUR PROFILE\n");
    printf("\n\t\t=========================================================================================================\n\n");

    if(personnel[session_Login_id].adminStatus == 1){
        printf("\t\t\t-----------------------------------------------------------------------------------------\n\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|");
        printf("\n\t\t\t|\t(*) WELCOME, %s, you are an Administrator!%*s\n\t\t\t|\t What would you like to do today?\t\t\t\t\t\t|\n", personnel[session_Login_id].firstName, 87 - 20 - 26 - strlen(personnel[session_Login_id].firstName),"|");
        printf("\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t-----------------------------------------------------------------------------------------\n");
    }else{
        printf("\t\t\t-----------------------------------------------------------------------------------------\n\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|");
        printf("\n\t\t\t|\t(*) WELCOME, %s!\t\t\t\t\t\t\t\t|\n\t\t\t|\t What would you like to do today?\t\t\t\t\t\t|\n", personnel[session_Login_id].firstName);
        printf("\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t-----------------------------------------------------------------------------------------\n");
    }
}

/**
 *  \brief The main activity for WELCOME SCREEN. This function works differently depends on user privilege (Admin or User).
 *
 */
void userProfileMenuActivity(){

    reAcquireSessionID();
    /// If the USER is an ADMIN.
    if(personnel[session_Login_id].adminStatus == 1){
        int selection = 1;
        print_userProfileMenuActivityHeader();
        printf("\n\n\t\t\t\t\t[*] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
        printf("\n\t\t\t\t\t[ ] EDIT OTHER USER's PROFILE\n\t\t\t\t\t   - made changes in other user info\n\n");
        printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
        printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
        printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
        printf("\n\t\t\t\t\t[ ] DELETE A USER\n\t\t\t\t\t   - Administrators are allowed to use only\n\n");
        printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
        printf("\n\t\t=========================================================================================================\n");
        printf("\t\tMove the selector by pressing W or S, and Press ENTER to select!");

        while(1){
            switch(getch()){
                case 'S':
                case 's':
                    // code for arrow right
                    selection++;
                    if(selection > 7){
                        selection = 7;
                    }
                    break;
                case 'W':
                case 'w':
                    // code for arrow left
                    selection--;
                    if(selection < 1){
                        selection = 1;
                    }
                    break;
                case 13:
                    switch(selection){
                        case 1:
                            // Enter Profile Editing Page!
                            editProfileActivity(context_editProfileActivity);
                            break;
                        case 2:
                            searchProfiles(context_ADMIN_editOtherProfileActivity);
                            break;
                        case 3:
                            printAllUserActivity();
                            break;
                        case 4:
                            searchProfiles(context_searchProfiles);
                            break;
                        case 5:
                            favoriteMenuActivity();
                            break;
                        case 6:
                            searchProfiles(context_ADMIN_deleteProfiles);
                            break;
                        case 7:
                            // Log the user out, and reset the session login ID!
                            session_Login_id = -1;
                            // Go back to main menu.
                            goodByeActivity();
                            main();
                            break;
                    }
                    break;
                default:
                    selection = 1;
            }

            system("cls");

            print_userProfileMenuActivityHeader(session_Login_id);

            switch(selection){
                case 1:
                    printf("\n\n\t\t\t\t\t[*] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[ ] EDIT OTHER USER's PROFILE\n\t\t\t\t\t   - made changes in other user info\n\n");
                    printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[ ] DELETE A USER\n\t\t\t\t\t   - Administrators are allowed to use only\n\n");
                    printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
                case 2:
                    printf("\n\n\t\t\t\t\t[ ] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[*] EDIT OTHER USER's PROFILE\n\t\t\t\t\t   - made changes in other user info\n\n");
                    printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[ ] DELETE A USER\n\t\t\t\t\t   - Administrators are allowed to use only\n\n");
                    printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
                case 3:
                    printf("\n\n\t\t\t\t\t[ ] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[ ] EDIT OTHER USER's PROFILE\n\t\t\t\t\t   - made changes in other user info\n\n");
                    printf("\n\t\t\t\t\t[*] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[ ] DELETE A USER\n\t\t\t\t\t   - Administrators are allowed to use only\n\n");
                    printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
                case 4:
                    printf("\n\n\t\t\t\t\t[ ] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[ ] EDIT OTHER USER's PROFILE\n\t\t\t\t\t   - made changes in other user info\n\n");
                    printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[*] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[ ] DELETE A USER\n\t\t\t\t\t   - Administrators are allowed to use only\n\n");
                    printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
                case 5:
                    printf("\n\n\t\t\t\t\t[ ] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[ ] EDIT OTHER USER's PROFILE\n\t\t\t\t\t   - made changes in other user info\n\n");
                    printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[*] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[ ] DELETE A USER\n\t\t\t\t\t   - Administrators are allowed to use only\n\n");
                    printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
                case 6:
                    printf("\n\n\t\t\t\t\t[ ] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[ ] EDIT OTHER USER's PROFILE\n\t\t\t\t\t   - made changes in other user info\n\n");
                    printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[*] DELETE A USER\n\t\t\t\t\t   - Administrators are allowed to use only\n\n");
                    printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
                case 7:
                    printf("\n\n\t\t\t\t\t[ ] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[ ] EDIT OTHER USER's PROFILE\n\t\t\t\t\t   - made changes in other user info\n\n");
                    printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[ ] DELETE A USER\n\t\t\t\t\t   - Administrators are allowed to use only\n\n");
                    printf("\n\t\t\t\t\t[*] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
            }
            printf("\n\t\t=========================================================================================================\n");
            printf("\t\tMove the selector by pressing W or S, and Press ENTER to select!");
        }
    }else{
        int selection = 1;
        print_userProfileMenuActivityHeader();
        printf("\n\n\t\t\t\t\t[*] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
        printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
        printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
        printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
        printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
        printf("\n\t\t=========================================================================================================\n");
        printf("\t\tMove the selector by pressing W or S, and Press ENTER to select!");

        while(1){
            switch(getch()){
                case 'S':
                case 's':
                    // code for arrow down
                    selection++;
                    if(selection > 5){
                        selection = 5;
                    }
                    break;
                case 'W':
                case 'w':
                    // code for arrow up
                    selection--;
                    if(selection < 1){
                        selection = 1;
                    }
                    break;
                case 13:
                    switch(selection){
                        case 1:
                            // Enter Profile Editing Page!
                            editProfileActivity(context_editProfileActivity);
                            break;
                        case 2:
                            printAllUserActivity();
                            break;
                        case 3:
                            searchProfiles(context_searchProfiles);
                            break;
                        case 4:
                            favoriteMenuActivity();
                            break;
                        case 5:
                            // Log the user out, and reset the session login ID!
                            session_Login_id = -1;
                            // Go back to main menu.
                            goodByeActivity();
                            main();
                            break;
                    }
                    break;
                        default:
                    selection = 1;
            }

            system("cls");

            print_userProfileMenuActivityHeader(session_Login_id);

            switch(selection){
                case 1:
                    printf("\n\n\t\t\t\t\t[*] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
                case 2:
                    printf("\n\n\t\t\t\t\t[ ] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[*] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
                case 3:
                    printf("\n\n\t\t\t\t\t[ ] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[*] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
                case 4:
                    printf("\n\n\t\t\t\t\t[ ] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[*] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[ ] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
                case 5:
                    printf("\n\n\t\t\t\t\t[ ] EDIT MY PROFILE\n\t\t\t\t\t   - made changes in your info\n\n");
                    printf("\n\t\t\t\t\t[ ] SHOW ALL CONTACT\n\t\t\t\t\t   - show every single contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] SEARCH FOR A CONTACT\n\t\t\t\t\t   - search through all contact in the database\n\n");
                    printf("\n\t\t\t\t\t[ ] YOUR FAVORITE LIST\n\t\t\t\t\t   - let's see who is your favorite!\n\n");
                    printf("\n\t\t\t\t\t[*] LOGOUT\n\t\t\t\t\t   - stop using the system\n\n");
                    break;
            }
            printf("\n\t\t=========================================================================================================\n");
            printf("\t\tMove the selector by pressing W or S, and Press ENTER to select!");
        }
    }
    return 0;
}


