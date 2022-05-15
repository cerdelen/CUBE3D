/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:23:46 by cerdelen          #+#    #+#             */
/*   Updated: 2022/05/16 00:17:48 by cerdelen         ###   ########.fr       */
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
	if (data->map[(int)((data->p_y + (data->p_dy * dir)) / T_SIZE)][(int)((data->p_x + (data->p_dx * dir)) / T_SIZE)] != '1')
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

// int render_after_move(t_c3d_data *data)
// {
// 	mlx_put_image_to_window(data->mlx, data->mlx_win2, data->td_p_img.img, data->p_x+ 58 , data->p_y + 47);
// 	return (0);
// }



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
	// render_top_down_map(data);
	// printf("dir x = %lf dir y = %lf\n", data->p_dx, data->p_dy);
	// draw_line(data->mlx, data->mlx_win, 0, 0, 100 ,100 , 0x0033CC00);
	// printf("hello\n");
	// draw_line()
	mlx_clear_window(data->mlx, data->mlx_win);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->f_p_view.img, 0, 0);
	
	return (0);
}
bool	epsilon_function(double target, double patient, double offset)
{
	if (patient < target + offset && patient > target - offset)
		return (true);
	return (false);
}
double fix_rounding_errors(double tra)
{
	double	ra;

	ra = tra;
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

	a = fabs(s_x - e_x);
	b = fabs(s_y - e_y);
	return (sqrt((a * a)+(b * b)));
}



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// create array of doubles and ints and use enums to itterate through iut

rightes ray different color for debugging

void	draw_rays(t_c3d_data *data)
{
	int r, mx, my, mp, dof;
	double rx, ry, xo, ra ,yo, ninvtan, ntan, trx, try, vdist, hdist, rdist;

	// detect_horizontal_wall();
	// detect_vertical_wall();
	
	data->f_p_view.img = mlx_new_image(data->mlx, WINDOW_W, WINDOW_H);
	data->f_p_view.addr = mlx_get_data_addr(data->f_p_view.img,
			&data->f_p_view.bits_per_pixel,
			&data->f_p_view.line_length,
			&data->f_p_view.endian);
	
	r = - FOV / 2;
	while (r <= FOV / 2)
	{

		// horizontal rays
		ra = data->p_a + (r * RAD);
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		ra = fix_rounding_errors(ra);
		printf("ra = %f\n", ra);
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
			yo = -T_SIZE;
			xo = -yo * ninvtan;
		}
		else if (ra < PI)
		{
			ry = (((int)data->p_y>>6)<<6) +T_SIZE;
			rx = (data->p_y - ry) * ninvtan + data->p_x;
			yo = T_SIZE;
			xo = -yo * ninvtan;
		}
		while(dof < 8)
		{
			if (rx < 0 || ry < 0)
			{
				rx = data->p_x;
				ry = data->p_y;
				break ;
			}
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			if (my <= 0 || mx <= 0 || my > data->rows || mx > data->columns)
				break ;
			if (my < data->rows && mx < data->columns && my > 0 && mx > 0 && data->map[my][mx] == '1')
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

		//verticall rays
		
		dof = 0;
		ntan = -tan(ra);
		if (ra == P2 || ra == P3)
		{
			rx = data->p_x;
			ry = data->p_y;
			dof = 8;
		}
		else if (ra > P2 && ra < P3)
		{
			rx = (((int)data->p_x>>6)<<6) -0.0001;
			ry = (data->p_x - rx) * ntan + data->p_y;
			xo = -T_SIZE;
			yo = -xo * ntan;
		}
		else if (ra < P2 || ra > P3)
		{
			rx = (((int)data->p_x>>6)<<6) +T_SIZE;
			ry = (data->p_x - rx) * ntan + data->p_y;
			xo = T_SIZE;
			yo = -xo * ntan;
		}
		while(dof < 8)
		{
			if (rx < 0 || ry < 0)
			{
				rx = data->p_x;
				ry = data->p_y;
				break ;
			}
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			if (my <= 0 || mx <= 0 || my > data->rows || mx > data->columns)
				break ;
			if (my < data->rows && mx < data->columns && my > 0 && mx > 0 && data->map[my][mx] == '1')
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
		if ((vdist == 0 || hdist < vdist) && hdist != 0) // horrizontalen
			rdist = hdist;
		else											//vertikalen
			rdist = vdist;
		double ca = data->p_a - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 0)
			ca -= 2 * PI;
		rdist = rdist * cos(ca);
		double lineH = (T_SIZE * WINDOW_H) / rdist;
		if (lineH>WINDOW_H)							
			lineH = WINDOW_H;
		double lineO = WINDOW_H / 2 - lineH/2;
											//line height	
		int i = 0;
		while (i < (WINDOW_W / FOV))
		{
			draw_line_img(&data->f_p_view, (r + FOV / 2) * (WINDOW_W / FOV) + i, lineO, (r + FOV / 2) * (WINDOW_W / FOV) + i, lineH + lineO, RED);
			// draw_line(data->mlx, data->mlx_win, (r + FOV / 2) * (WINDOW_W / FOV) + i, lineO, (r + FOV / 2) * (WINDOW_W / FOV) + i, lineH + lineO, 0x0033CC00);
			i++;
		}
		// draw_line(data->mlx, data->mlx_win, (r + FOV / 2) * (WINDOW_W / FOV), lineO, (r + FOV / 2) * (WINDOW_W / FOV), lineH + lineO, 0x0033CC00);
		r++;
	}
}
 
void	cube3d_game(t_c3d_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WINDOW_W, WINDOW_H , "CUBE3D");
	mlx_hook(data->mlx_win, ON_DESTROY, 0, close_game, data);
	mlx_hook(data->mlx_win, ON_KEYDOWN, 0, key_press, data);
	mlx_loop(data->mlx);
}
