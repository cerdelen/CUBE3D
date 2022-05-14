#include "../includes/cube3d.h"

int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double	deltaX;
	double	deltaY;
	int pixels;
	double pixelX;
	double pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	pixelX = beginX;
	pixelY = beginY;
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
    mlx_pixel_put(mlx, win, pixelX, pixelY, color);
    pixelX += deltaX;
    pixelY += deltaY;
    --pixels;
	}
	return (0);
}