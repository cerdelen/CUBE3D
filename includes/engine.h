#ifndef ENGINE_H
#define ENGINE_H


void draw_line_img(t_img *img, t_vec first, t_vec second, int colour);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	render(t_data *data);
double		single_ray(t_data *data, t_vec dir, int dimension);
void		print_vec(t_vec vec, char *mes);


#endif