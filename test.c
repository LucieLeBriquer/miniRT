#include "mlx.h"
#include <unistd.h>
#define PURPLE 0x00A061D1
#define WHITE 0x00FFFFFF
#define BLACK 0x00000000
#define SIZE 150
#define SQ_X 300
#define SQ_Y 200
#define TOT_X 600
#define TOT_Y 400

void	fill_sqr(void *mlx, void *win, int x1, int x2, int y1, int y2, int color)
{
	int		y;

	while (x1 <= x2)
	{
		y = y1;
		while (y <= y2)
		{
			mlx_pixel_put(mlx, win, x1, y, color);
			y++;
		}
		x1++;
	}
	
}

int		deal_key(int key, void *param[2])
{
	char		c;
	static int	i;
	static int	j;
	int		purple = 0x00A061D1;
	int		white = 0x00FFFFFF;

	c = (unsigned char)key;
	if (c == 'z' || c == 'q' || c == 's' || c == 'd')
	{
		i += 5 * (c == 'q');
		i -= 5 * (c == 'd');
		j += 5 * (c == 'z');
		j -= 5 * (c == 's');
		//fill_sqr(param[0], param[1], SQ_X - i - 5, SQ_X + SIZE - i + 5, SQ_Y - j
		//- 5, SQ_Y + SIZE - j + 5, BLACK);
		fill_sqr(param[0], param[1], SQ_X - i, SQ_X + SIZE - i, SQ_Y - j, SQ_Y +
		SIZE - j, PURPLE);
	}
	return (0);
}

int		main()
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	void	*param[2];

	mlx = mlx_init();
	win = mlx_new_window(mlx, TOT_X, TOT_Y, "test");
	//fill_sqr(mlx, win, 0, TOT_X, 0, TOT_Y, WHITE);
	fill_sqr(mlx, win, SQ_X, SQ_X + SIZE, SQ_Y, SQ_Y + SIZE, PURPLE);
	fill_sqr(mlx, win, SQ_X + 12, SQ_X + SIZE - 12, SQ_Y + 12, SQ_Y + SIZE - 12,
	WHITE);
	param[0] = mlx;
	param[1] = win;
	mlx_hook(win, 2, (1L<<0), deal_key, param);
	mlx_loop(mlx);
	return (0);
}
