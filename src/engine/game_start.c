/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:23:46 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/14 16:20:06 by cerdelen         ###   ########.fr       */
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
	if (data->map[(int)((data->p_y + (data->p_dy * dir)) / 100)][(int)((data->p_x + (data->p_dx * dir)) / 100)] != '1')
	{
		data->p_x += data->p_dx * dir;
		data->p_y += data->p_dy * dir;
	}
	return (0);
}

// simple maths einheitskreis sin cos

int	turn_left(t_c3d_data *data)
{
	data->p_a += r_speed;
	if (data->p_a > 2 * PI)
		data->p_a -= 2 * PI;
	data->p_dx = cos(data->p_a) * m_speed;
	data->p_dy = sin(data->p_a) * m_speed;
	return (0);
}

int	turn_right(t_c3d_data *data)
{
	data->p_a -= r_speed;
	if (data->p_a < 0)
		data->p_a += 2 * PI;
	data->p_dx = cos(data->p_a) * m_speed;
	data->p_dy = sin(data->p_a) * m_speed;
	return (0);
}

int render_after_move(t_c3d_data *data)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->td_p_img.img, data->p_x+ 58 , data->p_y + 47);
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
	printf("dir x = %lf dir y = %lf\n", data->p_dx, data->p_dy);
	
	
	int x;
	if (data->p_dx < 0 && data->p_dy < 0)
		x = 0 - (data->p_dx + data->p_dy);
	if (data->p_dx > 0 && data->p_dy > 0)
		x = data->p_dx + data->p_dy;
	if (data->p_dx < 0 && data->p_dy > 0)
		x = data->p_dy - data->p_dx;
	if (data->p_dx > 0 && data->p_dy < 0)
		x = data->p_dx - data->p_dy;
	
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

	data->td_p_img.img = mlx_new_image(data->mlx,
			15, 15);
	data->td_p_img.addr = mlx_get_data_addr(data->td_p_img.img,
			&data->td_p_img.bits_per_pixel,
			&data->td_p_img.line_length,
			&data->td_p_img.endian);
	x = 0;
	while (x < 15)
	{
		y = 0;
		while (y < 15)
		{
			my_mlx_pixel_put(&data->td_p_img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->td_p_img.img, data->p_x - 7, data->p_y - 7);
	return (0);
}

int	render_top_down_map(t_c3d_data *data)
{
	int	x;
	int	y;


	mlx_put_image_to_window(data->mlx, data->mlx_win, data->td_bg_img.img, 0, 0);
	y = 0;
	while (y < data->rows)
	{
		x = 0;
		while (x < data->columns)
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->td_w_img.img, x * 101, y * 101);
			else if (data->map[y][x] == '0' || data->map[y][x] == 'S')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->td_ft_img.img, x * 101, y * 101);
			x++;
		}
		y++;
	}
	draw_player(data);
	draw_line(data->mlx, data->mlx_win, data->p_x, data->p_y,
		data->p_x + (data->p_dx * 3), data->p_y + (data->p_dy * 3), 0x0033CC00);
	return (0);
}



int	top_down_background(t_c3d_data *data)
{
	int	x;
	int	y;

	data->td_bg_img.img = mlx_new_image(data->mlx,
			data->columns * 101, data->rows * 101);
	data->td_bg_img.addr = mlx_get_data_addr(data->td_bg_img.img,
			&data->td_bg_img.bits_per_pixel,
			&data->td_bg_img.line_length,
			&data->td_bg_img.endian);
	x = 0;
	while (x < data->columns * 101)
	{
		y = 0;
		while (y < data->rows * 101)
		{
			my_mlx_pixel_put(&data->td_bg_img, x, y, 0x00999999);
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

	data->td_ft_img.img = mlx_new_image(data->mlx,
			100, 100);
	data->td_ft_img.addr = mlx_get_data_addr(data->td_ft_img.img,
			&data->td_ft_img.bits_per_pixel,
			&data->td_ft_img.line_length,
			&data->td_ft_img.endian);
	x = 0;
	while (x < 100)
	{
		y = 0;
		while (y < 100)
		{
			my_mlx_pixel_put(&data->td_ft_img, x, y, 0x006E4F4F);
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

	data->td_w_img.img = mlx_new_image(data->mlx,
			100, 100);
	data->td_w_img.addr = mlx_get_data_addr(data->td_w_img.img,
			&data->td_w_img.bits_per_pixel,
			&data->td_w_img.line_length,
			&data->td_w_img.endian);
	x = 0;
	while (x < 100)
	{
		y = 0;
		while (y < 100)
		{
			my_mlx_pixel_put(&data->td_w_img, x, y, 0);
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
