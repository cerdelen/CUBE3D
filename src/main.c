#include "../includes/cub.h"

void	cleanup(t_data *data)
{
	if (data->img.img != NULL)
		mlx_destroy_image(data->mlx, data->img.img);  // this segfaults if i press the red x
	if (data->mlx_win != NULL)
		mlx_destroy_window(data->mlx, data->mlx_win);
}

int		closing(int key, t_data* data)
{
	// if (key == ESC_KEY)								//patch fix because of segfault if i click red x
	cleanup(data);
	exit(0);
}

static bool	check_if_move_possible(t_data *data, t_vec res)
{
	if (res.x < 0 || res.y < 0 || res.y > data->map_y * 100 || res.x > ft_strlen(data->map[(int)(res.y / 100)]) * 100)
		return (false);
	if (data->map[(int)res.y / 100][(int)res.x / 100] == '1')
		return (false);
	return (true);
}

static void		move(t_data *data, int dir)
{
	t_vec	tmp;
	if (dir == MV_FWRD)
		tmp = vec_add(data->player.pos, data->player.dir);
	if (dir == MV_BACK)
		tmp = vec_sub(data->player.pos, data->player.dir);
	if (dir == MV_RIGHT)
		tmp = vec_sub(data->player.pos, dir_rotation(data->player.dir, -90));
	if (dir == MV_LEFT)
		tmp = vec_sub(data->player.pos, dir_rotation(data->player.dir, 90));
	if (!check_if_move_possible(data, tmp))
		return ;
	data->player.pos = tmp;
}

static void		change_dir(t_data *data, int dir)
{
	data->player.dir = dir_rotation(data->player.dir, ROTATION_ANGLE * dir);
}

static void	adjust_pos(t_data *data)
{
	if (fmod(data->player.pos.x, TILE) < 1)
		data->player.pos.x += 1;
	if (fmod(data->player.pos.x, TILE) > 99)
		data->player.pos.x -= 1;
	if (fmod(data->player.pos.y, TILE) < 1)
		data->player.pos.y += 1;
	if (fmod(data->player.pos.y, TILE) > 99)
		data->player.pos.y -= 1;
}

int		keypress(int key, t_data* data)
{
	// printf("keypress got: %i\n", key);
	if (key == W_KEY)
		move(data, MV_FWRD);
	if (key == S_KEY)
		move(data, MV_BACK);
	if (key == A_KEY)
		move(data, MV_LEFT);
	if (key == D_KEY)
		move(data, MV_RIGHT);
	if (key == LEFT_KEY)
		change_dir(data, -1);
	if (key == RIGHT_KEY)
		change_dir(data, 1);
	if (key == ESC_KEY)
		closing(key, data);
	adjust_pos(data);
	render(data);
	return (0);
}
unsigned int	my_mlx_pixel_get(t_img *data, int x, int y);

int main(int argc, char **argv)
{
	t_data	data;

	// printf("argc == %i\n", argc);
	init(&data);
	print_2d_array(data.map,1);

	parsing(argc, argv, &data);
	mlx_hook(data.mlx_win, ON_KEYDOWN, 1L<<0, keypress, &data);
	mlx_hook(data.mlx_win, ON_DESTROY, 0, closing, &data);
	render(&data);
	

	// printf("%f res\n", degree);
	// printf("%x lel\n", my_mlx_pixel_get(data.walls[EAST_WALL].img,0, 0));
	// printf("%x lel\n", my_mlx_pixel_get(data.walls[EAST_WALL].img,0, 1));
	// mlx_put_image_to_window(data.mlx, data.mlx_win, data.walls[SOUTH_WALL].img, 0, 0);
	mlx_loop(data.mlx);
}