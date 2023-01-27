#include "../includes/cub.h"

static void		fatal(char *error, t_data *data)
{
	cleanup(data);
	write(2, error, strlen(error));
	exit(1);
}

static int		skip_whitespace(char *str)
{
	int	i = 0;
	while(str[i] == 9 || 
			str[i] == 10 || 
			str[i] == 11 || 
			str[i] == 12 || 
			str[i] == 13 || 
			str[i] == 32)
		i++;
	return (i);
}

static int		skip_nbrs(char *str, int skipping)
{
	int	i = skip_whitespace(str);

	while(skipping > 0)
	{
		while(ft_isdigit(str[i]))
			i++;
		if (str[i] == ',')
			i++;
		skipping--;
	}
	return (i);
}

static bool		init_texture(char *buf, t_wall_stats *texture, t_data *data)
{
	texture->img->img = mlx_xpm_file_to_image(data->mlx, buf + skip_whitespace(buf), &texture->width, &texture->height);
	if(texture->img == NULL)
		return (true);
	texture->img->addr = mlx_get_data_addr(texture->img->img, &(texture->img->bits_per_pixel),
				&(texture->img->line_length), &(texture->img->endian));
	return (false);
}


// void	init_texture(t_data *data, t_texture *texture, char *path)
// {
// 	printf("wot\n");
// 	texture->img->ptr = mlx_xpm_file_to_image(data->mlx, path, \
// 						&texture->width, &texture->height);
// 	texture->img->data = mlx_get_data_addr(texture->img->ptr, &texture->img->bpp, &texture->img->size_l, &texture->img->endian);
// 	if (!texture->img->ptr)
// 		errno(TEXTURE, path, data);
// }

static bool		invalid_value(int value)
{
	if (value < 0 || value > 255)
		return (true);
	return (false);
}

static bool		init_Ceiling_Floor(char *buf, int *colour, t_data *data)
{
	int	r = ft_atoi(buf + skip_nbrs(buf, 0));
	int	g = ft_atoi(buf + skip_nbrs(buf, 1));
	int	b = ft_atoi(buf + skip_nbrs(buf, 2));

	if (invalid_value(r) || invalid_value(g) || invalid_value(b))
		return (true);
	*colour = r * pow(256, 2) + g * pow(256, 1) + b;
	return (false);
}	

static bool		extract_images(int file_fd, t_data *data)
{
	int		imgs = 0;
	char	*buf;
	bool	fatal = false;

	while(1)
	{
		buf = get_next_line(file_fd);
		if (buf == NULL)
			return (false);
		if (buf[ft_strlen(buf) - 1] == '\n')
			buf[ft_strlen(buf) - 1] = 0;
		// printf("\"%s\"\n", buf);
		if (strlen(buf) == 0)
		{
			free(buf);
			continue ;
		}
		else if (ft_strncmp(buf, "NO ", 3) == 0)
			fatal = init_texture(buf + 3, &(data->walls[NORTH_WALL]), data);
		else if (ft_strncmp(buf, "SO ", 3) == 0)
			fatal = init_texture(buf + 3, &(data->walls[SOUTH_WALL]), data);
		else if (ft_strncmp(buf, "WE ", 3) == 0)
			fatal = init_texture(buf + 3, &(data->walls[WEST_WALL]), data);
		else if (ft_strncmp(buf, "EA ", 3) == 0)
			fatal = init_texture(buf + 3, &(data->walls[EAST_WALL]), data);
		else
		{
			free(buf);
			return (false);
		}
		free(buf);
		if (fatal)
			return (false);
		imgs++;
		if (imgs == 4)
			break ;
	}
	// printf("%p %p %p %p \n", data->walls[0].img, data->walls[1].img, data->walls[2].img, data->walls[3].img);
	// printf("%d img height east \n", data->walls[EAST_WALL].height);
	// printf("%d img height no \n", data->walls[NORTH_WALL].height);
	// printf("%d img height we \n", data->walls[WEST_WALL].height);
	// printf("%d img height so \n", data->walls[SOUTH_WALL].height);
	return (true);
}

static bool		Floor_Ceiling_Colour(int file_fd, t_data *data)
{
	int		colours = 0;
	char	*buf;
	bool	fatal = false;

	while (1)
	{
		buf = get_next_line(file_fd);
		if (buf == NULL)
			return (false);
		if (buf[ft_strlen(buf) - 1] == '\n')
			buf[ft_strlen(buf) - 1] = 0;
		if (strlen(buf) == 0)
		{
			free(buf);
			continue ;
		}
		else if (ft_strncmp(buf, "C ", 2))
			fatal = init_Ceiling_Floor(buf + 2, &data->ceiling_col, data);
		else if (ft_strncmp(buf, "F ", 2))
			fatal = init_Ceiling_Floor(buf + 2, &data->floor_col, data);
		else
		{
			free(buf);
			return (false);
		}
		free(buf);
		if (fatal)
			return (false);
		colours++;
		if (colours == 2)
			break ;
	}
	return (true);
}

