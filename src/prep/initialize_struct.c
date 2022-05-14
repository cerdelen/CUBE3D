/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:58:20 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/14 16:13:55 by cerdelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	set_direction(t_c3d_data *data, char d)
{
	if (d == 'N')
		data->p_a = PI / 2;
	if (d == 'E')
		data->p_a = 0;
	if (d == 'S')
		data->p_a = (3 * PI) / 2;
	if (d == 'W')
		data->p_a = PI;
	data->p_dx = cos(data->p_a) * m_speed;
	data->p_dy = sin(data->p_a) * m_speed;
}

bool	initialize_player_pos(char **map, t_c3d_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->columns)
		{
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'W')
			{	
				data->p_x = j * 64;
				data->p_y = i * 64;
				set_direction(data, map[i][j]);
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

bool	initialize_struct(char **map, t_c3d_data *data)
{
	if (initialize_player_pos(map, data) == false)
		return (false);
	return (true);
}
