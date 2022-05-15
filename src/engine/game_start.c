/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:23:46 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/15 13:37:22 by cerdelen         ###   ########.fr       */
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
	if (data->map[(int)((data->p_y + (data->p_dy * dir)) / 64)][(int)((data->p_x + (data->p_dx * dir)) / 64)] != '1')
	{
		data->p_x += data->p_dx * dir;
		data->p_y += data->p_dy * dir;
	}
	return (0);
}

int	turn_left(t_c3d_data *data)
{
	data->p_a += r_speed;
	if (data->p_a >= 2 * PI)
		data->p_a -= 2 * PI;
	data->p_dx = cos(data->p_a) * m_speed;
	data->p_dy = sin(data->p_a) * m_speed;
	return (0);
}

int	turn_right(t_c3d_data *data)
{
	data->p_a -= r_speed;
	if (data->p_a <= 0)
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
		turn_right(data);
		
	if (key == 1)
		move_func(data, -1);
	if (key == 2)
		turn_left(data);
	render_top_down_map(data);
	// printf("dir x = %lf dir y = %lf\n", data->p_dx, data->p_dy);
	
	
	double x;
	x = (data->p_dx * data->p_dx) + (data->p_dy * data->p_dy);
	x = sqrt(x);
	
	// printf("added together == %fd\n", x);
	
	
	return (0);
}
bool	epsilon_function(double target, double patient, double offset)
{
	if (patient < target + offset && patient > target - offset)
		return (true);
	return (false);
}
double fix_rounding_errors(t_c3d_data *data)
{
	double	ra;

	ra = data->p_a;
	if (epsilon_function(0, ra, rotationfix) == true || epsilon_function(2 * PI, ra, rotationfix) == true)
		ra = 0;
	else if (epsilon_function(PI, ra, rotationfix) == true)
		ra = PI;
	if (epsilon_function(P2, ra, rotationfix) == true)
		ra = P2;
	else if (epsilon_function(P3, ra, rotationfix) == true)
		ra = P3;
	return (ra);
}

double	dist_2d(double s_x, double s_y, double e_x, double e_y)
{
	double	a;
	double	b;

	a = s_x - e_x;
	if (s_x < e_x)
		a = e_x - s_x;
	b = s_y - e_y;
	if (s_y < e_y)
		b = e_y - s_y;
	return (sqrt((a * a)+(b * b)));
}



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// create array of doubles and ints and use enums to itterate through iut

