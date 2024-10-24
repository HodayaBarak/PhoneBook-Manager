#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 26
#define TEN  10
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define ZERO 0
#define FIRST_LETTER 'A'
#define MAGICNUM 32
#define TRUE 1
#define FALSE 0

//struct of linked list
typedef struct contact{

    char* firstName;
    char* lastName;
    char* phoneNum;
    struct contact* next;
} contact;

/************************************************************************
* function name: menu *
* The Input: void *
* The output: print the menu*
* The Function operation: the function prints the menu*
*************************************************************************/
void menu (){
    printf("Welcome to the phone book manager!\n"
           "Choose an option:\n"
           "1. Add a new contact to the phone book.\n"
           "2. Delete a contact from the phone book.\n"
           "3. Find a contact in the phone book by phone number.\n"
           "4. Find a contact in the phone book by name.\n"
           "5. Update phone number for a contact.\n"
           "6. Print phone book.\n"
           "7. Exit.\n");
}
/************************************************************************
* function name: checkIfcontactNameExist *
* The Input: pointer in the array to the first struct in the linked list *
* The output: if the first and last name exist returns FALSE, else - TRUE*
* The Function operation: the function checks if the full name already exist in
 * in all the structs in the linked list*
*************************************************************************/
int checkIfContactNameExist (contact* phonebook[] ,char fName[], char lName[]){

    for (int i = ZERO; i <MAX ; ++i) {
        contact *exist = phonebook[i];
        if (exist==NULL){
            continue;
        } else {
            //check if the firstName or lastName already existed
            while (exist != NULL) {
                if ((strcmp(exist->firstName, fName) == ZERO)
                    && (strcmp(exist->lastName, lName) == ZERO)) {
                    return FALSE;
                } else {
                    exist = exist->next;
                }
            }
        }
    }
    return TRUE;

}
/************************************************************************
* function name: checkIfcontactPhoneNumExist *
* The Input: pointer in the array to the first struct in the linked list *
* The output: if the first and last name exist returns FALSE, else - TRUE*
* The Function operation: the function checks if the full name already exist in
 * in all the structs in the linked list*
*************************************************************************/
int checkIfContactPhoneNumExist (contact* phonebook[] ,char phoneNum[]){

    for (int i = ZERO; i <MAX ; ++i) {
        contact *exist = phonebook[i];
        if (exist == NULL) {
            continue;
        } else {
            //check if the values already existed
            while (exist != NULL) {
                if (strcmp(exist->phoneNum, phoneNum) == ZERO) {
                    return FALSE;
                } else {
                    exist = exist->next;
                }
            }
        }
    }
    return TRUE;

}
/************************************************************************
* function name: deleteContact *
* The Input: array of pointers to linked lists *
* The output: tells the user if the deletion succeed or failed *
* The Function operation: the function gets first&last name from user, than
 * checks if the contact exist. if not - prints the deletion has failed.
 * else - it asks the user if he sure. if no- prints the deletion canceled.
 * if yes - checks all the structs in the linked, when it gets the contact that
 * the user wants to delete it connects the previous struct (if there is one)
 * to the next struct and deletes the contact*
*************************************************************************/
void deleteContact (contact* phonebook []) {
    char firstName[TEN + ONE], lastName[TEN + ONE];
    char delete_sure;
    int check;
    printf("Enter a contact name (<first name> <last name>): ");
    scanf("%s %s", firstName, lastName);
    //check if the contact exist
    check = checkIfContactNameExist(phonebook, firstName, lastName);
    //if contact doesn`t exist
    if (check != ZERO) {
        printf("The deletion of the contact has failed!\n");
        return;
    }
        //if contact does exist
    else{
        printf("Are you sure? (y/n) ");
        scanf("%c", &delete_sure);
        // if user sure about the deletion
        if (delete_sure == 'y' || delete_sure == 'Y') {
//            int first_Family_letter = lastName[ZERO] - FIRST_LETTER;
            int first_Family_letter = toupper(lastName[ZERO]) - FIRST_LETTER;

            contact *current = phonebook[first_Family_letter];
            contact *prev;
            //check if the first struct in the linked list is the contact that
            // the user wants to delete
            if ((strcmp(current->firstName,firstName)==ZERO)&&
                (strcmp(current->lastName,lastName)==ZERO)){
                //if next struct =NULL
                if (current->next==NULL){
                    free(current->firstName);
                    free(current->lastName);
                    free(current->phoneNum);
                    phonebook[first_Family_letter]=NULL;
                    free(current);
                    printf("The contact has been deleted successfully!\n");
                    return;
                }
                    //if next struct != NULL
                else {
                    phonebook[first_Family_letter]=current->next;
                    free(current->firstName);
                    free(current->lastName);
                    free(current->phoneNum);
                    free(current);
                    printf("The contact has been deleted successfully!\n");
                    return;
                }
            }
                //if the first struct isn`t the contact that the
                //user wants to delete
            else{
                current = current->next;
                prev = phonebook[first_Family_letter];
                prev->next=current;
                contact* next;
                while (current !=NULL){
                    //checks if the next struct in the linked list match to
                    // the contact that the user wants to delete
                    if ((current->firstName==firstName)&&
                        (current->lastName==lastName)){
                        //if next != NULL
                        if (current->next!=NULL) {
                            prev->next = current->next;
                            free(current->firstName);
                            free(current->lastName);
                            free(current->phoneNum);
                            free(current);
                            printf("The contact has been deleted successfully!\n");
                            return;
                        }
                            //if next ==NULL
                        else {
                            free(current->firstName);
                            free(current->lastName);
                            free(current->phoneNum);
                            prev->next=NULL;
                            free(current);
                            printf("The contact has been deleted successfully!\n");
                            return;
                        }

                    }
                        //if the next struct isn`t the contact that the
                        //user wants to delete - moving to the next struct
                    else {
                        next = current;
                        prev->next = next;
                        current= current->next;
                        next->next= current;
                    }

                }
            }
        }
            // if user inputs != 'Y' \ 'y'
        else {
            printf("\nThe deletion of the contact has been canceled.\n");
        }


    }
}


