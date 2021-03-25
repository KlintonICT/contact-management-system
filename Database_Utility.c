#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "header.h"

char const fileName[] = "personnelsDatabase.bin";
//char const fileName_totalNumber[] = "personnelsDatabase_totalNumber.bin";

/**
 *\brief This function reads Data from file.
 */
void read_DatabaseUtility(){
    FILE *input_filePointer;
    input_filePointer = fopen(fileName, "rb");
    if(input_filePointer != 0){
        if(fread(personnel, sizeof(personnel), 1, input_filePointer) != 1){
            fprintf(stderr, "Failed to read to %s\n", fileName);
            exit(-1);
        }
        fclose(input_filePointer);
    }
}

/**
 *\brief This function writes Data from file.
 */
void write_DatabaseUtility(){
    FILE *output_filePointer;
    output_filePointer = fopen(fileName, "wb");
    if(output_filePointer != 0){
        if(fwrite(personnel, sizeof(personnel), 1, output_filePointer) != 1){
            fprintf(stderr, "Failed to write to %s\n", fileName);
            exit(-1);
        }
        fclose(output_filePointer);
    }
}

/** \brief This function sorts a favorite list by ID from lower to higher and puts ID which equals to zero to the end.
 *
 * \param a favorite list
 *
 */
void favorite_selectionSortByID_Ascending(struct favoriteElement favoriteArray[]){
    int index, kndex, position;
    struct favoriteElement swap;
    for(index = 0; index < (checkAmountOfFavorited(session_Login_id) - 1); index++){
        position = index;
        for(kndex = index + 1; kndex < checkAmountOfFavorited(session_Login_id); kndex++){
            if(favoriteArray[position].favoriteID > favoriteArray[kndex].favoriteID){
                position = kndex;
            }
        }
        if(position != index){
            swap = favoriteArray[index];
            favoriteArray[index] = favoriteArray[position];
            favoriteArray[position] = swap;
        }
    }

    int countZero = 0;  // Count of non-zero elements

    // Traverse the array. If element encountered is non-
    // zero, then replace the element at index 'count'
    // with this element
    for(index = 0; index < sizeof(favoriteArray) / sizeof(favoriteArray[0]); index++){
        if(favoriteArray[index].favoriteID != 0){
            favoriteArray[countZero++] = favoriteArray[index]; // here count is
        }// incremented
    }
    // Now all non-zero elements have been shifted to
    // front and  'count' is set as index of first 0.
    // Make all elements 0 from count to end.
    while(countZero < (sizeof(favoriteArray) / sizeof(favoriteArray[0]))){
        countZero++;
        favoriteArray[countZero].favoriteID = 0;
        favoriteArray[countZero].favoriteIndex = 0;
        //strcpy(favoriteArray[countZero].nameString, "");
    }
    write_DatabaseUtility();
}

void selectionSortByID_Ascending(){
    int index, kndex, position;
    struct contact swap;
    for(index = 0; index < (TOTAL_NUMBER_ofPersonnel - 1); index++){
        position = index;
        for(kndex = index + 1; kndex < TOTAL_NUMBER_ofPersonnel; kndex++){
            if(personnel[position]._id > personnel[kndex]._id){
                position = kndex;
            }
        }
        if(position != index){
            swap = personnel[index];
            personnel[index] = personnel[position];
            personnel[position] = swap;
        }
    }

    reAcquireSessionID();
    int countZero = 0;  // Count of non-zero elements

    // Traverse the array. If element encountered is non-
    // zero, then replace the element at index 'count'
    // with this element
    for(index = 0; index < sizeof(personnel) / sizeof(personnel[0]); index++)
        if(personnel[index]._id != 0){
            personnel[countZero++] = personnel[index]; // here count is
        }// incremented

    // Now all non-zero elements have been shifted to
    // front and  'count' is set as index of first 0.
    // Make all elements 0 from count to end.
    while(countZero < (sizeof(personnel) / sizeof(personnel[0]))){
        //personnel[countZero++]._id = 0;
        deleteAnEntryInArray(countZero++);
    }

    reAcquireSessionID();
    write_DatabaseUtility();
}

void deleteAnEntryInArray(int targetPosition){
    personnel[targetPosition]._id = 0;

    strcpy(personnel[targetPosition].firstName, "");
    strcpy(personnel[targetPosition].lastName, "");

    personnel[targetPosition].gender = -1;
    strcpy(personnel[targetPosition].phoneNumber, "");
    strcpy(personnel[targetPosition].email, "");
    strcpy(personnel[targetPosition].password, "");
    personnel[targetPosition].adminStatus = -1;
    personnel[targetPosition].isDeleted = 1;

    int index;
    for(index = 0; index < checkAmountOfFavorited(targetPosition); index++){
        personnel[targetPosition].favorite[index].favoriteIndex = 0;
        personnel[targetPosition].favorite[index].favoriteID = 0;
    }

    checkTotalNumber_ofPeople();
    reAcquireSessionID();
    write_DatabaseUtility();
}

void reAcquireSessionID(){
    int index;
    for(index = 0; index < TOTAL_NUMBER_ofPersonnel; index++){
        if(temporaryID != personnel[index]._id){
            if(compare2Strings(temporaryFirstName, personnel[index].firstName) == 0){
                if(compare2Strings(temporaryLastName, personnel[index].lastName) == 0){
                    if(compare2Strings(temporaryEmail, personnel[index].email) == 0){
                        session_Login_id = index;
                        //printf("Enter Statement for reAcquireSessionID\n");
                        //printf("session_Login_id = %d ", session_Login_id);
                        //system("pause");
                    }
                }
            }
        }
    }
}

int checkTotalNumber_ofPeople(){
    int index = 0, countPeople = 0;
    for(index = 0; index < 50; index++){
        if(personnel[index]._id > 0 && personnel[index].isDeleted == 0 && personnel[index]._id != 0){
                countPeople++;
        }
    }
    return countPeople;
}
