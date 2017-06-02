#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include </opt/X11/include/X11/X.h>

int		mandelbrot(double x, double y);
int		ft_colorpoint(int i);
void	dis_screen(int f, void **mlx, double *coord);
void	init(int fractal, int *z, void **mlx);
int		my_key_fct(int keycode, void *all);
int		ft_display(int fractol);

#endif
