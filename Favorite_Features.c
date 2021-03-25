#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "header.h"

/** \brief This is a function to convert to lower case then find substring in two string.
 *
 * \param A string of any cases (lower or capital)
 * \param A string of any cases (lower or capital)
 * \return Truth value
 */
char *strcasestr(const char *arg1, const char *arg2)
{
   const char *a, *b;

   for(;*arg1;*arg1++) {

     a = arg1;
     b = arg2;

     while((*a++ | 32) == (*b++ | 32))
        if(!*b){
            return (arg1);
        }
   }

   return(NULL);
}

void reAssignFavoriteIndexes(){
    int index, jndex;
    for(index = 0; index < checkAmountOfFavorited(session_Login_id); index++){
        for(jndex = 0; jndex < TOTAL_NUMBER_ofPersonnel; jndex++){
            if(personnel[session_Login_id].favorite[index].favoriteID == personnel[jndex]._id){
                personnel[session_Login_id].favorite[index].favoriteIndex = jndex;
            }
        }
    }
}

void addItemToFavorite(int targetPosition){
    //printf("\n\naddItemToFavorite:\n");
    scanFavoriteItems();
    int lastIndex = checkAmountOfFavorited(session_Login_id), index;

    //printf("\n\ntotalFavorite = %d\n", lastIndex);

    /// Store target favorite user's ID
    personnel[session_Login_id].favorite[lastIndex].favoriteID = personnel[targetPosition]._id;

    for(index = 0; index < TOTAL_NUMBER_ofPersonnel; index++){
        if(personnel[session_Login_id].favorite[lastIndex].favoriteID == personnel[index]._id){
            personnel[session_Login_id].favorite[lastIndex].favoriteIndex = index;
        }
    }

    //printf("personnel[%d].favorite[%d].favoriteID = %d\tpersonnel[targetPosition]._id = %d\n", session_Login_id, lastIndex, personnel[session_Login_id].favorite[lastIndex++].favoriteID, personnel[targetPosition]._id);
    lastIndex++;
    write_DatabaseUtility();
}

void removeItemFromFavorite(int targetPosition, int favoriteArraySize){
    int index;
    //printf("\n\removeItemFromFavorite:\n");
    scanFavoriteItems();

    //printf("\n\ntotalFavorite = %d\n", targetPosition);

    for(index = 0; index < favoriteArraySize; index++){
        if(personnel[session_Login_id].favorite[index].favoriteIndex == targetPosition){
            personnel[session_Login_id].favorite[index].favoriteID = 0;
        }
    }
    write_DatabaseUtility();
}

int checkAmountOfFavorited(int session_id){
    int index, countFavorite = 0;
    for(index = 0; index < 50; index++){
        if(personnel[session_id].favorite[index].favoriteID != 0){
            countFavorite++;
        }
    }
    return countFavorite;
}

void scanFavoriteItems(){
    int index, jndex;
    if(checkAmountOfFavorited(session_Login_id) > 0){
        for(index = 0; index < checkAmountOfFavorited(session_Login_id); index++){
            for(jndex = 0; jndex < checkTotalNumber_ofPeople(); jndex++){
                if(personnel[session_Login_id].favorite[index].favoriteID == personnel[jndex]._id){
                    personnel[session_Login_id].favorite[index].favoriteIndex = jndex;
                }
            }
        }
    }
    favorite_selectionSortByID_Ascending(personnel[session_Login_id].favorite);
}

void DEBUG_showAllFavoriteArray(){
    int index;
    scanFavoriteItems();
    system("cls");
    favorite_selectionSortByID_Ascending(personnel[session_Login_id].favorite);
    printf("Number of Favorite = %d\n", checkAmountOfFavorited(session_Login_id));

    for(index = 0; index < checkAmountOfFavorited(session_Login_id); index++){
        printf("%d\t\t%07d\t\t\tfavIndex = %d\n", index, personnel[session_Login_id].favorite[index].favoriteID, personnel[session_Login_id].favorite[index].favoriteIndex);
    }

    system("pause");
}

