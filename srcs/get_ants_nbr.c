/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:52:41 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/25 14:12:45 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			get_ants_nbr(char *input, int *ants)
{
	if (!ft_is_valid_int(input))
		return (-1);
	if ((*ants = ft_atoi(input)) < 0)
		return (-1);
	return (0);
}
