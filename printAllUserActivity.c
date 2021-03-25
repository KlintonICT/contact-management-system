#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "header.h"

/**
 *  \brief The header for showing all user table
 */
void print_printAllUserActivity_Header(){
	system("cls");
    printf("\n\n\n\n\t\t=================================================================================================================\n\n");
    printf("\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ YOUR PROFILE \\\\ SHOW ALL CONTACTS\n");
    printf("\n\t\t=================================================================================================================\n\n");
    printf("\t\t\t\t-----------------------------------------------------------------------------------------\n\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|");
    printf("\n\t\t\t\t|\t(*) SHOWING ALL CONTACTS! %s, you are at the INDEX #%02d!%*s\n\t\t\t\t|\t\ explore whatever you like!\t\t\t\t\t\t\t|\n", personnel[session_Login_id].firstName, session_Login_id, 87 +2 - 34 - 27 - strlen(personnel[session_Login_id].firstName), "|");
    printf("\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t\t-----------------------------------------------------------------------------------------\n");
}

/**
 *  \brief The main activity for ALL USER SCREEN
 */
void printAllUserActivity(){
    read_DatabaseUtility();
    print_printAllUserActivity_Header();
    int index, size = sizeof(personnel) / sizeof(personnel[0]);
    printf("\n\t\t\t\tMAXIMUM SIZE OF THE DATABASE: %d\t\t", size);
    TOTAL_NUMBER_ofPersonnel = checkTotalNumber_ofPeople();
    printf("TOTAL PEOPLE IN THE DATABASE: %d\n", TOTAL_NUMBER_ofPersonnel);

    printf("\n\t+-------------------------------------------------------------------------------------------------------------------------------+\n\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
    printf("\n\t|ID\t\t|FIRST NAME\t|LAST NAME\t\t|STATUS\t\t|PHONE NUMBER\t\t|EMAIL\t\t\t\t|\n\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("\t+-------------------------------------------------------------------------------------------------------------------------------+\n");

    for(index = 0; index < TOTAL_NUMBER_ofPersonnel; index++){
        if(personnel[index].isDeleted == 0){
            printf("#%d\t|%07d\t%-16s%-24s%-16s%-24s%-32s|\n", index, personnel[index]._id, personnel[index].firstName, personnel[index].lastName, (personnel[index].adminStatus == 0)? "Student" : "Admin", personnel[index].phoneNumber, personnel[index].email);
        }
    }
    printf("\t+-------------------------------------------------------------------------------------------------------------------------------+\n\n");
    printf("\t\t\t\t");
    system("pause");
}
