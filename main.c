/*
 * 2017, Aurelio Colosimo <aurelio@aureliocolosimo.it>
 * This file is part of fatfs-stm32f4:
 * https://github.com/colosimo/fatfs-stm32
 * MIT License
 */

#include <log.h>
#include <ff.h>

#define FNAME "ff_demo.txt"
char CONTENT[] = "This is a test file, created by ff_demo\n";

int create_file(const char *fname, const char *content)
{
	FIL fp;
	int ret;
	unsigned wr;

	log("I will now create file %s with a dummy content\n", fname);

	ret = f_open(&fp, fname, FA_CREATE_ALWAYS | FA_WRITE);
	if (ret != FR_OK) {
		err("%s open failed\n", fname);
		return ret;
	}

	ret = f_write(&fp, content, sizeof(CONTENT), &wr);
	if (ret != FR_OK || wr != sizeof(CONTENT))
		err("%s fwrite failed, written %d bytes\n", fname, wr);

	f_close(&fp);
	return ret;
}

int read_file(const char *fname)
{
	FIL fp;
	int ret;
	char buf[64];
	unsigned rd;
	int i;

	log("I will now try to open the file %s and dump its "
	    "content here\n", fname);

	ret = f_open(&fp, FNAME, FA_OPEN_EXISTING | FA_READ);
	if (ret != FR_OK) {
		log(FNAME " open failed\n");
		return ret;
	}

	log("----" FNAME " dump begin ----\n");
	do {
		ret = f_read(&fp, buf, sizeof(buf), &rd);
		for (i = 0; i < rd; i++)
			putchar(buf[i]);
	} while(rd && ret == FR_OK);
	log("----" FNAME " dump end   ----\n");

	f_close(&fp);

	return ret;
}

int main(void)
{
	FATFS fs;
#if (FF_FS_MINIMIZE == 0)
	FILINFO finfo;
#endif
	int ret;

	log("Hello from ff_demo\n");

	ret = f_mount(&fs, "", 1);
	if (ret != FR_OK) {
		log("Mount failed\n");
		goto done;
	}

	ret = create_file(FNAME, CONTENT);

	if (ret != FR_OK)
		goto done;

#if (FF_FS_MINIMIZE == 0)
	ret = f_stat(FNAME, &finfo);
	if (ret != FR_OK) {
		err("could not find " FNAME "\n");
		goto done;
	}
	log(FNAME " size: %d bytes\n", (uint)finfo.fsize);
#endif

	read_file(FNAME);

done:
	while(1);
	return 0;
}
