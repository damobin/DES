#ifndef PUBLIC_H
#define PUBLIC_H

// add c head file
#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef __cplusplus
}
#endif
//end add c head file

typedef unsigned int  uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;






#define PRINTSTRDATA(src,len,step)	do{			\
	if(len<=step){								\
		printf("\n");							\
		for(int a=0;  a<len;  a++){				\
			printf("%02x ",src[a]);				\
		}										\
	}else{										\
		printf("\n");							\
		for(int a=0;  a<len;  a++){				\
			printf("%02x ",src[a]);				\
			if(a!=0 && (a+1)%step == 0){		\
				printf("\n");					\
			}									\
		}										\
	}											\
	printf("\n");								\
}while(0);


#endif
