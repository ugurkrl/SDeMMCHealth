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

void read_tsb(int fc,__u8 data_in[512]){
  int fd;
  const char *device;

  int ret;

        ret = tsbCMD56(fc, 5, data_in,0);
        ret = tsbCMD56(fc, 5, data_in,1);
  //0: 7 0 0 a0 0 0 1 f8 0 0 1 9d 0 0 0 0

      printf("Device Health Report%d\n",0);
      printf("Stat: %x\n",data_in[3]);
      printf("MLC Used Life: %u\n",data_in[4]*10);
      printf("SLC Used Life: %u\n",data_in[5]*10);
      printf("All Device Used Life: %u\n",data_in[6]*10);

      ret = tsbCMD56(fc, 7, data_in,0);
      ret = tsbCMD56(fc, 7, data_in,1);
      printf("Erase Report\n");
      printf("Stat: %x\n",data_in[3]);
      printf("MLC Erase Count Max:%u Avg:%u\n",(int)((data_in[4] << 24) + (data_in[5] << 16) + (data_in[6] << 8) + data_in[7]),
        (int)((data_in[131] << 8) + (data_in[9] << 16) + (data_in[10] << 8) + data_in[11]));
        printf("SLC Erase Count Max:%u Avg:%u\n\n",(int)((data_in[12] << 24) + (data_in[13] << 16) + (data_in[14] << 8) + data_in[15]),
        (int)((data_in[16] << 24) + (data_in[17] << 16) + (data_in[18] << 8) + data_in[19]));

  close(fc);
}
