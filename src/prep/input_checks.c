/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:08:52 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/14 16:09:32 by cerdelen         ###   ########.fr       */
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

bool	input_map(t_c3d_data *data, int argc, char **argv)
{
	int fd;

	if (right_amt_args(argc) == false)
		return (false);
	fd = open_fd_to_file(argv[1]);
	if (fd < 0)
		return (false);
	 

	
}