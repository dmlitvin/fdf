/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:04:26 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/04/15 19:40:56 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int ac, char **av)
{
	t_fdf	fdf;

	ft_bzero(&fdf, sizeof(t_fdf));
	if (ac == 2)
		fdf.points = read_file(open_file(av[1]), &fdf);
	else
	{
		ft_printf("usage: %s source_file.fdf\n", *av);
		exit(0);
	}
	if (fdf.matrix_y_size)
	{
		fdf.mlx_ptr = mlx_init();
		fdf.zoom = 35;
		fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIDTH, HEIGHT, "fdf");
		draw(&fdf);
	}
	else
		throw_error(0, "empty file");
	return (0);
}
