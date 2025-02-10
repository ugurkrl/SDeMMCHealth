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
#include "cards/samsung.c"
#define SD_GEN_CMD 56
#define SD_BLOCK_SIZE 512
   __u8 data_in[512];

int read_extcsd(__u8 *ext_csd,char location[])
{
	int ret = 0;
	int fd = open(location, O_RDWR);
	struct mmc_ioc_cmd idata;
    memset(&idata, 0, sizeof(idata));
    //idata.data_timeout_ns = 0x10000000;
    idata.write_flag = 0;
	idata.opcode =62;
	idata.arg =0;
    mmc_62_vendor_cmd(0xEFAC62EC, fd);
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	 
	//idata.blksz = 512;
	//idata.blocks = 1;
	
	ret = ioctl(fd, MMC_IOC_CMD, &idata);
     if(ret){
        perror("ioctl");}
	
	return ret;
}

int sdCMD56(int fd, int cmd56_arg, unsigned char *smart) {
  int ret = 0;
  struct mmc_ioc_cmd idata;
  memset(&idata, 0, sizeof(idata));
  memset(smart, 0, sizeof(__u8) * SD_BLOCK_SIZE);
  idata.write_flag = 0;
  idata.opcode = SD_GEN_CMD;
  idata.arg = cmd56_arg;
  idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
  idata.blksz = SD_BLOCK_SIZE;
  idata.blocks = 1;
  mmc_ioc_cmd_set_data(idata, smart);
  ret = ioctl(fd, MMC_IOC_CMD, &idata);

  return ret;
}

int mmcCMD8(int fd, int arg, unsigned char *smart) {
  int ret = 0;
  struct mmc_ioc_cmd idata;
  memset(&idata, 0, sizeof(idata));
  memset(smart, 0, sizeof(__u8) * SD_BLOCK_SIZE);
  idata.write_flag = 0;
  idata.opcode = 8;
  idata.arg = arg;
  idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
  idata.blksz = SD_BLOCK_SIZE;
  idata.blocks = 1;
  mmc_ioc_cmd_set_data(idata, smart);
  ret = ioctl(fd, MMC_IOC_CMD, &idata);

  return ret;
}


