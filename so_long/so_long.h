
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

typedef struct	s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct	s_win
{
	void			*ptr;
	int				x;
	int				y;
}				t_win;

typedef struct	s_err
{
	int				n;
	int				m;
	int				l;
	int				p;
}				t_err;

typedef struct	s_img
{
	void			*ptr;
	char			*adr;
	int				n;
	int				fsh;
	int				m;
}				t_img;

typedef struct	s_map
{
	char			**tab;
	int				x;
	int				y;
	int				ts;
	int				spr;
}				t_map;

typedef struct	s_ply
{
	double			x;
	double			y;
	int				mv;
	int				mr;
	int				mup;
}				t_ply;

typedef struct	s_weeed
{
	double			x;
	double			y;
}				t_weed;

typedef struct	s_exit
{
	double			x;
	double			y;
}				t_exit;

typedef struct	s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*h;
	unsigned int	*w;
	unsigned int	*i;
	unsigned int	c;
	unsigned int	f;
}				t_tex;

typedef struct	s_all
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

#endif
