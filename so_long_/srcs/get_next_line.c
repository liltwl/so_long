/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:54:43 by otaouil           #+#    #+#             */
/*   Updated: 2021/09/21 12:22:54 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *str, char p)
{
	char	*tmp;
	int		i;

	i = ft_strlen(str);
	tmp = malloc(i + 2);
	i = -1;
	while (str && str[++i])
		tmp[i] = str[i];
	tmp[i++] = p;
	tmp[i] = '\0';
	if (str)
		free (str);
	return (tmp);
}

int	get_next_line(int fd, char **line)
{
	int		i;
	char	buff[1];
	char	*str;

	str = malloc(1);
	str[0] = '\0';
	i = read(fd, buff, 1);
	while (i && buff[0] != '\n')
	{
		str = ft_strjoin(str, buff[0]);
		i = read(fd, buff, 1);
	}
	*line = str;
	if (buff[0] == '\n')
		i = 1;
	else
		i = 0;
	return (i);
}