void addFavoriteActivity(){
    char fav_inputKeyword[30];
    int fav_resultArray[50];
    int fav_resultArraySize;
    int index = 0;

    print_Favorite_Header(context_addFavorite);

    printf("\n\n\t\t\t\t\t< > KEYWORD: ");
    scanf("%s", fav_inputKeyword);
    searchThruDatabase(fav_inputKeyword, &fav_resultArray, &fav_resultArraySize, context_addFavorite);

    int result_index;

    if(fav_resultArraySize > 0){
        print_Table(fav_resultArray, fav_resultArraySize);
    }else{
        printf("\n\n\t\t\t\t|\t\t\t!!! NO RESULT FOR YOUR CRITERIA !!!\t\t\t|\n\n");
    }

    int selection = 1, editIndex, isAvailable;
    char confirmAdd[10];
    if(fav_resultArraySize > 0){
        printf("\n\t\t[*] SELECT TO ADD TO FAVORITE\t\t\t\t[ ] SEARCH AGAIN\t\t\t[ ] GO BACK");
        printf("\n\t\t   - add an item in the search result to your list\t\t  - if you want to do it again.\t\t  - return to your profile menu.\n");
    }else{
        printf("\n\t\t\t[*] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
        printf("\n\t\t\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
    }

    printf("\n\t\t=================================================================================================================\n");
    printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");

    while(1){
        switch(getch()){
            case 'A':
            case 'a':
                // code for arrow up
                selection--;
                if(selection < 1){
                    selection = 1;
                }
                break;
            case 'D':
            case 'd':
                // code for arrow down
                selection++;
                if(selection > 3){
                    selection = 3;
                }
                break;
            case 13:
                switch(selection){
                    case 1:
                        if(fav_resultArraySize > 0){
                            system("cls");
                            print_Favorite_Header(context_addFavorite);
                            printf("\n\n\t\t\t\t\t< > KEYWORD: ");
                            printf("%s\n", fav_inputKeyword);
                            print_Table(fav_resultArray, fav_resultArraySize);

                            reEnterDeleteIndex:
                            printf("\n\n\t\t\t\t\t< > ENTER A NUMBER ON THE LEFT YOU WANT TO ADD TO FAVORITE : ");
                            // Leaving a space after %d is intended to consume the \n before calling getchar()
                            scanf("%d", &editIndex);

                            for(index = 0; index < fav_resultArraySize; index++){
                                if(editIndex == fav_resultArray[index]){
                                    isAvailable = 1;
                                    break;
                                }
                            }
                            if(isAvailable != 1){
                                printf("\n\n\t\t\t\t\t\a** INVALID INDEX ** - please enter a new index");
                                goto reEnterDeleteIndex;
                            }

                            reConfirmAdd:
                            printf("\n\n\t\t\t\t\t< > ARE YOU SURE? (Y/N): ");
                            scanf(" %[^\t\n]s", confirmAdd);

                            switch(confirmAdd[0]){
                                case 'y':
                                case 'Y':
                                    addItemToFavorite(editIndex);
                                    //cleanUpDeletedProfile(editIndex);
                                    selectionSortByID_Ascending();
                                    write_DatabaseUtility();
                                    read_DatabaseUtility();
                                    selectionSortByID_Ascending();

                                    printf("\n\n\t\t\t\t\t\a** ADDED THE ITEM SUCCESSFULLY ! ** ");
                                    system("pause");
                                    favoriteMenuActivity();
                                    break;
                                case 'n':
                                case 'N':
                                    printf("\n\n\t\t\t\t\t\a** LEAVING TO FAVORITE MENU **");
                                    favoriteMenuActivity();
                                    break;
                                default:
                                    printf("\n\n\t\t\t\t\t\a** INVALID CHARACTER ** - please enter again");
                                    goto reConfirmAdd;
                            }
                        }else{
                            addFavoriteActivity();
                        }
                        break;
                    case 2:
                        if(fav_resultArraySize > 0){
                            addFavoriteActivity();
                        }else{
                            favoriteMenuActivity();
                        }
                        break;
                    case 3:
                        favoriteMenuActivity();
                        break;
                }
                break;
            default:
                selection = 1;
        }

        system("cls");
        print_Favorite_Header(context_addFavorite);

        printf("\n\n\t\t\t\t\t< > KEYWORD: ");
        printf("%s\n", fav_inputKeyword);

            // Re-print the TABLE AGAIN
            if(fav_resultArraySize > 0){
                print_Table(fav_resultArray, fav_resultArraySize);

                switch(selection){
                    case 1:
                        printf("\n\t\t[*] SELECT TO ADD TO FAVORITE\t\t\t\t[ ] SEARCH AGAIN\t\t\t[ ] GO BACK");
                        printf("\n\t\t   - add an item in the search result your list\t\t  - if you want to do it again.\t\t  - return to your profile menu.\n");
                        break;
                    case 2:
                        printf("\n\t\t[ ] SELECT TO ADD TO FAVORITE\t\t\t\t[*] SEARCH AGAIN\t\t\t[ ] GO BACK");
                        printf("\n\t\t   - add an item in the search result your list\t\t  - if you want to do it again.\t\t  - return to your profile menu.\n");
                        break;
                    case 3:
                        printf("\n\t\t[ ] SELECT TO ADD TO FAVORITE\t\t\t\t[ ] SEARCH AGAIN\t\t\t[*] GO BACK");
                        printf("\n\t\t   - add an item in the search result your list\t\t  - if you want to do it again.\t\t  - return to your profile menu.\n");
                        break;
                }

            }else{
                printf("\n\t\t\t\t|\t\t\t!!! NO RESULT FOR YOUR CRITERIA !!!\t\t\t|\n\n");

                if(selection == 3){
                    selection = 2;
                }

                switch(selection){
                    case 1:
                        printf("\n\t\t\t[*] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
                        printf("\n\t\t\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
                        break;
                    case 2:
                        printf("\n\t\t\t[ ] SEARCH AGAIN\t\t\t\t[*] GO BACK");
                        printf("\n\t\t\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
                        break;
                }
            }
            printf("\n\t\t=================================================================================================================\n");
            printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");
        }
}

void removeFavoriteActivity(){
    char favRemove_inputKeyword[30];
    int favRemove_resultArray[50];
    int favRemove_resultArraySize;
    int index = 0;

    print_Favorite_Header(context_removeFavorite);

    if(checkAmountOfFavorited(session_Login_id) > 1){
        printf("\n\n\t\t\t\t\t< > KEYWORD: ");
        scanf("%s", favRemove_inputKeyword);
    }else{
        strcpy(favRemove_inputKeyword, "@");
    }
    searchThruDatabase(favRemove_inputKeyword, &favRemove_resultArray, &favRemove_resultArraySize, context_removeFavorite);

    int result_index;

    printf("\n");

    if(favRemove_resultArraySize > 0){
        print_Table(favRemove_resultArray, favRemove_resultArraySize);
    }else{
        printf("\n\n\t\t\t\t|\t\t\t!!! NO RESULT FOR YOUR CRITERIA !!!\t\t\t|\n\n");
    }

    int selection = 1, editIndex, isAvailable;
    char confirmRemove[10];
    if(favRemove_resultArraySize > 0){
        printf("\n\t\t[*] SELECT TO REMOVE FROM FAVORITE\t\t\t\t[ ] SEARCH AGAIN\t\t\t[ ] GO BACK");
        printf("\n\t\t   - remove an item in the search result from list\t\t  - if you want to do it again.\t\t  - return to your profile menu.\n");
    }else{
        printf("\n\t\t\t[*] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
        printf("\n\t\t\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
    }

    printf("\n\t\t=================================================================================================================\n");
    printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");

    while(1){
        switch(getch()){
            case 'A':
            case 'a':
                // code for arrow up
                selection--;
                if(selection < 1){
                    selection = 1;
                }
                break;
            case 'D':
            case 'd':
                // code for arrow down
                selection++;
                if(selection > 3){
                    selection = 3;
                }
                break;
            case 13:
                switch(selection){
                    case 1:
                        if(favRemove_resultArraySize > 0){
                            system("cls");
                            print_Favorite_Header(context_removeFavorite);

                            if(checkAmountOfFavorited(session_Login_id) > 1){
                                printf("\n\n\t\t\t\t\t< > KEYWORD: ");
                                printf("%s\n", favRemove_inputKeyword);
                            }

                            print_Table(favRemove_resultArray, favRemove_resultArraySize);

                            reEnterRemoveFavIndex:
                            printf("\n\n\t\t\t\t\t< > ENTER A NUMBER ON THE LEFT YOU WANT TO REMOVE FROM FAVORITE : ");
                            // Leaving a space after %d is intended to consume the \n before calling getchar()
                            scanf("%d", &editIndex);

                            for(index = 0; index < favRemove_resultArraySize; index++){
                                //printf("favRemove_resultArray %d = %d\n", index, favRemove_resultArray[index]);
                                if(editIndex == favRemove_resultArray[index]){
                                    isAvailable = 1;
                                    break;
                                }
                            }
                            //printf("isAvailable = %d", isAvailable);
                            if(isAvailable != 1){
                                printf("\n\n\t\t\t\t\t\a** INVALID INDEX ** - please enter a new index");
                                goto reEnterRemoveFavIndex;
                            }

                            reConfirmRemoveFav:
                            printf("\n\n\t\t\t\t\t< > ARE YOU SURE TO REMOVE %s from your favorite? (Y/N): ", personnel[editIndex].firstName);
                            scanf(" %[^\t\n]s", confirmRemove);

                            switch(confirmRemove[0]){
                                case 'y':
                                case 'Y':
                                    removeItemFromFavorite(editIndex, favRemove_resultArraySize);
                                    //cleanUpDeletedProfile(editIndex);
                                    selectionSortByID_Ascending();
                                    write_DatabaseUtility();
                                    read_DatabaseUtility();
                                    selectionSortByID_Ascending();

                                    printf("\n\n\t\t\t\t\t\a** REMOVED THE ITEM SUCCESSFULLY ! ** ");
                                    system("pause");
                                    favoriteMenuActivity();
                                    break;
                                case 'n':
                                case 'N':
                                    printf("\n\n\t\t\t\t\t\a** LEAVING TO FAVORITE MENU **");
                                    system("pause");
                                    favoriteMenuActivity();
                                    break;
                                default:
                                    printf("\n\n\t\t\t\t\t\a** INVALID CHARACTER ** - please enter again");
                                    goto reConfirmRemoveFav;
                            }
                        }else{
                            removeFavoriteActivity();
                        }
                        break;
                    case 2:
                        if(favRemove_resultArraySize > 0){
                            removeFavoriteActivity();
                        }else{
                            favoriteMenuActivity();
                        }
                        break;
                    case 3:
                        favoriteMenuActivity();
                        break;
                }
                break;
            default:
                selection = 1;
        }

        system("cls");
        print_Favorite_Header(context_removeFavorite);

        if(checkAmountOfFavorited(session_Login_id) > 1){
            printf("\n\n\t\t\t\t\t< > KEYWORD: ");
            printf("%s\n", favRemove_inputKeyword);
        }

        // Re-print the TABLE AGAIN
        if(favRemove_resultArraySize > 0){
            print_Table(favRemove_resultArray, favRemove_resultArraySize);
            switch(selection){
                case 1:
                    printf("\n\t\t[*] SELECT TO REMOVE FROM FAVORITE\t\t\t\t[ ] SEARCH AGAIN\t\t\t[ ] GO BACK");
                    printf("\n\t\t   - remove an item in the search result from list\t\t  - if you want to do it again.\t\t  - return to your profile menu.\n");
                    break;
                case 2:
                    printf("\n\t\t[ ] SELECT TO REMOVE FROM FAVORITE\t\t\t\t[*] SEARCH AGAIN\t\t\t[ ] GO BACK");
                    printf("\n\t\t   - remove an item in the search result from list\t\t  - if you want to do it again.\t\t  - return to your profile menu.\n");
                    break;
                case 3:
                    printf("\n\t\t[ ] SELECT TO REMOVE FROM FAVORITE\t\t\t\t[ ] SEARCH AGAIN\t\t\t[*] GO BACK");
                    printf("\n\t\t   - remove an item in the search result from list\t\t  - if you want to do it again.\t\t  - return to your profile menu.\n");
                    break;
            }

        }else{
            printf("\n\n\t\t\t\t|\t\t\t!!! NO RESULT FOR YOUR CRITERIA !!!\t\t\t|\n\n");
            if(selection == 3){
                selection = 2;
            }

            switch(selection){
                case 1:
                    printf("\n\t\t\t[*] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
                    printf("\n\t\t\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
                    break;
                case 2:
                    printf("\n\t\t\t[ ] SEARCH AGAIN\t\t\t\t[*] GO BACK");
                    printf("\n\t\t\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
                    break;
            }
        }
        printf("\n\t\t=================================================================================================================\n");
        printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");
    }
}


void print_Favorite_Header(int context){
    system("cls");
    printf("\n\n\n\n\t\t=================================================================================================================\n\n");
    printf("\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ YOUR PROFILE \\\\ YOUR FAVORITE\n");
    printf("\n\t\t=================================================================================================================\n\n");
    printf("\t\t\t\t-----------------------------------------------------------------------------------------\n\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|");
    if(context == context_addFavorite){
        printf("\n\t\t\t\t|\t(*) Search to add to favorite\t\t\t\t\t\t\t|\n\t\t\t\t|\t\ enter the keyword of the person you want!\t\t\t\t\t|\n");
    }else if(context == context_removeFavorite){
        printf("\n\t\t\t\t|\t(*) Search to remove from favorite\t\t\t\t\t\t|\n\t\t\t\t|\t\ enter the keyword of the person you want!\t\t\t\t\t|\n");
    }else{
        printf("\n\t\t\t\t|\t(*) FAVORITE MANAGER\t\t\t\t\t\t\t\t|\n\t\t\t\t|\t\ manage your favorite list.\t\t\t\t\t\t\t|\n");
    }
    printf("\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\|\n\t\t\t\t-----------------------------------------------------------------------------------------\n");
}

void seeAllFavoriteActivity(int session_id){

    /// Loading Message
    system("cls");
    printf("\n\n\n\n\n\t\t\t\t\tProcessing...");
    //printf("\n\n\n\n\n\t\t\t\t\t%d", checkAmountOfFavorited());
    int index, kndex, size = checkAmountOfFavorited(session_Login_id);

    if(size != 0){
        read_DatabaseUtility();
        scanFavoriteItems();
    }

    print_Favorite_Header(context_favorite);

    if(size > 0){
        printf("\n\t\tTOTAL FAVORITE: %d\n", size);
        print_tableHeader();

        for(index = 0; index < size; index++){
            for(kndex = 0; kndex < 50; kndex++){
                if(personnel[session_id].favorite[index].favoriteIndex == kndex){
                    printf("#%d\t|%07d\t%-16s%-24s%-16s%-24s%-32s|\n", kndex, personnel[kndex]._id, personnel[kndex].firstName, personnel[kndex].lastName, (personnel[kndex].adminStatus == 0)? "Student" : "Admin", personnel[kndex].phoneNumber, personnel[kndex].email);
                }
            }
        }
        printf("\t+-------------------------------------------------------------------------------------------------------------------------------+\n\n");
    }else{
        printf("\n\n\t\t\t\t|\t\t\t!!! NO RESULT FOR YOUR CRITERIA !!!\t\t\t|\n\n");
    }
    printf("\t\t\t\t");
    system("pause");
}

void favoriteMenuActivity(){

    int selectionX = 1, selectionY = 1;
    reAssignFavoriteIndexes();
    print_Favorite_Header(context_favorite);
    printf("\n\t\t\t[*] SEE YOUR FAVORITE\t\t\t\t\t[ ] SEARCH TO ADD TO FAVORITE");
    printf("\n\t\t\t   - see the list of who is your favorite.\t\t   - add someone to favorite.\n");
    printf("\n\t\t\t[ ] DELETE YOUR FAVORITE\t\t\t\t[ ] GO BACK");
    printf("\n\t\t\t   - remove someone from your favorite.\t\t\t   - return to your profile menu.\n");
    printf("\n\t\t=================================================================================================================\n");
    printf("\t\tMove the selector by pressing W, A, S or D, and Press ENTER to select!");

    while(1){
        switch(getch()){
            case 'A':
            case 'a':
                // Arrow left
                selectionX--;
                if(selectionX < 1){
                    selectionX = 1;
                }
                break;
            case 'D':
            case 'd':
                // Arrow right
                selectionX++;
                if(selectionX > 2){
                    selectionX = 2;
                }
                break;
            case 'W':
            case 'w':
                // Arrow up
                selectionY--;
                if(selectionY < 1){
                    selectionY = 1;
                }
                break;
            case 'S':
            case 's':
                // Arrow down
                selectionY++;
                if(selectionY > 2){
                    selectionY = 2;
                }
                break;
            case 13:
                if(selectionX == 1 && selectionY == 1){
                    // SEE YOUR FAVORITE
                    seeAllFavoriteActivity(session_Login_id);
                }else if(selectionX == 2 && selectionY == 1){
                    // SEARCH TO ADD TO FAVORITE
                    addFavoriteActivity();
                }else if(selectionX == 1 && selectionY == 2){
                    // DELETE YOUR FAVORITE
                    removeFavoriteActivity();
                }else if(selectionX == 2 && selectionY == 2){
                    // GO BACK
                    userProfileMenuActivity();
                }
                break;
            case '/':
                DEBUG_showAllFavoriteArray();
                break;
            default:
                selectionX = 1;
                selectionY = 1;
        }

        system("cls");

        print_Favorite_Header(context_favorite);

        if(selectionX == 1 && selectionY == 1){
            // SEE YOUR FAVORITE
            printf("\n\t\t\t[*] SEE YOUR FAVORITE\t\t\t\t\t[ ] SEARCH TO ADD TO FAVORITE");
            printf("\n\t\t\t   - see the list of who is your favorite.\t\t   - add someone to favorite.\n");
            printf("\n\t\t\t[ ] DELETE YOUR FAVORITE\t\t\t\t[ ] GO BACK");
            printf("\n\t\t\t   - remove someone from your favorite.\t\t\t   - return to your profile menu.\n");
        }else if(selectionX == 2 && selectionY == 1){
            // SEARCH TO ADD TO FAVORITE
            printf("\n\t\t\t[ ] SEE YOUR FAVORITE\t\t\t\t\t[*] SEARCH TO ADD TO FAVORITE");
            printf("\n\t\t\t   - see the list of who is your favorite.\t\t   - add someone to favorite.\n");
            printf("\n\t\t\t[ ] DELETE YOUR FAVORITE\t\t\t\t[ ] GO BACK");
            printf("\n\t\t\t   - remove someone from your favorite.\t\t\t   - return to your profile menu.\n");
        }else if(selectionX == 1 && selectionY == 2){
            // DELETE YOUR FAVORITE
            printf("\n\t\t\t[ ] SEE YOUR FAVORITE\t\t\t\t\t[ ] SEARCH TO ADD TO FAVORITE");
            printf("\n\t\t\t   - see the list of who is your favorite.\t\t   - add someone to favorite.\n");
            printf("\n\t\t\t[*] DELETE YOUR FAVORITE\t\t\t\t[ ] GO BACK");
            printf("\n\t\t\t   - remove someone from your favorite.\t\t\t   - return to your profile menu.\n");
        }else if(selectionX == 2 && selectionY == 2){
            // GO BACK
            printf("\n\t\t\t[ ] SEE YOUR FAVORITE\t\t\t\t\t[ ] SEARCH TO ADD TO FAVORITE");
            printf("\n\t\t\t   - see the list of who is your favorite.\t\t   - add someone to favorite.\n");
            printf("\n\t\t\t[ ] DELETE YOUR FAVORITE\t\t\t\t[*] GO BACK");
            printf("\n\t\t\t   - remove someone from your favorite.\t\t\t   - return to your profile menu.\n");
        }
        printf("\n\t\t=================================================================================================================\n");
        printf("\t\tMove the selector by pressing W, A, S or D, and Press ENTER to select!");
    }
}
