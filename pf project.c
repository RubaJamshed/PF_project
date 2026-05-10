
#include <stdio.h>
#include <string.h>

// Function prototypes
int authenticateController(const char *password);
int checkWeatherConditions(int windSpeed, int visibility);
int checkPlaneStatus(int fuel, int engineStatus);
int takeoffConflicts(int distanceBetweenPlanes);

int main() {
    char password[20];
    int windSpeed, visibility, fuel, engineStatus, distanceBetweenPlanes;

    // Authentication
    printf("Enter controller password: ");
    scanf("%s", password);
    if (authenticateController(password) == 0) {  // Explicitly check for failure
        printf("Authentication failed. Access denied.\n");
        return 1;  // Exit with error code 1
    }
    printf("Authentication successful.\n");

    // Weather check
    printf("Enter wind speed (in km/h): ");
    scanf("%d", &windSpeed);
    printf("Enter visibility (in meters): ");
    scanf("%d", &visibility);
    if (checkWeatherConditions(windSpeed, visibility) == 0) {  // Explicitly check for failure
        printf("Unsafe weather conditions. Operation not allowed.\n");
        return 2;  // Exit with error code 2
    }
    printf("Weather conditions are safe for operation.\n");

    // Aircraft status check
    printf("Enter plane fuel level (in percentage) ");
    scanf("%d", &fuel);
    printf("Enter plane engine status (1 for operational, 0 for not operational): ");
    scanf("%d", &engineStatus);
    if (checkPlaneStatus(fuel, engineStatus) == 0) {  // Explicitly check for failure
        printf("Plane is not ready for operation.\n");
        return 3;  // Exit with error code 3
    }
    printf("Plane is ready for operation.\n");

    // Conflict detection
    printf("Enter distance between planes (in meters): ");
    scanf("%d", &distanceBetweenPlanes);
    if (takeoffConflicts(distanceBetweenPlanes) == 0) {  // Explicitly check for failure
        printf("Conflict detected! Operation not allowed.\n");
        return 4;  // Exit with error code 4
    }
    printf("No conflicts detected. Safe to proceed.\n");

    // Final clearance
    printf("Aircraft is cleared for operation.\n");
    return 0;  // Exit with success code
}

// Function 1: Authentication Module
int authenticateController(const char *password) {
    const char *correctPassword = "AT123c";
    if (strcmp(password, correctPassword) == 0) {  // Returns 1 if correct password
        return 1;
    }
    return 0;  // Returns 0 for incorrect password
}

// Function 2: Weather Check Module
int checkWeatherConditions(int windSpeed, int visibility) {
    if (windSpeed <= 40 && visibility >= 1000) {
        return 1;  // Safe weather conditions
    }
    return 0;  // Unsafe weather conditions
}

// Function 3: Aircraft Status Check Module
int checkPlaneStatus(int fuel, int engineStatus) {
    if (fuel >= 50 && engineStatus == 1) {
        return 1;  // Plane is operational
    }
    return 0;  // Plane is not operational
}

// Function 4: Conflict Detection Module
int takeoffConflicts(int distanceBetweenPlanes) {
    if (distanceBetweenPlanes >= 300) {
        return 1;  // Safe distance between planes
    }
    return 0;  // Unsafe distance
}   
    
    