#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "header.h"

void print_EditProfileActivityHeader(int session_Login_id){
    system("cls");
    printf("\n\n\n\n\t\t=========================================================================================================\n\n");
    printf("\t\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ YOUR PROFILE \\\\ EDIT PROFILE\n");
    printf("\n\t\t=========================================================================================================\n\n");
    printf("\t\t\t-----------------------------------------------------------------------------------------\n\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|");
    printf("\n\t\t\t|\t(*) EDIT %s's PROFILE%*s\n\t\t\t|\t Select the item you want to edit\t\t\t\t\t\t|\n", personnel[session_Login_id].firstName, 87 - 16 - 10 - strlen(personnel[session_Login_id].firstName) + 1, "|");
    printf("\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t-----------------------------------------------------------------------------------------\n");
}

void print_ADMIN_EditProfileActivity_Header(int remoteSession_id){
    system("cls");
    printf("\n\n\n\n\t\t=========================================================================================================\n\n");
    printf("\t\t\tICT CONTACT MANAGEMENT SYSTEM \\\\ MAIN MENU \\\\ YOUR PROFILE \\\\ EDIT OTHER's USER PROFILE\n");
    printf("\n\t\t=========================================================================================================\n\n");
    printf("\t\t\t-----------------------------------------------------------------------------------------\n\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|");
    printf("\n\t\t\t|\t(*) EDIT %s's PROFILE%*s\n\t\t\t|\t Select the item you want to edit\t\t\t\t\t\t|\n", personnel[remoteSession_id].firstName, 87 - 16 - 10 - strlen(personnel[remoteSession_id].firstName) + 1, "|");
    printf("\t\t\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t-----------------------------------------------------------------------------------------\n");
}

