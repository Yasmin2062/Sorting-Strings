
/*----------------------------------------------------------------------------------------------------------------------
                                          STUDENT NAME: YASMIN MUIN JWABREH
                                                 STUDENT ID: 1180815
                                                      PROJECT #1
                                                 RADIX SORT FOR STRINGS
--------------------------------------------------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000

typedef struct str {
    char string[15];
    int length;
    struct str *next;
} str;
/* Buckets For Sorting */
typedef struct ch {
    str *head;
    str *tail;
} ch;
char filename[20];
/* Global Array That Holds The Strings After Sorting */
char a[MAXCHAR][15];

/* Global Array That Holds The Strings Before Sorting */
char b[MAXCHAR][15];

/* Global Variable That Holds The Number Of Strings */
int numOfStrings = 0;

/* Global Pointer To Hold The Head Of The Linked List */
str *head;

/* Display The Main Menu Of The Program */
void menu();

/* Function The Reads The Strings From A Given Filename */
void readString();

/* Function The Checks If The Linked List Is Empty */
int isEmpty(str *);

/*Function That Start Sorting The Strings */
void SortStrings(int);

/* Function The Buckets The Strings Recording On The Ascii Value */
void BucketingStrings( ch *, int);

/* Function That Return The Ascii Value For A Given Character */
int convert(char c);

/* Prints The Strins Before Sorting Them */
void printBeforeSort();

/* Function That Fills The Buckets Of The Character Linked Lists */
str *FillingBuckets(ch *);

/*Function The Prints The Strings After Sorting */
void printAfterSort();

/* Function That Empties The Buckets */
void initialBucket(ch *buckets);


/* Function The Prints The Linked List */
void printLL(const ch *);


int main() {
    printf("\n---------------- WELCOME TO MY RADIX SORT FOR STRINGS PROGRAM! -------------------\n");
    menu();
}

// ------------------------------------------------------ Menu ------------------------------------------------------ //
void menu() {

    int choice;
//printf("---------------------------------------------------------------------\n");
    printf("                      ->         MENU         <-                      \n");
    printf("         PLEASE ENTER THE NUMBER OF THE OPTION YOU WANT TO RUN NEXT.         \n");
    printf("         1. Read The Input file                     \n");
    printf("         2. Print The Strings Before Sorting                                 \n");
    printf("         3. Sort The Strings.                                 \n");
    printf("         4. Print The Strings After Sorting.                             \n");
    printf("         5. Exit the program.                        \n");
    scanf("%d", &choice);
    if (choice == 1) {
        readString(filename);
    }
    if (choice == 2) {
        printBeforeSort();
    }
    if (choice == 3) {
        SortStrings(numOfStrings);
    }
    if (choice == 4) {
        printAfterSort();
        printf("   ________________________________________________________________  \n");
    }

    if (choice == 5) {
        printf("         EXITING FROM THE PROGRAM..");
        exit(1);
    } else
        printf("         OOPS! YOU ENTERED AN INVALID NUMBER\n");

}
// ----------------------------------------- Read Strings From The Text File ---------------------------------------- //

void readString() {
    printf("       Enter The Name Of The File That Contains The Strings You Want To Sort: \n");
    printf("                  Make Sure That You Write it As (filename.txt)                \n");
    scanf("%s", filename);
    FILE *fp;
    char str[MAXCHAR];
    fp = fopen(filename, "r");
    if (NULL == fp) {
        printf("       Oops! Could Not Open File %s", filename);
        exit(0);
    }
    while (fgets(str, MAXCHAR, fp) != NULL) {
        char *token = strtok(str, "\n");
        token = strtok(str, " ");
        strcpy(a[numOfStrings], token);
        strcpy(b[numOfStrings],token);

        numOfStrings += 1;
    }
    printf("--------------------------------------------------------------------------\n");
    printf("       YOU READ THE STRINGS FROM %s FILE SUCCESSFULLY!\n\n", filename);

    fclose(fp);
    menu();
}

// ------------------------------------------ Print Strings Before Sorting ------------------------------------------ //

void printBeforeSort() {
    int i = 0;
    printf("         The Strings Before Sorting: \n");

    while (i != numOfStrings) {
        printf("    %d:    %s\n", i + 1, b[i]);
        i++;
    }
    printf("   ________________________________________________________________  \n");
    menu();
}

