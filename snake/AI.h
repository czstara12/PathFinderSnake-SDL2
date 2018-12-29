#pragma once
#include <Windows.h>
struct DFSmap
{
	bool w, s, a, d, sign, active, nopen;
};
Direction ai(short const map[][WIDTH]//µØÍ¼
	,short size//Éß³¤
	,short x,short y
	,int qiantao);
int simulate(const short map[][WIDTH]
	, DFSmap * p_start
	, short size
	, short x, short y);