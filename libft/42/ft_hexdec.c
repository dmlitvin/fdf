/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:44:03 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/04/16 16:24:25 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_hexdec(const char *hex)
{
	int				factor;
	unsigned int	result;

	result = 0;
	if (hex)
	{
		factor = 1;
		if (*hex == '0' && *(hex + 1) == 'x')
			hex += 2;
		ft_reverse((void*)hex, sizeof(char), ft_strlen(hex));
		while (*hex)
		{
			result += (ft_isdigit(*hex)
				? *hex - '0' : *hex - 'a' + 10) * factor;
			factor *= 16;
			hex++;
		}
	}
	return (result);
}
