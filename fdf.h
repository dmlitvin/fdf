/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:04:07 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/04/16 16:21:50 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/include/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <sys/errno.h>

# define WIDTH  1020
# define HEIGHT 1280

# define ISO 1
# define TORAD(x) x * M_PI / 180
# define ESC 53

typedef struct	s_point3d
{
	int			x;
	int			y;
	int			z;
	unsigned	color;
}				t_point3d;

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	size_t		matrix_y_size;
	size_t		matrix_x_size;
	int			zoom;
	int			mode;
	t_point3d	**points;
	t_point		**projectionpoints;
}				t_fdf;

void			throw_error(int line, char *error);
int				open_file(char *filename);
int				line_valid(char *line);
t_point3d		**read_file(int fd, t_fdf *fdf);
void			draw_line(t_fdf *fdf, t_point p1, t_point p2);
void			draw(t_fdf *fdf);
t_point			get2dpoint(t_point3d point, t_fdf *fdf,
		const double cos_value, const double sin_value);
void			clean_window(t_fdf *fdf);

#endif
