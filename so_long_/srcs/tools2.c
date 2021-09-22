#include "../so_long.h"

extern struct g_all	g_data;

char	haswallat(int x, int y, t_all *s)
{
	int	xX;
	int	xY;

	if (x < 0 || x >= s->win.x || y < 0 || y >= s->win.y)
		return (0);
	xX = floor(x / 64);
	xY = floor(y / 64);
	return (s->map.tab[xY][xX]);
}

int	ft_namecheck(char *arg, char *ext)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1])
		&& (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int	ft_addtolst(char **p, t_weed *w, t_exit *x)
{
	int	i;
	int	j;
	int	cnt;
	int	l;

	cnt = 0;
	i = -1;
	l = 0;
	while (p[++i])
	{
		j = -1;
		while (p[i][++j])
		{
			if (p[i][j] == 'C')
				ft_addtowd(i, j, &l, w);
			else if (p[i][j] == 'E')
				ft_addtoexit(i, j, &cnt, x);
		}
	}
	return (0);
}

void	ft_lst(t_all *s)
{
	int	exit;
	int	weed;

	weed = ft_nlen('C', s->map.tab);
	exit = ft_nlen('E', s->map.tab);
	if (s->weed == NULL)
		s->weed = malloc(sizeof(t_weed) * (weed + 1));
	if (s->exit == NULL)
		s->exit = malloc(sizeof(t_exit) * (exit + 2));
	ft_addtolst(s->map.tab, s->weed, s->exit);
}

int	ft_nlen(char n, char **p)
{
	int	i;
	int	j;
	int	cnt;

	cnt = 0;
	i = -1;
	while (p[++i])
	{
		j = -1;
		while (p[i][++j])
		{
			if (p[i][j] == n)
				cnt++;
		}
	}
	return (cnt);
}
