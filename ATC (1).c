#include<stdio.h>
#include<string.h>



int authenticateController(const char *password) {
    const char correctPassword[] = "AT123c";
    if (strcmp(password, correctPassword) == 0) {
        return 1;  // Success
    }
    return 0;  // Failure
}


int checkWeatherConditions(int windSpeed, int visibility) {
    if (windSpeed <= 40 && visibility >= 1000) {
        return 1; 
    }
    return 0;  
}


int checkPlaneStatus(int fuel, int engineStatus) {
    if (fuel >= 50 && engineStatus == 1) {
        return 1;  
    }
    return 0; 
}

int takeoffconflict(int distanceBetweenPlanes) {
    if (distanceBetweenPlanes >= 300) {
        return 1;  
    }
    return 0;  
}




typedef enum {
    CRITICAL = 1,
    SEVERE = 2,
    MODERATE = 3,
    NORMAL = 4
} SeverityLevel;

void handleEmergency(const char *code, const char *description, SeverityLevel level) 
{
    printf("\n=!!! Emergency Detected !!!==\n");
    printf("Emergency Code: %s\n", code);
    printf("Description: %s\n", description);

    switch (level) {
        case CRITICAL:
            printf("Severity: Critical\n");
            printf("Action: REDIRECTING TO UPPER CONTROL ROOM IMMEDIATELY!\n");
            break;
        case SEVERE:
            printf("Severity: Severe\n");
            printf("Action: High urgency. All personnel on board. \n");
            break;
        case MODERATE:
            printf("Severity: Moderate\n");
            printf("Action: Monitor the situation. Prepare for potential escalation. Contact if needed.\n");
            break;
        case NORMAL:
            printf("Severity: Normal\n");
            printf("Action: Routine operation. No immediate concerns. Proceed as normal.\n");
            break;
        default:
            printf("Unknown severity level.\n");
            break;
    }
    printf("================================\n");
}

void filesearch(const char *filename, const char *code) 
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file");
        return;
    }
    char line[256];
    char fileCode[10];
    char description[100];
    int level;
    int found = 0; 
    while (fgets(line, sizeof(line), file)) {
        
        sscanf(line, "%[^:]:%[^:]:%d", fileCode, description, &level);
        if (strcmp(fileCode, code) == 0) {
            handleEmergency(fileCode, description, level);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Emergency Code %s not found. Incorrect code. Stay calm, pilot, and try again.\n", code);
    }
    fclose(file);
}




typedef struct{
		char id[20];
		int time;
		int isemergency;
	} flight;

int isauthorized(char *id)
{
	int i;
	const char *authorizedplane[] = {"A495","B729","J616"};
	int count = 3;
	for(i=0 ; i<count ; i++)
	{
		if(strcmp(id, authorizedplane[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int landingconflict(flight aircraft, flight scheduled[], int count)
{
	int i;
	for(i=0 ; i<count ; i++)
	{
		if(aircraft.time == scheduled[i].time)
		{
			printf("Conflict Detected: %s and %s has the same landing time\n", aircraft.id, scheduled[i].id);
			return 1;
		}
	}
	return 0;
}

//Ruba


int main() {
	
    char password[20];
    int windSpeed, visibility, fuel, engineStatus, distanceBetweenPlanes;
    
    printf("Enter controller password: ");
    scanf("%s", password);
    if (authenticateController(password) == 0) {  
        printf("Authentication failed. Access denied.\n");
        return 1;  
    }
    printf("Authentication successful.\n\n\n");

    
    printf("Enter wind speed (in km/h): ");
    scanf("%d", &windSpeed);
    printf("Enter visibility (in meters): ");
    scanf("%d", &visibility);
    if (checkWeatherConditions(windSpeed, visibility) == 0) {  
        printf("Unsafe weather conditions. Operation not allowed.\n");
        return 2;  
    }
    printf("Weather conditions are safe for operation.\n\n\n");

   
    printf("Enter plane fuel level (in percentage) ");
    scanf("%d", &fuel);
    printf("Enter plane engine status (1 for operational, 0 for not operational): ");
    scanf("%d", &engineStatus);
    if (checkPlaneStatus(fuel, engineStatus) == 0) {  
        printf("Plane is not ready for operation.\n");
        return 3;  
    }
    printf("Plane is ready for operation.\n\n");

   
    printf("Enter distance between planes (in meters): ");
    scanf("%d", &distanceBetweenPlanes);
    if (takeoffconflict(distanceBetweenPlanes) == 0) {  
        printf("Conflict detected! Operation not allowed.\n");
        return 4;  
    }
    printf("No conflicts detected. Safe to proceed.\n");

    
    printf("Plane is ready for take-off. Have a safe flight!\n\n");

    
    
    //Sehla
    flight scheduled[3];
	int count = 0;
	int i;
	
	while(1)
	{
	printf("\n\n---------------------ENTER AIRCRAFT(LANDING/IN-AIR) DETAILS-------------------------------\n");
	
	flight aircraft;
	printf("Enter aircraft id:    ");
	scanf("%s", &aircraft.id);
	for(i=0 ; i<count ; i++)
	{
	if(strcmp(aircraft.id, "exit") == 0)
	{
		printf("Exiting\n");
		break;
	}
	}
	printf("Enter time left to land(in minutes):  ");
	scanf("%d", &aircraft.time);
	printf("Is it a emergency landing(Enter 1 for yes and 0 for no):  ");
	scanf("%d", &aircraft.isemergency);
	if(aircraft.isemergency)
	{
		printf("---------EMERGENCY ALERT-----------\n");
		printf("%s is being directed to control room\n\n\n", aircraft.id);
		//hiba
		
		
    char code[10];
    printf("Enter transponder code Pilot: ");
    scanf("%s", code);
    
    filesearch("emergency_codes.txt", code);
    
	}
	else if(!isauthorized(aircraft.id))
	{
		printf("Unauthorized id\n");
		printf("flight %s is not allowed to land\n", aircraft.id);
		return 0;
	}
	else if(landingconflict(aircraft, scheduled, count))
	{
		printf("Landing denied for flight %s due to conflicts \n", aircraft.id);
		return 0;
	}
	else 
	{
		scheduled[count++] = aircraft;
		printf("Landing Approved\n");
	}
}
    return 0;
}
