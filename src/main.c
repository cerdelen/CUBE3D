/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:28:56 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/14 18:28:57 by cerdelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

char	**testing_map(void)
{
	char **map;
	char *line;
	int		i;

	i = 0;

	map = calloc(sizeof(char *) , 7);
	map[0] = ft_strdup("111111");
	map[1] = ft_strdup("100001");
	map[2] = ft_strdup("101101");
	map[3] = ft_strdup("101101");
	map[4] = ft_strdup("100001");
	map[5] = ft_strdup("111111");
	return (map);
}

int main(int argc, char **argv)
{
	t_c3d_data	data;
	
	// if (input_map(&data, argc, argv) == false)
	// 	return (1);
	data.map = testing_map();
	data.rows = 6;
	data.columns = 6;
	data.p_x = 104;
	data.p_y = 104;
	data.p_a = PI;
	data.p_dx = cos(data.p_a) * m_speed;
	data.p_dy = sin(data.p_a) * m_speed;
	cube3d_game(&data);
}