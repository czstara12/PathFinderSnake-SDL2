#pragma once
#include <Windows.h>
struct DFSmap
{
	bool w, s, a, d, sign, active, nopen;
};
Direction ai(short const map[][WIDTH]//地图
	,short size//蛇长
	,short x,short y
	,int qiantao);
int simulate(const short map[][WIDTH]
	, DFSmap * p_start
	, short size
	, short x, short y);
Direction ai2(short const map[][WIDTH]//地图
	, short size//蛇长
	, short x, short y);
int simulate2(const short map[][WIDTH]
	, DFSmap * p_start
	, short size
	, short x, short y);