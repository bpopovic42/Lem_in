/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:52:41 by bopopovi          #+#    #+#             */
/*   Updated: 2018/11/27 18:30:44 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		get_ants_nbr_if_valid(const char *str, unsigned int *output)
{
	int result;

	result = ft_atoi(str);
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
