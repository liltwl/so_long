
#include "so_long.h"

t_all   data;

int		ft_spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

char	 haswallat(int x, int y,t_all *s)
{
    int xX, xY;
    if (x < 0 || x >= s->win.x || y < 0 || y >= s->win.y)
        return 0;
    xX = floor(x / 64);
    xY = floor(y / 64);
    return (s->map.tab[xY][xX]);
}

void	plyupdate(void)
{
	int		x;
	int		y;

	x = (data.ply.mr * data.map.ts) + data.ply.x;
	y = (data.ply.mup * data.map.ts) + data.ply.y;
	if (haswallat(x, y, &data) != '1')
	{
		data.ply.x = x;
		data.ply.y = y;
	}
}

void	my_mlx_pixel_put(int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > data.win.x || y < 0 || y > data.win.y)
		return ;
	dst = data.img.adr + (y * data.img.n + x * (data.img.fsh / 8));
	*(unsigned int*)dst = color;
}

void	drawline(int x0, int y0, int y1, int i)
{
	int		dx;
	int		dy;
	int		steps;
	int		j;

	dx = x0 - x0;
	dy = y1 - y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	j = i;
	dx = dx / (float)steps;
	dy = dy / (float)steps;
	while (++j <= steps)
	{
		//my_mlx_pixel_put(x0, y0, i);
		x0 += dx;
		y0 += dy;
	}
}

void drawrect(int x0, int y0,int p)
{
    int x, y;

    x = x0;
    y = y0 - 1;
    while (x <= x0 + 64 && x < data.win.x)
    {
        //drawline(x, y0, x,  y1, p);
        y = y0 - 1;
        while (++y <= y0 + 64 && y < data.win.y)
            my_mlx_pixel_put(x, y, p);
        x++;
    }
}

void drawmap(void)
{
	int i;
	int j;

	i = -1;
	while (++i < data.map.y && (j = -1))
	{
		while (++j < data.map.x)
		{
			printf("*******************%d ,%d  ,%c , %d***********************\n",i,j,haswallat(i* data.map.ts,j* data.map.ts, &data),data.map.y);
			if (data.map.tab[i][j] == '1')
				drawrect(j * data.map.ts, i* data.map.ts, WHITE);
			else if (data.map.tab[i][j] == 'C')
				drawrect(j * data.map.ts , i* data.map.ts, GREEN);
			else if (data.map.tab[i][j] == 'E')
				drawrect(j * data.map.ts , i* data.map.ts, YELLOW);
			else
				drawrect(j * data.map.ts , i* data.map.ts, BLACK);
			
		}
	}
	//drawline(0,s.map.ts* s.map.x * MSF,s.map.ts* s.map.y * MSF,s.map.ts* s.map.x * MSF,BLUE);
}

void	ft_draw(void)
{
	plyupdate();
	if ((data.img.ptr = mlx_new_image(data.mlx.ptr,
		data.win.x, data.win.y)) == NULL)
		return ;
	data.img.adr = mlx_get_data_addr(data.img.ptr,
		&data.img.fsh, &data.img.n, &data.img.m);
	drawmap();
	//printf("%f\n",data.ply.x);
	drawrect(data.ply.x , data.ply.y, RED);
	mlx_put_image_to_window(data.mlx.ptr, data.win.ptr, data.img.ptr, 0, 0);
	free(data.img.ptr);
	free(data.img.adr);
}

int		ft_press(int key, void *param)
{
	/*if (key == ESC)
		ft_close(param, 1);*/
	if (key == W)
		((t_all*)param)->ply.mup = -1;
	else if (key == S)
		((t_all*)param)->ply.mup = 1;
	else if (key == D)
		((t_all*)param)->ply.mr = 1;
	else if (key == A)
		((t_all*)param)->ply.mr = -1;
	ft_draw();
	((t_all*)param)->ply.mr = 0;
	((t_all*)param)->ply.mup = 0;
	return (0);
}


int     ft_nlen(char n, char **p)
{
    int i;
    int j;
    int cnt;

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

int     ft_addtolst(char **p, t_weed *w, t_exit *x)
{
    int i;
    int j;
    int cnt;
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
            {
                w[l].x = j;
				printf("%f\n", w[l].x);
                w[l++].y = i;
                //w++;
            }
            else if (p[i][j] == 'E')
            {
                x[cnt].x = j;
                x[cnt++].y = i;
                //x++;
            }
        }
    }
    return (0);
}
void    ft_lst(t_all *s)
{
    int     exit;
    int     weed;

    weed = ft_nlen('C', s->map.tab);
    exit = ft_nlen('E', s->map.tab);
    if (s->weed == NULL)
        s->weed = malloc(sizeof(t_weed) * (weed + 1));
    if (s->exit == NULL)
        s->exit = malloc(sizeof(t_exit) * (exit + 2));
    ft_addtolst(s->map.tab, s->weed, s->exit);
}

void	ft_pos(t_all *s)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	s->map.ts = 64;
	while (++i < s->map.y && (j = -1))
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
char	*ft_slab(char *line, int i, int x)
{
	char	*slab;
	int		j;

	if (!(slab = malloc(sizeof(char) * x + 1)))
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

int		ft_map(t_all *s, char *line)
{
	char	**tmp;
	int		j;

	s->err.m = 1;
	if (!(tmp = malloc(sizeof(char *) * (s->map.y + 2))) || s->err.l == 1)
		return (-11);
	j = -1;
	if (s->map.x != ft_strlen(line) && s->map.x == 0)
		s->map.x = ft_strlen(line);
	while (++j < s->map.y)
	{
		tmp[j] = ft_slab(s->map.tab[j], 0, s->map.x);
		free(s->map.tab[j]);
	}
	if ((tmp[s->map.y] = ft_slab(line, 0, s->map.x)) == NULL)
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

int		ft_line(t_all *s, char *l)
{
	int		i;

	if (!(i = 0) && s->err.m != 1)
		ft_spaceskip(l, &i);
	s->err.n = ft_map(s, l);
	return (0);
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
	data.win.x = data.map.x * data.map.ts;
	data.win.y = data.map.y * data.map.ts;
	fd = -1;
	return (0); //return (ft_parcheck(s));
}

void    init()
{
    data.mlx.ptr = NULL;
	data.img.ptr = NULL;
	data.img.adr = NULL;
	data.win.x = 0;
	data.win.y = 0;
	data.img.fsh = 0;
	data.err.n = 0;
	data.err.m = 0;
	data.err.p = 0;
	data.map.ts = 64;
	data.map.tab = NULL;
	data.tex.n = NULL;
	data.tex.s = NULL;
	data.tex.e = NULL;
	data.tex.w = NULL;
	data.tex.i = NULL;
	data.weed = NULL;
    data.map.x = 0;
	data.map.y = 0;
    data.exit = NULL;
    data.mlx.ptr = mlx_init();
}



int     main(int agc, char **agv)
{
    int     i = -1;
    init();
    if (agc == 2)
        config(&data, agv[1]);
    ft_lst(&data);
	data.win.ptr = mlx_new_window(data.mlx.ptr, data.win.x,
		data.win.y, "so_long");
	//plyupdate();
    //printf("%f\n", data.weed[0].x);
	//ft_draw();
    while (data.map.tab[++i])
    {
        printf("%s\n", data.map.tab[i]);
    }
	//mlx_hook(data.win.ptr, 17, 1L << 2, ft_close, &data);
	mlx_hook(data.win.ptr, 2, 0, ft_press, &data);
	mlx_loop(data.mlx.ptr);
}