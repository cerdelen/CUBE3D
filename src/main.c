/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:28:56 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/14 15:46:27 by cerdelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int main(int argc, char **argv)
{
	t_c3d_data	data;
	
	data.map = input_map(&data, argc, argv);
	start_game(&data);
}