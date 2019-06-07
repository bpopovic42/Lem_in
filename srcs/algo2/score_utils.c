/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 15:18:12 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/07 20:12:39 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_score(t_score **score)
{
	ft_bzero(*score, sizeof(**score));
	ft_memdel((void**)score);
}

t_score		*score_new()
{
	t_score *new;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	new->output_size = -1;
	return (new);
}
