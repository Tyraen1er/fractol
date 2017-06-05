#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include </opt/X11/include/X11/X.h>

int		scroll(int, int, int, void*);
int		my_key_fct(int, void*);
int		mouse_event(int, int, void*);
int		julia(double, double, double*);
int		mandelbrot(double, double);
int		perso(double, double);
int		ft_colorpoint(int);
void	dis_screen(int, void**, double*, double*);
void	init(int, double*, void**);
int		my_key_fct(int, void*);
int		ft_display(int);

#endif
