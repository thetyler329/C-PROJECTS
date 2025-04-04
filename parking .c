#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FLOORS 3
#define SECTIONS 4
#define EMPTY 0
#define OCCUPIED 1

// Structure to hold parking space coordinates
struct ParkingSpace {
    int floor;
    int section;
};

// Function prototypes
struct ParkingSpace* findAvailableSpace(int garage[FLOORS][SECTIONS]);
bool parkVehicle(int garage[FLOORS][SECTIONS], int floor, int section);
void visualizeGarage(int garage[FLOORS][SECTIONS]);
void initializeGarage(int garage[FLOORS][SECTIONS]);

// Initialize garage with all empty spaces
void initializeGarage(int garage[FLOORS][SECTIONS]) {
    for (int i = 0; i < FLOORS; i++) {
        for (int j = 0; j < SECTIONS; j++) {
            garage[i][j] = EMPTY;
        }
    }
}

// Find an available parking space
struct ParkingSpace* findAvailableSpace(int garage[FLOORS][SECTIONS]) {
    struct ParkingSpace* space = malloc(sizeof(struct ParkingSpace));
    
    for (int floor = 0; floor < FLOORS; floor++) {
        for (int section = 0; section < SECTIONS; section++) {
            if (garage[floor][section] == EMPTY) {
                space->floor = floor;
                space->section = section;
                return space;
            }
        }
    }
    
    // No space found
    space->floor = -1;
    space->section = -1;
    return space;
}

// Park a vehicle in specified location
bool parkVehicle(int garage[FLOORS][SECTIONS], int floor, int section) {
    // Validate input
    if (floor < 0 || floor >= FLOORS || section < 0 || section >= SECTIONS) {
        return false;
    }
    
    // Check if space is available
    if (garage[floor][section] == EMPTY) {
        garage[floor][section] = OCCUPIED;
        return true;
    }
    
    return false;
}

// Visualize current garage occupancy
void visualizeGarage(int garage[FLOORS][SECTIONS]) {
    printf("\nParking Garage Status:\n");
    printf("=====================\n");
    
    // Column headers
    printf("   ");
    for (int j = 0; j < SECTIONS; j++) {
        printf("S%d  ", j + 1);
    }
    printf("\n");
    
    for (int i = 0; i < FLOORS; i++) {
        printf("F%d ", i + 1);
        for (int j = 0; j < SECTIONS; j++) {
            if (garage[i][j] == EMPTY) {
                printf("[  ] ");
            } else {
                printf("[🚗] ");
            }
        }
        printf("\n");
    }
    printf("=====================\n");
    printf("Empty: [  ]  Occupied: [🚗]\n\n");
}

int main() {
    int garage[FLOORS][SECTIONS];
    char choice;
    
    // Initialize garage
    initializeGarage(garage);
    
    while (1) {
        printf("\nParking Garage Management System\n");
        printf("1. Find available space\n");
        printf("2. Park a vehicle\n");
        printf("3. View garage status\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        
        scanf(" %c", &choice);
        while (getchar() != '\n');  // Clear input buffer
        
        switch (choice) {
            case '1': {
                struct ParkingSpace* space = findAvailableSpace(garage);
                if (space->floor == -1) {
                    printf("Garage is full!\n");
                } else {
                    printf("Available space found at Floor %d, Section %d\n", 
                           space->floor + 1, space->section + 1);
                }
                free(space);
                break;
            }
            
            case '2': {
                int floor, section;
                printf("Enter floor number (1-%d): ", FLOORS);
                scanf("%d", &floor);
                printf("Enter section number (1-%d): ", SECTIONS);
                scanf("%d", &section);
                
                if (parkVehicle(garage, floor - 1, section - 1)) {
                    printf("Vehicle parked successfully!\n");
                } else {
                    printf("Failed to park vehicle. Space might be occupied or invalid.\n");
                }
                break;
            }
            
            case '3':
                visualizeGarage(garage);
                break;
                
            case '4':
                printf("Thank you for using Parking Garage Management System!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}