/************************************************************************
* function name: printPhonebook *
* The Input: array of pointers to linked lists *
* The output: prints all the exist linked lists*
* The Function operation: the function checks if the the pointer in the array
 * isn`t NULL and prints all the contact in the linked lists for every pointer*
*************************************************************************/
void printPhonebook (contact* phonebook[]){
    for (int i=ZERO; i < MAX; ++i) {
        contact *temp = phonebook[i];
        if (temp == NULL) {
            continue;
        }
        if (temp != NULL) {
            while (temp != NULL) {
                printf("%10s %10s %10s\n", temp->firstName,
                       temp->lastName, temp->phoneNum);
                temp = temp->next;
            }
//            //check if OK
//            temp = phonebook[i];
//            printf("\n");
//            while (temp != NULL) {
//                printf("%p", temp);
//                temp = temp->next;
        }

    }
}

/************************************************************************
* function name: freeAll *
* The Input: array of pointers to linked lists *
* The output: free all the pointers in the array*
* The Function operation: the function free all the fields of each pointer
 * and the pointer itself*
*************************************************************************/
void freeAll (contact* phonebook []){
    for (int i = ZERO; i <MAX ; ++i) {
        //if the place in the array is empty
        if (phonebook[i]==NULL){
            continue;
        } else{
            //free all fields and the pointer
            free(phonebook[i]->firstName);
            free(phonebook[i]->lastName);
            free(phonebook[i]->phoneNum);
            free(phonebook[i]->next);
            free(phonebook[i]);
        }
    }
}





