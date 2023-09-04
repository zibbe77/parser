#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// If debugbuild is defined, debug funcitons will be included
#define DEBUG_BUILD

struct IntermeditData
{
    char firstRowName[50];
    char secondRowName[50];
    char weight[4];
};

struct Relationships
{
    char name[100];
    int weight;
};

struct Person
{
    char name[50];
    int numberOfRelationships;
    Relationships relationships[100];
};

enum columns_e
{
    COL_SOURCE,
    COL_TARGET,
    COL_WEIGHT
};

struct Person personsArray[400];
struct IntermeditData intermeditDataArray[400];

// splitrar datan
void BreakString(char *readString, int readStringLenght, IntermeditData *save)
{
    // loop logic
    int column = 0;
    int line = 0;

    for (int i = 0; i < readStringLenght; i++)
    {
        if (readString[i] == '\n')
        {
            break;
        }
        if (readString[i] == ',')
        {
            column++;
            line = 0;
            continue;
        }

        if (column == COL_SOURCE)
        {
            save->firstRowName[line] = readString[i];
        }
        else if (column == COL_TARGET)
        {
            save->secondRowName[line] = readString[i];
        }
        else // COL_WEIGHT
        {
            save->weight[line] = readString[i];
        }
        line++;
    }
}

#ifdef DEBUG_BUILD

// printar splitrade datan
void Debug_PrintIntermidetData(IntermeditData *save, int num)
{
    printf("num %i|%s|%s|%s\n", num, save->firstRowName, save->secondRowName, save->weight);
}

// printar varje person efter den har sorterat dom
void Debug_PrintEveryPerson(Person *target)
{
    for (int i = 0; i < 354; i++)
    {
        printf("num %i|%s|frindes %i \n", i, target[i].name, target[i].numberOfRelationships);
        for (int k = 0; k < target[i].numberOfRelationships; k++)
        {
            printf("%s - %i \n", target[i].relationships[k].name, target[i].relationships[k].weight);
        }
    }
}

#endif

// Orgenserar datan
void OrganizeData(IntermeditData *listofdata, Person *target, int dataPoints)
{
    int pointCount = 0;

    // kollar första namnet
    for (int i = 0; i < dataPoints; i++)
    {

        bool foundName = false;

        for (int j = 0; j < dataPoints; j++)
        {
            // kollar datan
            int sameName = 0;
            for (int L = 0; L < 50; L++)
            {
                if (listofdata[i].firstRowName[L] == target[j].name[L])
                {
                    sameName++;
                }
            }

            // om samma kopierara
            if (sameName == 50)
            {
                // kopierar data
                for (int k = 0; k < 50; k++)
                {
                    target[j].relationships[target[j].numberOfRelationships].name[k] = listofdata[i].secondRowName[k];
                    target[j].relationships[target[j].numberOfRelationships].weight = atoi(listofdata[i].weight);
                }
                target[j].numberOfRelationships++;
                foundName = true;
            }
        }

        if (foundName == false)
        {
            for (int k = 0; k < 50; k++)
            {
                target[pointCount].name[k] = listofdata[i].firstRowName[k];

                target[pointCount].relationships->name[k] = listofdata[i].secondRowName[k];
                target[pointCount].relationships->weight = atoi(listofdata[i].weight);
            }
            target[pointCount].numberOfRelationships++;
            pointCount++;
        }
    }

    // kollar andra namnet
    for (int i = 0; i < dataPoints; i++)
    {

        bool foundName = false;

        for (int j = 0; j < dataPoints; j++)
        {
            // kollar datan
            int sameName = 0;
            for (int L = 0; L < 50; L++)
            {
                if (listofdata[i].secondRowName[L] == target[j].name[L])
                {
                    sameName++;
                }
            }

            // om samma kopierara
            if (sameName == 50)
            {
                // kopierar data
                for (int k = 0; k < 50; k++)
                {
                    target[j].relationships[target[j].numberOfRelationships].name[k] = listofdata[i].firstRowName[k];
                    target[j].relationships[target[j].numberOfRelationships].weight = atoi(listofdata[i].weight);
                }
                target[j].numberOfRelationships++;
                foundName = true;
            }
        }

        if (foundName == false)
        {
            for (int k = 0; k < 50; k++)
            {
                target[pointCount].name[k] = listofdata[i].secondRowName[k];

                target[pointCount].relationships->name[k] = listofdata[i].firstRowName[k];
                target[pointCount].relationships->weight = atoi(listofdata[i].weight);
            }
            target[pointCount].numberOfRelationships++;
            pointCount++;
        }
    }
}