void read_7232(int fc){
    printf("\nSanDisk iNAND 7232 Device Report Reader\n\n");
    int i=0;
    int x = 0;
    int y=1;
    unsigned long b1=0,b2=0,b3=0,b4=0;
    float total;
 //   printf("send vendor cmd ?\n"); //for debug purpose
 //   scanf("%d",&y);
    if(y==1){
    x = mmc_62_vendor_cmd(0x96C9D71C, fc);
	if(x==b1)printf("[OK] SMART Report Command\n");
   }
    int ret=0;
    struct mmc_ioc_cmd idata;
	memset(&idata, 0, sizeof(idata));
	memset(data_in, 0, sizeof(__u8) * 512);
	idata.write_flag = 0;
	idata.arg = 0;
	idata.opcode=63;
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	idata.blksz = 512;
	idata.blocks = 1;
	
	mmc_ioc_cmd_set_data(idata, data_in);
    x = ioctl(fc, MMC_IOC_CMD, &idata);
    if(x==0)printf("[OK] Get Device Report\n");  
//    printf("Enter '1' if you want to print all SMART Block : ");
//    scanf("%d",&i); debug 2
    printf("\n");
    if(i==1){
	for(int i=0;i<512;i++){
	printf("Data Slice %d : %x\n",i,data_in[i]);}printf("\n");}

	b1=data_in[0x60];
    b2=data_in[0x61]<<8;
    b3=data_in[0x62]<<16;
    b4=data_in[0x63]<<24;
    printf("Average PE Cycles of Hybrid Area  is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[0];
    b2=data_in[1]<<8;
    b3=data_in[2]<<16;
    b4=data_in[3]<<24;
    printf("Average PE Cycles of Enhanced Area is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[4];
    b2=data_in[5]<<8;
    b3=data_in[6]<<16;
    b4=data_in[7]<<24;
    printf("Average PE Cycles of SLC Area  is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[8];
    b2=data_in[9]<<8;
    b3=data_in[10]<<16;
    b4=data_in[11]<<24;
    printf("Average PE Cycles of MLC/TLC Area  is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=data_in[12];
    b2=data_in[13]<<8;
    b3=data_in[14]<<16;
    b4=data_in[15]<<24;
    printf("Read Reclaim Count of Enhanced Area is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[16];
    b2=data_in[17]<<8;
    b3=data_in[18]<<16;
    b4=data_in[19]<<24;
    printf("Read Reclaim Count of SLC Area is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[20];
    b2=data_in[21]<<8;
    b3=data_in[22]<<16;
    b4=data_in[23]<<24;
    printf("Read Reclaim Count of MLC/TLC Area is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=data_in[0x18];
    b2=data_in[0x19]<<8;
    b3=data_in[0x1a]<<16;
    b4=data_in[0x1b]<<24;
    printf("Manufactory Bad Block Count is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[28];
    b2=data_in[29]<<8;
    b3=data_in[30]<<16;
    b4=data_in[31]<<24;
    printf("Runtime Enhanced Area Bad Block Count is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[32];
    b2=data_in[33]<<8;
    b3=data_in[34]<<16;
    b4=data_in[35]<<24;
    printf("Runtime SLC Area Bad Block Count is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[36];
    b2=data_in[37]<<8;
    b3=data_in[38]<<16;
    b4=data_in[39]<<24;
    printf("Runtime MLC/TLC Area Bad Block Count is : %lu\n\n" , b1+b2+b3+b4);
  
    b1=data_in[40];
    b2=data_in[41]<<8;
    b3=data_in[42]<<16;
    b4=data_in[43]<<24;
    printf("Patch Trial Count is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[0x2c];
    b2=data_in[0x2d];
    b3=data_in[0x2e];
    b4=data_in[0x2f];
    printf("Patch Release Date : %c%c%c%c" , b1,b2,b3,b4); //will modify
    b1=data_in[0x30];
    b2=data_in[0x31];
    b3=data_in[0x32];
    b4=data_in[0x33];
    printf("%c%c%c%c" , b1,b2,b3,b4);
    b1=data_in[0x34];
    b2=data_in[0x35];
    b3=data_in[0x36];
    b4=data_in[0x37];
    printf("%c%c%c%c\n" , b1,b2,b3,b4);  
    
    b1=data_in[0x38];
    b2=data_in[0x39];
    b3=data_in[0x3a];
    b4=data_in[0x3b];
    printf("Patch Release Time : %c%c%c%c" , b1,b2,b3,b4); //will modify
    b1=data_in[0x3c];
    b2=data_in[0x3d];
    b3=data_in[0x3e];
    b4=data_in[0x3f];
    printf("%c%c%c%c\n\n" , b1,b2,b3,b4);  
    
    b1=data_in[0x40];
    b2=data_in[0x41]<<8;
    b3=data_in[0x42]<<16;
    b4=data_in[0x43]<<24;
    total = b1+b2+b3+b4;
    printf("Cumulative Write Data Size is : %.1f GB\n" , (total)/10);
    
    b1=data_in[0x54];
    b2=data_in[0x55]<<8;
    b3=data_in[0x56]<<16;
    b4=data_in[0x57]<<24;
    total = b1+b2+b3+b4;
    printf("Cumulative Write Data Size in data_inSLC Area is : %.1f GB\n" , (total)/10);
    
    b1=data_in[0x58];
    b2=data_in[0x59]<<8;
    b3=data_in[0x5a]<<16;
    b4=data_in[0x5b]<<24;
    total = b1+b2+b3+b4;
    printf("Cumulative SLC Write Data Size in MLC/TLC Area is : %.1f GB\n\n" , (total)/10);
  

    b1=data_in[0x5c];
    b2=data_in[0x5d]<<8;
    b3=data_in[0x5e]<<16;
    b4=data_in[0x5f]<<24;
    printf("Allowed hybrid write size exceed limit ? : %lu\n\n" , b1+b2+b3+b4);
    
    b1=data_in[0x44];
    b2=data_in[0x45]<<8;
    b3=data_in[0x46]<<16;
    b4=data_in[0x47]<<24;
    printf("Hard VCC Power drop count is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[0x48];
    b2=data_in[0x49]<<8;
    b3=data_in[0x4a]<<16;
    b4=data_in[0x4b]<<24;
    printf("Soft VCC Power drop count is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[0x4c];
    b2=data_in[0x4d]<<8;
    b3=data_in[0x4e]<<16;
    b4=data_in[0x4f]<<24;
    printf("Failed Host Data Recovery Count After Power Loss is : %lu\n" , b1+b2+b3+b4);
    
    b1=data_in[0x50];
    b2=data_in[0x51]<<8;
    b3=data_in[0x52]<<16;
    b4=data_in[0x53]<<24;
    printf("Total Recovery Operations After Voltage Drop is : %lu\n" , b1+b2+b3+b4);
    

 
}
void read_adata1(int fc){
  int fd;
  const char *device;
  int cmd56_arg;

  int ret;
    cmd56_arg = 0x110005F1;
      ret = sdCMD56(fc, cmd56_arg, data_in);
       printf("\"Flash ID\": "
         "[\"0x%02x\",\"0x%02x\",\"0x%02x\",\"0x%02x\",\"0x%02x\",\"0x%02x\","
         "\"0x%02x\"],\n",
         data_in[0x50], data_in[0x51], data_in[0x52], data_in[0x53], data_in[0x54], data_in[0x55], data_in[0x56]);
  printf("\"Controller Version\": %c%c%c%c%c%c%c,\n", data_in[0x58], data_in[0x59], data_in[0x5a], data_in[0x5b], data_in[0x5c], data_in[0x5d]);
  printf("\"icVersion\": %c%c%c%c%c%c%c,\n", data_in[0x80], data_in[0x81], data_in[0x82], data_in[0x83], data_in[0x84], data_in[0x85]);



  printf("\"Spare Block Count\": %d,\n", (int)((data_in[0x1e] << 8) + data_in[0x1f]));
  printf("\"Factory Bad Block Count\": %d,\n", (int)((data_in[0x18] << 8) + data_in[0x19]));
  printf("\"Grown Bad Block Count\": %d,\n", (int)(data_in[0x1a]));
  printf("\"Spare SLC Block Count\": %d,\n", (int)(data_in[0x1b]));
  printf("\"Remaning Life\": %d,\n", (int)data_in[0x46]);
  printf("\"PECycleLife\": %ld,\n", (long)((data_in[0x44] << 8) + data_in[0x45]));
  printf("\"Average Erase Count(DATA)\": %ld,\n", (long)((data_in[0x2c] << 24) + (data_in[0x2d] << 16) + (data_in[0x2e] << 8) + data_in[0x2f]));
  printf("\"Minimum Erase Count(DATA)\": %ld,\n", (long)((data_in[0x20] << 24) + (data_in[0x21] << 16) + (data_in[0x22] << 8) + data_in[0x23]));
  printf("\"Maximum Erase Count(DATA)\": %ld,\n", (long)((data_in[0x24] << 24) + (data_in[0x25] << 16) + (data_in[0x26] << 8) + data_in[0x27]));
  printf("\"Total Erase Count(DATA)\": %ld,\n", (long)((data_in[0x28] << 24) + (data_in[0x29] << 16) + (data_in[0x2a] << 8) + data_in[0x2b]));
  printf("\"Average Erase Count(SYSTEM)\": %ld,\n", (long)((data_in[0x3c] << 24) + (data_in[0x3d] << 16) + (data_in[0x3e] << 8) + data_in[0x3f]));
  printf("\"Minimum Erase Count(SYSTEM)\": %ld,\n", (long)((data_in[0x30] << 24) + (data_in[0x31] << 16) + (data_in[0x32] << 8) + data_in[0x33]));
  printf("\"Maximum Erase Count(SYSTEM)\": %ld,\n", (long)((data_in[0x34] << 24) + (data_in[0x35] << 16) + (data_in[0x36] << 8) + data_in[0x37]));
  printf("\"Total Erase Count(SYSTEM)\": %ld,\n", (long)((data_in[0x38] << 24) + (data_in[0x39] << 16) + (data_in[0x3a] << 8) + data_in[0x3b]));
  printf("\"RAW Card Capacity\": %ld MB,\n", (long)((data_in[0x40] << 24) + (data_in[0x41] << 16) + (data_in[0x42] << 8) + data_in[0x43]));
  printf("\"Power ON/OFF Count\": %ld,\n", (long)((data_in[0x4c] << 24) + (data_in[0x4d] << 16) + (data_in[0x4e] << 8) + data_in[0x4f]));
  printf("\"TLC Refresh Count\": %d,\n", (int)((data_in[0x88] << 24) + (data_in[0x89] << 16) + (data_in[0x8a] << 8) + data_in[0x8b]));
  printf("\"SLC Refresh Count\": %d,\n", (int)((data_in[0x8C] << 24) + (data_in[0x8D] << 16) + (data_in[0x8F] << 8) + data_in[0x90]));
  printf("\"TLC Read Reclaim\": %ld,\n", (long)((data_in[0x60] << 8) + data_in[0x61]));
  printf("\"SLC Read Reclaim\": %ld,\n", (long)((data_in[0x62] << 8) + data_in[0x63]));
  printf("\"Firmware Block Refresh\": %ld,\n", (long)((data_in[0x64] << 8) + data_in[0x65]));
  printf("\"TLC Read Threshold\": %ld,\n", (long)((data_in[0x68] << 24) + (data_in[0x69] << 16) + (data_in[0x6a] << 8) + data_in[0x6b]));
  printf("\"SLC Read Threshold\": %ld,\n", (long)((data_in[0x6c] << 24) + (data_in[0x6d] << 16) + (data_in[0x6e] << 8) + data_in[0x6f]));
  close(fc);
}

void read_hynix1(int fc){
  int fd;
  const char *device;
  int cmd_arg;

  int ret;
    cmd_arg = 0x53454852;
      ret = mmcCMD8(fc, cmd_arg, data_in);
  printf("\tugurkrcl's SDeMMC Health Reader V1.1\n\n");
  printf("\"Initial Bad Block Count\": %d,\n", (int)((data_in[271] << 8) + data_in[270]));
  printf("\"Run Time Bad Block Count\": %d,\n", (int)((data_in[273] << 8) + data_in[272]));
  printf("\"Maximum Erase Count\": %d,\n", (int)((data_in[275] << 8) + data_in[274]));
  printf("\"Minimum Erase Count Count\": %d,\n", (int)((data_in[277] << 8) + data_in[276]));
  printf("\"Average Erase Count\": %d,\n", (int)((data_in[279] << 8) + data_in[278]));
  printf("\"Read Reclaim Count\": %ld,\n", (int)((data_in[281] << 8) + data_in[280]));
  printf("\"SPO Count\": %ld,\n", (long)((data_in[285] << 24) + (data_in[284] << 16) + (data_in[283] << 8) + data_in[282]));
  printf("\"Cumulative Written Data Size\": %0.1f GB,\n", (float)((data_in[289] << 24) + (data_in[288] << 16) + (data_in[287] << 8) + data_in[286])/10);
  printf("\"LVD Count\": %ld,\n", (long)((data_in[293] << 24) + (data_in[292] << 16) + (data_in[291] << 8) + data_in[290]));
  printf("\"FFU Count\": %d,\n", (int)((data_in[295] << 8) + data_in[294]));
  printf("\"Reserved Blocks\": %d,\n", (int)((data_in[297] << 8) + data_in[296]));
  printf("\"Cumulative Read Data Size\": %0.1f GB,\n", (float)((data_in[301] << 24) + (data_in[300] << 16) + (data_in[299] << 8) + data_in[298])/10);

  close(fc);
}

int main(){
    int key;
    int altkey;
    char location[64];
    system("clear");
    printf("\tugurkrcl's SDeMMC Health Reader V1.1\n");
    printf("\nEnter Location of eMMC:");
    scanf("%s",&location);
    int fc = open(location, O_RDWR);
    system("clear");
    printf("\tugurkrcl's SDeMMC Health Reader V1.1\n");
    printf("\nSelect Vendor:");
    printf("\n[0] Samsung");
    printf("\n[1] Sandisk/WD");
	printf("\n[2] Hynix");
    printf("\n[3] SD Card\n");
    scanf("%d",&key);
    system("clear");
    printf("\tugurkrcl's SDeMMC Health Reader V1.1\n");
    
    if(key==0){
    system("clear");
    printf("\tugurkrcl's SDeMMC Health Reader V1.1\n");
    printf("\nSelect Device:");
    printf("\n[0] MoviNAND 4.3");
    printf("\n[1] MoviNAND 4.41");
    printf("\n[2] MoviNAND SD Card\n");
    scanf("%d",&altkey);
    system("clear");
    if(altkey==0){
    read_movi_43(fc);
        }
    if(altkey==1){
    read_movi_441(fc);
        }
    if(altkey==2){
    read_movi_sd(fc);
        }
    }

	if(key==1){
    read_7232(fc);
    }
	
	if(key==2){
    system("clear");
    printf("\tugurkrcl's SDeMMC Health Reader V1.1\n");
    printf("\nSelect Device:");
    printf("\n[0] Hynix V1 hB8aP");
    scanf("%d",&altkey);
    system("clear");
    if(altkey==0){
    read_hynix1(fc);
        }
    }
	
	
    if(key==3){
    system("clear");
    printf("\tugurkrcl's SDeMMC Health Reader V1.1\n");
    printf("\nSelect Device:");
    printf("\n[0] ADATA SM2707 ARG:0x110005F1 ");
    scanf("%d",&altkey);
    system("clear");
    if(altkey==0){
    read_adata1(fc);
        }

    }
    

    printf("Enter '1' if you want to print all SMART Block : ");
   scanf("%d",&key);                                                    printf("\n");
    if(key==1){
        
        for(int i=0;i<512;i++){
            if(i%16==0){
                printf("\n %d: ",i);
            }
        printf("%x ",data_in[i]);

        }
		printf("\n");}
return -1;	
}



