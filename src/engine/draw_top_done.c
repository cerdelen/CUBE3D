// int	draw_player(t_c3d_data *data)
// {
// 	int	x;
// 	int	y;

// 	data->td_p_img.img = mlx_new_image(data->mlx,
// 			15, 15);
// 	data->td_p_img.addr = mlx_get_data_addr(data->td_p_img.img,
// 			&data->td_p_img.bits_per_pixel,
// 			&data->td_p_img.line_length,
// 			&data->td_p_img.endian);
// 	x = 0;
// 	while (x < 15)
// 	{
// 		y = 0;
// 		while (y < 15)
// 		{
// 			my_mlx_pixel_put(&data->td_p_img, x, y, 0x00FF0000);
// 			y++;
// 		}
// 		x++;
// 	}
// 	mlx_put_image_to_window(data->mlx, data->mlx_win2, data->td_p_img.img, data->p_x - 7, data->p_y - 7);
// 	return (0);
// }

// int	render_top_down_map(t_c3d_data *data)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < data->rows)
// 	{
// 		x = 0;
// 		while (x < data->columns)
// 		{
// 			if (data->map[y][x] == '1')
// 				mlx_put_image_to_window(data->mlx, data->mlx_win2, data->td_w_img.img, (x * T_SIZE), (y * T_SIZE));
// 			else if (data->map[y][x] == '0' || data->map[y][x] == 'S')
// 				mlx_put_image_to_window(data->mlx, data->mlx_win2, data->td_ft_img.img, (x * T_SIZE), (y * T_SIZE));
// 			x++;
// 		}
// 		y++;
// 	}
// 	draw_player(data);
// 	draw_rays(data);
// 	// draw_line(data->mlx, data->mlx_win2, data->p_x, data->p_y,
// 	// 	data->p_x + (data->p_dx * 3), data->p_y + (data->p_dy * 3), 0x0033CC00);
// 	return (0);
// }



// int	top_down_background(t_c3d_data *data)
// {
// 	int	x;
// 	int	y;

// 	data->td_bg_img.img = mlx_new_image(data->mlx,
// 			(data->columns * T_SIZE), (data->rows * T_SIZE));
// 	data->td_bg_img.addr = mlx_get_data_addr(data->td_bg_img.img,
// 			&data->td_bg_img.bits_per_pixel,
// 			&data->td_bg_img.line_length,
// 			&data->td_bg_img.endian);
// 	x = 0;
// 	while (x < (data->columns * T_SIZE))
// 	{
// 		y = 0;
// 		while (y < (data->rows * T_SIZE))
// 		{
// 			my_mlx_pixel_put(&data->td_bg_img, x, y, 0x00999999);
// 			y++;
// 		}
// 		x++;
// 	}
// 	return (0);
// }

// int	top_down_free_tile(t_c3d_data *data)
// {
// 	int	x;
// 	int	y;

// 	data->td_ft_img.img = mlx_new_image(data->mlx,
// 			T_SIZE, T_SIZE);
// 	data->td_ft_img.addr = mlx_get_data_addr(data->td_ft_img.img,
// 			&data->td_ft_img.bits_per_pixel,
// 			&data->td_ft_img.line_length,
// 			&data->td_ft_img.endian);
// 	x = 0;
// 	while (x < T_SIZE)
// 	{
// 		y = 0;
// 		while (y < T_SIZE)
// 		{
// 			my_mlx_pixel_put(&data->td_ft_img, x, y, 0x006E4F4F);
// 			y++;
// 		}
// 		x++;
// 	}
// 	return (0);
// }

// int	top_down_wall(t_c3d_data *data)
// {
// 	int	x;
// 	int	y;

// 	data->td_w_img.img = mlx_new_image(data->mlx,
// 			T_SIZE, T_SIZE);
// 	data->td_w_img.addr = mlx_get_data_addr(data->td_w_img.img,
// 			&data->td_w_img.bits_per_pixel,
// 			&data->td_w_img.line_length,
// 			&data->td_w_img.endian);
// 	x = 0;
// 	while (x < T_SIZE)
// 	{
// 		y = 0;
// 		while (y < T_SIZE)
// 		{
// 			my_mlx_pixel_put(&data->td_w_img, x, y, 0);
// 			y++;
// 		}
// 		x++;
// 	}
// 	return (0);
// }