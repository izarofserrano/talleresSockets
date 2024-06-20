#include "logger.h"

void logMessage(const char* format, ...) {
    FILE *logFile = fopen("server.log", "a");
    if (logFile == NULL) {
        perror("Error opening log file");
        return;
    }

    // Get current time
    time_t rawtime;
    struct tm *timeinfo;
    char timeStr[20];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Write the timestamp to the log file
    fprintf(logFile, "[%s] ", timeStr);

    // Write the formatted log message
    va_list args;
    va_start(args, format);
    vfprintf(logFile, format, args);
    va_end(args);

    // Write a new line and close the file
    fprintf(logFile, "\n");
    fclose(logFile);
}