int selection_editProfileActivity = 2;
void editStringField(int session_id, int context){

    char fieldName[20];
    char currentValue[30];
    int currentGenderValue;

    char newValue[30];
    int newGenderValue;

    int newAdminStatus = 0;

    /// Variables for new password and new password confirmation
    char password_A[30];
    char password_B[30];

    /// Variables for user input validity checking
    int errorChker_ID;
    int errorChker_firstName;
    int errorChker_lastName;
    int errorChker_phoneNumber;
    int errorChker_email;
    int errorChker_password;

    if(context == context_editProfileActivity){
        print_EditProfileActivityHeader(session_id);
    }else if(context == context_ADMIN_editOtherProfileActivity){
        print_ADMIN_EditProfileActivity_Header(session_id);
    }

    switch(selection_editProfileActivity){
        case 1:
            strcpy(fieldName, "ID");
            sprintf(currentValue, "%07d", personnel[session_id]._id);
            break;
        case 2:
            strcpy(fieldName, "FIRST NAME");
            strcpy(currentValue, personnel[session_id].firstName);
            break;
        case 3:
            strcpy(fieldName, "SURNAME");
            strcpy(currentValue, personnel[session_id].lastName);
            break;
        case 4:
            strcpy(fieldName, "GENDER");
            currentGenderValue = personnel[session_id].gender;
            //genderCodeToString(currentGenderValue, currentGender);
            break;
        case 5:
            strcpy(fieldName, "PHONE NUMBER");
            strcpy(currentValue, personnel[session_id].phoneNumber);
            break;
        case 6:
            strcpy(fieldName, "EMAIL ADDRESS");
            strcpy(currentValue, personnel[session_id].email);
            break;
        case 7:
            strcpy(fieldName, "PASSWORD");
            strcpy(currentValue, personnel[session_id].password);
            break;
    }

    reEntering:
    if(selection_editProfileActivity != 7 && selection_editProfileActivity != 4){
        //printf("\n\n\t\t\t\t[ ] statement 1");
        printf("\n\n\t\t\t\t\t< > EDIT YOUR %s\n\n\t\t\t\t\t   - YOUR CURRENT %s: %s", fieldName, fieldName, currentValue);
        printf("\n\n\t\t\t\t\t   - ENTER A NEW %s: ", fieldName);
        scanf(" %[^\t\n]s", newValue);
    }else if(selection_editProfileActivity == 7){
        printf("\n\n\t\t\t\t\t< > EDIT YOUR %s\n\n\t\t\t\t\t   - YOUR CURRENT %s: %s", fieldName, fieldName, currentValue);
        printf("\n\n\t\t\t\t\t   - ENTER A NEW %s: ", fieldName);
        scanf(" %[^\t\n]s", password_A);
        printf("\n\t\t\t\t\t   - CONFIRM YOUR NEW %s: ", fieldName);
        scanf(" %[^\t\n]s", password_B);
    }else if(selection_editProfileActivity == 4){
        printf("\n\n\t\t\t\t\t< > EDIT YOUR %s\n\n\t\t\t\t\t   - YOUR CURRENT %s: %s", fieldName, fieldName, (currentGenderValue == 0)? "Male" : "Female");
        printf("\n\n\t\t\t\t\t   - ENTER A NEW %s: \n", fieldName);
        newGenderValue = checkInputGender();
        //printf("\n\n\t\t\t\t   - newGenderValue : %d\n", newGenderValue);
        //genderCodeToString(newGenderValue, newGender);
    }

    confirmProfileEdit:
    /// Reprint Header
    if(context == context_editProfileActivity){
        print_EditProfileActivityHeader(session_id);
    }else if(context == context_ADMIN_editOtherProfileActivity){
        print_ADMIN_EditProfileActivity_Header(session_id);
    }

    int isNewInputOkay = 0;

    switch(selection_editProfileActivity){
        case 1:
            //fieldName = "ID";
            errorChker_ID = checkID(newValue, context_editProfileActivity);
            if(errorChker_ID != 0){
                printf("\n\n\t\t\t\t  \a*** INVALID ID: Make sure it is your 7-digits ID. ***");
                printf("\n\t\t\t\t  --> Please to re-enter your ID again\n");
            }else{
                isNewInputOkay = 1;
            }
            break;
        case 2:
            //fieldName = "FIRST NAME";
            /// Check for possible duplication and weird symbols
            errorChker_firstName = checkFirstAndLastName(newValue, personnel[session_id].lastName);
            if(errorChker_firstName == -1){
                printf("\n\n\t\t\t\t  \a*** INVALID First Name and Last Name: This First Name and Last Name is already registered ***");
                printf("\n\t\t\t\t  --> Please to re-enter your First Name and Last Name again\n");
            }else if(errorChker_firstName == -2){
                printf("\n\n\t\t\t\t  \a*** INVALID First Name and Last Name: First Name and Last Name must contain only alphabets ***");
                printf("\n\t\t\t\t  --> Please to re-enter your First Name and Last Name again\n");
            }else{
                isNewInputOkay = 1;
            }
            break;
        case 3:
            //fieldName = "LAST NAME";
            /// Check for possible duplication and weird symbols
            errorChker_lastName = checkFirstAndLastName(personnel[session_id].firstName, newValue);
            if(errorChker_lastName == -1){
                printf("\n\n\t\t\t\t  \a*** INVALID First Name and Last Name: This First Name and Last Name is already registered ***");
                printf("\n\t\t\t\t  --> Please to re-enter your First Name and Last Name again\n");
            }else if(errorChker_lastName == -2){
                printf("\n\n\t\t\t\t  \a*** INVALID First Name and Last Name: First Name and Last Name must contain only alphabets ***");
                printf("\n\t\t\t\t  --> Please to re-enter your First Name and Last Name again\n");
            }else{
                isNewInputOkay = 1;
            }
            break;
        case 4:
            isNewInputOkay = 1;
            break;
        case 5:
            //fieldName = "PHONE NUMBER";
            errorChker_phoneNumber = checkPhoneNumber(newValue);
            if(errorChker_phoneNumber != 0){
                if(errorChker_phoneNumber == -1){
                    printf("\n\n\t\t\t\t  \a*** INVALID PHONE NUMBER: Do not put any character in your phone NUMBER! ***");
                }else if(errorChker_phoneNumber == -2){
                    printf("\n\n\t\t\t\t  \a*** INVALID PHONE NUMBER: The phone number is already registered! ***");
                }else if(errorChker_phoneNumber == -3){
                    printf("\n\n\t\t\t\t  \a*** INVALID PHONE NUMBER: Your phone number must be 10 digits long. ***");
                }else if(errorChker_phoneNumber == -4){
                    printf("\n\n\t\t\t\t  \a*** INVALID PHONE NUMBER: Phone number must start with ZERO. ***");
                }
                printf("\n\t\t\t\t  --> Please re-enter your Phone Number again\n");
            }else{
                isNewInputOkay = 1;
            }
            break;
        case 6:
            //fieldName = "EMAIL ADDRESS";
            errorChker_email = checkEmail(newValue);
            if(errorChker_email != 0){
                if(errorChker_email == -2){
                    printf("\n\n\t\t\t\t  \a*** INVALID EMAIL: The email address is already registered! ***");
                }else{
                    printf("\n\n\t\t\t\t  \a*** INVALID EMAIL: Make sure that your email is in proper format ***");
                }
                printf("\n\t\t\t\t  --> Please to re-enter your Email again\n");
            }else{
                isNewInputOkay = 1;
            }
            break;
        case 7:
            //fieldName = "PASSWORD";
            errorChker_password = passwordDoubleChecker(password_A, password_B);
            if(errorChker_password != 0){
                if(errorChker_password == -1 || passwordDoubleChecker(password_A, password_B) == -4){
                    printf("\n\n\t\t\t\t  \a*** INVALID PASSWORD: Make sure that they are match. ***");
                }else if(errorChker_password == -2){
                    printf("\n\n\t\t\t\t  \a*** INVALID PASSWORD: Make sure that the length is at least 8. ***");
                }else if(errorChker_password == -3){
                    printf("\n\n\t\t\t\t  \a*** INVALID PASSWORD: Make sure that there are only numbers or alphabets. ***");
                }
                printf("\n\t\t\t\t  --> Please to re-enter your Password again\n");
            }else{
                //printf("\n\t\t\t\t  \a*** Are you sure with information you provided? ***\n");
                isNewInputOkay = 1;
            }
            break;
    }

    if(selection_editProfileActivity != 7 && selection_editProfileActivity != 4){
        printf("\n\n\t\t\t\t\t< > EDIT YOUR %s\n\n\t\t\t\t\t   - YOUR CURRENT %s: %s", fieldName, fieldName, currentValue);
        printf("\n\n\t\t\t\t\t   - ENTER A NEW %s: ", fieldName);
        printf("%s\n", newValue);
    }else if(selection_editProfileActivity == 7){
        printf("\n\n\t\t\t\t\t< > EDIT YOUR %s\n\n\t\t\t\t\t   - YOUR CURRENT %s: %s", fieldName, fieldName, currentValue);
        printf("\n\n\t\t\t\t\t   - ENTER A NEW %s: ", fieldName);
        printf("%s\n", password_A);
        printf("\n\t\t\t\t\t   - CONFIRM YOUR NEW %s: ", fieldName);
        printf("%s\n", password_B);
    }else if(selection_editProfileActivity == 4){
        printf("\n\n\t\t\t\t\t< > EDIT YOUR %s\n\n\t\t\t\t\t   - YOUR CURRENT %s: %s", fieldName, fieldName,(currentGenderValue == 0)? "Male" : "Female");
        printf("\n\n\t\t\t\t\t   - ENTER A NEW %s: %s\n", fieldName, (newGenderValue == 0)? "Male" : "Female");
    }

    if(isNewInputOkay == 1){
        printf("\n\t\t\t\t[*] CONTINUE\t\t[ ] CANCEL\t\t[ ] CLEAR");
    }else{
        printf("\n\t\t\t\t\t\t[*] CLEAR\t\t[ ] CANCEL");
    }
    printf("\n");
    printf("\n\t\t=========================================================================================================\n");
    printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");

    int selectionInEdit = 1;
    while(1){
        switch(getch()){
            case 'D':
            case 'd':
                // code for arrow right
                selectionInEdit++;
                if(isNewInputOkay == 1){
                    if(selectionInEdit > 3){
                        selectionInEdit = 3;
                    }
                }else{
                    if(selectionInEdit > 2){
                        selectionInEdit = 2;
                    }
                }
                break;
            case 'A':
            case 'a':
                // code for arrow left
                selectionInEdit--;
                if(selectionInEdit < 1){
                    selectionInEdit = 1;
                }
                break;
            case 13:
                switch(selectionInEdit){
                    case 1:
                        if(isNewInputOkay == 1){
                            /// Confirms inputted data
                            switch(selection_editProfileActivity){
                                case 1:
                                    //fieldName = "ID";
                                    newAdminStatus = checkAdminStatus(newValue);
                                    personnel[session_id].adminStatus = newAdminStatus;
                                    personnel[session_id]._id = stringToInteger(newValue);
                                    break;
                                case 2:
                                    //fieldName = "FIRST NAME";
                                    /// Stores New Name in structure
                                    capitalizeFirstLetterOfString(newValue);
                                    strcpy(personnel[session_id].firstName, newValue);
                                    break;
                                case 3:
                                    //fieldName = "LAST NAME";
                                    /// Check for possible duplications and weird symbols
                                    capitalizeFirstLetterOfString(newValue);
                                    strcpy(personnel[session_id].lastName, newValue);
                                    break;
                                case 4:
                                    personnel[session_id].gender = newGenderValue;
                                    break;
                                case 5:
                                    //fieldName = "PHONE NUMBER";
                                    strcpy(personnel[session_id].phoneNumber, newValue);
                                    break;
                                case 6:
                                    //fieldName = "EMAIL ADDRESS";
                                    strcpy(personnel[session_id].email, newValue);
                                    break;
                                case 7:
                                    //fieldName = "PASSWORD";
                                    strcpy(personnel[session_id].password, password_A);
                                    break;
                            }

                            selectionSortByID_Ascending();
                            write_DatabaseUtility();
                            read_DatabaseUtility();

                            printf("\n\n\t\t\t\t  \a*** Record Successfully UPDATED! *** ");
                            system("pause");
                            editProfileActivity(context);
                        }else{
                            if(context == context_editProfileActivity){
                                print_EditProfileActivityHeader(session_id);
                            }else if(context == context_ADMIN_editOtherProfileActivity){
                                print_ADMIN_EditProfileActivity_Header(session_id);
                            }
                            goto reEntering;
                        }
                        break;
                    case 2:
                        /// Go back to favorite activity
                        selectionSortByID_Ascending();
                        editProfileActivity(context);
                        break;
                    case 3:
                        /// Re enter current form field again
                        editStringField(session_id, context);
                        break;
                }
                break;
            default:
                selectionInEdit = 1;
        }

        if(context == context_editProfileActivity){
            print_EditProfileActivityHeader(session_id);
        }else if(context == context_ADMIN_editOtherProfileActivity){
            print_ADMIN_EditProfileActivity_Header(session_id);
        }

        if(selection_editProfileActivity != 7 && selection_editProfileActivity != 4){
            printf("\n\n\t\t\t\t\t< > EDIT YOUR %s\n\n\t\t\t\t\t   - YOUR CURRENT %s: %s", fieldName, fieldName, currentValue);
            printf("\n\n\t\t\t\t\t   - ENTER A NEW %s: ", fieldName);
            printf("%s\n", newValue);
        }else if(selection_editProfileActivity == 7){
            printf("\n\n\t\t\t\t\t< > EDIT YOUR %s\n\n\t\t\t\t\t   - YOUR CURRENT %s: %s", fieldName, fieldName, currentValue);
            printf("\n\n\t\t\t\t\t   - ENTER A NEW %s: ", fieldName);
            printf("%s\n", password_A);
            printf("\n\t\t\t\t\t   - CONFIRM YOUR NEW %s: ", fieldName);
            printf("%s\n", password_B);
        }else if(selection_editProfileActivity == 4){
            printf("\n\n\t\t\t\t\t< > EDIT YOUR %s\n\n\t\t\t\t\t   - YOUR CURRENT %s: %s", fieldName, fieldName,(currentGenderValue == 0)? "Male" : "Female");
            printf("\n\n\t\t\t\t\t   - ENTER A NEW %s: %s\n", fieldName, (newGenderValue == 0)? "Male" : "Female");
        }

        if(isNewInputOkay == 1){
            switch(selectionInEdit){
                case 1:
                    //print_completedForms(selectionInEdit);
                    printf("\n\t\t\t\t[*] CONTINUE\t\t[ ] CANCEL\t\t[ ] CLEAR");
                    break;
                case 2:
                    //print_completedForms(selectionInEdit);
                    printf("\n\t\t\t\t[ ] CONTINUE\t\t[*] CANCEL\t\t[ ] CLEAR");
                    break;
                case 3:
                    //print_completedForms(selectionInEdit);
                    printf("\n\t\t\t\t[ ] CONTINUE\t\t[ ] CANCEL\t\t[*] CLEAR");
                    break;
            }
        }else{
            switch(selectionInEdit){
                case 1:
                    //print_completedForms(selectionInEdit);
                    printf("\n\t\t\t\t\t\t[*] CLEAR\t\t[ ] CANCEL");
                    break;
                case 2:
                    //print_completedForms(selectionInEdit);
                    printf("\n\t\t\t\t\t\t[ ] CLEAR\t\t[*] CANCEL");
                    break;
            }
        }
        printf("\n\n\t\t=========================================================================================================\n");
        printf("\t\tMove the selector by pressing A or D, and Press ENTER to select!");
    }

}

