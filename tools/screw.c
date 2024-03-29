#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "../php_screw.h"
#include "../my_screw.h"

main(int argc, char**argv)
{
	FILE	*fp;
	struct	stat	stat_buf;
	char	*datap, *newdatap;
	int	datalen, newdatalen;
	int	cryptkey_len = sizeof pm9screw_mycryptkey / 2;
	char	oldfilename[256];
	int	i;

	if (argc != 2) {
		fprintf(stderr, "Usage: filename.\n");
		exit(0);
	}
	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		fprintf(stderr, "File not found(%s)\n", argv[1]);
		exit(0);
	}

	fstat(fileno(fp), &stat_buf);
	datalen = stat_buf.st_size;
	datap = (char*)malloc(datalen + PM9SCREW_LEN);
	fread(datap, datalen, 1, fp);
	fclose(fp);

	sprintf(oldfilename, "%s.screw", argv[1]);

	if (memcmp(datap, PM9SCREW, PM9SCREW_LEN) == 0) {
		fprintf(stderr, "Already Crypted(%s)\n", argv[1]);
		exit(0);
	}

	fp = fopen(oldfilename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Can not create backup file(%s)\n", oldfilename);
		exit(0);
	}
	fwrite(datap, datalen, 1, fp);
	fclose(fp);

	newdatap = zencode(datap, datalen, &newdatalen);

	for(i=0; i<newdatalen; i++) {
		newdatap[i] = (char)pm9screw_mycryptkey[(newdatalen - i) % cryptkey_len] ^ (~(newdatap[i]));
	}

	fp = fopen(argv[1], "wb");
	if (fp == NULL) {
		fprintf(stderr, "Can not create crypt file(%s)\n", oldfilename);
		exit(0);
	}
	fwrite(PM9SCREW, PM9SCREW_LEN, 1, fp);
	fwrite(newdatap, newdatalen, 1, fp);
	fclose(fp);
	fprintf(stderr, "Success Crypting(%s)\n", argv[1]);
	free(newdatap);
	free(datap);
}

//
//fstat(fileno(fp), &stat_buf);
//	datalen = stat_buf.st_size;
//	datap = (char*)malloc(datalen);
//	memset(datap,'\0',datalen);
//	fread(datap, datalen, 1, fp);
//	fclose(fp);
//
//	fp = fopen("k.php", "wb");
//	if (fp == NULL) {
//		fprintf(stderr, "Can not create backup file(%s)\n", oldfilename);
//		exit(0);
//	}
//	fwrite(datap, datalen, 1, fp);
//	fclose(fp);
//
//
//	for(i=0; i<datalen; i++) {
//		datap[i] = (char)pm9screw_mycryptkey[(datalen - i) % cryptkey_len] ^ (~(datap[i]));
//	}
//
//	newdatap = zdecode(datap, datalen, &newdatalen);
//
//
//	return 1;
//
