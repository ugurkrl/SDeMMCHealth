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
#include "../mmc.h"
#include "../mmc_cmds.h"

int mmcCMD8(int fd, int arg, unsigned char *smart);

void read_hynixold(int fc, __u8 data_in[512]){
int fd;
  const char *device;
  int cmd_arg;

  int ret;
   ret = hycmd60(fc, 0x534D4900);
   ret = hycmd60(fc, 0x48525054);
   ret = mmcCMD8(fc, cmd_arg, data_in);
  printf("\tugurkrcl's SDeMMC Health Reader V1.1\n\n");
  printf("Reserved Blocks(SLC): %d,\n", (int)((data_in[35] << 24) + (data_in[34] << 16) + (data_in[33] << 8) + data_in[32]));
  printf("Maximum Block Erase(SLC): %d,\n", (int)((data_in[39] << 24) + (data_in[38] << 16) + (data_in[37] << 8) + data_in[36]));
  printf("Minimum Block Erase(SLC): %d,\n", (int)((data_in[43] << 24) + (data_in[42] << 16) + (data_in[41] << 8) + data_in[40]));
  printf("Average Block Erase(SLC): %d,\n", (int)((data_in[47] << 24) + (data_in[46] << 16) + (data_in[45] << 8) + data_in[44]));
  printf("Reserved Blocks(MLC): %d,\n", (int)((data_in[51] << 24) + (data_in[50] << 16) + (data_in[49] << 8) + data_in[48]));
  printf("Maximum Block Erase(MLC): %d,\n", (int)((data_in[55] << 24) + (data_in[54] << 16) + (data_in[53] << 8) + data_in[52]));
  printf("Minimum Block Erase(MLC): %d,\n", (int)((data_in[59] << 24) + (data_in[58] << 16) + (data_in[57] << 8) + data_in[56]));
  printf("Average Block Erase(MLC): %d,\n", (int)((data_in[63] << 24) + (data_in[62] << 16) + (data_in[61] << 8) + data_in[60]));
  printf("Reserved Blocks(Total): %d,\n", (int)((data_in[67] << 24) + (data_in[66] << 16) + (data_in[65] << 8) + data_in[64]));
  printf("Cumulative Initialization Count: %d,\n", (int)((data_in[95] << 24) + (data_in[94] << 16) + (data_in[93] << 8) + data_in[92]));
  printf("Cumulative Written Data Size: %d,\n", (int)((data_in[99] << 24) + (data_in[98] << 16) + (data_in[97] << 8) + data_in[96]));
  printf("Cumulative Read Data Size: %d,\n", (int)((data_in[103] << 24) + (data_in[102] << 16) + (data_in[101] << 8) + data_in[100]));
  printf("Runtime Bad Block Count: %d,\n", (int)((data_in[107] << 24) + (data_in[106] << 16) + (data_in[105] << 8) + data_in[104]));
  printf("Read Reclaim Count: %d,\n", (int)((data_in[139] << 24) + (data_in[138] << 16) + (data_in[137] << 8) + data_in[136]));
  printf("VCC Drop Count: %d,\n", (int)((data_in[143] << 24) + (data_in[142] << 16) + (data_in[141] << 8) + data_in[140]));

  close(fc);

}