/************************************************************************
* function name: searchNum *
* The Input: array of pointers to linked lists *
* The output: prints the contact that the user search by phone number*
* The Function operation: the function asks the user to input phone number
 * than search the phone number in the array of the pointers,
 * if it founds, it prints the contact details. else, it prints the user that
 * the contact doesn`t exist*
*************************************************************************/
void searchNum (contact* phonebook []){

    char phoneNum [TEN+ONE];
    printf("Enter a phone number:' '");
    scanf("%s", phoneNum);
    //checks all the pointers in the array
    for (int i = ZERO; i <MAX ; ++i) {
        contact* searchNum = phonebook [i];
        //if NULL - moving to the nest pointer
        if (searchNum == NULL){
            continue;
        }
            // if not NULL
        else {
            //check if the phone number match to the phone number the user input
            while (searchNum != NULL) {
                //if there is a match - prints contact details
                if (strcmp(searchNum->phoneNum, phoneNum) == ZERO) {
                    printf("The following contact was found: %s %s"
                           " %s\n", searchNum->firstName, searchNum->lastName,
                           searchNum->phoneNum);
                    return;
                }
                    //else - moving to the next contact in the list
                else {
                    searchNum = searchNum->next;
                    //if the next = NULL
                    if (searchNum->next == NULL){
                        continue;
                    }
                }
            }
        }
    }
    //if there is no contact with this phone number
    printf("No contact with a phone number %s was found in the phone "
           "book\n", phoneNum);
}

/************************************************************************
* function name: searchName *
* The Input: array of pointers to linked lists *
* The output: prints the contact that the user search by first&last name*
* The Function operation: the function asks the user to input first&last name
 * than search the first&last name in the array according to the first letter
 * of the family name, if it founds, it prints the contact details. else,
 * it prints the user that the contact does`nt exist*
*************************************************************************/
void searchNameContact (contact* phonebook[]){
    char firstName [TEN + ONE], lastName [TEN + ONE];
    printf("Enter a contact name (<first name> <last name>):  ");
    scanf("%s %s", firstName, lastName);

    //check first letter in the family name for the place in the array
//    int first_Family_letter = lastName[ZERO] - FIRST_LETTER;
    int first_Family_letter = toupper(lastName[ZERO]) - FIRST_LETTER;

    contact* searchName = phonebook[first_Family_letter];

    //if the array for this family first letter is NULL
    if (searchName == NULL){
        printf("No contact with a name %s %s was found in the"
               " phone book\n", firstName, lastName);
        return;
    }
    //if the array for this first family letter isn`t NULL
    while (searchName != NULL){
        //check if first&last name match to the first&last name the user input
        if ((strcmp(searchName->firstName, firstName) == ZERO)
            && (strcmp(searchName->lastName, lastName) == ZERO)){
            printf("The following contact was found: %s %s %s\n",
                   searchName->firstName, searchName->lastName,
                   searchName->phoneNum);
            return;
        }
            //else - moving to the next contact in the list
        else {
            searchName = searchName->next;
            //if the next = NULL
            if (searchName == NULL){
                printf("No contact with a name %s %s was found in the"
                       " phone book\n", firstName, lastName);
                return;
            }
        }
    }
}

