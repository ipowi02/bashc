#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../da/da.h"

int main(int argc, const char **argv) {
    static const char *const usage = "Usage: sftp-fazek [-u username] [-p password]";
    char *usr = "pongoradam";
    char *pwd = NULL;
    optind = 1;
    int opt;
    while ((opt = getopt(argc, (char**)argv, "u:p:")) != -1) {
        switch (opt) {
        case 'u':
            usr = optarg;
            break;
        case 'p':
            pwd = optarg;
            break;
        default:
            goto err;
        }
    }

    // If not provided via -p, try positional arg
    if (!pwd && optind < argc)
        pwd = (char*)argv[optind++];

    // If still not provided, try env
    if (!pwd)
        pwd = getenv("FAZEKAS_PWD");

    if (!pwd)
        goto err;

    const size_t cmdcap = snprintf(NULL, 0, "lftp -u \"%s,%s\" -p 22 sftp://sftp.fazekas.hu -e \"cd /share/tananyag\"",
                                   usr, pwd) + 1;
    da_char_t cmd;
    da_reserve(&cmd, cmdcap);
    snprintf(cmd.data, cmdcap, "lftp -u \"%s,%s\" -p 22 sftp://sftp.fazekas.hu -e \"cd /share/tananyag\"",
             usr, pwd);

    for (int i = optind; i < argc; i++) {
        da_push(&cmd, ' ');
        da_npush(&cmd, argv[i], strlen(argv[i]));
    }

    if (system(cmd.data) != 0) goto fatal;
    return 0;

err:    fprintf(stderr, "%s\n", usage);
fatal:  return -1;
}



