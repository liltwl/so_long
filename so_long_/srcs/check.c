/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:38:05 by otaouil           #+#    #+#             */
/*   Updated: 2021/09/21 14:54:22 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

extern struct g_all	g_data;

int	ft_lstupdate(int i, int j, int x1, int z)
{
	t_weed	*w;

	w = g_data.weed;
	if (x1 == 1)
	{
		x1 = -1;
		while (w[++x1].x)
		{
			if (w[x1].x == i && w[x1].y == j)
			{
				if (z == 1)
					w[x1].v = 0;
				return (w[x1].v);
			}
		}
	}
	else
	{
		return (ft_lstexitupdate(i, j, x1, z));
	}
	return (0);
}

int	ft_cisv(void)
{
	int		i;
	t_weed	*w;

	w = g_data.weed;
	i = 0;
	while (i < g_data.err.c)
	{
		if (w[i].v == 1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_press(int key, void *param)
{
	if (key == ESC)
		ft_close(&g_data, 1);
	if (key == W)
		((t_all *)param)->ply.mup = -1;
	else if (key == S)
		((t_all *)param)->ply.mup = 1;
	else if (key == D)
		((t_all *)param)->ply.mr = 1;
	else if (key == A)
		((t_all *)param)->ply.mr = -1;
	ft_draw();
	((t_all *)param)->ply.mr = 0;
	((t_all *)param)->ply.mup = 0;
	return (0);
}

int	ft_mapcheck(t_all *s)
{
	int		i;
	int		j;

	i = -1;
	while (++i < s->map.y)
	{
		j = -1;
		while (++j < s->map.x)
		{
			if (s->map.tab[i][j] == '0' || s->map.tab[i][j] == 'P' ||
				s->map.tab[i][j] == 'E' || s->map.tab[i][j] == 'C')
			{
				if (i == 0 || j == 0 || i == s->map.y - 1
					|| j == s->map.x - 1
					|| s->map.tab[i][j + 1] == '\0' ||
					s->map.tab[i + 1][j] == '\0' ||
					s->map.tab[i - 1][j] == '\0' ||
					s->map.tab[i][j - 1] == '\0')
					return (-1);
			}
		}
	}
	return (1);
}

int	ft_parcheck(t_all *s)
{
	if (s->win.x <= 0 || s->win.y <= 0)
		return (ft_strerror(-14));
	else if (s->err.n < 0)
		return (ft_strerror(-7));
	else if ((s->tex.pd == NULL || s->tex.h == NULL || s->tex.e == NULL)
		|| (s->tex.w == NULL || s->tex.c == NULL || s->tex.ps == NULL
			|| s->tex.pw == NULL) || s->tex.pa == NULL)
		return (ft_strerror(-15));
	else if (s->err.p == 0)
		return (ft_strerror(-17));
	else if (s->err.m < 0)
		return (ft_strerror(-12));
	else if (s->err.c <= 0)
		return (ft_strerror(-4));
	else if (s->err.e <= 0)
		return (ft_strerror(-3));
	else if (s->err.p > 1)
		return (ft_strerror(-18));
	else if (ft_mapcheck(s) == -1)
		return (ft_strerror(-19));
	return (1);
}
