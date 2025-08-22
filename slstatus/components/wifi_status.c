/* wifi custom */

#include <stdio.h>     // FILE, fopen, fgets, fclose, snprintf
#include <string.h>    // strncmp, strncpy, strcmp, strcspn
#include <dirent.h>    // DIR, struct dirent, opendir, readdir, closedir

#include "../slstatus.h"

const char *
wifi_status(const char *arg) {
    static char status[8];
    char iface[32] = {0};
    char path[64];
    FILE *fp;
    DIR *dir;
    struct dirent *ent;

    dir = opendir("/sys/class/net");
    if (!dir)
        return "DOWN";

    while ((ent = readdir(dir)) != NULL) {
        if (strncmp(ent->d_name, "wl", 2) == 0) {
            strncpy(iface, ent->d_name, sizeof(iface)-1);
            break;
        }
    }
    closedir(dir);

    if (iface[0] == '\0')
        return "DOWN"; 

    snprintf(path, sizeof(path), "/sys/class/net/%s/operstate", iface);
    fp = fopen(path, "r");
    if (!fp)
        return "DOWN";

    if (fgets(status, sizeof(status), fp) == NULL) {
        fclose(fp);
        return "DOWN";
    }
    fclose(fp);

    status[strcspn(status, "\n")] = 0; 

    if (strcmp(status, "up") == 0)
        return "up";
    else
        return "dwn";
}

