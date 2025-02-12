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
void read_movi(int fc, __u8 data_in[512],int ver){
    printf("\nMoviNAND Health Reader\n\n");
    int i=0;
    int x = 0;


    x = mmc_62_vendor_cmd(0xEFAC62EC, fc);
	if(x==0)printf("[OK] Vendor Command\n");
    x = mmc_62_vendor_cmd(0x0000CCEE, fc);
    if(x==0)printf("[OK] SMART Report Command\n");
   

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

    printf("\n");


    printf("Error Mode is : 0x%x%x%x%x\n\n" , data_in[0],data_in[1],data_in[2],data_in[3]);
    printf("Super Block Size is : %u\n" ,(int)((data_in[7] << 24) + (data_in[6] << 16) + (data_in[5] << 8) + data_in[4]));
    printf("Super Page Size is : %u\n" ,(int)((data_in[11] << 24) + (data_in[10] << 16) + (data_in[9] << 8) + data_in[8]));
    printf("Optimal Write Size is : %u\n" ,(int)((data_in[15] << 24) + (data_in[14] << 16) + (data_in[13] << 8) + data_in[12]));
    printf("Bank Count is : %u\n\n" ,(int)((data_in[19] << 24) + (data_in[18] << 16) + (data_in[17] << 8) + data_in[16]));
    printf("Bad Block Table: Init|Later|Reserved\n");
    printf("Bank0: %u|%u|%u\n" ,(int)((data_in[23] << 24) + (data_in[22] << 16) + (data_in[21] << 8) + data_in[20]),
    (int)((data_in[27] << 24) + (data_in[26] << 16) + (data_in[25] << 8) + data_in[24]),
    (int)((data_in[31] << 24) + (data_in[30] << 16) + (data_in[29] << 8) + data_in[28]));

    printf("Bank1: %u|%u|%u\n" ,(int)((data_in[35] << 24) + (data_in[34] << 16) + (data_in[33] << 8) + data_in[32]),
    (int)((data_in[39] << 24) + (data_in[38] << 16) + (data_in[37] << 8) + data_in[36]),
    (int)((data_in[43] << 24) + (data_in[42] << 16) + (data_in[41] << 8) + data_in[40]));
    
    printf("Bank2: %u|%u|%u\n" ,(int)((data_in[47] << 24) + (data_in[46] << 16) + (data_in[45] << 8) + data_in[44]),
    (int)((data_in[51] << 24) + (data_in[50] << 16) + (data_in[49] << 8) + data_in[48]),
    (int)((data_in[55] << 24) + (data_in[54] << 16) + (data_in[53] << 8) + data_in[52]));

    printf("Bank3: %u|%u|%u\n\n" ,(int)((data_in[59] << 24) + (data_in[58] << 16) + (data_in[57] << 8) + data_in[56]),
    (int)((data_in[63] << 24) + (data_in[62] << 16) + (data_in[61] << 8) + data_in[60]),
    (int)((data_in[67] << 24) + (data_in[66] << 16) + (data_in[65] << 8) + data_in[64]));

    printf("All Erase Count Max:%u Min:%u Avg:%u\n",(int)((data_in[71] << 24) + (data_in[70] << 16) + (data_in[69] << 8) + data_in[68]),
    (int)((data_in[75] << 24) + (data_in[74] << 16) + (data_in[73] << 8) + data_in[72]),
    (int)((data_in[79] << 24) + (data_in[78] << 16) + (data_in[77] << 8) + data_in[76]));

    if(ver==441){ //4.41+
        printf("SLC Erase Count Max:%u Min:%u Avg:%u\n",(int)((data_in[123] << 24) + (data_in[122] << 16) + (data_in[121] << 8) + data_in[120]),
        (int)((data_in[127] << 24) + (data_in[126] << 16) + (data_in[125] << 8) + data_in[124]),
        (int)((data_in[131] << 24) + (data_in[130] << 16) + (data_in[129] << 8) + data_in[128]));
        printf("MLC Erase Count Max:%u Min:%u Avg:%u\n\n",(int)((data_in[135] << 24) + (data_in[134] << 16) + (data_in[133] << 8) + data_in[132]),
        (int)((data_in[139] << 24) + (data_in[138] << 16) + (data_in[137] << 8) + data_in[136]),
        (int)((data_in[143] << 24) + (data_in[142] << 16) + (data_in[141] << 8) + data_in[140]));
    } 
    if(ver==64){ //SD
        printf("SLC Erase Count Max:%u Min:%u Avg:%u\n",(int)((data_in[71] << 24) + (data_in[70] << 16) + (data_in[69] << 8) + data_in[68]),
        (int)((data_in[75] << 24) + (data_in[74] << 16) + (data_in[73] << 8) + data_in[72]),
        (int)((data_in[79] << 24) + (data_in[78] << 16) + (data_in[77] << 8) + data_in[76]));
        printf("MLC Erase Count Max:%u Min:%u Avg:%u\n\n",(int)((data_in[83] << 24) + (data_in[82] << 16) + (data_in[81] << 8) + data_in[80]),
        (int)((data_in[87] << 24) + (data_in[86] << 16) + (data_in[85] << 8) + data_in[84]),
        (int)((data_in[91] << 24) + (data_in[90] << 16) + (data_in[89] << 8) + data_in[88]));
        printf("Read Reclaim Count is : %u\n\n" ,(int)((data_in[83] << 24) + (data_in[82] << 16) + (data_in[81] << 8) + data_in[80]));
        printf("Optimal Trim Size is : %u\n" ,(int)((data_in[87] << 24) + (data_in[86] << 16) + (data_in[85] << 8) + data_in[84]));
    }

    if(ver==43){ //4.41-
    printf("Number of UECC Error is : %u\n" ,(int)((data_in[83] << 24) + (data_in[82] << 16) + (data_in[81] << 8) + data_in[80]));

    printf("Read Reclaim count is : %u\n\n" ,(int)((data_in[223] << 24) + (data_in[222] << 16) + (data_in[221] << 8) + data_in[220]));
    }

    if(ver==441){
    printf("Read Reclaim Count is : %u\n\n" ,(int)((data_in[83] << 24) + (data_in[82] << 16) + (data_in[81] << 8) + data_in[80]));
    printf("Optimal Trim Size is : %u\n" ,(int)((data_in[87] << 24) + (data_in[86] << 16) + (data_in[85] << 8) + data_in[84]));
    printf("Hash Code is : 0x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x\n\n" , 
                                             data_in[119],data_in[118],data_in[117],data_in[116],data_in[115],data_in[114],data_in[113],data_in[112],
                                             data_in[111],data_in[110],data_in[109],data_in[108],data_in[107],data_in[106],data_in[105],data_in[104],
                                             data_in[103],data_in[102],data_in[101],data_in[100],data_in[99],data_in[98],data_in[97],data_in[96],
                                             data_in[95],data_in[94],data_in[93],data_in[92],data_in[91],data_in[90],data_in[89],data_in[88]);                
    
    }
    printf("Controller Name is : %c%c%c%c\n\n" ,data_in[312] , data_in[313] , data_in[314] , data_in[315]);
    

 
}

