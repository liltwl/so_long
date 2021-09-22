#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "minilibx_opengl/mlx.h"
# include "get_next_line.h"

# define NONE 0xFF000000
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

typedef struct s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct s_win
{
	void			*ptr;
	int				x;
	int				y;
}				t_win;

typedef struct s_err
{
	int				n;
	int				m;
	int				c;
	int				e;
	int				p;
}				t_err;

typedef struct s_img
{
	void			*ptr;
	char			*adr;
	int				n;
	int				fsh;
	int				m;
}				t_img;

typedef struct s_map
{
	char			**tab;
	int				x;
	int				y;
	int				ts;
	int				spr;
}				t_map;

typedef struct s_ply
{
	double			x;
	double			y;
	int				mv;
	int				mr;
	int				mup;
	int				ms;
}				t_ply;

typedef struct s_weed
{
	double			x;
	double			y;
	int				v;
}				t_weed;

typedef struct s_exit
{
	double			x;
	double			y;
	int				v;
}				t_exit;

typedef struct s_tex
{
	unsigned int	*e;
	unsigned int	*c;
	unsigned int	*h;
	unsigned int	*w;
	unsigned int	*pw;
	unsigned int	*pa;
	unsigned int	*ps;
	unsigned int	*pd;
	unsigned int	f;
}				t_tex;

typedef struct g_all
{
	t_mlx			mlx;
	t_win			win;
	t_map			map;
	t_err			err;
	t_ply			ply;
	t_tex			tex;
	t_weed			*weed;
	t_exit			*exit;
	t_img			img;
}				t_all;

int		ft_strerror(int err);
int		ft_putchar_fd(char c, int fd);
int		ft_putnbr_fd(unsigned int n, int fd);
int		ft_close(t_all *s, int win);
int		ft_spaceskip(char *line, int *i);
char	haswallat(int x, int y, t_all *s);
int		ft_namecheck(char *arg, char *ext);
int		ft_addtolst(char **p, t_weed *w, t_exit *x);
void	ft_lst(t_all *s);
int		ft_nlen(char n, char **p);
void	my_mlx_pixel_put(int x, int y, unsigned int color);
void	drawwall(int i, int j, unsigned int	*v);
void	drawmap(void);
void	plyupdate(void);
void	ft_draw(void);
void	plyup2(int x, int y);
int		ft_xppm(unsigned int **adr, char *file);
int		ft_texture(char *line, unsigned int **adr, int i);
void	ft_text(t_all *s);
void	ft_pos(t_all *s);
char	*ft_slab(char *line, int i, int x);
int		ft_map2(t_all *s, char *line, char **tmp);
int		ft_map(t_all *s, char *line);
int		ft_line(t_all *s, char *l);
int		ft_lstupdate(int i, int j, int x1, int z);
int		ft_cisv(void);
int		ft_press(int key, void *param);
int		ft_mapcheck(t_all *s);
int		ft_parcheck(t_all *s);
int		config(t_all *s, char *cub);
void	init2(void);
void	init(void);
int		ft_lstexitupdate(int i, int j, int x1, int z);
void	ft_addtowd(int i, int j, int *l, t_weed *w);
void	ft_addtoexit(int i, int j, int *cnt, t_exit *x);

#endif
