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

void isocom(int fc,__u8 data_in[512]){
  int fd;
  const char *device;
  int cmd56_arg=0x110005F1;
 int temp[8];
  int ret;

      ret = generic56(fc, cmd56_arg, data_in);

      printf("Original Bad Block: %u \n",(int)(data_in[26] << 8)  +
			(data_in[25]));
      printf("Grown Bad Block: %u \n",(int)(data_in[27] << 8)  +
			(data_in[28]));
      printf("Minimum Erase: %u \n",(int)((data_in[35] << 24) + (data_in[34] << 16) + (data_in[33] << 8) + data_in[32]));
      printf("Average Erase: %u \n",(int)((data_in[47] << 24) + (data_in[46] << 16) + (data_in[45] << 8) + data_in[44]));
      printf("Maximum Erase: %u \n",(int)((data_in[39] << 24) + (data_in[38] << 16) + (data_in[37] << 8) + data_in[36]));
      for (int i = 0; i < 8; i++){
		 temp[i] = data_in[112+i];
	}
      printf("Sector Write: %u%u%u%u%u%u%u%u \n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7]);
//
  close(fc);
  /*&foresee_original_bad_block_fops,
	&foresee_increase_bad_block_fops,
	&foresee_max_wear_number_fops,
	&foresee_degree_of_wear_fops,
	&foresee_write_all_sector_number_fops,
    */
}