void editProfileActivity(int context){

    read_DatabaseUtility();

    int session_id = -1;
    if(context == context_editProfileActivity){
        reAcquireSessionID();
        session_id = session_Login_id;
        print_EditProfileActivityHeader(session_id);
    }else if(context == context_ADMIN_editOtherProfileActivity){
        session_id = remoteSession_id;
        print_ADMIN_EditProfileActivity_Header(session_id);
    }

    //printf("\n\t\tsession_id = %d\n", session_id);
    char temp_string_gender[6];

    printf("\n\n\t\t\t\t\tYOUR ID\n\t\t\t\t\t   - %07d (You are %s)\n\n", personnel[session_id]._id, (personnel[session_id].adminStatus == 0)? "a Student" : "an Administrator");
    printf("\n\t\t\t\t\t[*] FIRST NAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].firstName);
    printf("\n\t\t\t\t\t[ ] SURNAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].lastName);

    //genderCodeToString(personnel[session_id].gender, temp_string_gender);
    printf("\n\t\t\t\t\t[ ] GENDER\n\t\t\t\t\t   - %s\n\n", (personnel[session_id].gender == 0)? "Male" : "Female");

    printf("\n\t\t\t\t\t[ ] PHONE NUMBER\n\t\t\t\t\t   - %s\n\n", personnel[session_id].phoneNumber);
    printf("\n\t\t\t\t\t[ ] EMAIL ADDRESS\n\t\t\t\t\t   - %s\n\n", personnel[session_id].email);
    printf("\n\t\t\t\t\t[ ] PASSWORD\n\t\t\t\t\t   - make sure you can remember it\n\n");
    printf("\n\t\t\t\t\t[ ] GO BACK\n\t\t\t\t\t   - save data and return to profile menu\n\n");
    printf("\n\t\t=========================================================================================================\n");
    printf("\t\tMove the selector by pressing W or S, and Press ENTER to select!");

    selection_editProfileActivity = 2;
    while(1){
        switch(getch()){
            case 'S':
            case 's':
                // code for arrow right
                selection_editProfileActivity++;
                if(selection_editProfileActivity > 8){
                    selection_editProfileActivity = 8;
                }
                break;
            case 'W':
            case 'w':
                // code for arrow left
                selection_editProfileActivity--;
                if(selection_editProfileActivity < 2){
                    selection_editProfileActivity = 2;
                }
                break;
            case 13:
                switch(selection_editProfileActivity){
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        editStringField(session_id, context);
                        //genderCodeToString(personnel[session_id].gender, temp_string_gender);
                        break;
                    case 8:
                        userProfileMenuActivity();
                        break;
                }
                break;
            default:
                selection_editProfileActivity = 2;
        }

        system("cls");

        if(context == context_editProfileActivity){
            print_EditProfileActivityHeader(session_id);
        }else if(context == context_ADMIN_editOtherProfileActivity){
            print_ADMIN_EditProfileActivity_Header(session_id);
        }
        //printf("\n\t\tsession_id = %d\n", session_id);

        switch(selection_editProfileActivity){
            case 1:
                printf("\n\n\t\t\t\t\tYOUR ID\n\t\t\t\t\t   - %07d (You are %s)\n\n", personnel[session_id]._id, (personnel[session_id].adminStatus == 0)? "a Student" : "an Administrator");
                printf("\n\t\t\t\t\t[ ] FIRST NAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].firstName);
                printf("\n\t\t\t\t\t[ ] SURNAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].lastName);
                printf("\n\t\t\t\t\t[ ] GENDER\n\t\t\t\t\t   - %s\n\n", (personnel[session_id].gender == 0)? "Male" : "Female");
                printf("\n\t\t\t\t\t[ ] PHONE NUMBER\n\t\t\t\t\t   - %s\n\n", personnel[session_id].phoneNumber);
                printf("\n\t\t\t\t\t[ ] EMAIL ADDRESS\n\t\t\t\t\t   - %s\n\n", personnel[session_id].email);
                printf("\n\t\t\t\t\t[ ] PASSWORD\n\t\t\t\t\t   - make sure you can remember it\n\n");
                printf("\n\t\t\t\t\t[ ] GO BACK\n\t\t\t\t\t   - save data and return to profile menu\n\n");
                break;
            case 2:
                printf("\n\n\t\t\t\t\tYOUR ID\n\t\t\t\t\t   - %07d (You are %s)\n\n", personnel[session_id]._id, (personnel[session_id].adminStatus == 0)? "a Student" : "an Administrator");
                printf("\n\t\t\t\t\t[*] FIRST NAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].firstName);
                printf("\n\t\t\t\t\t[ ] SURNAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].lastName);
                printf("\n\t\t\t\t\t[ ] GENDER\n\t\t\t\t\t   - %s\n\n", (personnel[session_id].gender == 0)? "Male" : "Female");
                printf("\n\t\t\t\t\t[ ] PHONE NUMBER\n\t\t\t\t\t   - %s\n\n", personnel[session_id].phoneNumber);
                printf("\n\t\t\t\t\t[ ] EMAIL ADDRESS\n\t\t\t\t\t   - %s\n\n", personnel[session_id].email);
                printf("\n\t\t\t\t\t[ ] PASSWORD\n\t\t\t\t\t   - make sure you can remember it\n\n");
                printf("\n\t\t\t\t\t[ ] GO BACK\n\t\t\t\t\t   - save data and return to profile menu\n\n");
                break;
            case 3:
                printf("\n\n\t\t\t\t\tYOUR ID\n\t\t\t\t\t   - %07d (You are %s)\n\n", personnel[session_id]._id, (personnel[session_id].adminStatus == 0)? "a Student" : "an Administrator");
                printf("\n\t\t\t\t\t[ ] FIRST NAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].firstName);
                printf("\n\t\t\t\t\t[*] SURNAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].lastName);
                printf("\n\t\t\t\t\t[ ] GENDER\n\t\t\t\t\t   - %s\n\n", (personnel[session_id].gender == 0)? "Male" : "Female");
                printf("\n\t\t\t\t\t[ ] PHONE NUMBER\n\t\t\t\t\t   - %s\n\n", personnel[session_id].phoneNumber);
                printf("\n\t\t\t\t\t[ ] EMAIL ADDRESS\n\t\t\t\t\t   - %s\n\n", personnel[session_id].email);
                printf("\n\t\t\t\t\t[ ] PASSWORD\n\t\t\t\t\t   - make sure you can remember it\n\n");
                printf("\n\t\t\t\t\t[ ] GO BACK\n\t\t\t\t\t   - save data and return to profile menu\n\n");
                break;
            case 4:
                printf("\n\n\t\t\t\t\tYOUR ID\n\t\t\t\t\t   - %07d (You are %s)\n\n", personnel[session_id]._id, (personnel[session_id].adminStatus == 0)? "a Student" : "an Administrator");
                printf("\n\t\t\t\t\t[ ] FIRST NAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].firstName);
                printf("\n\t\t\t\t\t[ ] SURNAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].lastName);
                printf("\n\t\t\t\t\t[*] GENDER\n\t\t\t\t\t   - %s\n\n", (personnel[session_id].gender == 0)? "Male" : "Female");
                printf("\n\t\t\t\t\t[ ] PHONE NUMBER\n\t\t\t\t\t   - %s\n\n", personnel[session_id].phoneNumber);
                printf("\n\t\t\t\t\t[ ] EMAIL ADDRESS\n\t\t\t\t\t   - %s\n\n", personnel[session_id].email);
                printf("\n\t\t\t\t\t[ ] PASSWORD\n\t\t\t\t\t   - make sure you can remember it\n\n");
                printf("\n\t\t\t\t\t[ ] GO BACK\n\t\t\t\t\t   - save data and return to profile menu\n\n");
                break;
            case 5:
                printf("\n\n\t\t\t\t\tYOUR ID\n\t\t\t\t\t   - %07d (You are %s)\n\n", personnel[session_id]._id, (personnel[session_id].adminStatus == 0)? "a Student" : "an Administrator");
                printf("\n\t\t\t\t\t[ ] FIRST NAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].firstName);
                printf("\n\t\t\t\t\t[ ] SURNAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].lastName);
                printf("\n\t\t\t\t\t[ ] GENDER\n\t\t\t\t\t   - %s\n\n", (personnel[session_id].gender == 0)? "Male" : "Female");
                printf("\n\t\t\t\t\t[*] PHONE NUMBER\n\t\t\t\t\t   - %s\n\n", personnel[session_id].phoneNumber);
                printf("\n\t\t\t\t\t[ ] EMAIL ADDRESS\n\t\t\t\t\t   - %s\n\n", personnel[session_id].email);
                printf("\n\t\t\t\t\t[ ] PASSWORD\n\t\t\t\t\t   - make sure you can remember it\n\n");
                printf("\n\t\t\t\t\t[ ] GO BACK\n\t\t\t\t\t   - save data and return to profile menu\n\n");
                break;
            case 6:
                printf("\n\n\t\t\t\t\tYOUR ID\n\t\t\t\t\t   - %07d (You are %s)\n\n", personnel[session_id]._id, (personnel[session_id].adminStatus == 0)? "a Student" : "an Administrator");
                printf("\n\t\t\t\t\t[ ] FIRST NAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].firstName);
                printf("\n\t\t\t\t\t[ ] SURNAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].lastName);
                printf("\n\t\t\t\t\t[ ] GENDER\n\t\t\t\t\t   - %s\n\n", (personnel[session_id].gender == 0)? "Male" : "Female");
                printf("\n\t\t\t\t\t[ ] PHONE NUMBER\n\t\t\t\t\t   - %s\n\n", personnel[session_id].phoneNumber);
                printf("\n\t\t\t\t\t[*] EMAIL ADDRESS\n\t\t\t\t\t   - %s\n\n", personnel[session_id].email);
                printf("\n\t\t\t\t\t[ ] PASSWORD\n\t\t\t\t\t   - make sure you can remember it\n\n");
                printf("\n\t\t\t\t\t[ ] GO BACK\n\t\t\t\t\t   - save data and return to profile menu\n\n");
                break;
            case 7:
                printf("\n\n\t\t\t\t\tYOUR ID\n\t\t\t\t\t   - %07d (You are %s)\n\n", personnel[session_id]._id, (personnel[session_id].adminStatus == 0)? "a Student" : "an Administrator");
                printf("\n\t\t\t\t\t[ ] FIRST NAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].firstName);
                printf("\n\t\t\t\t\t[ ] SURNAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].lastName);
                printf("\n\t\t\t\t\t[ ] GENDER\n\t\t\t\t\t   - %s\n\n", (personnel[session_id].gender == 0)? "Male" : "Female");
                printf("\n\t\t\t\t\t[ ] PHONE NUMBER\n\t\t\t\t\t   - %s\n\n", personnel[session_id].phoneNumber);
                printf("\n\t\t\t\t\t[ ] EMAIL ADDRESS\n\t\t\t\t\t   - %s\n\n", personnel[session_id].email);
                printf("\n\t\t\t\t\t[*] PASSWORD\n\t\t\t\t\t   - make sure you can remember it\n\n");
                printf("\n\t\t\t\t\t[ ] GO BACK\n\t\t\t\t\t   - save data and return to profile menu\n\n");
                break;
            case 8:
                printf("\n\n\t\t\t\t\tYOUR ID\n\t\t\t\t\t   - %07d (You are %s)\n\n", personnel[session_id]._id, (personnel[session_id].adminStatus == 0)? "a Student" : "an Administrator");
                printf("\n\t\t\t\t\t[ ] FIRST NAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].firstName);
                printf("\n\t\t\t\t\t[ ] SURNAME\n\t\t\t\t\t   - %s\n\n", personnel[session_id].lastName);
                printf("\n\t\t\t\t\t[ ] GENDER\n\t\t\t\t\t   - %s\n\n", (personnel[session_id].gender == 0)? "Male" : "Female");
                printf("\n\t\t\t\t\t[ ] PHONE NUMBER\n\t\t\t\t\t   - %s\n\n", personnel[session_id].phoneNumber);
                printf("\n\t\t\t\t\t[ ] EMAIL ADDRESS\n\t\t\t\t\t   - %s\n\n", personnel[session_id].email);
                printf("\n\t\t\t\t\t[ ] PASSWORD\n\t\t\t\t\t   - make sure you can remember it\n\n");
                printf("\n\t\t\t\t\t[*] GO BACK\n\t\t\t\t\t   - save data and return to profile menu\n\n");
                break;
        }
        printf("\n\t\t=========================================================================================================\n");
        printf("\t\tMove the selector by pressing W or S, and Press ENTER to select!");
    }

    return 0;
}
