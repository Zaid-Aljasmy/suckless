/* microphone custom */

#include <stdio.h>    // FILE, popen, pclose, fgets
#include <string.h>   // strstr, strcspn, snprintf

#include "../slstatus.h"

const char *
mic_status(const char *arg) {
    static char status[16];
    char muted[16];
    FILE *fp;

    fp = popen("pactl get-source-mute @DEFAULT_SOURCE@", "r");
    if (!fp)
        return "Err";

    if (fgets(muted, sizeof(muted), fp) == NULL) {
        pclose(fp);
        return "Err";
    }
    pclose(fp);

    muted[strcspn(muted, "\n")] = 0;

    if (strstr(muted, "yes") || strstr(muted, "1"))
        snprintf(status, sizeof(status), "muted");
    else if (strstr(muted, "no") || strstr(muted, "0"))
        snprintf(status, sizeof(status), "on");
    else
        snprintf(status, sizeof(status), "Err");

    return status;
}

