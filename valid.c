/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:18:11 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/04/16 16:08:50 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			open_file(char *file_name)
{
	int		fd;
	size_t	name_size;

	name_size = ft_strlen(file_name);
	if (name_size >= 5 && ft_strequ(file_name + name_size - 4, ".fdf"))
	{
		if ((fd = open(file_name, O_RDONLY)) != -1 && read(fd, NULL, 0) != -1)
			return (fd);
	}
	else
		throw_error(0, "Wrong file extension!");
	return (-1);
}

int			line_valid(char *line)
{
	char	*comma;

	comma = ft_strchr(line, ',');
	if (line[1] && (*line == '-' || *line == '+'))
		line++;
	if (comma)
	{
		while (line != comma)
		{
			if (!(ft_isdigit(*line)))
				return (0);
			line++;
		}
		return (ft_is_hexdec(comma));
	}
	return (ft_isnumeric(line));
}

void		throw_error(int line, char *error)
{
	ft_putstr_fd("fdf: ", 2);
	if (line)
	{
		ft_putstr_fd("error on line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error, 2);
	exit(1);
}