/************************************************************************
* function name: updatePhoneNumber *
* The Input: array of pointers to linked lists *
* The output: update the phone number*
* The Function operation: the function asks the user to input first&last name
 * than search the first&last name in the array according to the first letter
 * of the family name. if the contact does`nt exist it prints the user that the
 * contact does`nt exist. if it founds, it prints the contact details and asks the
 * user to input a new phone number. than it checks if the phone number already
 * exist for other contact, if so- it prints that phone number already exist.
 * else,it update the phone number and prints that the phone number update*
*************************************************************************/
void updatePhoneNumber (contact* phonebook []) {
    char firstName[TEN + ONE], lastName[TEN + ONE], phoneNumber[TEN + TWO];
    int check_exist;
    printf("Enter a contact name (<first name> <last name>): ");
    scanf("%s %s", firstName, lastName);

    //check first letter in the family name for the place in the array
//    int first_Family_letter = lastName[ZERO] - FIRST_LETTER;
    int first_Family_letter = toupper(lastName[ZERO]) - FIRST_LETTER;

    contact *updatePhoneNum = phonebook[first_Family_letter];

    //if the array for this family first letter is NULL
    if (updatePhoneNum == NULL) {
        printf("No contact with a name %s %s was found in the"
               " phone book", firstName, lastName);
        return;
    }

    //if the array for this first family letter isn`t NULL
    while (updatePhoneNum != NULL) {
        //check if first&last name match to the first&last name the user input
        if ((strcmp(updatePhoneNum->firstName, firstName) == ZERO)
            && (strcmp(updatePhoneNum->lastName, lastName) == ZERO)) {
            printf("The following contact was found: %s %s %s\n",
                   updatePhoneNum->firstName, updatePhoneNum->lastName,
                   updatePhoneNum->phoneNum);
            printf("Enter the new phone number: ");
            scanf("%s", phoneNumber);
            //check if the phone number already exist
            check_exist = checkIfContactPhoneNumExist(phonebook,
                                                      phoneNumber);
            //if the phone number doesn`t exist
            if (check_exist == TRUE) {
                strcpy(updatePhoneNum->phoneNum, phoneNumber);
                printf("The contact has been updated successfully!\n");
                return;
            }
                //if the phone number already exist
            else {
                printf("The update of the contact has failed, since the"
                       " phone number %s already exists!\n", phoneNumber);
                return;

            }
        }
            // if there is no match to the first connected list
        else {
            updatePhoneNum = updatePhoneNum->next;
            //if the next = NULL
            if (updatePhoneNum->next == NULL) {
                printf("No contact with a name %s %s was found in the"
                       " phone book", firstName, lastName);
                return;
            }
        }
    }
}

