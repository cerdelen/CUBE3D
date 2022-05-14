/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:28:56 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/14 15:51:14 by cerdelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int main(int argc, char **argv)
{
	t_c3d_data	data;
	
	if (input_map(&data, argc, argv) == false)
		return (1);
	start_game(&data);
}