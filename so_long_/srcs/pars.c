/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:37:14 by otaouil           #+#    #+#             */
/*   Updated: 2021/09/21 12:46:14 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

extern struct g_all	g_data;

void	ft_pos(t_all *s)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	s->map.ts = 64;
	while (++i < s->map.y)
	{
		j = -1;
		while (++j < s->map.x)
		{
			c = s->map.tab[i][j];
			if (c == 'P')
			{
				s->ply.y = (double)(i * s->map.ts);
				s->ply.x = (double)(j * s->map.ts);
				s->err.p++;
			}
		}
	}
}

char	*ft_slab(char *line, int i, int x)
{
	char	*slab;
	int		j;

	slab = malloc(sizeof(char) * x + 1);
	if (!(slab))
		return (NULL);
	j = 0;
	while (j < x)
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'P'
			|| line[i] == 'E' || line[i] == 'C')
			slab[j++] = line[i];
		else
		{
			free(slab);
			return (NULL);
		}
		(i)++;
	}
	slab[j] = '\0';
	return (slab);
}

int	ft_map2(t_all *s, char *line, char **tmp)
{
	tmp[s->map.y] = ft_slab(line, 0, s->map.x);
	if (tmp[s->map.y] == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[s->map.y + 1] = NULL;
	if (s->map.y > 0)
		free(s->map.tab);
	s->map.tab = tmp;
	s->map.y++;
	return (1);
}

int	ft_map(t_all *s, char *line)
{
	char	**tmp;
	int		j;

	s->err.m = 1;
	tmp = malloc(sizeof(char *) * (s->map.y + 2));
	if (!(tmp))
		return (-11);
	j = -1;
	if (s->map.x != ft_strlen(line) && s->map.x == 0)
		s->map.x = ft_strlen(line);
	else if (s->map.x != ft_strlen(line))
		return (-2);
	while (++j < s->map.y)
	{
		tmp[j] = ft_slab(s->map.tab[j], 0, s->map.x);
		if (tmp[j] == NULL)
			return (-12);
		free(s->map.tab[j]);
	}
	return (ft_map2(s, line, tmp));
}

int	ft_line(t_all *s, char *l)
{
	int		i;

	i = 0;
	if (s->err.m != 1)
		ft_spaceskip(l, &i);
	s->err.m = ft_map(s, l);
	if (s->err.m < 0)
		return (ft_strerror(-12));
	return (0);
}
