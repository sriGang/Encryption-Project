#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#define BFSZ	1024

#include <stdbool.h>

extern char encrypt(char inchar, char key);
extern char decrypt(char inchar, char key);
void usage(char **argv);

int
main (int argc, char **argv) {
	int opt;
	bool caseD = 0;
	bool caseE = 0;
	bool caseB = 0;
	char *filename = NULL;
	char *encryptionFile = NULL;
	int offsetInput = 0;

	while((opt = getopt(argc, argv, "deb:o:")) != -1) {
		switch(opt) {
			case('d'):
				caseD = 1;
			break;
			case('e'):
				caseE = 1;
			break;
			case('b'):
				caseB = 1;
				filename = optarg;
			break;
			case('o'):
				offsetInput = atoi(optarg);
			break;
			default:
			break;
		}
	}
	encryptionFile = argv[argc-1];
	if(!caseD && !caseE) {
		usage(argv);
		return EXIT_FAILURE;
	}
	if(caseD && caseE)
		return EXIT_FAILURE;
	if(encryptionFile == NULL) {
		return EXIT_FAILURE;
	}

	if(caseB) {
		struct stat size;
		int bookSize=0;
		int encryptSize=0;
		char *ptr;
		char *file_ptr;
		int i,j;
		FILE *fp = NULL;
		FILE *fp2 = NULL;
		char buffer[BFSZ*2];
		memset(buffer, 0, sizeof(buffer));
		char ch[1];
		char val;
		int bytesEncrypt;

		fp = fopen(filename,"r");
		if (fp != NULL) {
			stat(filename, &size);
			bookSize = size.st_size;
		}

		offsetInput =  offsetInput % bookSize;

		if ((ptr = (char*) malloc(bookSize)) == NULL) {
			fclose(fp);
			return EXIT_FAILURE;
		}

		fread(ptr, 1, bookSize, fp);
		if(caseD) {
			fp2 = fopen(encryptionFile,"r");
			if (fp2 != NULL) {
				stat(encryptionFile, &size);
				encryptSize = size.st_size;
				if ((file_ptr = (char*) calloc(encryptSize, sizeof(char))) == NULL) {
					free(ptr);
					fclose(fp2);
					fclose(fp);
					return EXIT_FAILURE;
				}
			}
			bytesEncrypt = fread(file_ptr, 1, encryptSize, fp2);
			for(i = 0, j = offsetInput; i < bytesEncrypt; i++, j++) {
				val = decrypt(file_ptr[i], ptr[j]);
				printf("%c", val);
			}
			free(file_ptr);
			fclose(fp2);
		}

		if(caseE) {
			fp2 = fopen(encryptionFile, "w");
			j = offsetInput;
			while((fgets(buffer , BFSZ*2, stdin)) != NULL) {
				for(i = 0; buffer[i] != '\0'; i++) {
					ch[0] = encrypt(buffer[i], ptr[j]);
					j++;
					fwrite(ch, 1, 1, fp2);
				}
			}
			fclose(fp2);
		}
		fclose(fp);
		free(ptr);
	} else {
		return EXIT_FAILURE;
	}
		
}

void
usage(char **argv) {
    fprintf(stderr,"Usage: %s (-d|-e) -b <bookfile> [-o <offset>] <filename>\n", *argv);
    return;
}
