#include "../so_long.h"

extern struct g_all	g_data;

void	ft_addtoexit(int i, int j, int *cnt, t_exit *x)
{
	x[*cnt].x = j;
	x[*cnt].v = 1;
	x[(*cnt)++].y = i;
	g_data.err.e++;
}

void	ft_addtowd(int i, int j, int *l, t_weed *w)
{
	w[(*l)].x = j;
	w[(*l)].v = 1;
	w[(*l)++].y = i;
	g_data.err.c++;
}
