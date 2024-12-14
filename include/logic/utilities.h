#include <time.h>

/**
 * Gets current time and formats it in YYYY-MM-DDTHH:MM:SS into dest
 * @pre dest has at least 20 allocated spaces
 * @post dest is in YYYY-MM-DDTHH:MM:SS format with the current time in UTC
 */
void getFormattedTime(char *dest);