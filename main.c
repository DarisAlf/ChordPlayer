#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <unistd.h>

//To compile this program on your own, install the MinGW compiler and reset your settings in CodeBlocks to default.
//Add "winmm" in the "linker" tab. This is necessary to run the function "playsound"


LPCTSTR chords[15] = {"No Sound" ,"C Major", "D Minor", "E Minor", "F Major", "G Major", "A Minor", "E Major",
                      "C Major Half", "D Minor Half", "E Minor Half", "F Major Half", "G Major Half", "A Minor Half", "E Major Half"};

struct node
{
    int chords;
    struct node *next;
};

struct node *head = NULL;
FILE *chordFile;

void playChord(int i);
void printChord(int i);
void printDisplay();
void insert(int chords);
void deleteChord();
void Reverse(struct node* head);
void playProgression(struct node *head);
int chooseFile(int choice);
void readFile();
void writeFile();
void deleteAllChord();
int getInteger();

int main()
{

    int errorchecker;

    printf("=========================================\n");
    printf("Welcome to ChordPlayer !!!\n");
    printf("=========================================\n");
    printf("\nPress enter to continue...");
    getchar();
    fflush(stdin);

    while (1)
    {
        int choice = 0;
        int stop = 0;
        int halfCounter = 0;

        deleteAllChord();
        system("cls");
        printf("===================================================\n");
        printf("                   ChordPlayer\n");
        printf("===================================================\n\n");
        printf("Menu\n");
        printf("1. Create file\n");
        printf("2. Play file\n");
        printf("3. Exit\n");
        printf("Your choice: ");

        while (choice = getInteger())
        {
            if (choice == 1) {
                printf("Enter the file's name: ");
                chooseFile(choice);
                break;
            }
            else if (choice == 2) {
                printf("Enter the file's name: ");
                if (chooseFile(choice) != 1) {
                    printf("File does not exist!");
                    getchar();
                    fflush(stdin);
                };
                break;
            }
            else if (choice == 3) {
                return 0;
            }
            else {
                printf("ERROR");
            }
        }

        printDisplay(choice);

        int chordCounter = 0;
        if (choice == 1)
        {
            while (stop == 0)
            {
                int chordNumber;

                printf("Input Code:\n [1] C Major [8] 1/2 C Major\n [2] D Minor [9] 1/2 D Minor\n [3] E Minor [10] 1/2 E Minor\n [4] F Major [11] 1/2 F Major\n [5] G Major [12] 1/2 G Major\n [6] A Minor [13] 1/2 A Minor\n [7] E Major [14] 1/2 E Major\n [15] Delete [16] Finish    \n\n");
                printf("Chord %d : ", chordCounter + 1);

                fflush(stdin);


                while(chordNumber = getInteger())
                {
                    if (halfCounter % 2 != 0)
                    {
                        if (chordNumber >= 8 && chordNumber <= 15)
                            break;
                        else if (chordNumber == 16)
                            printf("Please add a half chord to finish: ");
                        else
                            printf("Enter between 8 to 14: ");
                    }
                    else
                    {
                        if (chordNumber >= 1 && chordNumber <= 16)
                        break;
                    else
                        printf("Enter between 1 to 14: ");
                    }
                }

                if (chordNumber > 7 && chordNumber < 15)
                {
                    halfCounter += 1;
                }

                if (chordNumber >= 1 && chordNumber <= 14) {
                    insert(chordNumber);
                    chordCounter++;
                }

                else if (chordNumber == 15) {
                    if (head->chords > 7 && head->chords < 15)
                        halfCounter -= 1;
                        deleteChord();
                    if (chordCounter >= 1) {
                        printf("Nothing to delete!");
                        chordCounter--;
                    }
                }

                else if (chordNumber == 16)
                    stop = 1;

                printDisplay(choice);
            }
            writeFile();
            fclose(chordFile);
            printf("Your file has been saved!");
            }

        else
        {
            readFile();
            printf("Playing: \n");
            playProgression(head);
            fclose(chordFile);
        }
    }
}

int chooseFile(int choice) {
    int sucess = 0;
    fflush(stdin);
    char fname[20];
    char *fn = malloc(strlen(fname+5));
    fgets(fname, 20, stdin);
    fname[strcspn(fname, "\n")] = 0;
    sprintf(fn, "%s.txt", fname);
    if (choice == 1) {
        chordFile = fopen(fn, "w");
        sucess = 1;
    }
    else {
        if (chordFile = fopen(fn, "r")) {
            sucess = 1;
        }
    }
    free(fn);
    return sucess;
}

void readFile() {
    char buffer[255];
    int chordNumber;
    while(fgets(buffer, 255, chordFile)) {
        buffer[strcspn(buffer, "\n")] = 0;
        sscanf(buffer, "%d", &chordNumber);
        insert(chordNumber);
    }
}

void writeFile() {
    fflush(chordFile);
    struct node *temp = head;
    while (temp != NULL) {
        fprintf(chordFile, "%d\n", temp->chords);
        temp = temp->next;
    }
}

void printDisplay(int choice)
{
    struct node *temp = head;

    system("cls");
    printf("===================================================\n");
    printf("                   ChordPlayer\n");
    printf("===================================================\n\n");
    if (choice == 1) {
        printf("Current chords:\n");
        Reverse(temp);
        printf("_ ");
    }
    printf("\n\n");
}

void playProgression(struct node *head)
{
    struct node *temp = head;
    while (temp != NULL) {
        printChord(temp->chords);
        playChord(temp->chords);
        temp = temp->next;
    }
}

void Reverse(struct node *head)
{
    if (head == NULL)
       return;
    Reverse(head->next);
    printChord(head->chords);
}


void playChord(int i)
{
    PlaySound(chords[i], NULL, SND_SYNC);
}

void printChord(int i)
{
    switch(i)
    {
    case 1: printf("C "); break;
    case 2: printf("Dm "); break;
    case 3: printf("Em "); break;
    case 4: printf("F "); break;
    case 5: printf("G "); break;
    case 6: printf("Am "); break;
    case 7: printf("E "); break;
    case 8: printf("C "); break;
    case 9: printf("Dm "); break;
    case 10: printf("Em "); break;
    case 11: printf("F "); break;
    case 12: printf("G "); break;
    case 13: printf("Am "); break;
    case 14: printf("E "); break;
    default: i=i-1;
    }
}

void insert(int chords) {
   struct node *link = (struct node*) malloc(sizeof(struct node));

   link->chords = chords;
   link->next = head;
   head = link;
}

void deleteChord() {
    if (head != NULL) {
        struct node *temp = head;
        head = head->next;
        free(temp);
    }
}

void deleteAllChord() {
    struct node *temp = head;
    while (temp != NULL) {
        free(temp);
        temp = temp->next;
    }
    head = NULL;
}

int getInteger()
{
    char *end, str[20];
    int number;
    while(fgets(str, sizeof(str), stdin))
    {
        number = strtol(str, &end, 10);
        if (end == str || *end != '\n')
        {
            printf("Invalid input, please re-input: ");
        }
        else
            return number;
    }
}

