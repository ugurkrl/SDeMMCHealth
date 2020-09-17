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

void read_movi_43(int fc){
    printf("\nMoviNAND Health Reader\n\n");
    int i=0;
    int x = 0;
    int y=1;
    unsigned long b1=0,b2=0,b3=0,b4 = 0;
 //   printf("send vendor cmd ?\n"); //for debug purpose
 //   scanf("%d",&y);
    if(y==1){
    x = mmc_62_vendor_cmd(0xEFAC62EC, fc);
	if(x==0)printf("[OK] Vendor Command\n");
    x = mmc_62_vendor_cmd(0x0000CCEE, fc);
    if(x==0)printf("[OK] SMART Report Command\n");
   }
    int ret=0;
   __u8 smart[512];
    struct mmc_ioc_cmd idata;
	memset(&idata, 0, sizeof(idata));
	memset(smart, 0, sizeof(__u8) * 512);
	idata.write_flag = 0;
	idata.arg = 0;
	idata.opcode=17;
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	idata.blksz = 512;
	idata.blocks = 1;
	
	mmc_ioc_cmd_set_data(idata, smart);
    x = ioctl(fc, MMC_IOC_CMD, &idata);
    if(x==0)printf("[OK] Get SMART Report\n");
    x = mmc_62_vendor_cmd(0x00DECCEE, fc);    
//    printf("Enter '1' if you want to print all SMART Block : ");
//    scanf("%d",&i); debug 2
    printf("\n");
    if(i==1){
	for(int i=0;i<512;i++){
	printf("Data Slice %d : %x\n",i,smart[i]);}printf("\n");}

	b1=smart[0];
    b2=smart[1];
    b3=smart[2];
    b4=smart[3];
    printf("Error Mode is : 0x%x%x%x%x\n\n" , b1,b2,b3,b4);
    
    b1=smart[4];
    b2=smart[5]<<8;
    b3=smart[6]<<16;
    b4=smart[7]<<24;
    printf("Super Block Size is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[8];
    b2=smart[9]<<8;
    b3=smart[10]<<16;
    b4=smart[11]<<24;
    printf("Super Page Size is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[12];
    b2=smart[13]<<8;
    b3=smart[14]<<16;
    b4=smart[15]<<24;
    printf("Optimal Write Size is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[16];
    b2=smart[17]<<8;
    b3=smart[18]<<16;
    b4=smart[19]<<24;
    printf("Bank Count is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[20];
    b2=smart[21]<<8;
    b3=smart[22]<<16;
    b4=smart[23]<<24;
    printf("Bank0 Init Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[24];
    b2=smart[25]<<8;
    b3=smart[26]<<16;
    b4=smart[27]<<24;
    printf("Bank0 Init and Runtime Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[28];
    b2=smart[29]<<8;
    b3=smart[30]<<16;
    b4=smart[31]<<24;
    printf("Bank0 Remaining Reserved Block is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[32];
    b2=smart[33]<<8;
    b3=smart[34]<<16;
    b4=smart[35]<<24;
    printf("Bank1 Init Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[36];
    b2=smart[37]<<8;
    b3=smart[38]<<16;
    b4=smart[39]<<24;
    printf("Bank1 Init and Runtime Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[40];
    b2=smart[41]<<8;
    b3=smart[42]<<16;
    b4=smart[43]<<24;
    printf("Bank1 Remaining Reserved Block is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[44];
    b2=smart[45]<<8;
    b3=smart[46]<<16;
    b4=smart[47]<<24;
    printf("Bank2 Init Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[48];
    b2=smart[49]<<8;
    b3=smart[50]<<16;
    b4=smart[51]<<24;
    printf("Bank2 Init and Runtime Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[52];
    b2=smart[53]<<8;
    b3=smart[54]<<16;
    b4=smart[55]<<24;
    printf("Bank2 Remaining Reserved Block is : %lu\n\n" , b1+b2+b3+b4);
  
    b1=smart[56];
    b2=smart[57]<<8;
    b3=smart[58]<<16;
    b4=smart[59]<<24;
    printf("Bank3 Init Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[60];
    b2=smart[61]<<8;
    b3=smart[62]<<16;
    b4=smart[63]<<24;
    printf("Bank3 Init and Runtime Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[64];
    b2=smart[65]<<8;
    b3=smart[66]<<16;
    b4=smart[67]<<24;
    printf("Bank3 Remaining Reserved Block is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[68];
    b2=smart[69]<<8;
    b3=smart[70]<<16;
    b4=smart[71]<<24;
    printf("Device Max erase count is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[72];
    b2=smart[73]<<8;
    b3=smart[74]<<16;
    b4=smart[75]<<24;
    printf("Device Min erase count is : %lu\n" , b1+b2+b3+b4);
  

    b1=smart[76];
    b2=smart[77]<<8;
    b3=smart[78]<<16;
    b4=smart[79]<<24;
    printf("Device Avg erase count is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[80];
    b2=smart[81]<<8;
    b3=smart[82]<<16;
    b4=smart[83]<<24;
    printf("Number of UECC Error is : %lu\n\n" , b1+b2+b3+b4);
  
    b1=smart[220];
    b2=smart[221]<<8;
    b3=smart[222]<<16;
    b4=smart[223]<<24;
    printf("Read Reclaim Count is : %lu\n\n" , b1+b2+b3+b4);

    printf("Controller Name is : %c%c%c%c\n\n" , smart[312] , smart[313] , smart[314] , smart[315]);
 
}
void read_movi_441(int fc){
    

    printf("\nMoviNAND Health Reader\n\n");
    int i=0;
    int x = 0;
    int y=1;
    unsigned long b1=0,b2=0,b3=0,b4 = 0;
 //   printf("send vendor cmd ?\n"); //for debug purpose
 //   scanf("%d",&y);
    if(y==1){
    x = mmc_62_vendor_cmd(0xEFAC62EC, fc);
	if(x==0)printf("[OK] Vendor Command\n");
    x = mmc_62_vendor_cmd(0x0000CCEE, fc);
    if(x==0)printf("[OK] SMART Report Command\n");
   }
    int ret=0;
   __u8 smart[512];
    struct mmc_ioc_cmd idata;
	memset(&idata, 0, sizeof(idata));
	memset(smart, 0, sizeof(__u8) * 512);
	idata.write_flag = 0;
	idata.arg = 0;
	idata.opcode=17;
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	idata.blksz = 512;
	idata.blocks = 1;
	
	mmc_ioc_cmd_set_data(idata, smart);
    x = ioctl(fc, MMC_IOC_CMD, &idata);
    if(x==0)printf("[OK] Get SMART Report\n");
    x = mmc_62_vendor_cmd(0x00DECCEE, fc);    
//    printf("Enter '1' if you want to print all SMART Block : ");
//    scanf("%d",&i); debug 2
    printf("\n");
    if(i==1){
	for(int i=0;i<512;i++){
	printf("Data Slice %d : %x\n",i,smart[i]);}printf("\n");}

	b1=smart[0];
    b2=smart[1];
    b3=smart[2];
    b4=smart[3];
    printf("Error Mode is : 0x%x%x%x%x\n\n" , b1,b2,b3,b4);
    
    b1=smart[4];
    b2=smart[5]<<8;
    b3=smart[6]<<16;
    b4=smart[7]<<24;
    printf("Super Block Size is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[8];
    b2=smart[9]<<8;
    b3=smart[10]<<16;
    b4=smart[11]<<24;
    printf("Super Page Size is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[12];
    b2=smart[13]<<8;
    b3=smart[14]<<16;
    b4=smart[15]<<24;
    printf("Optimal Write Size is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[16];
    b2=smart[17]<<8;
    b3=smart[18]<<16;
    b4=smart[19]<<24;
    printf("Bank Count is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[20];
    b2=smart[21]<<8;
    b3=smart[22]<<16;
    b4=smart[23]<<24;
    printf("Bank0 Init Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[24];
    b2=smart[25]<<8;
    b3=smart[26]<<16;
    b4=smart[27]<<24;
    printf("Bank0 Init and Runtime Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[28];
    b2=smart[29]<<8;
    b3=smart[30]<<16;
    b4=smart[31]<<24;
    printf("Bank0 Remaining Reserved Block is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[32];
    b2=smart[33]<<8;
    b3=smart[34]<<16;
    b4=smart[35]<<24;
    printf("Bank1 Init Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[36];
    b2=smart[37]<<8;
    b3=smart[38]<<16;
    b4=smart[39]<<24;
    printf("Bank1 Init and Runtime Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[40];
    b2=smart[41]<<8;
    b3=smart[42]<<16;
    b4=smart[43]<<24;
    printf("Bank1 Remaining Reserved Block is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[44];
    b2=smart[45]<<8;
    b3=smart[46]<<16;
    b4=smart[47]<<24;
    printf("Bank2 Init Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[48];
    b2=smart[49]<<8;
    b3=smart[50]<<16;
    b4=smart[51]<<24;
    printf("Bank2 Init and Runtime Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[52];
    b2=smart[53]<<8;
    b3=smart[54]<<16;
    b4=smart[55]<<24;
    printf("Bank2 Remaining Reserved Block is : %lu\n\n" , b1+b2+b3+b4);
  
    b1=smart[56];
    b2=smart[57]<<8;
    b3=smart[58]<<16;
    b4=smart[59]<<24;
    printf("Bank3 Init Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[60];
    b2=smart[61]<<8;
    b3=smart[62]<<16;
    b4=smart[63]<<24;
    printf("Bank3 Init and Runtime Bad Block is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[64];
    b2=smart[65]<<8;
    b3=smart[66]<<16;
    b4=smart[67]<<24;
    printf("Bank3 Remaining Reserved Block is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[68];
    b2=smart[69]<<8;
    b3=smart[70]<<16;
    b4=smart[71]<<24;
    printf("Device Max erase count is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[72];
    b2=smart[73]<<8;
    b3=smart[74]<<16;
    b4=smart[75]<<24;
    printf("Device Min erase count is : %lu\n" , b1+b2+b3+b4);
  

    b1=smart[76];
    b2=smart[77]<<8;
    b3=smart[78]<<16;
    b4=smart[79]<<24;
    printf("Device Avg erase count is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[80];
    b2=smart[81]<<8;
    b3=smart[82]<<16;
    b4=smart[83]<<24;
    printf("Read Reclaim count is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[84];
    b2=smart[85]<<8;
    b3=smart[86]<<16;
    b4=smart[87]<<24;
    printf("Optimal trim size is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[120];
    b2=smart[121]<<8;
    b3=smart[122]<<16;
    b4=smart[123]<<24;
    printf("SLC Max erase count is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[124];
    b2=smart[125]<<8;
    b3=smart[126]<<16;
    b4=smart[127]<<24;
    printf("SLC Min erase count is : %lu\n" , b1+b2+b3+b4);
  

    b1=smart[128];
    b2=smart[129]<<8;
    b3=smart[130]<<16;
    b4=smart[131]<<24;
    printf("SLC Avg erase count is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[132];
    b2=smart[133]<<8;
    b3=smart[134]<<16;
    b4=smart[135]<<24;
    printf("MLC Max erase count is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[136];
    b2=smart[137]<<8;
    b3=smart[138]<<16;
    b4=smart[139]<<24;
    printf("MLC Min erase count is : %lu\n" , b1+b2+b3+b4);
  

    b1=smart[140];
    b2=smart[141]<<8;
    b3=smart[142]<<16;
    b4=smart[143]<<24;
    printf("MLC Avg erase count is : %lu\n\n" , b1+b2+b3+b4);

    printf("Controller Name is : %c%c%c%c\n\n" , smart[312] , smart[313] , smart[314] , smart[315]);
 
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
   __u8 smart[512];
    struct mmc_ioc_cmd idata;
	memset(&idata, 0, sizeof(idata));
	memset(smart, 0, sizeof(__u8) * 512);
	idata.write_flag = 0;
	idata.arg = 0;
	idata.opcode=63;
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	idata.blksz = 512;
	idata.blocks = 1;
	
	mmc_ioc_cmd_set_data(idata, smart);
    x = ioctl(fc, MMC_IOC_CMD, &idata);
    if(x==0)printf("[OK] Get Device Report\n");  
//    printf("Enter '1' if you want to print all SMART Block : ");
//    scanf("%d",&i); debug 2
    printf("\n");
    if(i==1){
	for(int i=0;i<512;i++){
	printf("Data Slice %d : %x\n",i,smart[i]);}printf("\n");}

	b1=smart[0x60];
    b2=smart[0x61]<<8;
    b3=smart[0x62]<<16;
    b4=smart[0x63]<<24;
    printf("Average PE Cycles of Hybrid Area  is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[0];
    b2=smart[1]<<8;
    b3=smart[2]<<16;
    b4=smart[3]<<24;
    printf("Average PE Cycles of Enhanced Area is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[4];
    b2=smart[5]<<8;
    b3=smart[6]<<16;
    b4=smart[7]<<24;
    printf("Average PE Cycles of SLC Area  is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[8];
    b2=smart[9]<<8;
    b3=smart[10]<<16;
    b4=smart[11]<<24;
    printf("Average PE Cycles of MLC/TLC Area  is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[12];
    b2=smart[13]<<8;
    b3=smart[14]<<16;
    b4=smart[15]<<24;
    printf("Read Reclaim Count of Enhanced Area is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[16];
    b2=smart[17]<<8;
    b3=smart[18]<<16;
    b4=smart[19]<<24;
    printf("Read Reclaim Count of SLC Area is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[20];
    b2=smart[21]<<8;
    b3=smart[22]<<16;
    b4=smart[23]<<24;
    printf("Read Reclaim Count of MLC/TLC Area is : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[0x18];
    b2=smart[0x19]<<8;
    b3=smart[0x1a]<<16;
    b4=smart[0x1b]<<24;
    printf("Manufactory Bad Block Count is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[28];
    b2=smart[29]<<8;
    b3=smart[30]<<16;
    b4=smart[31]<<24;
    printf("Runtime Enhanced Area Bad Block Count is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[32];
    b2=smart[33]<<8;
    b3=smart[34]<<16;
    b4=smart[35]<<24;
    printf("Runtime SLC Area Bad Block Count is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[36];
    b2=smart[37]<<8;
    b3=smart[38]<<16;
    b4=smart[39]<<24;
    printf("Runtime MLC/TLC Area Bad Block Count is : %lu\n\n" , b1+b2+b3+b4);
  
    b1=smart[40];
    b2=smart[41]<<8;
    b3=smart[42]<<16;
    b4=smart[43]<<24;
    printf("Patch Trial Count is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[0x2c];
    b2=smart[0x2d];
    b3=smart[0x2e];
    b4=smart[0x2f];
    printf("Patch Release Date : %c%c%c%c" , b1,b2,b3,b4); //will modify
    b1=smart[0x30];
    b2=smart[0x31];
    b3=smart[0x32];
    b4=smart[0x33];
    printf("%c%c%c%c" , b1,b2,b3,b4);
    b1=smart[0x34];
    b2=smart[0x35];
    b3=smart[0x36];
    b4=smart[0x37];
    printf("%c%c%c%c\n" , b1,b2,b3,b4);  
    
    b1=smart[0x38];
    b2=smart[0x39];
    b3=smart[0x3a];
    b4=smart[0x3b];
    printf("Patch Release Time : %c%c%c%c" , b1,b2,b3,b4); //will modify
    b1=smart[0x3c];
    b2=smart[0x3d];
    b3=smart[0x3e];
    b4=smart[0x3f];
    printf("%c%c%c%c\n\n" , b1,b2,b3,b4);  
    
    b1=smart[0x40];
    b2=smart[0x41]<<8;
    b3=smart[0x42]<<16;
    b4=smart[0x43]<<24;
    total = b1+b2+b3+b4;
    printf("Cumulative Write Data Size is : %.1f GB\n" , (total)/10);
    
    b1=smart[0x54];
    b2=smart[0x55]<<8;
    b3=smart[0x56]<<16;
    b4=smart[0x57]<<24;
    total = b1+b2+b3+b4;
    printf("Cumulative Write Data Size in SmartSLC Area is : %.1f GB\n" , (total)/10);
    
    b1=smart[0x58];
    b2=smart[0x59]<<8;
    b3=smart[0x5a]<<16;
    b4=smart[0x5b]<<24;
    total = b1+b2+b3+b4;
    printf("Cumulative SLC Write Data Size in MLC/TLC Area is : %.1f GB\n\n" , (total)/10);
  

    b1=smart[0x5c];
    b2=smart[0x5d]<<8;
    b3=smart[0x5e]<<16;
    b4=smart[0x5f]<<24;
    printf("Allowed hybrid write size exceed limit ? : %lu\n\n" , b1+b2+b3+b4);
    
    b1=smart[0x44];
    b2=smart[0x45]<<8;
    b3=smart[0x46]<<16;
    b4=smart[0x47]<<24;
    printf("Hard VCC Power drop count is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[0x48];
    b2=smart[0x49]<<8;
    b3=smart[0x4a]<<16;
    b4=smart[0x4b]<<24;
    printf("Soft VCC Power drop count is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[0x4c];
    b2=smart[0x4d]<<8;
    b3=smart[0x4e]<<16;
    b4=smart[0x4f]<<24;
    printf("Failed Host Data Recovery Count After Power Loss is : %lu\n" , b1+b2+b3+b4);
    
    b1=smart[0x50];
    b2=smart[0x51]<<8;
    b3=smart[0x52]<<16;
    b4=smart[0x53]<<24;
    printf("Total Recovery Operations After Voltage Drop is : %lu\n" , b1+b2+b3+b4);
    

 
}

int main(){
    int key;
    int altkey;
    char location[64];
    system("clear");
    printf("\tugurkrcl's eMMC Health Reader V1\n");
    printf("\nEnter Location of eMMC:");
    scanf("%s",&location);
    int fc = open(location, O_RDWR);
    system("clear");
    printf("\tugurkrcl's eMMC Health Reader V1\n");
    printf("\nSelect Vendor:");
    printf("\n[0] Samsung");
    printf("\n[1] Sandisk/WD\n");
    scanf("%d",&key);
    system("clear");
    printf("\tugurkrcl's eMMC Health Reader V1\n");
    
    if(key==0){
    system("clear");
    printf("\tugurkrcl's eMMC Health Reader V1\n");
    printf("\nSelect Device:");
    printf("\n[0] MoviNAND 4.3");
    printf("\n[1] MoviNAND 4.41\n");
    scanf("%d",&altkey);
    system("clear");
    if(altkey==0){
    read_movi_43(fc);
        }
    if(altkey==1){
    read_movi_441(fc);
        }
    }
    
    if(key==1){
    read_7232(fc);
    }
return -1;	
}



