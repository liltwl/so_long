#include  "solong.h"


t_all  s;
/***********************tools******************/

void	my_mlx_pixel_put(int x, int y, int color, t_all *s)
{
	char	*dst;

	if (x < 0 || x > s.win.x || y < 0 || y > s.win.y)
		return ;
	dst = s.img.adr + (y * s.img.n + x * (s.img.fsh / 8));
	*(unsigned int*)dst = color;
	//mlx_pixel_put(s.mlx.ptr, s.win.ptr, x, y, color);
}

int		ft_namecheck(char *arg, char *ext)
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

int		ft_strcheck(char *arg, char *str)
{
	int	i;

	i = 0;
	while (arg[i] == str[i])
	{
		if (arg[i] == '\0' && str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void drawrect(int x0, int y0,int p, t_all *s)
{
    int x, y;

    x = x0;
    y = y0 - 1;
    while (x <= x0 + 64)
    {
        //drawline(x, y0, x,  y1, p);
        y = y0 - 1;
        while (++y <= y0 + 64)
            my_mlx_pixel_put(x, y, p, s);
        x++;
    }
}

char	 haswallat(int x, int y,t_all *s)
{
    int xX, xY;
    if (x < 0 || x >= s.map.x || y < 0 || y >= s.map.y)
        return 1;
    xX = floor(x / 64);
    xY = floor(y / 64);
    return (p[xY][xX]);
}

int		ft_close(t_all *s, int win)
{
	int			i;

	i = 0;
	while (i < s.map.y && &s.map.tab[i])
		free(s.map.tab[i++]);
	free(s.map.tab);
	if (win == 1)
		mlx_destroy_window(s.mlx.ptr, s.win.ptr);
	free(s.mlx.ptr);
	exit(0);
	return (1);
}
/***********************parse******************/

int		ft_slablen(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1')
			count++;
		else if (line[i] == 'C' || line[i] == 'E' || line[i] == 'P')
			count++;
		i++;
	}
	return (count);
}

char	*ft_slab(t_all *s, char *line, int i, int x)
{
	char	*slab;
	int		j;

	if (!(slab = malloc(sizeof(char) * x + 1)))
		return (NULL);
	j = 0;
	while (j < x)
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'C'
			|| line[i] == 'E' || line[i] == 'P')
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

int		ft_line(t_all *s, char *line)
{
	char	**tmp;
	int		j;

	if (!(tmp = malloc(sizeof(char *) * (s.map.y + 2))))
		return (-11);
	j = -1;
	if (s.map.x == 0)
		s.map.x = ft_slablen(line);
	if (s.map.x != ft_slablen(line) && s.map.x != 0)
		return (-10);
	while (++j < s.map.y)
		tmp[j] = s.map.tab[j];
	if ((tmp[s.map.y] = ft_slab(s, line, 0, s.map.x)) == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[s.map.y + 1] = NULL;
	if (s.map.y > 0)
		free(s.map.tab);
	s.map.tab = tmp;
	s.map.y++;
	return (1);
}

void	ft_pos(t_all *s)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	s.map.ts = 50;
	while (++i < s.map.y && (j = -1))
		while (++j < s.map.x)
		{
			c = s.map.tab[i][j];
			if (c == 'P')
			{
				s.ply.x = j * s.map.ts;
				s.ply.y = i * s.map.ts;
			}
		}
}

int		config(t_all *s, char *cub)
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
	if (ret == -1 || ret == -3)
		return (0);
	ft_pos(s);
	s.win.x = s.map.x * s.map.ts;
	s.win.y = s.map.y * s.map.ts;
	fd = -1;
	return (0);
}
   /*********************************************/
void	plyup(t_all *s)
{
	int		movesteph;
	int		movestepv;
	int		x;
	int		y;

	movestepv = s.ply.vm * s.map.ts;
	movesteph = s.ply.hm * s.map.ts;
	x = s.ply.x + movestepv;
	y = s.ply.y + movesteph;
	if (haswallat(x, y, s) == '1')
	{
		s.ply.x = x;
		s.ply.y = y;
	}
}

void drawmap(t_all *s)
{
	int i;
	int j;

	i = -1;
	while (++i < s.map.x && (j = -1))
	{
		while (++j < s.map.y)
		{
			//printf("*******************%d ,%d  ,%d***********************\n",i,j,haswallat(i,j));
			if (p[i][j] == '1')
				drawrect(i * s.map.ts * MSF, j* s.map.ts* MSF, WHITE, s);
			else if (p[i][j] == 'C')
				drawrect(i * s.map.ts * MSF, j* s.map.ts* MSF, GREEN, s);
			else if (p[i][j] == 'E')
				drawrect(i * s.map.ts * MSF, j* s.map.ts* MSF, YELLOW, s);
			else
				drawrect(i * s.map.ts * MSF, j* s.map.ts* MSF, BLACK, s);
			
		}
	}
	//drawline(0,s.map.ts* s.map.x * MSF,s.map.ts* s.map.y * MSF,s.map.ts* s.map.x * MSF,BLUE);
}

void	ft_draw(t_all *s)
{
	plyup(s);
	if ((s.img.ptr = mlx_new_image(s.mlx.ptr,
		s.win.x, s.win.y)) == NULL)
		return ;
	s.img.adr = mlx_get_data_addr(s.img.ptr,
		&s.img.fsh, &s.img.n, &s.img.m);
	//drawmap(s);
	my_mlx_pixel_put(s.ply.x, s.ply.y* s.map.ts, RED, s);
	drawrect(s.ply.x , s.ply.y* s.map.ts, RED, s);
	mlx_put_image_to_window(s.mlx.ptr, s.win.ptr, s.img.ptr, 0, 0);
	free(s.img.ptr);
	free(s.img.adr);
}

/*******************************/


int		ft_press(int key, void *param)
{
	if (key == ESC)
		ft_close(param, 1);
	if (key == W)
		((t_all*)param).ply.vm = -1;
	if (key == S)
		((t_all*)param).ply.vm = 1;
	if (key == D)
		((t_all*)param).ply.hm = -1;
	else if (key == A)
		((t_all*)param).ply.hm = 1;
	ft_draw(((t_all*)param));
	((t_all*)param).ply.hm = 0;
	((t_all*)param).ply.vm = 0;
	return (0);
}


int		ft_dynamic(t_all *s)
{
	mlx_hook(s.win.ptr, 17, 1L << 2, ft_close, &s);
	mlx_hook(s.win.ptr, 2, 0, ft_press, &s);
	ft_draw(s);  //&s
	return (0);
}

int	ft_init(t_all *s, char *cub)
{
	s.mlx.ptr = NULL;
	s.img.ptr = NULL;
	s.img.adr = NULL;
	s.win.x = 0;
	s.win.y = 0;
	s.img.fsh = 0;
	s.map.ts = 64;
	s.map.tab = NULL;
	s.map.x = 0;
	s.map.y = 0;
	s.ply.x = 0;
	s.ply.y = 0;
	s.ply.mv = 0;
	s.mlx.ptr = mlx_init();
	if (config(s, cub) == -1)
		return (ft_close(s, 0));
	if ((s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x,
		s.win.y, "solong")) == NULL)
		return (ft_close(s, 0));
	//mlx_loop_hook(s.mlx.ptr, ft_dynamic, s);
	mlx_hook(s.win.ptr, 2, 0, ft_press, &s);
	mlx_loop(s.mlx.ptr);
	return 1;
}

int main(int ac, char **av)
{
	t_all s;

	if (ac == 2 && ft_namecheck(av[1], "ber"))
		ft_init(&s, av[1]);
	else
		write(2, "Error : Invalid arguments\n", 26);

}