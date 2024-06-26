#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <assert.h>
#include "mmc.h"
#include "mmc_cmds.h"

int mmc_62_vendor_cmd(unsigned int arg, int fd) {
	int ret = 0;
	struct mmc_ioc_cmd idata = {0};

	//idata.data_timeout_ns = 0x10000000;
	idata.write_flag = 1;
	idata.opcode = 62;
	idata.arg = arg;
	idata.flags = MMC_RSP_R1B | MMC_CMD_AC;

	ret = ioctl(fd, MMC_IOC_CMD, &idata);

	return ret;
}
 
