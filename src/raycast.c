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

static unsigned int	my_mlx_pixel_get(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}


static void	draw_wall_3d(t_data *data, int x, double dist)
{
	t_vec	start;
	t_vec	end;
	double	wall_height = WIN_HEIGTH * TILE / dist;
	double	wall_offset = (WIN_HEIGTH - wall_height) / 2;
	double	texture_x_d;
	int		texture_x;

	printf("found wall %i", data->found_wall);
	print_vec(data->intersection, "intersection");
	if(data->found_wall == NORTH_WALL || data->found_wall == SOUTH_WALL)
		texture_x_d = fmod(data->intersection.y, TILE);
	else
		texture_x_d = fmod(data->intersection.x, TILE);
	texture_x =  (int)texture_x_d;
	int		texture_y;
	double	y_perc;


	start.x = x;
	end.x = x;
	start.y = wall_offset;
	end.y = wall_offset + wall_height;
	// print_vec(start, "start in 3d");
	// print_vec(start, "end in 3d");
	printf("%i x\n", texture_x);
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


			// printf("%f y perc", y_perc);
			
			texture_y = data->walls[EAST_WALL].height * y_perc;

			// printf(" and %i y text and %i x text", texture_y, texture_x);
			// printf(" results in colour %x\n", my_mlx_pixel_get(data->walls[EAST_WALL].img, texture_x, texture_y));
			// printf("%f y - walloff\n", (y - wall_offset));
			// printf("%f y percentage \n", ((y - wall_offset) / data->walls[EAST_WALL].height * 100));
			// texture_y = (int)(fmod(((y - wall_offset) / data->walls[EAST_WALL].height * 100), 100));

			
			// printf("%i text y\n", texture_y);
			// my_mlx_pixel_put(&data->img, x, y, 0x26E809);
			my_mlx_pixel_put(&data->img, x, y, my_mlx_pixel_get(data->walls[EAST_WALL].img, texture_x, texture_y));
		}
		y++;
	}
	
	// draw_line_img(&data->img, start, end, 0x26E809);
}

static void	ray_caster(t_data *data, int dimension)
{
	double		ray_angle = ((double) FOV) / ((double)RAY_COUNT);
	double		dist;

	for (int i = 0; i < RAY_COUNT; i++)
	{
		dist = single_ray(data, dir_rotation(data->player.dir, (-1 * FOV/2) + (ray_angle * i)), dimension);
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