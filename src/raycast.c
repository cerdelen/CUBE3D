#include "../includes/cub.h"


static void		place_player_2d(t_data *data, int col)
{
	t_vec	start;
	t_vec	end;
	double	x = data->player.pos.x;
	double 	y = data->player.pos.y;

	for (size_t xx = 0; xx < 5; xx++)
	{
		start.x = x + xx;
		start.y = y;
		end.x = start.x;
		end.y = start.y + 5;
		draw_line_img(&data->img, start, end, col);
	}
	draw_line_img(&data->img, data->player.pos, vec_add(data->player.pos, data->player.dir), 0xD946FA);
}

static void		draw_cube(int x, int y, t_data *data, int col)
{
	t_vec	start;
	t_vec	end;

	for (size_t xx = 0; xx < 100; xx++)
	{
		start.x = x * TILE + xx;
		start.y = y * TILE;
		end.x = start.x;
		end.y = start.y + 100;
		draw_line_img(&data->img, start, end, col);
	}
	
}

static void		draw_walls(t_data *data)
{
	int	y = 0;
	int	x = 0;
	int max_x = 0;

	while(y < data->map_y)
	{
		max_x = ft_strlen(data->map[y]) + 1;
		x = 0;
		while (x < max_x)
		{
			if (data->map[y][x] == '1')
				draw_cube(x, y, data, 0x000066);
			else if (data->map[y][x] == '0')
				draw_cube(x, y, data, 0xBD7A98);
			x++;
		}
		y++;
	}
}

unsigned int	my_mlx_pixel_get(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}


static void	draw_wall_3d(t_data *data, int x, double dist)
{
	double	wall_height = WIN_HEIGTH * TILE / dist;
	double	wall_offset = (WIN_HEIGTH - wall_height) / 2;
	double	texture_x_d;
	int		texture_x;

	if(data->found_wall == NORTH_WALL || data->found_wall == SOUTH_WALL)
		texture_x_d = fmod(data->intersection.x, TILE);
	else
		texture_x_d = fmod(data->intersection.y, TILE);
	texture_x =  (int)texture_x_d;
	int		texture_y;
	double	y_perc;
	texture_x = (int)(data->walls[data->found_wall].width * texture_x_d / 100);
	for (int y = 0; y < WIN_HEIGTH; y++)
	{
		if (y < wall_offset)
			my_mlx_pixel_put(&data->img, x, y, data->ceiling_col);
		else if (y > wall_height + wall_offset)
			my_mlx_pixel_put(&data->img, x, y, data->floor_col);
		else
		{
			texture_y = y - wall_offset;
			y_perc = (double)texture_y / wall_height;
			texture_y = data->walls[data->found_wall].height * y_perc;
			my_mlx_pixel_put(&data->img, x, y, my_mlx_pixel_get(data->walls[data->found_wall].img, texture_x, texture_y));
		}
	}
}
static int		find_quadrant(t_vec vec)
{
	if (vec.x > 0 && vec.y > 0)
		return (1);
	if (vec.x < 0 && vec.y > 0)
		return (2);
	if (vec.x < 0 && vec.y < 0)
		return (3);
	if (vec.x > 0 && vec.y < 0)
		return (4);
	return (1);

}

static double	calc_angle(t_vec dir)
{
	// double	angle;
	// int		quadrant = find_quadrant(dir);

	// printf("test atan %f\n", pow(tan(dir.y / dir.x), -1));
	// if (quadrant == 1)
	// 	angle = fabs(atan(dir.y / dir.x));
	// if (quadrant == 2)
	// 	angle = 180 - fabs(atan(dir.y / dir.x));
	// if (quadrant == 3)
	// 	angle = 180 + fabs(atan(dir.y / dir.x));
	// if (quadrant == 4)
	// 	angle = 360 - fabs(atan(dir.y / dir.x));
	// return (angle);
	double angle = atan2(dir.y, dir.x);
	// double degree = angle * 180 / M_PI;
	// if (degree < 0)
	// {
	// 	degree += 360;
	// }
	return (angle);
}

static t_vec	normalize_vec(t_vec vec)
{
	t_vec	out;
	double length = sqrt(vec.x*vec.x + vec.y*vec.y);
	out.x = vec.x/length;
	out.y = vec.y/length;
	return (out);
}

static double	vec_dot(t_vec one, t_vec two)
{
	t_vec	tmp1 = normalize_vec(one);
	t_vec	tmp2 = normalize_vec(two);

	// printf("normalize vec tmp1.x %f tmp1.y %f \n", tmp1.x, tmp1.y);
	// printf("normalize vec tmp2.x %f tmp2.y %f \n", tmp2.x, tmp2.y);
	return ((tmp1.x * tmp2.x) + (tmp1.y * tmp2.y));
}

static void	ray_caster(t_data *data, int dimension)
{
	double		ray_angle_diff = ((double) FOV) / ((double)RAY_COUNT);
	double		dist;
	t_vec		tmp;
	double		ray_angle;
	double		player_angle;
	double		dot;
	double		gpt_angle;

	// player_angle = calc_angle(data->player.dir);
	// // printf("%f player ang\n", player_angle);

	// for (int i = 0; i < RAY_COUNT; i++)
	// {
	// 	tmp = dir_rotation(data->player.dir, (-1 * FOV/2) + (ray_angle_diff * i));
	// 	dist = single_ray(data, tmp, dimension);
	// 	ray_angle = calc_angle(tmp);
	// 	dot = vec_dot(tmp, data->player.dir);
	// 	gpt_angle = acos(dot);
	// 	printf("%f dist before\n", dist);
	// 	printf("%f dist before, idk = %f, dot = %f\n", dist, gpt_angle, dot);
	// 	dist = dist / cos(gpt_angle);
	// 	printf("%f dist after\n", dist);
	// 	if (dimension == 3)
	// 		draw_wall_3d(data, i, dist);
	// }

	double		radiant_diff;
	double		degree_diff;
	for (int i = 0; i < RAY_COUNT; i++)
	{
		tmp = dir_rotation(data->player.dir, (-1 * FOV/2) + (ray_angle_diff * i));
		dist = single_ray(data, tmp, dimension);

		radiant_diff = acos(vec_dot(data->player.dir, tmp));
		degree_diff = radiant_diff * 180 / M_PI;
		if (i < 10 || i > RAY_COUNT - 10)
		{
			printf("%f diff   %f,  cos = %f \n", radiant_diff, degree_diff, cos(radiant_diff));
		}
		// printf("%f ressssss\n", cos(45 * M_PI / 180));
		printf("orgi dis %f\n", dist);
		dist = dist / cos(radiant_diff);
		printf("new dis %f\n", dist);
		if (dimension == 3)
			draw_wall_3d(data, i, dist);
	}
	
}

static void		render_2d(t_data *data)
{
	draw_walls(data);
	place_player_2d(data, 0X00EBE1);
	ray_caster(data, 2);
}

static void		render_3d(t_data *data)
{
	ray_caster(data, 3);

}

static void		print_player(t_data *data)
{
	printf("player pos.x = %f  player pos.y = %f\nplayer dir.x = %f  player pos.y = %f\n", data->player.pos.x, data->player.pos.y, data->player.dir.x, data->player.dir.y);
}

void	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	// mlxim
	// print_player(data);
	// render_2d(data);
	render_3d(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}