#ifndef HEADER_H
#define HEADER_H

    /// Current Login ID (Basically, ID is a number which will be used in Calling Array "personnel")
    extern int session_Login_id;
    extern int remoteSession_id;
    extern int TOTAL_NUMBER_ofPersonnel;

    /// Contexts is responsible for calling a function with different result
    extern int context_loginActivity;
    extern int context_registrationActivity;
    extern int context_editProfileActivity;
    extern int context_ADMIN_editOtherProfileActivity;
    extern int context_searchProfiles;
    extern int context_ADMIN_deleteProfiles;
    extern int context_DATABASE;
    extern int context_favorite;
    extern int context_addFavorite;
    extern int context_removeFavorite;

    /// These Variables are temporary because they will store data of the user who logs in.
    /// Used in reAcquiringIndex
    extern int temporarySessionID;
    extern int temporaryID;
    extern char temporaryFirstName[30];
    extern char temporaryLastName[30];
    extern char temporaryEmail[30];

    /// Structure for information of each individual
    struct contact{
        /// The ID is stored as an Integer because we also want to sort them
        int _id;

        char firstName[30];
        char lastName[30];

        /// 0 for MALE and 1 for FEMALE
        int gender;

        char phoneNumber[20];
        char email[30];
        char password[60];

        /// 0 for NORMAL USER and 1 for ADMIN
        int adminStatus;
        int isDeleted;
        /// Array for Indexes of each user favorite

        /// the Structure for information of each individual
        struct favoriteElement{
            int favoriteIndex;
            int favoriteID;
        }favorite[50];
    };

    extern struct contact personnel[50];

#endif // HEADER_H
