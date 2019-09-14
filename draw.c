/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:39:59 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/04/16 16:15:27 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	const t_point	delta = {ABS(p2.x - p1.x), ABS(p2.y - p1.y)};
	const t_point	sign = {p1.x < p2.x ? 1 : -1, p1.y < p2.y ? 1 : -1};
	int				error;
	int				error2;

	error = delta.x - delta.y;
	while (p1.x != p2.x || p1.y != p2.y)
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr,
				p1.x + WIDTH / 4, p1.y + HEIGHT / 4, 0xFF00FF);
		error2 = error * 2;
		if (error2 > -delta.y)
		{
			error -= delta.y;
			p1.x += sign.x;
		}
		if (error2 < delta.x)
		{
			error += delta.x;
			p1.y += sign.y;
		}
	}
	mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr,
			p1.x + WIDTH / 4, p1.y + HEIGHT / 4, 0xFF00FF);
}

t_point			get2dpoint(t_point3d point, t_fdf *fdf,
		const double cos_value, const double sin_value)
{
	t_point result;

	if (fdf->mode == ISO)
	{
		result.x = (point.x - point.y) * fdf->zoom * cos_value;
		result.y = (-point.z + (point.y + point.x)) * fdf->zoom * sin_value;
	}
	else
	{
		result.x = fdf->zoom * point.x;
		result.y = fdf->zoom * point.y;
	}
	return (result);
}

static void		calculate2dpoints(t_fdf *fdf)
{
	const double	sin_value = sin(TORAD(30));
	const double	cos_value = cos(TORAD(30));
	size_t			y;
	size_t			x;

	y = 0;
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	if (!fdf->projectionpoints)
		fdf->projectionpoints =
				ft_memalloc(sizeof(t_point*) * fdf->matrix_y_size);
	while (y < fdf->matrix_y_size)
	{
		if (!(fdf->projectionpoints[y]))
			fdf->projectionpoints[y] =
					malloc(sizeof(t_point) * fdf->matrix_x_size);
		x = 0;
		while (x < fdf->matrix_x_size)
		{
			fdf->projectionpoints[y][x] = get2dpoint(fdf->points[y][x],
					fdf, cos_value, sin_value);
			x++;
		}
		y++;
	}
}

int				key_press(int key_code, void *param)
{
	if (key_code == 49)
		((t_fdf*)param)->mode = (((t_fdf*)param)->mode == ISO) ? 0 : ISO;
	else if (key_code == 24)
		((t_fdf*)param)->zoom++;
	else if (key_code == 27)
		((t_fdf*)param)->zoom--;
	else if (key_code == 53)
		exit(0);
	draw(param);
	return (0);
}

void			draw(t_fdf *fdf)
{
	size_t			y;
	size_t			x;

	y = 0;
	calculate2dpoints(fdf);
	while (y < fdf->matrix_y_size - 1)
	{
		x = 0;
		while (x < fdf->matrix_x_size - 1)
		{
			draw_line(fdf, fdf->projectionpoints[y][x],
					fdf->projectionpoints[y][x + 1]);
			draw_line(fdf, fdf->projectionpoints[y][x],
					fdf->projectionpoints[y + 1][x]);
			x++;
		}
		y++;
	}
	mlx_hook(fdf->win_ptr, 2, 2, key_press, fdf);
	mlx_loop(fdf->mlx_ptr);
}
