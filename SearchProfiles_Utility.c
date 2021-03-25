#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "header.h"


int isInFavoriteArray(int targetID){
    int index;
    for(index = 0; index < checkAmountOfFavorited(session_Login_id); index++){
        //printf("isInFavoriteArray: personnel[session_Login_id].favorite[index].favoriteID = %d\t\ttargetID = %d\n", personnel[session_Login_id].favorite[index].favoriteID, targetID);
        if(personnel[session_Login_id].favorite[index].favoriteID == targetID){
            return 1;
        }
    }
    return 0;
}

void print_tableHeader(){
    printf("\n\t+-------------------------------------------------------------------------------------------------------------------------------+\n\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
    printf("\n\t|ID\t\t|FIRST NAME\t|LAST NAME\t\t|STATUS\t\t|PHONE NUMBER\t\t|EMAIL\t\t\t\t|\n\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("\t+-------------------------------------------------------------------------------------------------------------------------------+\n");
}

void print_Table(int arrayOfIndex[], int size_arrayOfIndex){
    print_tableHeader();
    int result_index, index;
    for(index = 0; index < size_arrayOfIndex; index++){
        result_index = arrayOfIndex[index];
        printf("#%d\t|%07d\t%-16s%-24s%-16s%-24s%-32s|\n", result_index, personnel[result_index]._id, personnel[result_index].firstName, personnel[result_index].lastName,
                                        (personnel[result_index].adminStatus == 0)? "Student" : "Admin",
                                        personnel[result_index].phoneNumber,
                                        personnel[result_index].email);
    }
    printf("\t+-------------------------------------------------------------------------------------------------------------------------------+\n");
}

void searchThruDatabase(char keyword[], int *parameterArrayPTR, int *parameterArraySizePTR, int context){

    int index, kndex, searchResults[50];
    int searchResultsCount = 0;

    char id[10];

    if(context == context_addFavorite){
        /// If the function is called in addFavorite
        for(index = 0; index < checkTotalNumber_ofPeople(); index++){
            sprintf(id, "%07d", personnel[index]._id);
            //printf("\nsearchThruDatabase: personnel[index]._id = %d | isInFavoriteArray = %d\n", personnel[index]._id, isInFavoriteArray(personnel[index]._id));
            /// If the item is already in Favorite Array, skip it.
            if(index == session_Login_id || isInFavoriteArray(personnel[index]._id) == 1){
                continue;
            }
            /// Check for duplication between new result and within favorite array itself!!
            if((strstr(id, keyword) || strcasestr(personnel[index].firstName, keyword) || strcasestr(personnel[index].lastName, keyword) || strcasestr(personnel[index].email, keyword) || strcasestr(personnel[index].phoneNumber, keyword)) && personnel[index].isDeleted == 0){
                //printf("personnel[index]._id = %d\n", personnel[index]._id);
                //system("pause");
                searchResults[searchResultsCount] = index;
                searchResultsCount++;
            }
        }
    }else if(context == context_removeFavorite){
        /// If the function is called in removeFavorite
        for(index = 0; index < checkTotalNumber_ofPeople(); index++){
            sprintf(id, "%07d", personnel[index]._id);
            //printf("\nsearchThruDatabase: personnel[index]._id = %d | isInFavoriteArray = %d\n", personnel[index]._id, isInFavoriteArray(personnel[index]._id));
            if(index == session_Login_id || isInFavoriteArray(personnel[index]._id) == 0){
                continue;
            }
            /// Check for duplication between new result and within favorite array itself!!
            if((strstr(id, keyword) || strcasestr(personnel[index].firstName, keyword) || strcasestr(personnel[index].lastName, keyword) || strcasestr(personnel[index].email, keyword) || strcasestr(personnel[index].phoneNumber, keyword)) && personnel[index].isDeleted == 0){
                //printf("personnel[index]._id = %d\n", personnel[index]._id);
                //system("pause");
                searchResults[searchResultsCount] = index;
                searchResultsCount++;
            }
        }
    }else if(context == context_searchProfiles){
        for(index = 0; index < checkTotalNumber_ofPeople(); index++){
            sprintf(id, "%07d", personnel[index]._id);
            /// If index is equal to current session index, skips to next loop!
            if(index == session_Login_id){
                // Disabled for now
                //continue;
            }
            if(strcasestr(personnel[index].firstName, keyword) && personnel[index].isDeleted == 0){
                searchResults[searchResultsCount] = index;
                searchResultsCount++;
            }
        }
    }else if(context == context_ADMIN_deleteProfiles){
        for(index = 0; index < checkTotalNumber_ofPeople(); index++){
            sprintf(id, "%07d", personnel[index]._id);
            /// If index is equal to current session index, skips to next loop!
            if(index == session_Login_id || personnel[index].adminStatus == 1){
                // Disabled for now
                continue;
            }
            if(strstr(id, keyword) && personnel[index].isDeleted == 0){
                searchResults[searchResultsCount] = index;
                searchResultsCount++;
            }
        }
    }else if(context_ADMIN_editOtherProfileActivity){
        for(index = 0; index < checkTotalNumber_ofPeople(); index++){
            sprintf(id, "%07d", personnel[index]._id);
            //printf("\nsearchThruDatabase: personnel[index]._id = %d | isInFavoriteArray = %d\n", personnel[index]._id, isInFavoriteArray(personnel[index]._id));
            if(index == session_Login_id || isInFavoriteArray(personnel[index]._id) == 0){
                continue;
            }
            /// Check for duplication between new result and within favorite array itself!!
            if((strstr(id, keyword) || strcasestr(personnel[index].firstName, keyword) || strcasestr(personnel[index].lastName, keyword) || strcasestr(personnel[index].email, keyword)) && personnel[index].isDeleted == 0){
                //printf("personnel[index]._id = %d\n", personnel[index]._id);
                //system("pause");
                searchResults[searchResultsCount] = index;
                searchResultsCount++;
            }
        }
    }else{
        for(index = 0; index < checkTotalNumber_ofPeople(); index++){
            sprintf(id, "%07d", personnel[index]._id);
            //printf("\nsearchThruDatabase: personnel[index]._id = %d | isInFavoriteArray = %d\n", personnel[index]._id, isInFavoriteArray(personnel[index]._id));
            if(index == session_Login_id || isInFavoriteArray(personnel[index]._id) == 0){
                continue;
            }
            /// Check for duplication between new result and within favorite array itself!!
            if((strstr(id, keyword) || strcasestr(personnel[index].firstName, keyword) || strcasestr(personnel[index].lastName, keyword) || strcasestr(personnel[index].email, keyword) || strcasestr(personnel[index].phoneNumber, keyword)) && personnel[index].isDeleted == 0){
                //printf("personnel[index]._id = %d\n", personnel[index]._id);
                //system("pause");
                searchResults[searchResultsCount] = index;
                searchResultsCount++;
            }
        }
    }

    for(index = 0; index < searchResultsCount; index++){
        //printf("%d ", searchResults[index]);
        *(parameterArrayPTR + index) = *(searchResults + index);
    }

    *parameterArraySizePTR = searchResultsCount;
}

void print_searchAllUserActivity_Header(int context){
	system("cls");
    printf("\n\n\n\n\t\t=================================================================================================================\n\n");
    if(context == context_searchProfiles){
        printf("\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ YOUR PROFILE \\\\ SEARCH CONTACT\n");
    }else if(context == context_ADMIN_editOtherProfileActivity){
        printf("\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ YOUR PROFILE \\\\ EDIT OTHER's CONTACT\n");
    }else if(context == context_ADMIN_deleteProfiles){
        printf("\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ YOUR PROFILE \\\\ DELETE A CONTACT\n");
    }else if(context == context_favorite){
        printf("\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ YOUR PROFILE \\\\ YOUR FAVORITE\n");
    }
    printf("\n\t\t=================================================================================================================\n\n");
    printf("\t\t\t\t-----------------------------------------------------------------------------------------\n\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|");

    if(context == context_searchProfiles){
        printf("\n\t\t\t\t|\t(*) SEARCH FOR A CONTACT\t\t\t\t\t\t\t|\n\t\t\t\t|\t\ please enter the criteria you want.\t\t\t\t\t\t|\n");
    }else if(context == context_ADMIN_editOtherProfileActivity){
        printf("\n\t\t\t\t|\t(*) SEARCH FOR A CONTACT TO EDIT\t\t\t\t\t\t|\n\t\t\t\t|\t\ please enter the criteria you want.\t\t\t\t\t\t|\n");
    }else if(context == context_ADMIN_deleteProfiles){
        printf("\n\t\t\t\t|\t(*) SEARCH FOR A CONTACT TO DELETE\t\t\t\t\t\t|\n\t\t\t\t|\t\ please enter the criteria you want.\t\t\t\t\t\t|\n");
    }else if(context == context_favorite){
        printf("\n\t\t\t\t|\t(*) SEARCH FOR A CONTACT TO ADD TO FAVORITE\t\t\t\t\t\t|\n\t\t\t\t|\t\ please tell us what you want me to do.\t\t\t\t\t\t|\n");
    }
    printf("\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t\t-----------------------------------------------------------------------------------------\n");
}


/**
 * \brief This Function contains 3 functionalities
 *          1. Profile Searching
 *          2. Search for target to Edit Other User's Profile
 *          3. Deleting a Profile (Admin only)
 *
 * \param context of the function, How should it act if being called by different functions!
 *
 */

void searchProfiles(int context){

    char inputKeyword[30];
    int resultArray[50];
    int resultArraySize;
    int index = 0;

    print_searchAllUserActivity_Header(context);

    printf("\n\n\t\t\t\t\t< > KEYWORD: ");
    scanf("%s", inputKeyword);
    searchThruDatabase(inputKeyword, &resultArray, &resultArraySize, context);

    //printf("\n");
    //printf("\n%d\n", resultArraySize);
    int result_index;
    for(index = 0; index < resultArraySize; index++){
            result_index = resultArray[index];
            //printf("%d ", result_index);
    }

    if(resultArraySize > 0){
        print_Table(resultArray, resultArraySize);
    }else{
        printf("\n\n\t\t\t\t|\t\t\t!!! NO RESULT FOR YOUR CRITERIA !!!\t\t\t|\n\n");
    }

    /** In case of a Normal User who want to search a profile **/
    if(context == context_searchProfiles || (context == context_ADMIN_editOtherProfileActivity && resultArraySize == 0)){
        int selection = 1;
        printf("\n\t\t\t[*] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
        printf("\n\t\t\t   - if you want to do it again.\t\t   - return to your profile menu.\n");
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
                    if(selection > 2){
                        selection = 2;
                    }
                    break;
                case 13:
                    switch(selection){
                        case 1:
                            searchProfiles(context);
                            break;
                        case 2:
                            userProfileMenuActivity();
                            break;
                    }
                    break;
                default:
                    selection = 1;
            }

            system("cls");

            print_searchAllUserActivity_Header(context);

            printf("\n\n\t\t\t\t\t< > KEYWOR(Name): ");
            printf("%s\n", inputKeyword);

            /// Re-print the TABLE AGAIN
            if(resultArraySize > 0){
                print_Table(resultArray, resultArraySize);
            }else{
                printf("\n\n\t\t\t\t|\t\t\t!!! NO RESULT FOR YOUR CRITERIA !!!\t\t\t|\n\n");
            }

            switch(selection){
                case 1:
                    printf("\n\t\t\t[*] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
                    printf("\n\t\t\t   - if you want to do it again.\t\t   - return to your profile menu.\n");
                    break;
                case 2:
                    printf("\n\t\t\t[ ] SEARCH AGAIN\t\t\t\t[*] GO BACK");
                    printf("\n\t\t\t   - if you want to do it again.\t\t   - return to your profile menu.\n");
                    break;
            }
            printf("\n\t\t=================================================================================================================\n");
            printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");

        }
    }else if(context == context_ADMIN_editOtherProfileActivity && resultArraySize > 0){
        /// TODO: Implement a way to edit other user profile
        int selection = 1, editIndex, index, isAvailable;
        printf("\n\t\t[*] SELECT TO EDIT\t\t\t\t[ ] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
        printf("\n\t\t   - edit an item in the search result\t\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
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
                            system("cls");
                            print_searchAllUserActivity_Header(context);
                            printf("\n\n\t\t\t\t\t< > KEYWORD(): ");
                            printf("%s\n", inputKeyword);
                            print_Table(resultArray, resultArraySize);

                            reEnterEditIndex:
                            printf("\n\n\t\t\t\t\t< > ENTER A NUMBER ON THE LEFT YOU WANT TO EDIT: ");
                            scanf("%d", &editIndex);
                            for(index = 0; index < resultArraySize; index++){
                                if(editIndex == resultArray[index]){
                                    isAvailable = 1;
                                    break;
                                }
                            }

                            if(isAvailable != 1){
                                printf("\n\n\t\t\t\t\t\a** INVALID INDEX ** - please enter a new index");
                                goto reEnterEditIndex;
                            }

                            remoteSession_id = editIndex;
                            editProfileActivity(context);
                            break;
                    case 2:
                        searchProfiles(context);
                        break;
                    case 3:
                        userProfileMenuActivity();
                        break;
                }
                break;
                default:
                selection = 1;
            }

            system("cls");

            print_searchAllUserActivity_Header(context_ADMIN_editOtherProfileActivity);

            printf("\n\n\t\t\t\t\t< > KEYWORD: ");
            printf("%s\n", inputKeyword);

            // Re-print the TABLE AGAIN
            if(resultArraySize > 0){
                print_Table(resultArray, resultArraySize);
            }

            switch(selection){
                case 1:
                    printf("\n\t\t[*] SELECT TO EDIT\t\t\t\t[ ] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
                    printf("\n\t\t   - edit an item in the search result\t\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
                    break;
                case 2:
                    printf("\n\t\t[ ] SELECT TO EDIT\t\t\t\t[*] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
                    printf("\n\t\t   - edit an item in the search result\t\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
                    break;
                case 3:
                    printf("\n\t\t[ ] SELECT TO EDIT\t\t\t\t[ ] SEARCH AGAIN\t\t\t\t[*] GO BACK");
                    printf("\n\t\t   - edit an item in the search result\t\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
                    break;
            }

            printf("\n\t\t=================================================================================================================\n");
            printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");

        }

    }else if(context == context_ADMIN_deleteProfiles){
        int selection = 1, targetID, index, isAvailable, countResultArray = 0;
        char confirmDeletion[10];
        if(resultArraySize > 0){
            printf("\n\t\t[*] SELECT TO DELETE\t\t\t\t[ ] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
            printf("\n\t\t   - delete an item in the search result\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
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
                            if(resultArraySize > 0){
                                system("cls");
                                print_searchAllUserActivity_Header(context);
                                printf("\n\n\t\t\t\t\t< > KEYWORD: ");
                                printf("%s\n", inputKeyword);
                                print_Table(resultArray, resultArraySize);

                                reEnterDeleteIndex:
                                printf("\n\n\t\t\t\t\t< > ENTER AN ID FROM A RESULT YOU WANT TO DELETE: ");
                                // Leaving a space after %d is intended to consume the \n before calling getchar()
                                scanf("%d", &targetID);

                                for(index = 0; index < resultArraySize; index++){
                                    if(targetID == personnel[resultArray[index]]._id){
                                        isAvailable = 1;
                                        break;
                                    }
                                    //countResultArray++;
                                }
                                //printf("\n\ntargetDel = %d", resultArray[index]);

                                if(isAvailable != 1){
                                    printf("\n\n\t\t\t\t\t\a** INVALID ID ** - please enter a new ID");
                                    goto reEnterDeleteIndex;
                                }

                                reConfirmDelete:
                                printf("\n\n\t\t\t\t\t< > ARE YOU SURE? (Y/N): ");
                                scanf(" %[^\t\n]s", confirmDeletion);

                                switch(confirmDeletion[0]){
                                    case 'y':
                                    case 'Y':
                                        deleteAnEntryInArray(resultArray[index]);
                                        reAcquireSessionID();
                                        //cleanUpDeletedProfile(editIndex);
                                        selectionSortByID_Ascending();
                                        write_DatabaseUtility();
                                        read_DatabaseUtility();
                                        selectionSortByID_Ascending();
                                        printf("\n\n\t\t\t\t\t\a** DELETE THE ITEM SUCCESSFULLY ! **");
                                        system("pause");
                                        userProfileMenuActivity();
                                        break;
                                    case 'n':
                                    case 'N':
                                        printf("\n\n\t\t\t\t\t\a** LEAVING TO PROFILE MENU **");
                                        userProfileMenuActivity();
                                        break;
                                    default:
                                        printf("\n\n\t\t\t\t\t\a** INVALID CHARACTER ** - please enter again");
                                        goto reConfirmDelete;
                                }
                            }else{
                                searchProfiles(context);
                            }
                            break;
                        case 2:
                            if(resultArraySize > 0){
                                searchProfiles(context);
                            }else{
                                userProfileMenuActivity();
                            }
                            break;
                        case 3:
                            userProfileMenuActivity();
                            break;
                    }
                    break;
                default:
                    selection = 1;
            }

            system("cls");

            print_searchAllUserActivity_Header(context);

            printf("\n\n\t\t\t\t\t< > KEYWORD: ");
            printf("%s\n", inputKeyword);

            // Re-print the TABLE AGAIN
            if(resultArraySize > 0){
                print_Table(resultArray, resultArraySize);
                switch(selection){
                    case 1:
                        printf("\n\t\t[*] SELECT TO DELETE\t\t\t\t[ ] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
                        printf("\n\t\t   - delete an item in the search result\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
                        break;
                    case 2:
                        printf("\n\t\t[ ] SELECT TO DELETE\t\t\t\t[*] SEARCH AGAIN\t\t\t\t[ ] GO BACK");
                        printf("\n\t\t   - delete an item in the search result\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
                        break;
                    case 3:
                        printf("\n\t\t[ ] SELECT TO DELETE\t\t\t\t[ ] SEARCH AGAIN\t\t\t\t[*] GO BACK");
                        printf("\n\t\t   - delete an item in the search result\t  - if you want to do it again.\t\t\t  - return to your profile menu.\n");
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
}

