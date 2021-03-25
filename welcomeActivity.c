#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "header.h"
#include <time.h>
#define MAX_LEN 128

void print_imageOnScreen(FILE *fptr, int isLogo)
{
    char read_string[MAX_LEN];
    int countRow = 1;

    while(fgets(read_string,sizeof(read_string),fptr) != NULL){
        if(isLogo == 1){
            if(countRow == 3){
                printf("\t\t\t\t\t");
            }else{
                printf("\t\t\t\t\t\t");
            }

        }else{
            printf("\t\t");
        }
        printf("%s",read_string);
        countRow++;
    }
}

void createGreetingMessageAccordingToTime(char targetString[]){
    time_t t = time(NULL);
    struct tm timeStruct = *localtime(&t);

    switch(timeStruct.tm_hour){
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            strcpy(targetString, "Good Morning!");
            break;
        case 11:
        case 12:
            strcpy(targetString, "Hello there!");
            break;
        case 13:
        case 14:
        case 15:
        case 16:
            strcpy(targetString, "Good Afternoon!");
            break;
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            strcpy(targetString, "Good Evening!");
            break;
        default:
            strcpy(targetString, "Hello, staying late tonight eh?");
    }
}

void welcomeActivity(){
    system("cls");

    char greetingMessage[35];
    createGreetingMessageAccordingToTime(greetingMessage);

    int is_LOGO = 1;
    int is_not_LOGO = 0;
    char *fileName1 = "logo.txt";
    char *fileName2 = "image.txt";

    FILE *fptr1 = NULL;
    FILE *fptr2 = NULL;

    if((fptr1 = fopen(fileName1,"r")) == NULL)
    {
        fprintf(stderr,"There is an error in opening file: %s\n",fileName1);
        return 1;
    }

    if((fptr2 = fopen(fileName2,"r")) == NULL)
    {
        fprintf(stderr,"There is an error in opening file: %s\n",fileName2);
        return 1;
    }

    printf("\n\n\n\n");
    print_imageOnScreen(fptr1, is_LOGO);
    //session_Login_id = 0;

    printf("\n\n");

    printf("\t\t\t\t-----------------------------------------------------------------------------------------\n\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|");
    if(personnel[session_Login_id].adminStatus == 1){
        printf("\n\t\t\t\t|\t(*) %s, %s!%*s\n\t\t\t\t|\t YOU LOGGED IN AS AN ADMINISTRATOR\t\t\t\t\t\t|\n", greetingMessage, personnel[session_Login_id].firstName, 87 - 6 - 7 - strlen(greetingMessage) - strlen(personnel[session_Login_id].firstName),"|");
    }else{
        printf("\n\t\t\t\t|\t(*) %s, %s!%*s\n\t\t\t\t|\t YOU LOGGED IN AS A STUDENT\t\t\t\t\t\t\t|\n", greetingMessage, personnel[session_Login_id].firstName, 87 - 6 - 7 - strlen(greetingMessage) - strlen(personnel[session_Login_id].firstName),"|");
    }
    printf("\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t\t-----------------------------------------------------------------------------------------\n");


    print_imageOnScreen(fptr2, is_not_LOGO);
    printf("\n\n\t\t");
    fclose(fptr1);
    fclose(fptr2);
    system("pause");
    userProfileMenuActivity();
}

void goodByeActivity(){
    system("cls");
    printf("\n\n\n\n\t\t\t\t-----------------------------------------------------------------------------------------\n\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|");
    printf("\n\t\t\t\t|\t(*) GOOD BYE!\t\t\t\t\t\t\t\t\t|\n\t\t\t\t|\t LOGGING YOU OUT!\t\t\t\t\t\t\t\t|\n");
    printf("\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t\t-----------------------------------------------------------------------------------------\n");
    printf("\n\n\t\t\t\t");
    system("pause");
}

void finishedRegisterActivity(char temp_firstName[], int temp_adminStatus){
    system("cls");
    char string_Admin[] = "AN ADMINISTRATOR";
    char string_Student[] = "A STUDENT";
    printf("\n\n\n\n\t\t\t\t-----------------------------------------------------------------------------------------\n\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|");
    printf("\n\t\t\t\t|\t(*) CONGRATULATIONS, %s!%*s\n\t\t\t\t|\t YOUR ACCOUNT HAS BEEN REGISTERED AS %s SUCCESSFULLY!%*s\n", temp_firstName, 87 - 28 - strlen(temp_firstName), "|", (temp_adminStatus == 1)? string_Admin : string_Student, 87 - 43 - 14 - strlen((temp_adminStatus == 1)? string_Admin : string_Student),"|");
    printf("\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t\t-----------------------------------------------------------------------------------------\n");
    printf("\n\n\t\t\t\t");
    system("pause");
}
