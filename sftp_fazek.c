#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../da/da.h"
int sftp_fazek(int argc, const char **argv) {
     static const char *const usage = "Usage: sftp-fazek [-u username] [-p password]";
     char *usr = "pongoradam";
     char *pwd = NULL;

     optind = 1; // Reset optind for multiple calls
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
     

     int remaining_args = argc - optind;
     if (pwd == NULL && remaining_args > 0) {
	  pwd = argv[optind++];
	  remaining_args--;
     }

     if (pwd == NULL) {
	  goto err;
     }

     // Constructing the lftp command
     // Note: This uses system() to mimic the original shell behavior
     const size_t cmdcap = snprintf(NULL, 0, "lftp -u \"%s,%s\" -p 22 sftp://sftp.fazekas.hu -e \"cd /share/tananyag\"",
				    usr, pwd) + 1;
     da_char_t cmd;
     da_reserve(&cmd, cmdcap);
     snprintf(cmd.data, cmdcap, "lftp -u \"%s,%s\" -p 22 sftp://sftp.fazekas.hu -e \"cd /share/tananyag\"",
	      usr, pwd);
     // Append any remaining arguments to the cmd
     for (int i = optind; i < argc; i++) {
	  da_push(&cmd, ' ');
	  da_npush(&cmd, argv[i], sizeof(argv[i]));
     }

     if (system(cmd.data) != 0) goto fatal;
     return 0;
     
err:  fprintf(stderr, "%s\n", usage);
fatal:return -1;
}






