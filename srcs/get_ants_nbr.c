/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:52:41 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/19 16:55:36 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_is_valid_int(const char *nbr)
{
	int i;

	i = 0;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]) && !ft_issign(nbr[i]))
			return (0);
		i++;
	}
	return (1);
}

static int		strict_atoi(const char *nbr, int *result)
{
	if (ft_is_valid_int(nbr))
	{
		*result = ft_atoi(nbr);
		return (0);
	}
	return (-1);
}

static int		get_ants_nbr_if_valid(const char *str, unsigned int *output)
{
	int result;

	if (strict_atoi(str, &result) < 0)
		return (-1);
	if (result < 0)
		return (-1);
	*output = (unsigned int)result;
	return (0);
}

/*
** Try to read the number of ants from the first line of input
** If first line isn't a valid unsigned int representation
*/

int			get_ants_nbr(char **input, unsigned int *ants)
{
	if (get_ants_nbr_if_valid(input[0], ants) < 0)
		return (-1);
	return (0);
}
