/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:08:52 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/16 18:11:36 by cerdelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int		open_fd_to_file(char **file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error!\n", 8);
		perror(file);
	}
	
	return (fd);
}

bool	right_amt_args(int argc)
{
	if (argc < 2)
	{
		write(2, "Error!\nYou forgot that cube3d needs a map :)\n", 46);
		return (false);
	}
	if (argc > 2)
	{
		write(2, "Error!\nYou are overzealous ... cube3d can only run 1 map at a time :)\n", 71);
		return (false);
	}
	return (true);
}


char	**add_line_to_2d_array(char **arr, char *line)
{
	int		i;
	char	**out;

	if (!arr || !line)
		return (false);
	i = 0;
	while (arr[i + 1] != NULL)
		i++;
	out = malloc((i + 3) * sizeof(char *));
	out[i + 2] = NULL;
	out[i + 1] = line;
	while (i > -1)
	{
		out[i] = arr[i];
		i++;	
	}
	free_2d_array(arr);
	return (out);
}

bool	check_for_map_info(char **map, int i)
{
	if (map[i][0] == )
}

char	**get_whole_file(int fd)
{
	char	*line;
	char	**full_file;
	
	line = get_next_line(fd);
	if (line != NULL)
	{
		full_file = malloc(sizeof(char *) * 2);
		if (full_file == NULL)
			return (NULL);
		full_file[0] = line;
		full_file[1] = NULL;
	}
	line = get_next_line(fd);
	while (line)
	{
		add_line_to_2d_array(full_file, line);
		line = get_next_line(fd);
	}
	return (full_file);
}

bool	make_map_out_of_full_file(t_c3d_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (data->map[i] != NULL)
	{
		check_for_map_info(data->map, i);
		i++;
	}
}

bool	input_map(t_c3d_data *data, int argc, char **argv)
{
	int fd;

	if (right_amt_args(argc) == false)
		return (false);
	fd = open_fd_to_file(argv[1]);
	if (fd < 0)
		return (false);
	data->map = get_whole_file(fd);
	if (make_map_out_of_full_file(data) == false)
		return (false);
	 

	
}