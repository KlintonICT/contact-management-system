#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "header.h"

void DEBUG_showAllUserActivity(){
    system("cls");
    int index, size = sizeof(personnel) / sizeof(personnel[0]);
    printf("Size of Personnels Array: %d\n", size);
    printf("Total people in Personnels Array: %d\n", TOTAL_NUMBER_ofPersonnel);
    for(index = 0; index < 50; index++){
        printf("#%d\t %s\t\t%s\t\t\t%d\n", index, personnel[index].firstName, personnel[index].lastName, personnel[index]._id);
    }
    system("pause");
}
