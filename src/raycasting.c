#include "../includes/cub.h"

int			map_width_for_y(t_data *data, int y)
{
	if (y < data->map_y)
	{
		if (data->map[y] != NULL)
			return (ft_strlen(data->map[y]));
	}
	return (-1);
}

bool		its_a_wall(t_data *data, t_vec pos)
{
	int	x = pos.x / 100;
	int	y = pos.y / 100;
	if(x < 0 || y < 0 || y > data->map_y || x > map_width_for_y(data, y))
	{
		write(2, "error in its a wall\n", 21);
		exit(1);
	}
	if (data->map[y][x] == '1')
		return (true);
	return (false);
}


static int			end_ray(t_data *data, t_vec pos)
{
	if (pos.x < 0 || pos.y < 0 || 
			pos.y > (data->map_y * TILE) || 
			pos.x > (double) map_width_for_y(data, (pos.y / 100)) * TILE)
	{
		// printf("returning here x %f y %f data.map+y %f data.map.x %f \n", pos.x, pos.y, (double)(data->map_y * TILE) ,(double) map_width_for_y(data, (pos.y / 100)) * TILE);
		return (2);
	}
	return(its_a_wall(data, pos));
}

static double	pyth_theorem(t_vec vect)
{
	return(sqrt((vect.x * vect.x) + (vect.y * vect.y)));
}

void		print_vec(t_vec vec, char *mes)
{
	printf("The vector %s has x %f and y %f\n", mes, vec.x, vec.y);
}

static double		horz_raycast(t_data *data, t_vec dir, int dimension)
{
	double		x_strich;
	double		y_strich;
	double		x;
	double		y;
	double		ratio;
	int			check;
	t_vec		first_cub;

	if (dir.y == 0)
		return (VERY_BIG_NUMBER);
	if (dir.y < 0)
		y_strich = fmod(data->player.pos.y, TILE);
	else
		y_strich = TILE - fmod(data->player.pos.y, TILE);
	y = fabs(dir.y);
	x = dir.x;
	ratio = y / y_strich;
	x_strich = x / ratio;
	if (dir.y < 0)
	{
		y_strich *= (-1);
		y_strich -= 0.01;
	}
	first_cub.x = data->player.pos.x + x_strich;
	first_cub.y = data->player.pos.y + y_strich;
	check = end_ray(data, first_cub);
	// print_vec(first_cub, "first_cub");
	// printf("after first end\n");
	if (dir.y < 0)
		y_strich += 0.01;
	if (check == 0)
	{
		double	x_str_str;
		t_vec	next_cub;

		ratio = y / TILE;
		x_str_str = x / ratio;

		if(dir.y < 0)
			next_cub.y = - TILE - 0.01;
		else
			next_cub.y = TILE;
		next_cub.x = x_str_str;
		while (check == 0)
		{
			// print_vec(first_cub, "first_cub in loop");
			first_cub = vec_add(first_cub, next_cub);
			// print_vec(first_cub, "first_cub in loop");
			check = end_ray(data, first_cub);
		}
		// printf("hello\n");
	}
	double		distance;
	if (check == 2)
		return	(VERY_BIG_NUMBER);
	else
	{
		data->intersection_horz = first_cub;
		first_cub = vec_sub(data->player.pos, first_cub); 
		return (pyth_theorem(first_cub));
	}
}

static double		vert_raycast(t_data *data, t_vec dir, int dimension)
{
	double		x_strich;
	double		y_strich;
	double		x;
	double		y;
	double		ratio;
	int			check;
	t_vec		first_cub;

	if (dir.x == 0)
		return (VERY_BIG_NUMBER);
	if (dir.x > 0)
		x_strich = TILE - fmod(data->player.pos.x, TILE);
	else
		x_strich = fmod(data->player.pos.x, TILE);
	x = fabs(dir.x);
	y = dir.y;
	ratio = x / x_strich;
	y_strich = y / ratio;
	if (dir.x < 0)
	{
		x_strich *= (-1);
		x_strich -= 0.01;
	}
	first_cub.x = data->player.pos.x + x_strich;
	first_cub.y = data->player.pos.y + y_strich;
	check = end_ray(data, first_cub);
	// print_vec(first_cub, "first_cub");
	// printf("after first end\n");
	if (dir.x < 0)
		y_strich += 0.01;
	if (check == 0)
	{
		double	y_str_str;
		t_vec	next_cub;

		ratio = x / TILE;
		y_str_str = y / ratio;

		if(dir.x < 0)
			next_cub.x = - TILE - 0.01;
		else
			next_cub.x = TILE;
		next_cub.y = y_str_str;
		while (check == 0)
		{
			// print_vec(first_cub, "first_cub in loop");
			first_cub = vec_add(first_cub, next_cub);
			// print_vec(first_cub, "first_cub in loop");
			check = end_ray(data, first_cub);
		}
		// printf("hello\n");
	}
	double		distance;
	if (check == 2)
		return	(VERY_BIG_NUMBER);
	else
	{
		data->intersection_vert = first_cub;
		first_cub = vec_sub(data->player.pos, first_cub); 
		return (pyth_theorem(first_cub));
	}
}

double		single_ray(t_data *data, t_vec dir, int dimension)
{
	double		horz = horz_raycast(data, dir, dimension);
	double		vert = vert_raycast(data, dir, dimension);

	if (horz < vert)
	{
		if (dir.y < 0)
			data->found_wall = NORTH_WALL;
		else
			data->found_wall = SOUTH_WALL;
		if (dimension == 2)
			draw_line_img(&data->img, data->player.pos, data->intersection_horz, 0xFFE036);
		data->intersection = data->intersection_horz;
		return (horz);
	}
	else
	{
		if (dir.x < 0)
			data->found_wall = WEST_WALL;
		else
			data->found_wall = EAST_WALL;
		if (dimension == 2)
			draw_line_img(&data->img, data->player.pos, data->intersection_vert, 0x26E809);
		data->intersection = data->intersection_vert;
		return (vert);
	}
}