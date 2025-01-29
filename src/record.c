#include "raylib.h"
#include "record.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


// Function to save player name, date, and score
void SavePlayerRecord(const char *filename, const char *playerName, int score) {
    FILE *file = fopen(filename, "a"); // Open file in append mode
    if (file) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        fprintf(file, "%s,%04d-%02d-%02d %02d:%02d:%02d,%d\n", playerName,
                t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                t->tm_hour, t->tm_min, t->tm_sec, score);
        fclose(file);
    } else {
        printf("Failed to open the file!\n");
    }
}

// Function to handle end-game input
void EndGameAndSaveRecord(int score) {
    const int screenWidth = 1800;
    const int screenHeight = 1200;

    //InitWindow(screenWidth, screenHeight, "Enter Your Name");
    //SetTargetFPS(60);

    char playerName[30] = ""; // Buffer for the player's name
    int letterCount = 0;
    bool nameSubmitted = false;

    while (!WindowShouldClose() && !nameSubmitted) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        char bf[100];
        sprintf(bf,"Game over. YOUR SCORE = %d",score);
        DrawText(bf, 110, 20, 20, RED);
        DrawText("Enter your name:", 10, 80, 20, DARKGRAY);
        DrawRectangle(10, 120, 480, 40, LIGHTGRAY);
        DrawText(playerName, 15, 130, 20, BLACK);

        DrawText("Press ENTER to submit", 10, 170, 20, DARKGRAY);

        EndDrawing();

        // Handle input
        if (IsKeyPressed(KEY_ENTER) && letterCount > 0) {
            nameSubmitted = true; // Name is submitted
        } else if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0) {
            letterCount--;
            playerName[letterCount] = '\0';
        } else if (letterCount < 29) { // Limit name to 29 characters
            int key = GetKeyPressed();
            if ((key >= 32) && (key <= 125)) { // Printable characters
                playerName[letterCount] = (char)key;
                playerName[letterCount + 1] = '\0';
                letterCount++;
            }
        }
    }

    if (nameSubmitted) {
        SavePlayerRecord("records.txt", playerName, score);
    }

    //CloseWindow(); // Close the input window
}
int LoadRecords(Record records[]) {
    FILE *file = fopen(RECORD_FILE, "r");
    if (!file) {
        printf("Failed to open records file!\n");
        return 0;
    }

    int count = 0;
    char line[100];

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Parse the line into the Record struct
        if (sscanf(line, "%49[^,],%19[^,],%d", records[count].playerName, records[count].date, &records[count].score) == 3) {
            count++;
            if (count >= MAX_RECORDS) break; // Stop if we exceed max records
        }
    }

    fclose(file);
    return count;
}

// Compare function for sorting records by score (descending)
int CompareRecords(const void *a, const void *b) {
    Record *recordA = (Record *)a;
    Record *recordB = (Record *)b;
    return recordB->score - recordA->score; // Sort in descending order
}
void RenderRecordsScreen() {
    Record records[MAX_RECORDS];
    int recordCount = LoadRecords(records);

    // Sort records by score in descending order
    qsort(records, recordCount, sizeof(Record), CompareRecords);

    // Render the records
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Top 10 High Scores", 50, 50, 40, RED);

    for (int i = 0; i < recordCount && i < 10; i++) { // Show top 10 records
        char recordText[100];
        sprintf(recordText, "%d. %s | %s | %d", i + 1, records[i].playerName, records[i].date, records[i].score);
        DrawText(recordText, 50, 100 + i * 30, 20, WHITE);
    }

    DrawText("Press ENTER to return to menu", 50, 100 + (recordCount < 10 ? recordCount : 10) * 30 + 10, 20, WHITE);

    EndDrawing();
}