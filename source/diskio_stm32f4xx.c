/*
 * 2017, Aurelio Colosimo <aurelio@aureliocolosimo.it>
 * MIT License
 */

#include "ff.h"
#include "diskio.h"

DSTATUS disk_initialize(BYTE pdrv)
{
	return RES_OK;
}

DSTATUS disk_status(BYTE pdrv)
{
	return RES_OK;
}

DRESULT disk_read(BYTE pdrv, BYTE* buff, DWORD sector, UINT count)
{
	return RES_OK;
}
