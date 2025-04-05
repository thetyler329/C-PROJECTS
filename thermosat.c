#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COMFORT_RANGE 3.0

float convertToFahrenheit(float celsius) {
    return (celsius * 9.0/5.0) + 32.0;
}

char* checkComfortLevel(float current, float desired) {
    if(current < (desired - COMFORT_RANGE)) {
        return "Heating";
    } else if(current > (desired + COMFORT_RANGE)) {
        return "Cooling";
    } else {
        return "Ideal";
    }
}

struct TempSensor {
    float currentTemp;
    float desiredTemp;
    bool isActive;
    char* status;
};

void initializeSensor(struct TempSensor* sensor) {
    sensor->currentTemp = 22.0;
    sensor->desiredTemp = 24.0;
    sensor->isActive = true;
    sensor->status = "Ideal";
}

void updateTemperature(struct TempSensor* sensor, float newTemp) {
    sensor->currentTemp = newTemp;
    float currentF = convertToFahrenheit(newTemp);
    float desiredF = convertToFahrenheit(sensor->desiredTemp);
    sensor->status = checkComfortLevel(currentF, desiredF);
}

void displayStatus(struct TempSensor* sensor) {
    printf("\nTemperature Status:\n");
    printf("Current: %.1f°C (%.1f°F)\n", 
           sensor->currentTemp, 
           convertToFahrenheit(sensor->currentTemp));
    printf("Desired: %.1f°C (%.1f°F)\n", 
           sensor->desiredTemp, 
           convertToFahrenheit(sensor->desiredTemp));
    printf("Status: %s\n", sensor->status);
}

int main() {
    struct TempSensor sensor;
    float newTemp;
    char choice;
    
    initializeSensor(&sensor);
    
    while(1) {
        printf("\n1. Update temperature\n");
        printf("2. Change desired temperature\n");
        printf("3. Display status\n");
        printf("4. Exit\n");
        printf("Select option: ");
        
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1':
                printf("Enter new temperature (°C): ");
                scanf("%f", &newTemp);
                updateTemperature(&sensor, newTemp);
                displayStatus(&sensor);
                break;
                
            case '2':
                printf("Enter desired temperature (°C): ");
                scanf("%f", &newTemp);
                sensor.desiredTemp = newTemp;
                updateTemperature(&sensor, sensor.currentTemp);
                displayStatus(&sensor);
                break;
                
            case '3':
                displayStatus(&sensor);
                break;
                
            case '4':
                printf("Exiting system\n");
                return 0;
                
            default:
                printf("Invalid option\n");
        }
    }
    
    return 0;
}