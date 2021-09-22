/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:32:37 by otaouil           #+#    #+#             */
/*   Updated: 2021/09/21 14:42:43 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

extern struct g_all	g_data;

void	plyup2(int x, int y)
{
	if ((ft_cisv() == 1 && haswallat(x, y, &g_data) == 'E')
		|| g_data.ply.ms == 0)
	{
		if (g_data.ply.ms != 0)
			write(1, "You Aree mkyf\n", 15);
		g_data.ply.ms = 0;
	}
	else if (g_data.ply.mr == 1)
		g_data.ply.ms = 1;
	else if (g_data.ply.mr == -1)
		g_data.ply.ms = 2;
	else if (g_data.ply.mup == 1)
		g_data.ply.ms = 3;
	else if (g_data.ply.mup == -1)
		g_data.ply.ms = 4;
}

int	ft_xppm(unsigned int **adr, char *file)
{
	int		fd;
	void	*img;
	int		tab[6];

	if (ft_namecheck(file, "xpm") == 0)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(g_data.mlx.ptr, file, &tab[0], &tab[1]);
	if (img == NULL || tab[0] != 64 || tab[1] != 64)
		return (-1);
	*adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	free(img);
	return (0);
}

int	ft_texture(char *line, unsigned int **adr, int i)
{
	char		*file;
	int			j;

	ft_spaceskip(line, &i);
	j = i;
	while (line[i] != ' ' && line[i] != '\0')
		(i)++;
	file = malloc(sizeof(char) * (i - j + 1));
	if (!(file))
		return (-8);
	i = j;
	j = 0;
	while (line[i] != ' ' && line[i] != '\0')
		file[j++] = line[(i)++];
	file[j] = '\0';
	if (*adr != NULL)
		return (-7);
	j = ft_xppm(adr, file);
	free(file);
	if (j == -1)
		return (-9);
	return (0);
}

void	ft_text(t_all *s)
{
	s->err.n += ft_texture("textr/grass.xpm", &g_data.tex.h, 0);
	s->err.n += ft_texture("textr/marijuana.xpm", &g_data.tex.c, 0);
	s->err.n += ft_texture("textr/zombieW.xpm", &g_data.tex.pw, 0);
	s->err.n += ft_texture("textr/zombieA.xpm", &g_data.tex.pa, 0);
	s->err.n += ft_texture("textr/zombieS.xpm", &g_data.tex.ps, 0);
	s->err.n += ft_texture("textr/zombieD.xpm", &g_data.tex.pd, 0);
	s->err.n += ft_texture("textr/bong2.xpm", &g_data.tex.e, 0);
	s->err.n += ft_texture("textr/water.xpm", &g_data.tex.w, 0);
}

int	ft_lstexitupdate(int i, int j, int x1, int z)
{
	t_exit	*x;

	x = g_data.exit;
	x1 = -1;
	while (x[++x1].x)
	{
		if (x[x1].x == i && x[x1].y == j)
		{
			if (z == 1)
				x[x1].v = 0;
			return (x[x1].v);
		}
	}
	return (0);
}
