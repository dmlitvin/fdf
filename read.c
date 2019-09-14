/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:26:24 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/04/16 15:55:23 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point3d	*save_points(t_fdf *fdf, char **line, int y)
{
	int			x;
	t_point3d	*point;
	char		*comma;

	x = 0;
	point = malloc(sizeof(t_point3d) * fdf->matrix_x_size);
	while (*line && **line)
	{
		if (!line_valid(*line))
			throw_error(y + 1, "syntax error");
		comma = ft_strchr(*line, ',');
		point[x].z = ft_atoi(*line);
		point[x].x = x;
		point[x].y = y;
		if (comma)
			point[x].color = ft_hexdec(comma + 1);
		x++;
		line++;
	}
	return (point);
}

static t_point3d	**extract_points(t_list *str_points, t_fdf *fdf)
{
	int			line_counter;
	t_point3d	**points;

	line_counter = 0;
	points = (t_point3d**)malloc(sizeof(t_point3d*) * fdf->matrix_y_size);
	while (str_points)
	{
		points[line_counter] = save_points(fdf,
				str_points->content, line_counter);
		str_points = str_points->next;
		line_counter++;
	}
	return (points);
}

static size_t		point_nb(t_list *list)
{
	size_t	point_nb;
	char	**line;

	point_nb = 0;
	if (list)
	{
		line = list->content;
		while (*line++)
			point_nb++;
	}
	return (point_nb);
}

static void			clean_points_str(t_list *list)
{
	int i;

	if (list)
	{
		clean_points_str(list->next);
		i = 0;
		while (((char**)list->content)[i])
			free(((char**)list->content)[i++]);
		free(list->content);
		free(list);
	}
}

t_point3d			**read_file(int fd, t_fdf *fdf)
{
	char		*line;
	t_point3d	**points;
	t_list		*tmp;
	t_list		*str_points;

	str_points = 0;
	if (fd == -1 || read(fd, 0, 0) == -1)
		throw_error(0, "error on file opening");
	while (get_next_line((int)(fdf->matrix_y_size++ * 0) + fd, &line))
	{
		tmp = ft_lstnew(NULL, 0);
		tmp->content = ft_strsplit(line, ' ');
		free(line);
		ft_lstadd_end(&str_points, tmp);
	}
	fdf->matrix_y_size--;
	fdf->matrix_x_size = point_nb(str_points);
	points = extract_points(str_points, fdf);
	clean_points_str(str_points);
	return (points);
}