static void		add_line_to_map(char *line, t_data *data)
{
	int		amt = 0;
	char	**new_map;
	int		i = 0;

	
	print_2d_array(data->map,1);
	while(data->map[amt] != NULL)
		amt++;
	printf("counting was fine amt == %i\n", amt);
	new_map = calloc(amt + 1, sizeof(char *));
	for (size_t x = 0; x < amt; x++)
	{
		printf("new[i] = %p\n", new_map[x]);
	}
	
	while(data->map[i] != NULL)
	{
		printf("XD %p\n", data->map[i]);
		new_map[i] = data->map[i];
		i++;
	}
	free(data->map);
	new_map[i] = line;
	data->map = new_map;
	printf("new = %p  map = %p  \n", new_map, data->map);
	printf("new[0] = %p\n", new_map[0]);
	printf("new[0] = %s\n", new_map[0]);

	print_2d_array(data->map, 1);
}

static bool		get_map(int file_fd, t_data *data)
{
	char	*buf;

	while (1)
	{
		printf("hello\n");
		buf = get_next_line(file_fd);
		printf("new line = %p\n", buf);
		if (buf == NULL)
			break ;
		if (buf[ft_strlen(buf) - 1] == '\n')
			buf[ft_strlen(buf) - 1] = 0;
		add_line_to_map(buf, data);
		// free(buf);
		// if (fatal)
		// 	return (false);
	}
	printf("done reading\n");
	print_2d_array(data->map, 1);
}

static bool		Correct_Map(int file_fd, t_data *data)
{
	// if(!get_map(file_fd, data))
	// 	return (false);
	data->map_y = 0;
	free(data->map);
	data->map = calloc(11, sizeof(char *));
	data->map[0] =	ft_strdup("11111111111");
	data->map[1] =	ft_strdup("10000000001");
	data->map[2] =	ft_strdup("10000000001");
	data->map[3] =	ft_strdup("10001100001");
	data->map[4] =	ft_strdup("100W0000001");
	data->map[5] =	ft_strdup("10000000001");
	data->map[6] =	ft_strdup("10000100011");
	data->map[7] =	ft_strdup("10000000001");
	data->map[8] =	ft_strdup("10000000001");
	data->map[9] =	ft_strdup("10000000001");
	data->map[10] =	ft_strdup("11111111111");
	while(data->map[data->map_y] != NULL)
		data->map_y++;

	// data->map_y--;
	// data->map
	return (true);
}
static void		init_player(t_data *data)
{
	int x = 0;
	int y = 0;
	// print_2d_array(data->map, 1);
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0' || data->map[y][x] == '1')
			{
				x++;
				continue ;
			}
			if (data->map[y][x] == 'N')
			{
				data->player.dir.x = 0;
				data->player.dir.y = (-1) * MOVE_DIST;
			}
			if (data->map[y][x] == 'E')
			{
				data->player.dir.x = MOVE_DIST;
				data->player.dir.y = 0;
			}
			if (data->map[y][x] == 'S')
			{
				data->player.dir.x = 0;
				data->player.dir.y = MOVE_DIST;
			}
			if (data->map[y][x] == 'W')
			{
				data->player.dir.x = (-1) * MOVE_DIST;
				data->player.dir.y = 0;
			}
			data->map[y][x] = '0';
			data->player.pos.x = x * TILE;
			data->player.pos.y = y * TILE;
			return ;
		}
		y++;
	}
	
}

void			parsing(int argc, char **argv, t_data *data)
{
	int		file_fd;

	// printf("argc == %i\n", argc);
	if(argc != 2)
		fatal("Wrong amount of arguments, please provide 1 and only 1 map\n", data);
	file_fd = open(argv[1], O_RDONLY);
	if (file_fd < 0)
		fatal("Could not open Map-File\n", data);
	if(!extract_images(file_fd, data))
		fatal("Images in Map-File not formatted properly\n", data);
	if(!Floor_Ceiling_Colour(file_fd, data))
		fatal("Floor or Ceiling Colour in Map-File not formatted properly\n", data);
	if(!Correct_Map(file_fd, data))
		fatal("Error with the Map in Map-File\n", data);
	init_player(data);
	close(file_fd);
}