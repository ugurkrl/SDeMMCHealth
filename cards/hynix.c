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
  printf("Reserved Blocks SLC:%u MLC:%u Total:%u\n", (int)((data_in[35] << 24) + (data_in[34] << 16) + (data_in[33] << 8) + data_in[32]),
  (int)((data_in[51] << 24) + (data_in[50] << 16) + (data_in[49] << 8) + data_in[48]),
  (int)((data_in[67] << 24) + (data_in[66] << 16) + (data_in[65] << 8) + data_in[64]));
  printf("SLC Erase Count Max:%u Min:%u Avg:%u\n",(int)((data_in[39] << 24) + (data_in[38] << 16) + (data_in[37] << 8) + data_in[36]),
  (int)((data_in[43] << 24) + (data_in[42] << 16) + (data_in[41] << 8) + data_in[40]),
  (int)((data_in[47] << 24) + (data_in[46] << 16) + (data_in[45] << 8) + data_in[44]));
  printf("MLC Erase Count Max:%u Min:%u Avg:%u\n",(int)((data_in[55] << 24) + (data_in[54] << 16) + (data_in[53] << 8) + data_in[52]),
  (int)((data_in[59] << 24) + (data_in[58] << 16) + (data_in[57] << 8) + data_in[56]),
  (int)((data_in[63] << 24) + (data_in[62] << 16) + (data_in[61] << 8) + data_in[60]));
  printf("Cumulative Initialization Count: %d,\n", (int)((data_in[95] << 24) + (data_in[94] << 16) + (data_in[93] << 8) + data_in[92]));
  printf("Cumulative Written Data Size: %d,\n", (int)((data_in[99] << 24) + (data_in[98] << 16) + (data_in[97] << 8) + data_in[96]));
  printf("Cumulative Read Data Size: %d,\n", (int)((data_in[103] << 24) + (data_in[102] << 16) + (data_in[101] << 8) + data_in[100]));
  printf("Runtime Bad Block Count: %d,\n", (int)((data_in[107] << 24) + (data_in[106] << 16) + (data_in[105] << 8) + data_in[104]));
  printf("Read Reclaim Count: %d,\n", (int)((data_in[139] << 24) + (data_in[138] << 16) + (data_in[137] << 8) + data_in[136]));
  printf("VCC Drop Count: %d,\n", (int)((data_in[143] << 24) + (data_in[142] << 16) + (data_in[141] << 8) + data_in[140]));

  close(fc);

}

void read_hynixnew(int fc, __u8 data_in[512]){
  int fd;
  const char *device;
  int cmd_arg;

  int ret;
    cmd_arg = 0x53454852;
      ret = mmcCMD8(fc, cmd_arg, data_in);
  printf("\tugurkrcl's SDeMMC Health Reader V1.1\n\n");
  printf("Bad Blocks Initial:%u Runtime:%u Reserved:%u\n", (int)((data_in[271] << 8) + data_in[270]),
  (int)((data_in[273] << 8) + data_in[272]),
  (int)((data_in[297] << 8) + data_in[296]));
  printf("Erase Count Max:%u Min:%u Avg:%u\n",(int)((data_in[275] << 8) + data_in[274]),
  (int)((data_in[277] << 8) + data_in[276]),
  (int)((data_in[279] << 8) + data_in[278]));
  printf("Read Reclaim Count: %d,\n", (int)((data_in[281] << 8) + data_in[280]));
  printf("SPO Count: %ld,\n", (long)((data_in[285] << 24) + (data_in[284] << 16) + (data_in[283] << 8) + data_in[282]));
  printf("Cumulative Written Data Size\": %0.1f GB,\n", (float)((data_in[289] << 24) + (data_in[288] << 16) + (data_in[287] << 8) + data_in[286])/10);
  printf("LVD Count: %ld,\n", (long)((data_in[293] << 24) + (data_in[292] << 16) + (data_in[291] << 8) + data_in[290]));
  printf("FFU Count: %d,\n", (int)((data_in[295] << 8) + data_in[294]));
  printf("Cumulative Read Data Size: %0.1f GB,\n", (float)((data_in[301] << 24) + (data_in[300] << 16) + (data_in[299] << 8) + data_in[298])/10);

  close(fc);
}