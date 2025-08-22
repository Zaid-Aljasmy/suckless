/* battery custom */

#include <stdio.h>    // FILE, popen, pclose, fgets, sscanf, snprintf
#include <string.h>   // strstr
#include <ctype.h>    // tolower

#include "../slstatus.h"

const char *
battery_custom(const char *bat)
{
    static char result[64];
    char buffer[256];
    char state[64];
    int perc = -1;
    char suffix[16];

    FILE *fp = popen("acpi -b", "r");
    if (!fp) {
        snprintf(result, sizeof(result), "Battery not found");
        return result;
    }

    suffix[0] = '\0';

    if (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "Battery 0: %63[^,], %d%%", state, &perc) == 2) {
            char state_lower[64];
            int i;
            for (i = 0; state[i] && i < 63; i++)
                state_lower[i] = tolower((unsigned char)state[i]);
            state_lower[i] = '\0';

            if (strstr(state_lower, "discharging")) {
                if (perc <= 20)
                    snprintf(suffix, sizeof(suffix), "low");
            } else if (strstr(state_lower, "full") != NULL || strstr(state_lower, "not") != NULL || perc >= 100) {
                snprintf(suffix, sizeof(suffix), "full");
            } else if (strstr(state_lower, "charging")) {
                snprintf(suffix, sizeof(suffix), "chr");
            }
        }
    }

    pclose(fp);

    if (perc >= 0) {
        if (suffix[0] != '\0')
            snprintf(result, sizeof(result), "%d%% %s", perc, suffix);
        else
            snprintf(result, sizeof(result), "%d%%", perc);
    } else {
        snprintf(result, sizeof(result), "Battery not found");
    }

    return result;
}

