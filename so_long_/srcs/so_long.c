/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:39:32 by otaouil           #+#    #+#             */
/*   Updated: 2021/09/21 12:39:35 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_all	g_data;

int	config(t_all *s, char *cub)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ft_line(s, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	g_data.win.x = g_data.map.x * g_data.map.ts;
	g_data.win.y = g_data.map.y * g_data.map.ts;
	ft_pos(s);
	ft_text(s);
	ft_lst(s);
	if (ret == -1 || ret == -3)
		return (-1);
	fd = -1;
	return (ft_parcheck(s));
}

void	init2(void)
{
	g_data.exit = NULL;
	g_data.mlx.ptr = mlx_init();
	g_data.ply.ms = 1;
	g_data.ply.mv = 0;
	g_data.err.c = 0;
	g_data.err.e = 0;
}

void	init(void)
{
	g_data.mlx.ptr = NULL;
	g_data.img.ptr = NULL;
	g_data.img.adr = NULL;
	g_data.win.x = 0;
	g_data.win.y = 0;
	g_data.img.fsh = 0;
	g_data.err.n = 0;
	g_data.err.m = 0;
	g_data.err.p = 0;
	g_data.map.ts = 64;
	g_data.map.tab = NULL;
	g_data.tex.h = NULL;
	g_data.tex.pw = NULL;
	g_data.tex.pd = NULL;
	g_data.tex.ps = NULL;
	g_data.tex.pa = NULL;
	g_data.tex.e = NULL;
	g_data.tex.w = NULL;
	g_data.tex.c = NULL;
	g_data.weed = NULL;
	g_data.map.x = 0;
	g_data.map.y = 0;
	init2();
}

int	main(int agc, char **agv)
{
	init();
	if (agc != 2)
		ft_strerror(-9);
	if (config(&g_data, agv[1]) < 0)
		ft_strerror(-12);
	g_data.win.ptr = mlx_new_window(g_data.mlx.ptr, g_data.win.x,
			g_data.win.y, "so_long");
	ft_draw();
	mlx_hook(g_data.win.ptr, 17, 1L << 2, ft_close, &g_data);
	mlx_hook(g_data.win.ptr, 2, 0, ft_press, &g_data);
	mlx_loop(g_data.mlx.ptr);
}
