#include "../includes/cub.h"

void	init(t_data *data)
{
	bzero(data, sizeof(t_data));
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGTH, "cub3D");
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGTH);
	printf("win width %i  win height  %i\n", WIN_WIDTH, WIN_HEIGTH);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length,
								&data->img.endian);
	data->walls[0].img = calloc(1, sizeof(t_img));
	data->walls[1].img = calloc(1, sizeof(t_img));
	data->walls[2].img = calloc(1, sizeof(t_img));
	data->walls[3].img = calloc(1, sizeof(t_img));
	data->map = calloc(1, sizeof(char *));
}