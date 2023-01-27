#include "../includes/cub.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_line_img(t_img *img, t_vec first, t_vec second, int colour)
{
	double	deltaX;
	double	deltaY;
	int 	pixels;
	double 	pixelX;
	double 	pixelY;

	deltaX = second.x - first.x;
	deltaY = second.y - first.y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	pixelX = first.x;
	pixelY = first.y;
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
		my_mlx_pixel_put(img, pixelX, pixelY, colour);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}