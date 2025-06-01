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
 
 int hycmd60(int fd, int arg) {
  int ret = 0;
  struct mmc_ioc_cmd idata;
  idata.write_flag = 1;
  idata.opcode = 60;
  idata.arg = arg;
  idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
  ret = ioctl(fd, MMC_IOC_CMD, &idata);

  return ret;
}

int tsbCMD56(int fd, __u8 page, void *buf,int mode) {
	uint8_t smartpwd7_cmd[8] = { 0x07, 0x00, 0x00, 0x00, 0x26, 0xE9,0x01, 0xEB};
	uint8_t smartpwd5_cmd[8] = { 0x05, 0x00, 0x00, 0x00, 0x63, 0x50,0x17, 0x00 };

  int ret = 0;
  int index=0;
	index &= 0x7F;
  void *smart;
  struct mmc_ioc_cmd idata;
  struct mmc_ioc_cmd cmd;

  smart  = malloc(512);
  if (!mode){

	  if(page==5){

		  memcpy(smart, smartpwd5_cmd, 8);
	}if(page==7){

		memcpy(smart, smartpwd7_cmd, 8);
	}
}
  cmd.opcode =  56;
	cmd.arg = (0 << 16) | (0 << 8) | (index << 1) | mode;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
    cmd.write_flag=!mode;
  cmd.blksz = 512;
  cmd.blocks = 1;
  mmc_ioc_cmd_set_data(cmd, smart);
  ret = ioctl(fd, MMC_IOC_CMD, &cmd);

  memcpy(buf, smart, 512);

  return ret;
}

int generic56(int fd, int cmd56_arg, void *buf) {
  int ret = 0;
  struct mmc_ioc_cmd idata;
  memset(&idata, 0, sizeof(idata));
  memset(buf, 0, sizeof(__u8) * 512);
  idata.write_flag = 0;
  idata.opcode = 56;
  idata.arg = cmd56_arg;
  idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
  idata.blksz = 512;
  idata.blocks = 1;
  mmc_ioc_cmd_set_data(idata, buf);
  ret = ioctl(fd, MMC_IOC_CMD, &idata);

  return ret;
}
