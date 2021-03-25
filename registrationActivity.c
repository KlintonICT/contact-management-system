#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "header.h"

int checkAdminStatus(char  input_id[7]){
    int zeroCount = 0;

    // If first two character in ID String is Zero.
    if(input_id[0] == '0' &&  input_id[1] == '0'){
        zeroCount = 2;
    }
    if(zeroCount != 2){
        /** User **/
        return 0;
    }else{
        /** Admin **/
        return 1;
    }
}

void capitalizeFirstLetterOfString(char string[]){
	string[0] = toupper(string[0]);
}
int checkID_Duplication(char input_id[]){
    int index = 0, duplicationCount = 0;
    for(index = 0; index < TOTAL_NUMBER_ofPersonnel; index++){
        if(personnel[index]._id == stringToInteger(input_id)){
            duplicationCount++;
        }
    }
    if(duplicationCount != 0){
        /** If there is a duplication of ID then return an error. **/
        return -1;
    }else{
        /** The input ID is fine! **/
        return 0;
    }
}
int checkID(char input_id[], int context){
    int index = 0,characterCount = 0;
    int stringLength = strlen(input_id);

    for(index = 0; index < stringLength; index++){
        // If the String contains a character other than Numbers
        if(!(input_id[index] >= 48 && input_id[index] <= 57)){
            characterCount++;
        }
    }

    if(characterCount != 0){
        /** The input has character in it**/
        return -1;
    }

    if((checkIntegerDigit(stringToInteger(input_id)) != 7 && checkAdminStatus(input_id) == 0) || strlen(input_id) != 7){
        /** The input is not 7-digit long. **/
        return -2;
    }

    if(compare2Strings("0000000", input_id) == 0){
        /** If input is "000000", then it is treason. **/
        return -3;
    }

    if(context == context_registrationActivity || context == context_editProfileActivity){
        if(checkID_Duplication(input_id) != 0){
            /** The input ID is not unique **/
            return -3;
        }
    }

    /** The integer is normal **/
    return 0;
}
int stringToInteger(char input[]){
    /** Convert String to Integer if possible. **/
    return atoi(input);
}
int checkIntegerDigit(int number){
    int countDigits = 0;
    while(number != 0){
        number = number / 10;
        countDigits++;
    }
    /** Count how many digit of the input number **/
    return countDigits;
}

int checkEmail_Duplication(char input_id[]){
    int index = 0, duplicationCount = 0;
    for(index = 0; index < TOTAL_NUMBER_ofPersonnel; index++){
        if(personnel[index]._id == stringToInteger(input_id)){
            duplicationCount++;
        }
    }
    if(duplicationCount != 0){
        /** If there is a duplication of ID then return an error. **/
        return -1;
    }else{
        /** The input ID is fine! **/
        return 0;
    }
}

/** \brief Check for validity of inputted email
 *
 * \param String of user email
 * \return Error value
 *
 */
int checkEmail(char input_Email[]){
    int stringLength = strlen(input_Email);
    int index;

    /// Check the input email if it is already in Database or not
    for(index = 0; index < TOTAL_NUMBER_ofPersonnel; index++){
        if(compare2Strings(personnel[index].email, input_Email) == 0){
            return -2;
        }
    }

    int count_AT = 0, position_AT, count_DOT = 0, count_SPACE = 0, countErrorBeforeAT = 0;

    /// If it is too short, it is invalid!
    if(stringLength <= 3){
        return -1;
    }

    /// If there is any space bar, it is invalid!
    if(checkSpacebar(input_Email) != 0){
        return -1;
    }

    for(index = 0; index < stringLength; index++){
        if(input_Email[index] == '@'){
            count_AT++;
            position_AT = index;
        }
        if(index < position_AT){
            if(!((input_Email[index] >= 65 && input_Email[index] <= 90) || (input_Email[index] >= 97 && input_Email[index] <= 122) || (input_Email[index] >= 47 && input_Email[index] <= 57) || input_Email[index] == '.')){
                countErrorBeforeAT++;
            }

            if((input_Email[index] == '.' && input_Email[index + 1] == '.')){
                countErrorBeforeAT++;
            }
        }
        if(input_Email[index] == '.' && index > position_AT){
            count_DOT++;
        }
        if(input_Email[index] == ' '){
            count_SPACE++;
        }
        if((input_Email[index] == '.' && input_Email[index + 1] == '@') || (input_Email[index] == '@' && input_Email[index + 1] == '.')){
            countErrorBeforeAT++;
        }

    }
    if(count_AT != 1 || count_DOT == 0 || input_Email[stringLength - 1] == '.' || count_SPACE != 0 || position_AT == 0 || countErrorBeforeAT != 0){
        return -1;
    }
    return 0;
}

