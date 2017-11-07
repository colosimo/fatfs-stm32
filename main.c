/*
 * 2017, Aurelio Colosimo <aurelio@aureliocolosimo.it>
 * MIT License
 */

#include <log.h>
#include <ff.h>

#define FNAME "test.txt"

int main(void)
{
	FATFS fs;
	FIL fp;
#if (FF_FS_MINIMIZE == 0)
	FILINFO finfo;
#endif
	int ret;
	unsigned rd;
	char buf[64];
	int i;

	log("Hello from ff_demo\n");
	log("I will now try to open the file " FNAME " and dump its "
	    "content here\n");

	ret = f_mount(&fs, "", 1);
	if (ret != FR_OK) {
		log("Mount failed\n");
		goto done;
	}

#if (FF_FS_MINIMIZE == 0)
	ret = f_stat(FNAME, &finfo);
	if (ret != FR_OK) {
		log("could not find " FNAME "\n");
		goto done;
	}
	log(FNAME " size: %d bytes\n", (uint)finfo.fsize);
#endif

	ret = f_open(&fp, FNAME, FA_OPEN_EXISTING | FA_READ);
	if (ret != FR_OK) {
		log(FNAME " open failed\n");
		goto done;
	}

	log("----" FNAME " dump begin ----\n");
	do {
		f_read(&fp, buf, sizeof(buf), &rd);
		for (i = 0; i < rd; i++)
			putchar(buf[i]);
	} while(rd);
	log("----" FNAME " dump end   ----\n");

done:
	while(1);
	return 0;
}

