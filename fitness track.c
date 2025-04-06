#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enumeration for exercise types
enum ExerciseType {
    RUNNING = 1,
    SWIMMING = 2,
    CYCLING = 3
};

// Structure to hold exercise data
struct Exercise {
    enum ExerciseType type;
    int duration;
    int calories;
};

// Function prototypes
int calculateCalories(enum ExerciseType type, int duration);
void displayResults(struct Exercise exercise);
const char* getExerciseName(enum ExerciseType type);

// Calculate calories based on exercise type and duration
int calculateCalories(enum ExerciseType type, int duration) {
    switch (type) {
        case RUNNING:
            return duration * 10;  // 10 calories per minute
        case SWIMMING:
            return duration * 8;   // 8 calories per minute
        case CYCLING:
            return duration * 6;   // 6 calories per minute
        default:
            return 0;
    }
}

// Get exercise name from type
const char* getExerciseName(enum ExerciseType type) {
    switch (type) {
        case RUNNING:
            return "Running";
        case SWIMMING:
            return "Swimming";
        case CYCLING:
            return "Cycling";
        default:
            return "Unknown";
    }
}

// Display exercise results in a formatted way
void displayResults(struct Exercise exercise) {
    printf("\n=========================\n");
    printf("Exercise Summary\n");
    printf("=========================\n");
    printf("Type: %s\n", getExerciseName(exercise.type));
    printf("Duration: %d minutes\n", exercise.duration);
    printf("Calories Burned: %d\n", exercise.calories);
    printf("=========================\n");
}

int main() {
    struct Exercise exercise;
    char continue_tracking;
    int valid_input;

    printf("Welcome to Fitness Tracker Calorie Calculator!\n");

    do {
        // Get exercise type
        do {
            printf("\nSelect exercise type:\n");
            printf("1. Running\n");
            printf("2. Swimming\n");
            printf("3. Cycling\n");
            printf("Choice: ");
            
            valid_input = scanf("%d", (int*)&exercise.type);
            while (getchar() != '\n');  // Clear input buffer
            
            if (!valid_input || exercise.type < 1 || exercise.type > 3) {
                printf("Invalid input! Please enter 1, 2, or 3.\n");
            }
        } while (!valid_input || exercise.type < 1 || exercise.type > 3);

        // Get duration
        do {
            printf("Enter duration in minutes: ");
            valid_input = scanf("%d", &exercise.duration);
            while (getchar() != '\n');  // Clear input buffer
            
            if (!valid_input || exercise.duration <= 0) {
                printf("Invalid duration! Please enter a positive number.\n");
            }
        } while (!valid_input || exercise.duration <= 0);

        // Calculate calories
        exercise.calories = calculateCalories(exercise.type, exercise.duration);

        // Display results
        displayResults(exercise);

        // Ask if user wants to continue
        do {
            printf("\nCalculate another exercise? (y/n): ");
            scanf(" %c", &continue_tracking);
            while (getchar() != '\n');  // Clear input buffer
            
            if (continue_tracking != 'y' && continue_tracking != 'Y' && 
                continue_tracking != 'n' && continue_tracking != 'N') {
                printf("Invalid input! Please enter 'y' or 'n'.\n");
            }
        } while (continue_tracking != 'y' && continue_tracking != 'Y' && 
                continue_tracking != 'n' && continue_tracking != 'N');

    } while (continue_tracking == 'y' || continue_tracking == 'Y');

    printf("\nThank you for using Fitness Tracker Calorie Calculator!\n");
    return 0;
}
