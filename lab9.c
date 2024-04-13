#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// HashType structure
struct HashType
{
    struct RecordType data;
    struct HashType *next; 
};

// Compute the hash function
int hash(int x)
{
    
    return x % 10; 
}

// Function to parse input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }
        fclose(inFile);
    }

    return dataSz;
}

// Function to print records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// Function to display records in the hash structure
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;

    for (i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);
        struct HashType *current = pHashArray[i].next;
        while (current != NULL)
        {
            printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table
    struct HashType hashArray[10]; 
    // Fill with empty linked lists
    for (int i = 0; i < 10; ++i)
    {
        hashArray[i].next = NULL;
    }

    // Insert records
    for (int i = 0; i < recordSz; ++i)
    {
        int index = hash(pRecords[i].id);
        struct HashType *newNode = (struct HashType *)malloc(sizeof(struct HashType));
        if (newNode == NULL)
        {
            printf("Memory allocation failed\n");
            exit(-1);
        }
        newNode->data = pRecords[i];
        newNode->next = NULL;

        // If empty, insert new node as head
        if (hashArray[index].next == NULL)
        {
            hashArray[index].next = newNode;
        }
        else
        {
            // If not empty, insert new node at the end
            struct HashType *current = hashArray[index].next;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Display records
    displayRecordsInHash(hashArray, 10); 

    // Free memory
    free(pRecords);

    return 0;
}
