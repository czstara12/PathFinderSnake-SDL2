#include "snake.h"
#include "AI.h"


Direction ai(short const map[][WIDTH]//地图
	, short size//蛇长
	, short x, short y//蛇头坐标
	, int qiantao
)
{

	DFSmap dmap[HEIGHT][WIDTH];
	DFSmap * p_start;

	short const * pa;
	DFSmap * pb;
	for (pa = map[0], pb = dmap[0]; pb <= &dmap[HEIGHT - 1][WIDTH - 1]; pa++, pb++)
	{
		pb->active = pb->d = pb->nopen = pb->s = pb->sign = pb->w = pb->a = false;
		if (*pa != 0)
			if (*pa == -1)
			{
				pb->active = true;
				pb->sign = true;
			}
			else if (*pa == size)
			{
				p_start = pb;
				pb->nopen = false;
			}
			else if (qiantao == 1 && *pa == 1) {
				pb->nopen = false;
				pb->active = true;
				pb->sign = true;
			}
			else
				pb->nopen = true;
	}

	int num = 1;
	while (p_start->sign == false && num != 0)
	{
		num = 0;
		DFSmap * pdmap;
		for (pdmap = &dmap[0][0]; pdmap <= &dmap[HEIGHT - 1][WIDTH - 1]; pdmap++)
		{
			if (pdmap->active == true)
			{
				num++;
				if ((pdmap - WIDTH)->nopen == false)
					if ((pdmap - WIDTH)->sign == false)
					{
						(pdmap - WIDTH)->s = true;
						(pdmap - WIDTH)->active = true;
					}
				if ((pdmap - 1)->nopen == false)
					if ((pdmap - 1)->sign == false)
					{
						(pdmap - 1)->d = true;
						(pdmap - 1)->active = true;
					}
				if ((pdmap + 1)->nopen == false)
					if ((pdmap + 1)->sign == false)
					{
						(pdmap + 1)->a = true;
						(pdmap + 1)->active = true;
					}
				if ((pdmap + WIDTH)->nopen == false)
					if ((pdmap + WIDTH)->sign == false)
					{
						(pdmap + WIDTH)->w = true;
						(pdmap + WIDTH)->active = true;
					}
				pdmap->active = false;
				pdmap->sign = true;
			}
		}
	}
	if (num == 0) {
		if (qiantao == 0)
			MessageBox(NULL, "没路了1", "error", MB_OK);
		return d_error;
	}
	else if (qiantao == 1)
	{
		if (p_start->w == true)return d_up;
		else if (p_start->a == true)return d_left;
		else if (p_start->s == true)return d_down;
		else if (p_start->d == true)return d_right;
	}
	else if (simulate(map, p_start, size, x, y) == 0)
		MessageBox(NULL, "没路了2", "error", MB_OK);
	else
		if (p_start->w == true)return d_up;
		else if (p_start->a == true)return d_left;
		else if (p_start->s == true)return d_down;
		else if (p_start->d == true)return d_right;

	return d_error;
}
int simulate(const short map[][WIDTH]
	, DFSmap * p_start
	, short size
	, short x, short y)
{
	short vir_map[HEIGHT][WIDTH], endx, endy;
	for (int h = 0; h < HEIGHT; h++)
		for (int w = 0; w < WIDTH; w++)
			vir_map[h][w] = map[h][w];
	Direction dire;
	DFSmap * pn = p_start;
	short * pv = &vir_map[y][x];
	while (1)
	{
		if (pn->w == true)
		{
			pn -= WIDTH;
			pv -= WIDTH;
		}
		else if (pn->a == true)
		{
			pn -= 1;
			pv -= 1;
		}
		else if (pn->s == true)
		{
			pn += WIDTH;
			pv += WIDTH;
		}
		else if (pn->d == true)
		{
			pn += 1;
			pv += 1;
		}
		if (*pv != -1)
		{
			*pv = size + 1;
			for (int a = 0; a < HEIGHT; a++)
				for (int b = 0; b < HEIGHT; b++)
					vir_map[a][b] = (vir_map[a][b] > 0 ? vir_map[a][b] - 1 : vir_map[a][b]);
		}
		else
		{
			*pv = size + 1;
			break;
		}
	}//模拟走一遍
	for (short h = 0; h < HEIGHT; h++)
		for (short w = 0; w < WIDTH; w++)
			if (vir_map[h][w] == 1)
			{
				endx = w;
				endy = h;
				h = HEIGHT;
				w = WIDTH;
			}
	if (ai(vir_map, size + 1, endx, endy, 1) != d_error)
		return 1;
	else
		return 0;
}