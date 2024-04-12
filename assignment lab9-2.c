#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order; 
};

// Node structure for the linked list in the hash table
struct Node {
    struct RecordType record;
    struct Node *next;
};

// HashType structure that contains the hash table
struct HashType {
    struct Node **heads; // Array of pointers to the head of the chains
    int size; // Size of the hash table
};

// Function to compute the hash key
int hash(int key, int tableSize) {
    return key % tableSize;
}

// Function to parse data from a file into an array of RecordType
int parseData(char* inputFileName, struct RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    if (!inFile) {
        printf("File could not be opened.\n");
        return 0;
    }

    fscanf(inFile, "%d", &dataSz);
    *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
    if (*ppData == NULL) {
        printf("Memory allocation failed.\n");
        fclose(inFile);
        return 0;
    }

    for (int i = 0; i < dataSz; ++i) {
        fscanf(inFile, "%d %c %d", &(*ppData)[i].id, &(*ppData)[i].name, &(*ppData)[i].order);
    }
    fclose(inFile);
    return dataSz;
}

// Function to print all records
void printRecords(struct RecordType* pData, int dataSz) {
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n");
}

// Function to insert a record into the hash table
void insert(struct HashType* hashTable, struct RecordType newRecord) {
    int index = hash(newRecord.id, hashTable->size);
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Failed to allocate memory for new node.\n");
        return;
    }
    newNode->record = newRecord;
    newNode->next = hashTable->heads[index];
    hashTable->heads[index] = newNode;
}

// Function to display all records in the hash table
void displayRecordsInHash(struct HashType* hashTable) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < hashTable->size; ++i) {
        struct Node* current = hashTable->heads[i];
        printf("Index %d -> ", i);
        while (current != NULL) {
            printf("[%d, %c, %d] -> ", current->record.id, current->record.name, current->record.order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Main function
int main(void) {
    struct RecordType* pRecords;
    int recordSz = parseData("input.txt", &pRecords);
    if (recordSz == 0) {
        return 1;
    }

    printRecords(pRecords, recordSz);

    struct HashType hashTable;
    hashTable.size = 10; // Set size of hash table as needed
    hashTable.heads = (struct Node**) malloc(sizeof(struct Node*) * hashTable.size);
    for (int i = 0; i < hashTable.size; ++i) {
        hashTable.heads[i] = NULL;
    }

    for (int i = 0; i < recordSz; ++i) {
        insert(&hashTable, pRecords[i]);
    }

    displayRecordsInHash(&hashTable);

    // Code to free memory would go here

    return 0;
}

