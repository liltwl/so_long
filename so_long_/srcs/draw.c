/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:32:02 by otaouil           #+#    #+#             */
/*   Updated: 2021/09/21 14:33:17 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

extern struct g_all	g_data;

void	my_mlx_pixel_put(int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x > g_data.win.x || y < 0 || y > g_data.win.y)
		return ;
	dst = g_data.img.adr + (y * g_data.img.n + x * (g_data.img.fsh / 8));
	*(unsigned int *)dst = color;
}

void	drawwall(int i, int j, unsigned int	*v)
{
	int	y;
	int	x;
	int	s;

	y = j;
	x = -1;
	s = 1;
	while (++x < 64 && i < g_data.win.x)
	{
		j = y - 1;
		s = -1;
		i++;
		while (++j < y + 64 && j < g_data.win.y - 1)
			if (x < 64 && ++s < 64)
				if ((unsigned int)v[(s * 64) + x] != (unsigned int)4278190080)
					my_mlx_pixel_put(i, j, v[(s * 64) + x]);
	}
}

void	drawmap(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g_data.map.y)
	{
		j = -1;
		while (++j < g_data.map.x)
		{
			drawwall(j * 64, i * 64, g_data.tex.h);
			if (g_data.map.tab[i][j] == '1')
				drawwall(j * 64, i * 64, g_data.tex.w);
			else if (g_data.map.tab[i][j] == 'C' && ft_lstupdate(j, i, 1, 0))
				drawwall(j * 64, i * 64, g_data.tex.c);
			else if (g_data.map.tab[i][j] == 'E' && ft_lstupdate(j, i, 2, 0))
				drawwall(j * 64, i * 64, g_data.tex.e);
		}
	}
}

void	plyupdate(void)
{
	int	x;
	int	y;

	x = (g_data.ply.mr * g_data.map.ts) + g_data.ply.x;
	y = (g_data.ply.mup * g_data.map.ts) + g_data.ply.y;
	if (haswallat(x, y, &g_data) != '1' && (x != g_data.ply.x
			||y != g_data.ply.y) && g_data.ply.ms
		&&haswallat(x, y, &g_data) != 'E')
	{
		g_data.ply.x = x;
		g_data.ply.y = y;
		g_data.ply.mv++;
		ft_putchar_fd('-', 1);
		ft_putchar_fd('>', 1);
		ft_putnbr_fd(g_data.ply.mv, 1);
		ft_putchar_fd('\n', 1);
	}
	plyup2(x, y);
}

void	ft_draw(void)
{
	plyupdate();
	if (haswallat(g_data.ply.x, g_data.ply.y, &g_data) == 'C')
		ft_lstupdate(g_data.ply.x / g_data.map.ts,
			g_data.ply.y / g_data.map.ts, 1, 1);
	g_data.img.ptr = mlx_new_image(g_data.mlx.ptr, g_data.win.x, g_data.win.y);
	if ((g_data.img.ptr) == NULL)
		return ;
	g_data.img.adr = mlx_get_data_addr(g_data.img.ptr,
			&g_data.img.fsh, &g_data.img.n, &g_data.img.m);
	drawmap();
	if (g_data.ply.ms == 1)
		drawwall(g_data.ply.x, g_data.ply.y, g_data.tex.pd);
	else if (g_data.ply.ms == 2)
		drawwall(g_data.ply.x, g_data.ply.y, g_data.tex.pa);
	else if (g_data.ply.ms == 3)
		drawwall(g_data.ply.x, g_data.ply.y, g_data.tex.ps);
	else if (g_data.ply.ms == 4)
		drawwall(g_data.ply.x, g_data.ply.y, g_data.tex.pw);
	mlx_put_image_to_window(g_data.mlx.ptr, g_data.win.ptr,
		g_data.img.ptr, 0, 0);
	free (g_data.img.ptr);
	free (g_data.img.adr);
}
