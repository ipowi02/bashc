#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    const char *github = "https://github.com/";
    const char *raw    = "https://raw.githubusercontent.com/";
    const char *blob   = "/blob/";

    for (char **arg = argv + 1; *arg; arg++) {
        if (strncmp(*arg, github, strlen(github)) != 0) {
            fprintf(stderr, "not a github url: %s\n", *arg);
            continue;
        }

        char *blob_pos = strstr(*arg, blob);
        if (!blob_pos) {
            fprintf(stderr, "no /blob/ in url: %s\n", *arg);
            continue;
        }

        printf("%s", raw);
        fwrite(*arg + strlen(github), 1, blob_pos - (*arg + strlen(github)), stdout);
        printf("/%s\n", blob_pos + strlen(blob));
    }

    return 0;
}