// ----------------------------------------- Sort The Strings By Radix Sort ----------------------------------------- //

void SortStrings(int numOfStrings) {
    // str *head;
    int i;
    str *strings = malloc(numOfStrings * sizeof(str));
    if (isEmpty(strings)) {
        printf("OUT OF MEMORY! \n ");
        free(strings);
    }
    int temp, longest = 0;
    for (temp = 0; temp < numOfStrings; temp++) {
        strcpy(strings[temp].string, a[temp]);
        strings[temp].length = strlen(a[temp]);
        if (strings[temp].length > longest)
            longest = strings[temp].length;
        if (temp < numOfStrings - 1)
            strings[temp].next = &strings[temp + 1];
        else
            strings[temp].next = NULL;
    }
    ch arrBucket[26];
    initialBucket(arrBucket);
    head = strings;
    printf("         The Linked Lists Of Sorting Is As Folllows: \n");

    for (i = 0; i < longest; i++) {
        BucketingStrings( arrBucket, i);
        printLL(arrBucket);
        head = FillingBuckets(arrBucket);
        initialBucket(arrBucket);
    }
    /* Copy back into array */
    const str *current;
    int temporar;
    for (current = head, temporar = 0; current != NULL; current = current->next, temporar++) {
        strcpy(a[temporar], current->string);
    }
    //StringsSorted();
    //free(arrBucket);
    free(strings);
    printf("         The Strings Are Sorted Successfully! \n");
    printf("   ________________________________________________________________  \n");

    menu();
}
// -------------------------------------------- Initializing The Buckets -------------------------------------------- //

void initialBucket(ch *buckets) {
    unsigned int K;
    for (K = 0; K < 26; K++) {
        buckets[K].head = NULL;
        buckets[K].tail = NULL;
    }
}
// -------------------------------- Bucketing The Strings Depending On The Ascii Code ------------------------------- //

void BucketingStrings( ch buckets[], int c) {
    str *current = head;
    while (current != NULL) {
        str *next = current->next;
        current->next = NULL;
        int pos = current->length - 1 - c;
        char cha;
        int place;
        if (pos < 0) {
            place = 0;
        } else {
            cha = current->string[pos];
            place = convert(cha);
        }
        if (buckets[place].head == NULL) {
            buckets[place].head = current;
            buckets[place].tail = current;
        } else {
            buckets[place].tail->next = current;
            buckets[place].tail = buckets[place].tail->next;
        }
        current = next;
    }
}
// --------------------------------------- Check If The Linked List Is Empty ---------------------------------------- //

int isEmpty(str *list) {
    if (!list)
        return 1;
    return 0;
}
// ------------------------------------- The Ascii Value For A Given Character -------------------------------------- //

int convert(char c) {
    int ci;
    ci = (int) c;
    if (ci >= 97 && ci <= 122)
        ci -= 97;
    else
        ci -= 65;
    return ci;
}

// ---------------------------------------------- Print The Linked List --------------------------------------------- //

void printLL(const ch *buckets) {
    unsigned int temporar;

    for (temporar = 0; temporar < 26; temporar++) {
        if (buckets[temporar].head != NULL) {
            const str *entry;
            printf("    [%d] ", temporar);
            for (entry = buckets[temporar].head; entry != NULL; entry = entry->next) {
                printf("%s", entry->string);
                if (entry->next) {
                    printf(" -> ");
                }
            }
            printf("\n");
        }
    }
    printf("\n");
}
// ----------------------------------------- Filling The Bucket Linked Lists ---------------------------------------- //

str *FillingBuckets(ch *buckets) {
    head = NULL;
    str *tail = NULL;
    unsigned int temporar;
    for (temporar = 0; temporar < 26; temporar++) {
        if (buckets[temporar].head != NULL) {
            if (head == NULL) {
                head = buckets[temporar].head;
                tail = buckets[temporar].tail;
            } else {
                tail->next = buckets[temporar].head;
                tail = buckets[temporar].tail;
            }
        }
    }
    return head;
}
// -------------------------------------------- Print The Strings Sorted -------------------------------------------- //

void printAfterSort() {
    int i = 0;
    printf("         The Strings After Sorting: \n");

    while (i != numOfStrings) {
         printf("    %d:    %s\n", i + 1, a[i]);
        i++;
    }
    printf("   ________________________________________________________________  \n");
    menu();
}