#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

//Sebelum di compile, Install MinGW dan compiler di codeblocks harus di reset. Di Linker settings tambahkan library "winmm"
//mengasign array link ke project file dalam windows.h

LPCTSTR chords[15] = {"No Sound" ,"C Major", "D Minor", "E Minor", "F Major", "G Major", "A Minor", "E Major",
                      "C Major Half", "D Minor Half", "E Minor Half", "F Major Half", "G Major Half", "A Minor Half", "E Major Half"};

void playChord(int i);
void printChord(int i);
void printDisplay(int array[], int limit);
int getInteger();

int main()
{
    int bar = 0;
    int progression [32] = {0};
    int halfCounter = 0;
    int errorchecker;

    printf("=========================================\n");
    printf("Welcome to the ChordPlayer Program   !!!!\n");
    printf("=========================================\n");
    printf("\nPress Enter to Continue...");
    getchar();
    fflush(stdin);
    system("cls");
    printf("===================================================\n");
    printf("                   ChordPlayer\n");
    printf("===================================================\n\n");
    printf("Input the number of bars that you want to play \n\nThe number of bars must be a multiply of 4 and less than 32\n\n");
    printf("Number of Bars: ");

    while (bar = getInteger())
    {
        if (bar >= 0 && bar <= 32 && bar % 4 == 0)
            break;
        else
            printf("Input is invalid, please re-enter : ");
    }

    printDisplay(progression, bar);

    for (int j = 0; j < bar; ++j)
    {
        int chordNumber;

        printf("Input Code:\n [1] C Major [8] 1/2 C Major\n [2] D Minor [9] 1/2 D Minor\n [3] E Minor [10] 1/2 E Minor\n [4] F Major [11] 1/2 F Major\n [5] G Major [12] 1/2 G Major\n [6] A Minor [13] 1/2 A Minor\n [7] E Major [14] 1/2 E Major\n [0] No Sound\n\n");
        printf("Chord %d : ", j + 1);

        fflush(stdin);
        if (halfCounter % 2 != 0)
        {
            while(chordNumber = getInteger())
            {
                if (chordNumber >= 0 && chordNumber <= 14)
                    break;
                else
                    printf("Input is invalid, please re-enter : ");
            }
        }
        else
        {
            while(chordNumber = getInteger())
            {
                if (chordNumber >= 0 && chordNumber <= 14)
                    break;
                else
                    printf("Input is invalid, please re-enter : ");
            }
        }

        progression[j] = chordNumber;

        if (chordNumber > 7 && chordNumber < 15)
        {
            halfCounter += 1;
        }

        if (halfCounter % 2 != 0)
            bar++;

        printDisplay(progression, bar);
    }

    printf("Playing: \n");

    for (int i = 0; i < bar; i++)
    {
        printChord(progression[i]);
        playChord(progression[i]);
    }

    return 0;
}

void printDisplay(int array[], int limit)
{
    system("cls");
    printf("===================================================\n");
    printf("                   ChordPlayer\n");
    printf("===================================================\n\n");
    printf("Chord Progression:\n");

    for (int k = 0; k < limit; ++k)
    {
    if (array[k] != 0)
            printChord(array[k]);
        else
            printf("_ ");
    }
    printf("\n\n");
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

int getInteger()
{
    char *end, str[20];
    int number;
    while(fgets(str, sizeof(str), stdin))
    {
        number = strtol(str, &end, 10);
        if (end == str || *end != '\n')
        {
            printf("Input is invalid, please re-enter : ");
        }
        else
            return number;
    }
}
