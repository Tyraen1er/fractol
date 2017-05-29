#include "fractol.h"

void	mandelbrot(int x, int y)
{
	int	a;
	int	c;
	int	evol;

	a = 0;
	c = x + (i * y);
	evol = 0;
	while (++a < 100 && evol < 2)
	{
		evol = pow(evol, 2) + c;
		++i;
	}
	return (i);
}

ft_colorpoint()
{
	static int	fractal = 0;


}

int		ft_display(int fractol)
{
	void	**mlx[4];
	char	*strpic;
	int		bpp = 0;
	int		s_l = 0;
	int		endian = 0;

	(void)fractol;
	if (!(mlx[0] = mlx_init()) || !(mlx[1] = mlx_new_window(mlx[0], 1800, 1800, "Fractol 42")))
		exit(3);
	mlx[2] = mlx_new_image(mlx[0], 1800, 1800);
	strpic = mlx_get_data_addr(mlx[2], &(bpp), &(s_l), &(endian));
	mlx_loop(mlx[0]);
	return (0);
}

int		main(int ac, char**av)
{
	if (ac != 2)
	{
		ft_putstr("usage: ./fractol [Julia / Mandelbrot / Perso]\n");
		return (0);
	}
	else
	{
		if (!ft_strcmp(av[1], "Julia"))
			ft_display(1);
		else if (!ft_strcmp(av[1], "Mandelbrot"))
			ft_display(2);
		else if (!ft_strcmp(av[1], "Perso"))
			ft_display(3);
		else
			ft_putstr("Cette fractal n est pas enregistrée.\n");
	}
	return (0);
}
