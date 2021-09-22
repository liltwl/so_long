/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:23:34 by otaouil           #+#    #+#             */
/*   Updated: 2021/09/21 12:29:17 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

extern struct g_all	g_data;

int	ft_strerror(int err)
{
	if (err == -7)
		write(2, "Error : Texture path specified twice\n", 37);
	else if (err == -9)
		write(2, "Error : Invalid arguments\n", 27);
	else if (err == -12)
		write(2, "Error : Invalid map\n", 20);
	else if (err == -15)
		write(2, "Error : Missing texture\n", 24);
	else if (err == -17)
		write(2, "Error : No starting position\n", 29);
	else if (err == -4)
		write(2, "Error : No collectibles\n", 25);
	else if (err == -3)
		write(2, "Error : No exit\n", 17);
	else if (err == -18)
		write(2, "Error : Multiple starting positions\n", 36);
	else if (err == -19)
		write(2, "Error : Map isn't surrounded by walls\n", 39);
	exit(0);
	return (0);
}

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putnbr_fd(unsigned int n, int fd)
{
	int	i;

	i = 0;
	if (n < 10)
		i += ft_putchar_fd(n + '0', fd);
	else if (n >= 10)
	{
		i += ft_putnbr_fd(n / 10, fd);
		i += ft_putchar_fd(n % 10 + '0', fd);
	}
	return (i);
}

int	ft_close(t_all *s, int win)
{
	int	i;

	i = 0;
	while (i < s->map.y && &s->map.tab[i])
		free(s->map.tab[i++]);
	free(s->map.tab);
	if (g_data.weed != NULL)
		free(g_data.weed);
	if (g_data.exit != NULL)
		free(g_data.exit);
	free(s->tex.pd);
	free(s->tex.ps);
	free(s->tex.e);
	free(s->tex.c);
	free(s->tex.h);
	free(s->tex.w);
	free(s->tex.pw);
	free(s->tex.pa);
	if (win == 1)
		mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	free(s->mlx.ptr);
	exit(0);
	exit(0);
}

int	ft_spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
		|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}
