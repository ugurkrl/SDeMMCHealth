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
#include "../cmds.c"
void read_movi_43(int fc, __u8 data_in[512]){
    printf("\nMoviNAND Health Reader\n\n");
    int i=0;
    int x = 0;
    int y=1;
    unsigned int b1=0,b2=0,b3=0,b4 = 0;
 //   printf("send vendor cmd ?\n"); //for debug purpose
 //   scanf("%d",&y);
    if(y==1){
    x = mmc_62_vendor_cmd(0xEFAC62EC, fc);
	if(x==0)printf("[OK] Vendor Command\n");
    x = mmc_62_vendor_cmd(0x0000CCEE, fc);
    if(x==0)printf("[OK] SMART Report Command\n");
   }
    int ret=0;

    struct mmc_ioc_cmd idata;
	memset(&idata, 0, sizeof(idata));
	memset(data_in, 0, sizeof(__u8) * 512);
	idata.write_flag = 0;
	idata.arg = 0;
	idata.opcode=17;
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	idata.blksz = 512;
	idata.blocks = 1;
	
	mmc_ioc_cmd_set_data(idata, data_in);
    x = ioctl(fc, MMC_IOC_CMD, &idata);
    if(x==0)printf("[OK] Get SMART Report\n");
    x = mmc_62_vendor_cmd(0x00DECCEE, fc);    
//    printf("Enter '1' if you want to print all SMART Block : ");
//    scanf("%d",&i); debug 2
    printf("\n");
    if(i==1){
	for(int i=0;i<512;i++){
	printf("Data Slice %d : %x\n",i,data_in[i]);}printf("\n");}

	b1=data_in[0];
    b2=data_in[1];
    b3=data_in[2];
    b4=data_in[3];
    printf("Error Mode is : 0x%x%x%x%x\n\n" , b1,b2,b3,b4);
    
    b1=data_in[4];
    b2=data_in[5]<<8;
    b3=data_in[6]<<16;
    b4=data_in[7]<<24;
    printf("Super Block Size is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[8];
    b2=data_in[9]<<8;
    b3=data_in[10]<<16;
    b4=data_in[11]<<24;
    printf("Super Page Size is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[12];
    b2=data_in[13]<<8;
    b3=data_in[14]<<16;
    b4=data_in[15]<<24;
    printf("Optimal Write Size is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[16];
    b2=data_in[17]<<8;
    b3=data_in[18]<<16;
    b4=data_in[19]<<24;
    printf("Bank Count is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[20];
    b2=data_in[21]<<8;
    b3=data_in[22]<<16;
    b4=data_in[23]<<24;
    printf("Bank0 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[24];
    b2=data_in[25]<<8;
    b3=data_in[26]<<16;
    b4=data_in[27]<<24;
    printf("Bank0 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[28];
    b2=data_in[29]<<8;
    b3=data_in[30]<<16;
    b4=data_in[31]<<24;
    printf("Bank0 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[32];
    b2=data_in[33]<<8;
    b3=data_in[34]<<16;
    b4=data_in[35]<<24;
    printf("Bank1 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[36];
    b2=data_in[37]<<8;
    b3=data_in[38]<<16;
    b4=data_in[39]<<24;
    printf("Bank1 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[40];
    b2=data_in[41]<<8;
    b3=data_in[42]<<16;
    b4=data_in[43]<<24;
    printf("Bank1 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[44];
    b2=data_in[45]<<8;
    b3=data_in[46]<<16;
    b4=data_in[47]<<24;
    printf("Bank2 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[48];
    b2=data_in[49]<<8;
    b3=data_in[50]<<16;
    b4=data_in[51]<<24;
    printf("Bank2 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[52];
    b2=data_in[53]<<8;
    b3=data_in[54]<<16;
    b4=data_in[55]<<24;
    printf("Bank2 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
  
    b1=data_in[56];
    b2=data_in[57]<<8;
    b3=data_in[58]<<16;
    b4=data_in[59]<<24;
    printf("Bank3 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[60];
    b2=data_in[61]<<8;
    b3=data_in[62]<<16;
    b4=data_in[63]<<24;
    printf("Bank3 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[64];
    b2=data_in[65]<<8;
    b3=data_in[66]<<16;
    b4=data_in[67]<<24;
    printf("Bank3 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[68];
    b2=data_in[69]<<8;
    b3=data_in[70]<<16;
    b4=data_in[71]<<24;
    printf("Device Max erase count is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[72];
    b2=data_in[73]<<8;
    b3=data_in[74]<<16;
    b4=data_in[75]<<24;
    printf("Device Min erase count is : %u\n" , b1+b2+b3+b4);
  

    b1=data_in[76];
    b2=data_in[77]<<8;
    b3=data_in[78]<<16;
    b4=data_in[79]<<24;
    printf("Device Avg erase count is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[80];
    b2=data_in[81]<<8;
    b3=data_in[82]<<16;
    b4=data_in[83]<<24;
    printf("Number of UECC Error is : %u\n\n" , b1+b2+b3+b4);
  
    b1=data_in[220];
    b2=data_in[221]<<8;
    b3=data_in[222]<<16;
    b4=data_in[223]<<24;
    printf("Read Reclaim Count is : %u\n\n" , b1+b2+b3+b4);

    printf("Controller Name is : %c%c%c%c\n\n" , data_in[312] , data_in[313] , data_in[314] , data_in[315]);
 
}
void read_movi_441(int fc){
    

    printf("\nMoviNAND Health Reader\n\n");
    int i=0;
    int x = 0;
    int y=1;
       __u8 data_in[512];
    unsigned int b1=0,b2=0,b3=0,b4 = 0;
 //   printf("send vendor cmd ?\n"); //for debug purpose
 //   scanf("%d",&y);
    if(y==1){
    x = mmc_62_vendor_cmd(0xEFAC62EC, fc);
	if(x==0)printf("[OK] Vendor Command\n");
    x = mmc_62_vendor_cmd(0x0000CCEE, fc);
    if(x==0)printf("[OK] SMART Report Command\n");
   }
    int ret=0;
    struct mmc_ioc_cmd idata;
	memset(&idata, 0, sizeof(idata));
	memset(data_in, 0, sizeof(__u8) * 512);
	idata.write_flag = 0;
	idata.arg = 0;
	idata.opcode=17;
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	idata.blksz = 512;
	idata.blocks = 1;
	
	mmc_ioc_cmd_set_data(idata, data_in);
    x = ioctl(fc, MMC_IOC_CMD, &idata);
    if(x==0)printf("[OK] Get SMART Report\n");
    x = mmc_62_vendor_cmd(0x00DECCEE, fc);    
//    printf("Enter '1' if you want to print all SMART Block : ");
//    scanf("%d",&i); debug 2
    printf("\n");
    if(i==1){
	for(int i=0;i<512;i++){
	printf("Data Slice %d : %x\n",i,data_in[i]);}printf("\n");}

	b1=data_in[0];
    b2=data_in[1];
    b3=data_in[2];
    b4=data_in[3];
    printf("Error Mode is : 0x%x%x%x%x\n\n" , b1,b2,b3,b4);
    
    b1=data_in[4];
    b2=data_in[5]<<8;
    b3=data_in[6]<<16;
    b4=data_in[7]<<24;
    printf("Super Block Size is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[8];
    b2=data_in[9]<<8;
    b3=data_in[10]<<16;
    b4=data_in[11]<<24;
    printf("Super Page Size is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[12];
    b2=data_in[13]<<8;
    b3=data_in[14]<<16;
    b4=data_in[15]<<24;
    printf("Optimal Write Size is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[16];
    b2=data_in[17]<<8;
    b3=data_in[18]<<16;
    b4=data_in[19]<<24;
    printf("Bank Count is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[20];
    b2=data_in[21]<<8;
    b3=data_in[22]<<16;
    b4=data_in[23]<<24;
    printf("Bank0 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[24];
    b2=data_in[25]<<8;
    b3=data_in[26]<<16;
    b4=data_in[27]<<24;
    printf("Bank0 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[28];
    b2=data_in[29]<<8;
    b3=data_in[30]<<16;
    b4=data_in[31]<<24;
    printf("Bank0 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[32];
    b2=data_in[33]<<8;
    b3=data_in[34]<<16;
    b4=data_in[35]<<24;
    printf("Bank1 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[36];
    b2=data_in[37]<<8;
    b3=data_in[38]<<16;
    b4=data_in[39]<<24;
    printf("Bank1 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[40];
    b2=data_in[41]<<8;
    b3=data_in[42]<<16;
    b4=data_in[43]<<24;
    printf("Bank1 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[44];
    b2=data_in[45]<<8;
    b3=data_in[46]<<16;
    b4=data_in[47]<<24;
    printf("Bank2 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[48];
    b2=data_in[49]<<8;
    b3=data_in[50]<<16;
    b4=data_in[51]<<24;
    printf("Bank2 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[52];
    b2=data_in[53]<<8;
    b3=data_in[54]<<16;
    b4=data_in[55]<<24;
    printf("Bank2 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
  
    b1=data_in[56];
    b2=data_in[57]<<8;
    b3=data_in[58]<<16;
    b4=data_in[59]<<24;
    printf("Bank3 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[60];
    b2=data_in[61]<<8;
    b3=data_in[62]<<16;
    b4=data_in[63]<<24;
    printf("Bank3 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[64];
    b2=data_in[65]<<8;
    b3=data_in[66]<<16;
    b4=data_in[67]<<24;
    printf("Bank3 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[68];
    b2=data_in[69]<<8;
    b3=data_in[70]<<16;
    b4=data_in[71]<<24;
    printf("Device Max erase count is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[72];
    b2=data_in[73]<<8;
    b3=data_in[74]<<16;
    b4=data_in[75]<<24;
    printf("Device Min erase count is : %u\n" , b1+b2+b3+b4);
  

    b1=data_in[76];
    b2=data_in[77]<<8;
    b3=data_in[78]<<16;
    b4=data_in[79]<<24;
    printf("Device Avg erase count is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[80];
    b2=data_in[81]<<8;
    b3=data_in[82]<<16;
    b4=data_in[83]<<24;
    printf("Read Reclaim count is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[84];
    b2=data_in[85]<<8;
    b3=data_in[86]<<16;
    b4=data_in[87]<<24;
    printf("Optimal trim size is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[120];
    b2=data_in[121]<<8;
    b3=data_in[122]<<16;
    b4=data_in[123]<<24;
    printf("SLC Max erase count is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[124];
    b2=data_in[125]<<8;
    b3=data_in[126]<<16;
    b4=data_in[127]<<24;
    printf("SLC Min erase count is : %u\n" , b1+b2+b3+b4);
  

    b1=data_in[128];
    b2=data_in[129]<<8;
    b3=data_in[130]<<16;
    b4=data_in[131]<<24;
    printf("SLC Avg erase count is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[132];
    b2=data_in[133]<<8;
    b3=data_in[134]<<16;
    b4=data_in[135]<<24;
    printf("MLC Max erase count is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[136];
    b2=data_in[137]<<8;
    b3=data_in[138]<<16;
    b4=data_in[139]<<24;
    printf("MLC Min erase count is : %u\n" , b1+b2+b3+b4);
  

    b1=data_in[140];
    b2=data_in[141]<<8;
    b3=data_in[142]<<16;
    b4=data_in[143]<<24;
    printf("MLC Avg erase count is : %u\n\n" , b1+b2+b3+b4);

    printf("Controller Name is : %c%c%c%c\n\n" , data_in[312] , data_in[313] , data_in[314] , data_in[315]);
}

void read_movi_sd(int fc){
    

    printf("\nMoviNAND Health Reader\n\n");
    int i=0;
    int x = 0;
    int y=1;
       __u8 data_in[512];
    unsigned int b1=0,b2=0,b3=0,b4 = 0;
 //   printf("send vendor cmd ?\n"); //for debug purpose
 //   scanf("%d",&y);
    if(y==1){
    x = mmc_62_vendor_cmd(0xEFAC62EC, fc);
	if(x==0)printf("[OK] Vendor Command\n");
    x = mmc_62_vendor_cmd(0x0000CCEE, fc);
    if(x==0)printf("[OK] SMART Report Command\n");
   }
    int ret=0;
    struct mmc_ioc_cmd idata;
	memset(&idata, 0, sizeof(idata));
	memset(data_in, 0, sizeof(__u8) * 512);
	idata.write_flag = 0;
	idata.arg = 0;
	idata.opcode=17;
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	idata.blksz = 512;
	idata.blocks = 1;
	
	mmc_ioc_cmd_set_data(idata, data_in);
    x = ioctl(fc, MMC_IOC_CMD, &idata);
    if(x==0)printf("[OK] Get SMART Report\n");
    x = mmc_62_vendor_cmd(0x00DECCEE, fc);    
//    printf("Enter '1' if you want to print all SMART Block : ");
//    scanf("%d",&i); debug 2
    printf("\n");
    if(i==1){
	for(int i=0;i<512;i++){
	printf("Data Slice %d : %x\n",i,data_in[i]);}printf("\n");}

	b1=data_in[0];
    b2=data_in[1];
    b3=data_in[2];
    b4=data_in[3];
    printf("Error Mode is : 0x%x%x%x%x\n\n" , b1,b2,b3,b4);
    
    b1=data_in[4];
    b2=data_in[5]<<8;
    b3=data_in[6]<<16;
    b4=data_in[7]<<24;
    printf("Super Block Size is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[8];
    b2=data_in[9]<<8;
    b3=data_in[10]<<16;
    b4=data_in[11]<<24;
    printf("Super Page Size is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[12];
    b2=data_in[13]<<8;
    b3=data_in[14]<<16;
    b4=data_in[15]<<24;
    printf("Optimal Write Size is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[16];
    b2=data_in[17]<<8;
    b3=data_in[18]<<16;
    b4=data_in[19]<<24;
    printf("Bank Count is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[20];
    b2=data_in[21]<<8;
    b3=data_in[22]<<16;
    b4=data_in[23]<<24;
    printf("Bank0 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[24];
    b2=data_in[25]<<8;
    b3=data_in[26]<<16;
    b4=data_in[27]<<24;
    printf("Bank0 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[28];
    b2=data_in[29]<<8;
    b3=data_in[30]<<16;
    b4=data_in[31]<<24;
    printf("Bank0 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[32];
    b2=data_in[33]<<8;
    b3=data_in[34]<<16;
    b4=data_in[35]<<24;
    printf("Bank1 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[36];
    b2=data_in[37]<<8;
    b3=data_in[38]<<16;
    b4=data_in[39]<<24;
    printf("Bank1 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[40];
    b2=data_in[41]<<8;
    b3=data_in[42]<<16;
    b4=data_in[43]<<24;
    printf("Bank1 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[44];
    b2=data_in[45]<<8;
    b3=data_in[46]<<16;
    b4=data_in[47]<<24;
    printf("Bank2 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[48];
    b2=data_in[49]<<8;
    b3=data_in[50]<<16;
    b4=data_in[51]<<24;
    printf("Bank2 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[52];
    b2=data_in[53]<<8;
    b3=data_in[54]<<16;
    b4=data_in[55]<<24;
    printf("Bank2 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
  
    b1=data_in[56];
    b2=data_in[57]<<8;
    b3=data_in[58]<<16;
    b4=data_in[59]<<24;
    printf("Bank3 Init Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[60];
    b2=data_in[61]<<8;
    b3=data_in[62]<<16;
    b4=data_in[63]<<24;
    printf("Bank3 Init and Runtime Bad Block is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[64];
    b2=data_in[65]<<8;
    b3=data_in[66]<<16;
    b4=data_in[67]<<24;
    printf("Bank3 Remaining Reserved Block is : %u\n\n" , b1+b2+b3+b4);
    
    
    printf("SLC Erase Count Min: %ld Max: %ld Avg: %ld \n" ,
    (long)((data_in[68]) + (data_in[69]<<8) + (data_in[70]<<16 )+ (data_in[71]<<24)),
    (long)((data_in[72]) + (data_in[73]<<8) + (data_in[74]<<16 )+ (data_in[75]<<24)),
    (long)((data_in[76]) + (data_in[77]<<8) + (data_in[78]<<16 )+ (data_in[79]<<24)));
    
    b1=data_in[72];
    b2=data_in[73]<<8;
    b3=data_in[74]<<16;
    b4=data_in[75]<<24;
    printf("SLC Min erase count is : %u\n" , b1+b2+b3+b4);
  

    b1=data_in[76];
    b2=data_in[77]<<8;
    b3=data_in[78]<<16;
    b4=data_in[79]<<24;
    printf("SLC Avg erase count is : %u\n\n" , b1+b2+b3+b4);
    
    b1=data_in[80];
    b2=data_in[81]<<8;
    b3=data_in[82]<<16;
    b4=data_in[83]<<24;
    printf("MLC Max Erase Count is: %u\n" , b1+b2+b3+b4);
    
    b1=data_in[84];
    b2=data_in[85]<<8;
    b3=data_in[86]<<16;
    b4=data_in[87]<<24;
    printf("MLC Min Erase Count is : %u\n" , b1+b2+b3+b4);
    
    b1=data_in[88];
    b2=data_in[89]<<8;
    b3=data_in[90]<<16;
    b4=data_in[91]<<24;
    printf("MLC Avg Erase Count is : %u\n" , b1+b2+b3+b4);
    
    printf("Controller Name is : %c%c%c%c\n\n" , data_in[312] , data_in[313] , data_in[314] , data_in[315]);
}