void	draw_rays(t_c3d_data *data)
{
	int r, mx, my, mp, dof;
	double rx, ry, xo, ra ,yo, ninvtan, ntan, trx, try, vdist, hdist;

	// detect_horizontal_wall();
	// detect_vertical_wall();
	ra = fix_rounding_errors(data);
	r = 0;
	while (r < 1)
	{
		dof = 0;
		if (ra != 0)
			ninvtan = -1/tan(ra);
		if (ra == 0 || ra == PI)
		{
			rx = data->p_x;
			ry = data->p_y;
			dof = 8;
		}
		else if (ra > PI)
		{
			ry = (((int)data->p_y>>6)<<6) -0.0001;
			rx = (data->p_y - ry) * ninvtan + data->p_x;
			yo = -64;
			xo = -yo * ninvtan;
		}
		else if (ra < PI)
		{
			ry = (((int)data->p_y>>6)<<6) +64;
			rx = (data->p_y - ry) * ninvtan + data->p_x;
			yo = 64;
			xo = -yo * ninvtan;
		}
		while(dof < 8)
		{
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			if (my < 0 || mx < 0 || my > data->rows || mx > data->columns)
				break ;
			if (my < data->rows && mx < data->columns && data->map[my][mx] == '1')
				dof = 8 ;
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		try = ry;
		trx = rx;
		dof = 0;
		ntan = -tan(ra);
		// if (ra == 0 || ra == PI)
		if (ra == P2 || ra == P3)
		{
			printf("ra == 0 || ra == PI\n");
			rx = data->p_x;
			ry = data->p_y;
			dof = 8;
		}
		else if (ra > P2 && ra < P3)
		{
			printf("ra > P2 && ra < P3\n");
			rx = (((int)data->p_x>>6)<<6) -0.0001;
			ry = (data->p_x - rx) * ntan + data->p_y;
			xo = -64;
			yo = -xo * ntan;
		}
		else if (ra < P2 || ra > P3)
		{
			printf("ra < P2 || ra > P3\n");
			rx = (((int)data->p_x>>6)<<6) +64;
			ry = (data->p_x - rx) * ntan + data->p_y;
			xo = 64;
			yo = -xo * ntan;
		}
		while(dof < 8)
		{
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			if (my < 0 || mx < 0 || my > data->rows || mx > data->columns)
				break ;
			if (my < data->rows && mx < data->columns && data->map[my][mx] == '1')
				dof = 8 ;
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		vdist = dist_2d(data->p_x, data->p_y, rx, ry);
		hdist = dist_2d(data->p_x, data->p_y, trx, try);
		if ((vdist == 0 || hdist < vdist) && hdist != 0)
			draw_line(data->mlx, data->mlx_win, data->p_x, data->p_y, trx, try, 0x0033CC00);
		else
			draw_line(data->mlx, data->mlx_win, data->p_x, data->p_y, rx, ry, 0x0033CC00);
		// printf("%f %f %f %f %f\n", data->p_x, data->p_y, rx, ry, ra);

		r++;
	}
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
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->td_w_img.img, (x * 65) - 1, (y * 65) - 1);
			else if (data->map[y][x] == '0' || data->map[y][x] == 'S')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->td_ft_img.img, (x * 65) - 1, (y * 65) - 1);
			x++;
		}
		y++;
	}
	draw_player(data);
	draw_rays(data);
	// draw_line(data->mlx, data->mlx_win, data->p_x, data->p_y,
	// 	data->p_x + (data->p_dx * 3), data->p_y + (data->p_dy * 3), 0x0033CC00);
	return (0);
}



int	top_down_background(t_c3d_data *data)
{
	int	x;
	int	y;

	data->td_bg_img.img = mlx_new_image(data->mlx,
			(data->columns * 65) - 1, (data->rows * 65) - 1);
	data->td_bg_img.addr = mlx_get_data_addr(data->td_bg_img.img,
			&data->td_bg_img.bits_per_pixel,
			&data->td_bg_img.line_length,
			&data->td_bg_img.endian);
	x = 0;
	while (x < (data->columns * 65) - 1)
	{
		y = 0;
		while (y < (data->rows * 65) - 1)
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
			64, 64);
	data->td_ft_img.addr = mlx_get_data_addr(data->td_ft_img.img,
			&data->td_ft_img.bits_per_pixel,
			&data->td_ft_img.line_length,
			&data->td_ft_img.endian);
	x = 0;
	while (x < 64)
	{
		y = 0;
		while (y < 64)
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
			64, 64);
	data->td_w_img.addr = mlx_get_data_addr(data->td_w_img.img,
			&data->td_w_img.bits_per_pixel,
			&data->td_w_img.line_length,
			&data->td_w_img.endian);
	x = 0;
	while (x < 64)
	{
		y = 0;
		while (y < 64)
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
	data->mlx_win = mlx_new_window(data->mlx, data->columns * 65, (data->rows * 65) , "CUBE3D");
	top_down_background(data);
	top_down_wall(data);
	top_down_free_tile(data);
	render_top_down_map(data);
	// mlx_key_hook(data->mlx_win, key_press, data);
	mlx_hook(data->mlx_win, ON_DESTROY, 0, close_game, data);
	mlx_hook(data->mlx_win, ON_KEYDOWN, 0, key_press, data);
	mlx_loop(data->mlx);
}
