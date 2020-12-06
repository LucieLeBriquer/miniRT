#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int        put_sq(int x_start, int y_start, int width, int color, void **mlx_ptr, void **win_ptr)
{
	int i;
	int j;

	i = x_start;
	j = y_start;
	while (i < x_start + width)
	{
		j = y_start;
		while (j < y_start + width)
		{
			mlx_pixel_put(*mlx_ptr, *win_ptr, i, j, color);
			j++;
		}
		i++;
	}
	return (0);
}

typedef struct s_rand_sq
{
	int x;
	int y;
	int width;
	int color;
}                t_rand_sq;

t_rand_sq            rand_sq(unsigned int i, int x)
{
	t_rand_sq sq;
	int max;

	sq.x = rand_r(&i) % x;
	sq.y = rand_r(&i) % x;
	if (sq.y > sq.x)
		max = sq.y;
	else
		max = sq.x;
	sq.width = rand_r(&i) % (x - max);
	sq.color = rand_r(&i) % (UINT_MAX);
	return (sq);
}


int main(void)
{

	void    *mlx_ptr;
	void    *mlx_win;
	char *color = "abdc";
	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 600, 600, "randomSquares.");
	int i;
	i = 8800;
	while (i < 9000)
	{
		t_rand_sq sq = rand_sq(i, 600);
		put_sq(sq.x, sq.y, sq.width, sq.color, &mlx_ptr, &mlx_win);
		i++;
	}
	mlx_loop(mlx_ptr);
}
