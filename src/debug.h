#ifndef	DEBUG_H_INCLUDED
#define	DEBUG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define	MAX_ERR_MSG	256

#ifdef	ERR_MSG
#undef	ERR_MSG
#endif
#ifdef	STD_ERR_MSG
#undef	STD_ERR_MSG
#endif
#ifdef	DEBUG_MSG
#undef	DEBUG_MSG
#endif

#ifndef	NDEBUG

#define	ERR_MSG(fmt,...) do {\
		fprintf(stderr,fmt,##__VA_ARGS__);\
	}while(0)

#define	STD_ERR_MSG(fmt,...) do{\
		char errmsg[MAX_ERR_MSG] = {0};\
		sprintf(errmsg,fmt,##__VA_ARGS__);\
		perror(errmsg);\
		fprintf(stderr,"\n");\
	}while(0)

#define	DEBUG_MSG(fmt,...) do{\
		printf(fmt,##__VA_ARGS__);\
	}while(0)

#else

#define	ERR_MSG(fmt,...)
#define	STD_ERR_MSG(fmt,...)
#define	DEBUG_MSG(fmt,...)

#endif

#endif
