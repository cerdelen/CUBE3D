/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:23:46 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/14 15:01:10 by cerdelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"


int	close_game(t_c3d_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	// free_and_exit(vars);
	exit(0);
}

int	move_func(t_c3d_data *data, int dir)
{
	if (data->map[(int)((data->player_pos[1] + (data->p_dir[1] * dir)) / 100)][(int)((data->player_pos[0] + (data->p_dir[0] * dir)) / 100)] != '1')
	{
		data->player_pos[0] += data->p_dir[0] * dir;
		data->player_pos[1] += data->p_dir[1] * dir;
	}
	return (0);
}

// simple maths einheitskreis sin cos

int	turn_left(t_c3d_data *data)
{
	data->player_ang += r_speed;
	if (data->player_ang > 2 * PI)
		data->player_ang -= 2 * PI;
	data->p_dir[0] = cos(data->player_ang) * m_speed;
	data->p_dir[1] = sin(data->player_ang) * m_speed;
	return (0);
}

int	turn_right(t_c3d_data *data)
{
	data->player_ang -= r_speed;
	if (data->player_ang < 0)
		data->player_ang += 2 * PI;
	data->p_dir[0] = cos(data->player_ang) * m_speed;
	data->p_dir[1] = sin(data->player_ang) * m_speed;
	return (0);
}

int render_after_move(t_c3d_data *data)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->top_down_player_img.img, data->player_pos[0]+ 58 , data->player_pos[1] + 47);
	return (0);
}

int	key_press(int key, t_c3d_data *data)
{
	if (key == 53)
		return (close_game(data));
	if (key == 13)
		move_func(data, 1);
	if (key == 0)
		turn_left(data);
	if (key == 1)
		move_func(data, -1);
	if (key == 2)
		turn_right(data);
	render_top_down_map(data);
	printf("dir x = %lf dir y = %lf\n", data->p_dir[0], data->p_dir[1]);
	
	
	int x;
	if (data->p_dir[0] < 0 && data->p_dir[1] < 0)
		x = 0 - (data->p_dir[0] + data->p_dir[1]);
	if (data->p_dir[0] > 0 && data->p_dir[1] > 0)
		x = data->p_dir[0] + data->p_dir[1];
	if (data->p_dir[0] < 0 && data->p_dir[1] > 0)
		x = data->p_dir[1] - data->p_dir[0];
	if (data->p_dir[0] > 0 && data->p_dir[1] < 0)
		x = data->p_dir[0] - data->p_dir[1];
	
	printf("added together == %d\n", x);
	
	
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	draw_player(t_c3d_data *data)
{
	int	x;
	int	y;

	data->top_down_player_img.img = mlx_new_image(data->mlx,
			15, 15);
	data->top_down_player_img.addr = mlx_get_data_addr(data->top_down_player_img.img,
			&data->top_down_player_img.bits_per_pixel,
			&data->top_down_player_img.line_length,
			&data->top_down_player_img.endian);
	x = 0;
	while (x < 15)
	{
		y = 0;
		while (y < 15)
		{
			my_mlx_pixel_put(&data->top_down_player_img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->top_down_player_img.img, data->player_pos[0] - 7, data->player_pos[1] - 7);
	return (0);
}

int	render_top_down_map(t_c3d_data *data)
{
	int	x;
	int	y;


	mlx_put_image_to_window(data->mlx, data->mlx_win, data->top_down_backg_img.img, 0, 0);
	y = 0;
	while (y < data->rows)
	{
		x = 0;
		while (x < data->columns)
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->top_down_wall_img.img, x * 101, y * 101);
			else if (data->map[y][x] == '0' || data->map[y][x] == 'S')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->top_down_free_tile_img.img, x * 101, y * 101);
			x++;
		}
		y++;
	}
	draw_player(data);
	draw_line(data->mlx, data->mlx_win, data->player_pos[0], data->player_pos[1],
		data->player_pos[0] + (data->p_dir[0] * 3), data->player_pos[1] + (data->p_dir[1] * 3), 0x0033CC00);
	return (0);
}



int	top_down_background(t_c3d_data *data)
{
	int	x;
	int	y;

	data->top_down_backg_img.img = mlx_new_image(data->mlx,
			data->columns * 101, data->rows * 101);
	data->top_down_backg_img.addr = mlx_get_data_addr(data->top_down_backg_img.img,
			&data->top_down_backg_img.bits_per_pixel,
			&data->top_down_backg_img.line_length,
			&data->top_down_backg_img.endian);
	x = 0;
	while (x < data->columns * 101)
	{
		y = 0;
		while (y < data->rows * 101)
		{
			my_mlx_pixel_put(&data->top_down_backg_img, x, y, 0x00999999);
			y++;
		}
		x++;
	}
	return (0);
}

int	top_down_free_tile(t_c3d_data *data)
{
	int	x;
	int	y;

	data->top_down_free_tile_img.img = mlx_new_image(data->mlx,
			100, 100);
	data->top_down_free_tile_img.addr = mlx_get_data_addr(data->top_down_free_tile_img.img,
			&data->top_down_free_tile_img.bits_per_pixel,
			&data->top_down_free_tile_img.line_length,
			&data->top_down_free_tile_img.endian);
	x = 0;
	while (x < 100)
	{
		y = 0;
		while (y < 100)
		{
			my_mlx_pixel_put(&data->top_down_free_tile_img, x, y, 0x006E4F4F);
			y++;
		}
		x++;
	}
	return (0);
}

int	top_down_wall(t_c3d_data *data)
{
	int	x;
	int	y;

	data->top_down_wall_img.img = mlx_new_image(data->mlx,
			100, 100);
	data->top_down_wall_img.addr = mlx_get_data_addr(data->top_down_wall_img.img,
			&data->top_down_wall_img.bits_per_pixel,
			&data->top_down_wall_img.line_length,
			&data->top_down_wall_img.endian);
	x = 0;
	while (x < 100)
	{
		y = 0;
		while (y < 100)
		{
			my_mlx_pixel_put(&data->top_down_wall_img, x, y, 0);
			y++;
		}
		x++;
	}
	return (0);
}

void	cube3d_game(t_c3d_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->columns * 101, data->rows * 101, "CUBE3D");
	top_down_background(data);
	top_down_wall(data);
	top_down_free_tile(data);
	render_top_down_map(data);
	mlx_key_hook(data->mlx_win, key_press, data);
	mlx_hook(data->mlx_win, 17, 0, close_game, data);
	mlx_loop(data->mlx);
}
