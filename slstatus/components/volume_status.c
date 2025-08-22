/* volume custom */

#include <stdio.h>    // FILE, popen, pclose, fgets
#include <string.h>   // strcmp, strcspn

#include "../slstatus.h"

const char *
volume_status(const char *arg) {
    static char status[32];
    char volume[8], mute[8];
    FILE *fp;

    fp = popen("pactl get-sink-volume @DEFAULT_SINK@ | grep -oP '\\d+%' | head -1", "r");
    if (!fp)
        return "err";
    if (fgets(volume, sizeof(volume), fp) == NULL) {
        pclose(fp);
        return "err";
    }
    pclose(fp);
    volume[strcspn(volume, "\n")] = 0;

    fp = popen("pactl get-sink-mute @DEFAULT_SINK@ | grep -oP '(yes|no)'", "r");
    if (!fp)
        return "err";
    if (fgets(mute, sizeof(mute), fp) == NULL) {
        pclose(fp);
        return "err";
    }
    pclose(fp);
    mute[strcspn(mute, "\n")] = 0;

    if (strcmp(mute, "yes") == 0)
        snprintf(status, sizeof(status), "muted");
    else
        snprintf(status, sizeof(status), "%s", volume);

    return status;
}

