/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:58:20 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/14 15:02:10 by cerdelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	set_direction(t_c3d_data *data, char d)
{
	if (d == 'N')
		data->player_ang = PI / 2;
	if (d == 'E')
		data->player_ang = 0;
	if (d == 'S')
		data->player_ang = (3 * PI) / 2;
	if (d == 'W')
		data->player_ang = PI;
	data->p_dir[0] = cos(data->player_ang) * m_speed;
	data->p_dir[1] = sin(data->player_ang) * m_speed;
}

bool	initialize_player_pos(char **map, t_c3d_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->player_pos[0] = -1;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->columns)
		{
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'W')
			{	
				data->player_pos[0] = j * 101;
				data->player_pos[1] = i * 101;
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
