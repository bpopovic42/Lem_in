/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:52:41 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/25 15:11:00 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			get_ants_nbr(char *input, int *ants)
{
	if (!ft_is_valid_int(input))
	{
		lemin_perror("Invalid ants integer representation.");
		return (-1);
	}
	if ((*ants = ft_atoi(input)) < 0)
	{
		lemin_perror("Negative ants integer value.");
		return (-1);
	}
	return (0);
}
