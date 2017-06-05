#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include </opt/X11/include/X11/X.h>

# define ESCAPE 53
# define ENTER 36

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_quad
{
	t_point		tl;
	t_point		br;
}				t_quad;

int		scroll(int, int, int, void**);
int		mouse_event(int, int, void**);
int		my_key_fct(int, void**);
int		julia(t_point, t_point*);
int		mandelbrot(t_point, t_point*);
int		perso(t_point, t_point*);
int		ft_colorpoint(int);
void	dis_screen(int, void**, t_quad*, t_point*);
void	init(int, int*, void**);
int		ft_display(int);
t_point	ft_point_in_quad_to_ratio(t_quad, t_point);
t_point	ft_point_ratio_to_quad(t_point, t_quad);

#endif