void PrintEveryPersonInAlphabetic(Person *target, int dataPoints)
{
    char finishedSlot[dataPoints];
    for (int i = 0; i < dataPoints; i++)
    {
        finishedSlot[i] = 0;
    }

    for (int i = 0; i < dataPoints; i++)
    {
        int lowestNum[10] = {1000, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int slot = 0;

        for (int j = 0; j < dataPoints; j++)
        {
            if (finishedSlot[j] == 1)
            {
                continue;
            }

            char tempName[50];
            for (int k = 0; k < 50; k++)
            {
                tempName[k] = tolower(target[j].name[k]);
            }

            for (int k = 0; k < 10; k++)
            {
                if (tempName[k] < lowestNum[k])
                {
                    for (int o = 0; o < 10; o++)
                    {
                        lowestNum[0] = tempName[0];
                    }
                    slot = j;
                    break;
                }
            }
        }
        finishedSlot[slot] = 1;
        printf("%s \n", target[slot].name);
    }
}

void PrintEveryRelations(Person *target, int dataPoints)
{
    char input[51];
    bool found = false;

    for (int i = 0; i < 50; i++)
    {
        input[i] = 0;
    }

    printf("%s \n", "skriv ett namn på en karaktär");
    scanf("%50s", input);

    for (int i = 0; i < dataPoints; i++)
    {
        int isTargetName = 0;
        for (int K = 0; K < 50; K++)
        {
            if (input[K] == target[i].name[K])
            {
                isTargetName++;
            }
        }
        if (isTargetName == 50)
        {
            found = true;

            printf("%s \n", "works");

            // sorterar och skriver utt data
            int tempArray[100];
            for (int j = 0; j < 100; j++)
            {
                tempArray[j] = target[i].relationships[j].weight;
                // printf("%i \n", tempArray[j]);
            }

            // körs en gång per rellarion
            for (int p = 0; p < target[i].numberOfRelationships; p++)
            {
                int highestNum = 0;
                int slot = 0;

                // hittar och printar det störst weighten
                for (int o = 0; o < 100; o++)
                {
                    if (tempArray[o] > highestNum)
                    {
                        highestNum = target[i].relationships[o].weight;
                        slot = o;
                    }
                }

                if (highestNum == 0)
                {
                    return;
                }
                // kör efter
                printf("%s - %i \n", target[i].relationships[slot].name, target[i].relationships[slot].weight);
                tempArray[slot] = 0;
            }

            // gå till target
            // se anntal vänner

            return;
        }
    }
    if (found == false)
    {
        printf("%s \n", "Hittade inte namnet");
    }
}

int main()
{
    FILE *fptr = fopen("thrones.csv", "r");

    if (fptr == NULL)
    {
        printf("%s", "fungera inte");
        return -1;
    }

    char myString[100];
    int count = 0;

    while (feof(fptr) != true)
    {
        fgets(myString, 100, fptr);

        BreakString(myString, 100, &intermeditDataArray[count]);
        count++;
    }
    OrganizeData(intermeditDataArray, personsArray, count);
    fclose(fptr);

    // PrintEveryPerson(personsArray);

    // val
    int input[2] = {0, 0};

    while (1)
    {
        printf("%s \n", "Du har 3 val. 1 skriv utt en lista på alla charatärer i alfabetisk ording. 2 visa alla relationer för en visa karatär. 3 avluta programet");
        scanf("%1i", input);

        bool found = false;

        if (input[0] == 1)
        {
            found = true;
            PrintEveryPersonInAlphabetic(personsArray, count);
        }
        if (input[0] == 2)
        {
            found = true;
            PrintEveryRelations(personsArray, count);
        }
        if (input[0] == 3)
        {
            break;
        }

        if (found == false)
        {
            printf("%s \n", "Du måste skriva 1 2 eller 3");
        }
    }

    return 0;
}