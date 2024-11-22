#include "incl.h"
#include "func.h"
// test 0
// input: section = "LOD"; param = "fLODFadeOutMultItems";
// return: 6
//out_buff: 2.5000

// test 1
// input: section = "Water"; param = bReflectLODTrees;
// return: 1
//out_buff: 0  

// test 2
// input: section = "Wate"; param = "bReflectLODLand";
// return: -2
//out_buff: error

// test 3
// input: section = "Waterr"; param = "bReflectLODLand";
// return: -2
//out_buff: error

// test 4
// input: section = "Archive"; param = "InvalidateOlderFiles"
// return: -3
//out_buff: error 

int main(void)
{
    int max = 64;
    char name[64] = "test.ini", section[64] = "Archive", param[64] = "InvalidateOlderFiles";
    char out_buffer[64] = "";
    char defaultt[] = "error";
    char c;
    int info;
    info = GetPrivateProfileString(section, param, defaultt,  out_buffer,  max, name);
    printf("num = %d\n", info);
    printf("%s\n", out_buffer);
    return 0;
}



