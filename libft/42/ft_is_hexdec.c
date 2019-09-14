/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_hexdec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:24:38 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/04/16 16:24:39 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_hexdec(const char *hex)
{
	if (ft_strnequ(hex, "0x", 2))
	{
		hex += 2;
		while (*hex)
		{
			if (!ft_isdigit(*hex) && (*hex < 'a' || *hex > 'f'))
				return (0);
			hex++;
		}
		return (1);
	}
	return (0);
}
