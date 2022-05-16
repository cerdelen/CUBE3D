/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:28:56 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/16 21:52:14 by cerdelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

char	**testing_map(void)
{
	char **map;
	char *line;
	int		i;

	i = 0;

	map = calloc(sizeof(char *) , 15);
	map[0] = ft_strdup("111111111111111");
	map[1] = ft_strdup("100000000000001");
	map[2] = ft_strdup("100000000000001");
	map[3] = ft_strdup("100000011110001");
	map[4] = ft_strdup("100000011110001");
	map[5] = ft_strdup("100000011110001");
	map[6] = ft_strdup("100000000000001");
	map[7] = ft_strdup("100000000000001");
	map[8] = ft_strdup("100000000000001");
	map[9] = ft_strdup("100000000000001");
	map[10] = ft_strdup("100110000000001");
	map[11] = ft_strdup("100110000000001");
	map[12] = ft_strdup("100000000001111");
	map[13] = ft_strdup("100000000000001");
	map[14] = ft_strdup("111111111111111");
	return (map);
}

void	init_move_deltas(t_c3d_data *data)
{
	double	t_ra1;
	double	t_ra2;

	data->p_a = 0;
	t_ra1 = P3;
	t_ra2 = P2;
	data->p_dx = cos(data->p_a) * m_speed;
	data->p_dy = sin(data->p_a) * m_speed;
	data->p_l_dx = cos(data->p_a + t_ra1) * m_speed;
	data->p_l_dy = sin(data->p_a + t_ra1) * m_speed;
	data->p_r_dx = cos(data->p_a + t_ra2) * m_speed;
	data->p_r_dy = sin(data->p_a + t_ra2) * m_speed;
}

int main(int argc, char **argv)
{
	t_c3d_data	data;
	
	// if (input_map(&data, argc, argv) == false)
	// 	return (1);
	data.map = testing_map();
	data.rows = 15;
	data.columns = 15;
	data.p_x = 384;
	data.p_y = 580;
	data.p_a = 0;
	init_move_deltas(&data);
	data.floor_colour = BRN;
	data.ceiling_colour = BLU;
	
	cube3d_game(&data);
}