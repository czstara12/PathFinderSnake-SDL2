#pragma once
#ifndef AI_H
#define AI_H

#include "public.h"
#include <stdlib.h>
#include <wtypes.h>

typedef struct DFSmap
{
	BOOL w, s, a, d, sign, active, nopen;
} DFSmap;
Direction ai(short const grid[][WIDTH], // 地图
			 short size,				// 蛇长
			 short x, short y, int qiantao);
int simulate(const short grid[][WIDTH], DFSmap *p_start, short size, short x, short y);
Direction ai2(short const grid[][WIDTH], // 地图
			  short size,				 // 蛇长
			  short x, short y);
int simulate2(const short grid[][WIDTH], DFSmap *p_start, short size, short x, short y);

#endif // !AI_H