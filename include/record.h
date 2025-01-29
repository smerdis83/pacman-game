
#ifndef RECORD_H
#define RECORD_H

#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_RECORDS 1000
#define RECORD_FILE "records.txt"
typedef struct {
    char playerName[30];
    int score;
    char date[30]; // Date format: YYYY-MM-DD
} Record;
// Function to save the player's name, date, and score to a file
void SavePlayerRecord(const char *filename, const char *playerName, int score);

// Function to display a window, take the player's name input, and save the record
void EndGameAndSaveRecord(int score);
int CompareRecords(const void *a, const void *b);
int LoadRecords(Record records[]);
void RenderRecordsScreen();

#endif // RECORD_H