/************************************************************************
* function name: addContact *
* The Input: array of pointers to linked lists *
* The output: insert the details from the user to the linked list in an
 * alphabet order*
* The Function operation: the function checks gets first&lase name and
 * phone number from the user, than it checks if the pointer in the array(for the
 * first letter of the last name) is null. if so - it allocate memory for the
 * struct and for all his fields, else - it checks if the contact that the user
 * insert is already exist, if not - it adds the contact by the same way as it
 * adds thr first struct in the linked list, and the field 'next' gets the
 * pointer of the previous struct the we add*
*************************************************************************/
void addContact (contact* phonebook[]){
    int check_exist_Name, check_exist_PhoneNum;
    //pointer to struct
    contact *ptr_contact_head= NULL;
    contact *ptr_contact = NULL;
    char firstName[TEN+ONE], lastName[TEN+ONE], phoneNumber[TEN + TWO];

    //get values from user
    printf("Enter a contact details (<first name> <last name>"
           " <phone number>):\n");
    scanf("%s", firstName);
    scanf("%s", lastName);
    scanf("%s", phoneNumber);

    //check first letter in the family name for the place in the array
    //int first_Family_letter = lastName[ZERO] - FIRST_LETTER;
    int first_Family_letter = toupper(lastName[ZERO]) - FIRST_LETTER;

    //check if the contact name already exist
    check_exist_Name = checkIfContactNameExist(phonebook,(char *) firstName,
                                               (char *) lastName);
    //check if the contact phone already exist
    check_exist_PhoneNum = checkIfContactPhoneNumExist(phonebook,
                                                       (char*) phoneNumber);


    //if contact name already exist
    if (check_exist_Name==ZERO){
        printf("The addition of the contact has failed, since the "
               "contact %s %s already exists!\n",firstName, lastName);
        return;
    }
        //if contact phoneNumber already exist
    else if (check_exist_PhoneNum==ZERO) {
        printf("The addition of the contact has failed, since the "
               "phone number %s already exists!\n", phoneNumber);
        return;
    }

    //check if there is value in the array
    if (phonebook[first_Family_letter] == NULL) {

        //allocate memory for struct
        ptr_contact = (contact *) malloc(sizeof(contact));


        //if allocate memory failed
        if (ptr_contact == NULL) {
            printf("The addition of the contact has failed!\n");
            exit(ONE);
        }

        //check string length
        int len_firstname = (int)strlen(firstName);
        int len_lastname = (int)strlen(lastName);
        int len_phonenum = (int) strlen(phoneNumber);


        //allocate memory for each field
        ptr_contact->firstName = (char *) malloc((len_firstname + ONE) *
                                                 sizeof(char));
        //if allocate failed
        if (ptr_contact->firstName == NULL) {
            free(ptr_contact);
            exit(ONE);
        }
        ptr_contact->lastName = (char *) malloc(
                (len_lastname + ONE) * sizeof(char));
        //if allocate failed
        if (ptr_contact->lastName == NULL) {
            free(ptr_contact->firstName);
            free(ptr_contact);
            exit(ONE);
        }
        ptr_contact->phoneNum = (char *) malloc(
                (len_phonenum + ONE) * sizeof(char));
        //if allocate failed
        if (ptr_contact->phoneNum == NULL) {
            free(ptr_contact->firstName);
            free(ptr_contact->lastName);
            free (ptr_contact);
            exit(ONE);
        }

        //copy strings values to the allocate memory in the struct
        strcpy(ptr_contact->firstName, firstName);
        strcpy(ptr_contact->lastName, lastName);
        strcpy(ptr_contact->phoneNum, phoneNumber);
        ptr_contact->next = NULL;
        printf("The contact has been added successfully!\n");
        printf("Added contact: %s %s %s\n", ptr_contact->firstName, ptr_contact->lastName, ptr_contact->phoneNum);

        phonebook[first_Family_letter] = ptr_contact;
        return;
    }
        // if there is value in the array
    else if (phonebook[first_Family_letter] != NULL){
        ptr_contact_head = (contact *) malloc(sizeof(contact));
        if (ptr_contact_head == NULL) {
            printf("The addition of the contact has failed!\n");
            exit(ONE);
        }
        //check string length
        int len_firstname = (int)strlen(firstName);
        int len_lastname = (int)strlen(lastName);
        int len_phonenum = (int) strlen(phoneNumber);

        //allocate memory for each field
        ptr_contact_head->firstName = (char *) malloc((len_firstname+ONE)
                                                      *sizeof(char));
        //if allocate failed
        if (ptr_contact_head->firstName == NULL) {
            free(ptr_contact_head);
            exit(ONE);
        }
        ptr_contact_head->lastName = (char *) malloc(
                (len_lastname + ONE) * sizeof(char));
        //if allocate failed
        if (ptr_contact_head->lastName == NULL) {
            free(ptr_contact_head->firstName);
            free(ptr_contact_head);
            exit(ONE);
        }
        ptr_contact_head->phoneNum = (char *) malloc(
                (len_phonenum + ONE) * sizeof(char));
        //if allocate failed
        if (ptr_contact_head->phoneNum == NULL) {
            free(ptr_contact_head->firstName);
            free(ptr_contact_head->lastName);
            free (ptr_contact_head);
            exit(ONE);
        }

        //copy strings values to the allocate memory in the struct
        strcpy(ptr_contact_head->firstName, firstName);
        strcpy(ptr_contact_head->lastName, lastName);
        strcpy(ptr_contact_head->phoneNum, phoneNumber);
        ptr_contact_head->next = phonebook[first_Family_letter];
        phonebook[first_Family_letter] = ptr_contact_head;
        printf("The contact has been added successfully!\n");
        return;
    }


}






int main() {
    int choice;
    //declaration on array of pointers to the struct
    contact* phonebook [MAX];
    for (int i = 0; i < MAX; ++i) {
        phonebook [i] = NULL;
    }

    while (ONE) {
        menu();
        scanf("%d",&choice);

        switch (choice) {
            case ONE: {
                addContact(phonebook);
                break;
            }
            case TWO:{
                deleteContact(phonebook);
                break;
            }
            case THREE:{
                searchNum(phonebook);
                break;
            }
            case FOUR:{
                searchNameContact(phonebook);
                break;
            }
            case FIVE:{
                updatePhoneNumber(phonebook);
                break;
            }
            case SIX:{
                printPhonebook(phonebook);
                break;
            }
            case SEVEN:{
                freeAll(phonebook);
                printf("Bye!\n");
                return ZERO;
            }

            default:{
                printf("Wrong option, try again: ");
                scanf("%d",&choice);
                break;
            }

        }
    }








    return 0;
}