int checkPhoneNumber(char temp_phoneNumber[]){
    int stringLength = strlen(temp_phoneNumber), countError = 0, index;
    if(stringLength != 10){
        /** The Phone Number must be 10 digit long **/
        return -3;
    }

    /// Check the input phone number if it is already in Database or not
    for(index = 0; index < TOTAL_NUMBER_ofPersonnel; index++){
        if(compare2Strings(personnel[index].phoneNumber, temp_phoneNumber) == 0){
            return -2;
        }
    }

    /// Check the first digit of phone number if it is Zero or not
    if(temp_phoneNumber[0] != '0'){
        return -4;
    }

    /// Only Numbers are allowed!
    for(index = 0; index < stringLength; index++){
        // if temp_phoneNumber[index] is not NUMBER 0 to 9
        if(!(temp_phoneNumber[index] >= 48 && temp_phoneNumber[index] <= 57)){
            countError++;
        }
    }
    if(countError != 0){
        /** There is at least a character in the Phone Number **/
        return -1;
    }
    /** There is no error **/
    return 0;
}

int checkInputGender(){
    char userInput_gender;
    int count = 0;
    printf("\n\t\t\t\t\t[m] Male\tor\t[f] Female ? : ");
    do{
        if(count > 0 && userInput_gender != '\n'){
            printf("\n\t\t\t\t\t[m] Male\tor\t[f] Female ? : ");
        }
        userInput_gender = getchar();
        switch(userInput_gender){
            case 'm':
            case 'M':
                /** For Male **/
                return 0;
                break;
            case 'f':
            case 'F':
                /** For Female **/
                return 1;
                break;
            case '\n':
                continue;
            default:
                printf("\n\t\t\t\t\t  \a*** INVALID INPUT: Please enter only \"M\" or \"F\"! ***\n");
        }
        count++;
    }while(1);
}
void genderCodeToString(int genderCode, char targetString[]){
    int index, strLength = 0;
    switch(strLength){
        case 0:
            strLength = 4;
        case 1:
            strLength = 6;
    }
    char stringFemale[] = "Female", stringMale[] = "Male";
    for(index = 0; index < strLength; index++){
        switch(genderCode){
            case 0:
                *(targetString + index) = *(stringMale + index);
                break;
            case 1:
                *(targetString + index) = *(stringFemale + index);
                break;
        }
    }
}

int passwordDoubleChecker(char passwordA[60], char passwordB[60]){
    int index, countLikeness = 0, countUpperCharacters = 0, countNumbers = 0, countLowerCharacters = 0;

    if(strlen(passwordA) != strlen(passwordB)){
        /** The lengths of these String are not the same **/
        return -1;
    }

    if(strlen(passwordA) < 8){
        /** The length is too low (Under 8) **/
        return -2;
    }

    for(index = 0; index < strlen(passwordA); index++){
        if(passwordA[index] == passwordB[index]){
            countLikeness++;
            if(passwordA[index] >= 65 && passwordA[index] <= 90){
                countUpperCharacters++;
            }else{
                if(passwordA[index] >= 97 && passwordA[index] <= 122){
                    countLowerCharacters++;
                }else{
                    if((passwordA[index] >= 48 && passwordA[index] <= 57)){
                        countNumbers++;
                    }
                }
            }
        }
    }

    /// If there is any space bar, it is invalid!
    if(checkSpacebar(passwordA) == 1){
        return -3;
    }

    if((countUpperCharacters + countLowerCharacters + countNumbers) != strlen(passwordA)){
        /** There is some invalid symbol in password (Lower and Upper case characters + Number is Okay) **/
        return -3;
    }

    if(countLikeness != strlen(passwordA)){
        /** There is some character or number which is not match **/
        return -4;
    }else{
        /** The Password is completely fine! **/
        return 0;
    }
}

