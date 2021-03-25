#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <Tchar.h>
#include "header.h"

#define arrow_up 0x48
#define arrow_down 0x50
#define arrow_left 0x4B
#define arrow_right 0x4D

// Contexts for each Activity
context_loginActivity = 0;
context_registrationActivity = 1;
context_editProfileActivity = 2;
context_ADMIN_editOtherProfileActivity = 3;
context_searchProfiles = 4;
context_ADMIN_deleteProfiles = 5;
context_DATABASE = 6;
context_favorite = 7;
context_addFavorite = 8;
context_removeFavorite = 9;

// Total Number of Personnel in the database
int TOTAL_NUMBER_ofPersonnel;

/** Temporary Login ID **/
int session_Login_id = -1;
int remoteSession_id = -1;
int temporarySessionID;
int temporaryID;
char temporaryFirstName[30];
char temporaryLastName[30];
char temporaryEmail[30];

void print_MainActivityHeader(){
    system("cls");
    printf("\n\n\n\n\t\t=========================================================================================================\n\n");
    printf("\t\t\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU\n");
    printf("\n\t\t=========================================================================================================\n\n");
}

/**
 *  \brief This is the MAIN MENU SCREEN.
 *      - There are hidden key to show debug menu.
 *          1. Enter '/' to sort data by ID and print out table of every user.
 *          2. Enter '.' to enter search User Activity.
 *          3. Enter ',' to enter search Favorite Activity. (Not working properly when call from Main Menu because session_login_id is -1)
 *          4. Enter 'm' to enter welcome Activity.
 */
int main(){
    read_DatabaseUtility();
    selectionSortByID_Ascending();
    TOTAL_NUMBER_ofPersonnel = checkTotalNumber_ofPeople();

    print_MainActivityHeader();

    int selection = 1;

    printf("\n\t\t\t[ ] LOGIN\n\t\t\t   - for A REGISTERED USER who want to use this program\n\n");
    printf("\n\t\t\t[ ] REGISTER\n\t\t\t   - for A NEW USER who want to use this program\n\n");
    printf("\n\t\t\t[ ] EXIT\n\t\t\t   - for any users who want to STOP USING this program\n\n");

    printf("\n\t\t=========================================================================================================\n");
    printf("\t\tMove the selector by pressing W or S, and Press ENTER to select!");

    while(1){
        switch(getch()){
            case 'W':
            case 'w':
            case arrow_up:
                // code for arrow up
                selection--;
                if(selection < 1){
                    selection = 1;
                }
                break;
            case 'S':
            case 's':
            case arrow_down:
                // code for arrow down
                selection++;
                if(selection > 3){
                    selection = 3;
                }
                break;
            case 'D':
            case 'd':
                // code for arrow right
                break;
            case 'A':
            case 'a':
                // code for arrow left
                break;
            case 13:
                switch(selection){
                    case 1:
                        loginActivity();
                        break;
                    case 2:
                        registrationActivity();
                        break;
                    case 3:
                        exit(0);
                        break;
                }
                break;
            case '/':
                //DEBUG_showAllUserActivity();
                selectionSortByID_Ascending();
                printAllUserActivity();
                break;
            case '.':
                //searchProfiles(context_searchProfiles);
                selectionSortByID_Ascending();
                //searchProfiles(context_ADMIN_editOtherProfileActivity);
                searchProfiles(context_ADMIN_deleteProfiles);
                break;
            case ',':
                //searchProfiles(context_searchProfiles);
                selectionSortByID_Ascending();
                //searchProfiles(context_ADMIN_editOtherProfileActivity);
                favoriteMenuActivity();
                break;
            case 'm':
                welcomeActivity();
                break;
            default:
                selection = 1;
        }

        print_MainActivityHeader();
        switch(selection){
            case 1:
                printf("\t\t\t-------------------------------------------------------------------------\n\t\t\t|\t\t\t\t\t\t\t\t\t|");
                printf("\n\t\t\t|\t[*] LOGIN\t\t\t\t\t\t\t|\n\t\t\t|\t- for A REGISTERED USER who want to use this program\t\t|\n");
                printf("\t\t\t|\t\t\t\t\t\t\t\t\t|\n\t\t\t-------------------------------------------------------------------------\n");
                printf("\n\t\t\t[ ] REGISTER\n\t\t\t   - for A NEW USER who want to use this program\n\n");
                printf("\n\t\t\t[ ] EXIT\n\t\t\t   - for any users who want to STOP USING this program\n\n");
                break;
            case 2:
                printf("\n\t\t\t[ ] LOGIN\n\t\t\t   - for A REGISTERED USER who want to use this program\n\n");
                printf("\t\t\t-------------------------------------------------------------------------\n\t\t\t|\t\t\t\t\t\t\t\t\t|");
                printf("\n\t\t\t|\t[*] REGISTER\t\t\t\t\t\t\t|\n\t\t\t|\t- for A NEW USER who want to use this program\t\t\t|\n");
                printf("\t\t\t|\t\t\t\t\t\t\t\t\t|\n\t\t\t-------------------------------------------------------------------------\n");
                printf("\n\t\t\t[ ] EXIT\n\t\t\t   - for any users who want to STOP USING this program\n\n");
                break;
            case 3:
                printf("\n\t\t\t[ ] LOGIN\n\t\t\t   - for A REGISTERED USER who want to use this program\n\n");
                printf("\n\t\t\t[ ] REGISTER\n\t\t\t  - for A NEW USER who want to use this program\n\n");
                printf("\t\t\t-------------------------------------------------------------------------\n\t\t\t|\t\t\t\t\t\t\t\t\t|");
                printf("\n\t\t\t|\t[*] EXIT\t\t\t\t\t\t\t|\n\t\t\t|\t- for any users who want to STOP USING this program\t\t|\n");
                printf("\t\t\t|\t\t\t\t\t\t\t\t\t|\n\t\t\t-------------------------------------------------------------------------\n");
                break;
        }

        printf("\n\t\t=========================================================================================================\n");
        printf("\t\tMove the selector by pressing W or S, and Press ENTER to select!");

    }
    return 0;
}
