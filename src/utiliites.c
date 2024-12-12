#include "../include/utilities.h"

void getFormattedTime(char * dest){
    // Create a time_t object to store the current time
    time_t rawTime;
    struct tm *timeInfo;

    // Get the current time
    time(&rawTime);

    // Convert time_t to struct tm for local timezone
    timeInfo = gmtime(&rawTime);

    // Format the time as YYYY-MM-DDTHH:MM:SS
    strftime(dest, 20, "%Y-%m-%dT%H:%M:%S", timeInfo);
}