void confirmRegistration(int temp_ID, char temp_firstName[], char temp_lastName[], int temp_gender, char temp_phoneNumber[],
                         char temp_email[], char temp_password1[], int temp_adminStatus){
    TOTAL_NUMBER_ofPersonnel = checkTotalNumber_ofPeople();
    personnel[TOTAL_NUMBER_ofPersonnel]._id = temp_ID;

    strcpy(personnel[TOTAL_NUMBER_ofPersonnel].firstName, temp_firstName);
    strcpy(personnel[TOTAL_NUMBER_ofPersonnel].lastName, temp_lastName);

    personnel[TOTAL_NUMBER_ofPersonnel].gender = temp_gender;
    strcpy(personnel[TOTAL_NUMBER_ofPersonnel].phoneNumber, temp_phoneNumber);
    strcpy(personnel[TOTAL_NUMBER_ofPersonnel].email, temp_email);
    strcpy(personnel[TOTAL_NUMBER_ofPersonnel].password, temp_password1);
    personnel[TOTAL_NUMBER_ofPersonnel].adminStatus = temp_adminStatus;
    personnel[TOTAL_NUMBER_ofPersonnel].isDeleted = 0;

    // Total Number of REGISTERED USERS will increase by 1 after A new registration
    TOTAL_NUMBER_ofPersonnel++;
}

int checkFirstAndLastName(char firstName[], char lastName[]){
    int index;
    int countWeirdChar = 0;

    /// Check for anything that is not an alphabet in first name
    for(index = 0; index < strlen(firstName); index++){
        if(!((firstName[index] >= 65 && firstName[index] <= 90) || (firstName[index] >= 97 && firstName[index] <= 122))){
            countWeirdChar++;
        }
    }
    if(countWeirdChar > 0){
        return -2;
    }

    /// Check for anything that is not an alphabet in last name
    for(index = 0; index < strlen(lastName); index++){
        if(!((lastName[index] >= 65 && lastName[index] <= 90) || (lastName[index] >= 97 && lastName[index] <= 122))){
            countWeirdChar++;
        }
    }
    if(countWeirdChar > 0){
        return -2;
    }

    /// Check for any duplication
    for(index = 0; index < TOTAL_NUMBER_ofPersonnel; index++){
        if(compare2Strings(personnel[index].firstName, firstName) == 0){
            if(compare2Strings(personnel[index].lastName, lastName) == 0){
                return -1;
            }
        }
    }
    return 0;
}

int checkSpacebar(char input[]){
    int index, countSpace = 0;
    for(index = 0; index < strlen(input); index++){
        if(input[index] == ' '){
            countSpace++;
            break;
        }
    }

    if(countSpace > 0){
        /// There are space bars.
        return 1;
    }else{
        return 0;
    }
}

void print_RegistrationActivityHeader(){
    system("cls");
    printf("\n\n\n\n\t\t=========================================================================================================\n\n");
    printf("\t\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ REGISTRATION\n");
    printf("\n\t\t=========================================================================================================\n\n");
    printf("\t\t\t-------------------------------------------------------------------------\n\t\t\t|\t\t\t\t\t\t\t\t\t|");
    printf("\n\t\t\t|\t(*) REGISTER\t\t\t\t\t\t\t|\n\t\t\t|\t- for A NEW USER who want to use this program\t\t\t|\n");
    printf("\t\t\t|\t\t\t\t\t\t\t\t\t|\n\t\t\t-------------------------------------------------------------------------\n");
}

char temp_firstName[30];
char temp_lastName[30];
int registrationActivity(){

    int selection = 1;

    char temp_string_gender[6];

	int temp_ID;
	char temp_inputID[20];

	int temp_gender;
	char temp_phoneNumber[10];
	char temp_email[30];
	char temp_password1[60];
	char temp_password2[60];
	int temp_adminStatus;

	/// Variables for user input validity checking
	int errorChker_ID;
    //int errorChker_firstName;
    //int errorChker_lastName;
    int errorChker_phoneNumber;
    int errorChker_email;
    int errorChker_password;

	print_RegistrationActivityHeader();
	printf("\n\t\t\t\tPlease Enter Following Information:");

    ID_register:
    // Prompt the user to enter student ID.
    printf("\n\n\t\t\t\t < > STUDENT ID\n\t\t\t\t\t-->> ");
    scanf(" %[^\t\n]s", temp_inputID);
    // If the input ID get error then ask user to re-enter it.
    errorChker_ID = checkID(temp_inputID, context_registrationActivity);
    if(errorChker_ID != 0){
        printf("\n\t\t\t\t\t  \a*** INVALID ID: Make sure it is your 7-digits ID. ***");
        printf("\n\t\t\t\t\t  --> Please to re-enter your ID again\n");
        goto ID_register;
    }else{
        // If the input ID is fine then convert to an Integer and store it.
        temp_adminStatus = checkAdminStatus(temp_inputID);
        temp_ID = stringToInteger(temp_inputID);
        if(temp_adminStatus == 1){
            printf("\n\t\t\t\t\t  \a*** You are an administrator! ***\n");
        }
    }

    Name_register:
    // Prompt the user to enter First Name.
    printf("\n\t\t\t\t < > FIRST NAME\n\t\t\t\t\t-->> ");
    scanf(" %[^\t\n]s", temp_firstName);
    capitalizeFirstLetterOfString(temp_firstName);

    // Prompt the user to enter LAST NAME.
    printf("\n\t\t\t\t < > LAST NAME\n\t\t\t\t\t-->> ");
    scanf(" %[^\t\n]s", temp_lastName);
    capitalizeFirstLetterOfString(temp_lastName);

    if(checkFirstAndLastName(temp_firstName, temp_lastName) == -1){
        printf("\n\t\t\t\t\t  \a*** INVALID First Name and Last Name: This First Name and Last Name is already registered ***");
        printf("\n\t\t\t\t\t  --> Please to re-enter your First Name and Last Name again\n");
        goto Name_register;
    }else if(checkFirstAndLastName(temp_firstName, temp_lastName) == -2){
        printf("\n\t\t\t\t\t  \a*** INVALID First Name and Last Name: First Name and Last Name must contain only alphabets ***");
        printf("\n\t\t\t\t\t  --> Please to re-enter your First Name and Last Name again\n");
        goto Name_register;
    }

    // Prompt the user to enter GENDER.
    printf("\n\t\t\t\t < > GENDER \n\t\t\t\t\t-->> ");
    // checkInputGender() has its own scanf, so we don't need to put another scanf here.
    temp_gender = checkInputGender();

    phoneNumber_register:
    // Prompt the user to enter PHONE NUMBER.
    printf("\n\t\t\t\t < > PHONE NUMBER\n\t\t\t\t\t-->> ");
    scanf(" %[^\t\n]s", temp_phoneNumber);
    // If the input PHONE NUMBER get error then ask user to re-enter it.
    errorChker_phoneNumber = checkPhoneNumber(temp_phoneNumber);
    if(errorChker_phoneNumber != 0){
        if(errorChker_phoneNumber == -1){
            printf("\n\t\t\t\t\t  \a*** INVALID PHONE NUMBER: Do not put any character in your phone NUMBER! ***");
        }else if(errorChker_phoneNumber == -2){
            printf("\n\t\t\t\t\t  \a*** INVALID PHONE NUMBER: The phone number is already registered! ***");
        }else if(errorChker_phoneNumber == -3){
            printf("\n\t\t\t\t\t  \a*** INVALID PHONE NUMBER: Your phone number must be 10 digits long. ***");
        }else if(errorChker_phoneNumber == -4){
            printf("\n\t\t\t\t\t  \a*** INVALID PHONE NUMBER: Phone number must start with ZERO. ***");
        }
        printf("\n\t\t\t\t\t  --> Please re-enter your Phone Number again\n");
        goto phoneNumber_register;
    }

    email_register:
    // Prompt the user to enter EMAIL.
    printf("\n\t\t\t\t < > EMAIL ADDRESS\n\t\t\t\t\t-->> ");
    scanf(" %[^\t\n]s", temp_email);
    // If the input EMAIL get error then ask user to re-enter it.
    errorChker_email = checkEmail(temp_email);
    if(errorChker_email != 0){
        if(errorChker_email == -2){
            printf("\n\t\t\t\t\t  \a*** INVALID EMAIL: The email address is already registered! ***");
        }else{
            printf("\n\t\t\t\t\t  \a*** INVALID EMAIL: Make sure that your email is in proper format ***");
        }
        printf("\n\t\t\t\t\t  --> Please to re-enter your Email again\n");
        goto email_register;
    }

    password_register:
    // Prompt the user to enter PASSWORD.
    printf("\n\t\t\t\t < > PASSWORD\n\t\t\t\t\t-->> ");
    scanf(" %[^\t\n]s", temp_password1);

    // Prompt the user to enter PASSWORD again to confirm.
    printf("\n\t\t\t\t < > CONFIRM PASSWORD\n\t\t\t\t\t-->> ");
    scanf(" %[^\t\n]s", temp_password2);
    // If the input PASSWORD and CONFIRMATION PASSWORD get AN ERROR when checking then ask user to re-enter them.
    errorChker_password = passwordDoubleChecker(temp_password1, temp_password2);
    if(errorChker_password != 0){
        if(errorChker_password == -1 || errorChker_password == -4){
            printf("\n\t\t\t\t\t  \a*** INVALID PASSWORD: Make sure that they are match. ***");
        }else if(errorChker_password == -2){
            printf("\n\t\t\t\t\t  \a*** INVALID PASSWORD: Make sure that the length is at least 8. ***");
        }else if(errorChker_password == -3){
            printf("\n\t\t\t\t\t  \a*** INVALID PASSWORD: Make sure that there are only numbers and alphabets. ***");
        }
        printf("\n\t\t\t\t\t  --> Please to re-enter your Password again\n");
        goto password_register;
    }else{
        printf("\n\t\t\t\t\t  \a*** Are you sure with information you provided? ***\n");
    }

    // Print Selection Menu
    printf("\n\t\t\t\t[*] CONTINUE\t\t[ ] CANCEL\t\t[ ] CLEAR\n");
    printf("\n\t\t=========================================================================================================\n");
    printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");

    while(1){
        switch(getch()){
            case 'D':
            case 'd':
                // code for arrow right
                selection++;
                if(selection > 3){
                    selection = 3;
                }
                break;
            case 'A':
            case 'a':
                // code for arrow left
                selection--;
                if(selection < 1){
                    selection = 1;
                }
                break;
            case 13:
                switch(selection){
                    case 1:
                        // If "CONTINUE" is selected then store every input Data to Structure.
                        //printf("\n\nid = %d, name = %s, last = %s, gender = %d, phone = %d, email = %s, pass1 = %s, pass2 = %s, admin = %d\n", temp_ID, temp_firstName, temp_lastName, temp_gender, temp_phoneNumber, temp_email, temp_password1, temp_adminStatus);
                        //ssystem("pause");
                        confirmRegistration(temp_ID, temp_firstName, temp_lastName, temp_gender, temp_phoneNumber, temp_email, temp_password1, temp_adminStatus);
                        selectionSortByID_Ascending();
                        write_DatabaseUtility();
                        finishedRegisterActivity(temp_firstName, temp_adminStatus);
                        // Get user to Main Menu
                        main();
                        break;
                    case 2:
                        // If "CANCEL" is selected then return to Main menu.
                        main();
                        break;
                    case 3:
                        // If "CLEAR" is selected then CLEAR the entire form.
                        registrationActivity();
                        break;
                }
                break;
            default:
                selection = 1;
        }

        print_RegistrationActivityHeader();
        printf("\n\t\t\tPlease Enter Following Information:");

        printf("\n\n\t\t\t\t < > STUDENT ID\n\t\t\t\t\t-->> ");
        printf("%07d\n", temp_ID);

        printf("\n\n\t\t\t\t < > FIRST NAME\n\t\t\t\t\t-->> ");
        printf("%s\n", temp_firstName);

        printf("\n\t\t\t\t < > LAST NAME\n\t\t\t\t\t-->> ");
        printf("%s\n", temp_lastName);

        printf("\n\t\t\t\t < > GENDER\n\t\t\t\t\t-->> ");
        printf("%s\n", (temp_gender == 0)? "Male" : "Female");

        printf("\n\t\t\t\t < > PHONE NUMBER\n\t\t\t\t\t-->> ");
        printf("%s\n", temp_phoneNumber);

        printf("\n\t\t\t\t < > EMAIL ADDRESS\n\t\t\t\t\t-->> ");
        printf("%s\n", temp_email);

        printf("\n\t\t\t\t < > PASSWORD\n\t\t\t\t\t-->> ");
        printf("%s\n", temp_password1);

        printf("\n\t\t\t\t < > CONFIRM PASSWORD\n\t\t\t\t\t-->> ");
        printf("%s\n", temp_password2);

        printf("\n\t\t\t\t\t  *** Are you sure with information you provided? ***\n");

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
    return 0;
}
