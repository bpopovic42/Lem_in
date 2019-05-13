/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:42:07 by bopopovi          #+#    #+#             */
/*   Updated: 2019/04/04 06:03:22 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bmap	*ft_bitmap_new(size_t binary_size)
{
	size_t total_size;
	t_bmap *new;

	total_size = (binary_size / (sizeof(int) * 8));
	if ((total_size * (sizeof(int) * 8)) < binary_size)
		total_size++;
	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	if (!(new->bits = ft_memalloc(sizeof(int) * total_size)))
		return (NULL);
	new->size = total_size;
	return (new);
}

void	ft_bitmap_set_bit(t_bmap *bmap, size_t bit)
{
	size_t index;
	size_t offset;

	index = bit / (sizeof(int) * 8);
	offset = bit % (sizeof(int) * 8);
	bmap->bits[index] |= 1 << offset;
}

void	ft_bitmap_clear_bit(t_bmap *bmap, size_t bit)
{
	size_t index;
	size_t offset;

	index = bit / (sizeof(int) * 8);
	offset = bit % (sizeof(int) * 8);
	bmap->bits[index] &= ~(1 << offset);
}

int		ft_bitmap_has_bit(t_bmap *bmap, size_t bit)
{
	size_t index;
	size_t offset;

	index = bit / (sizeof(int) * 8);
	offset = bit % (sizeof(int) * 8);
	return (bmap->bits[index] & (1 << offset));
}

t_bmap	*ft_bitmap_dup(t_bmap *bmap)
{
	t_bmap *new;

	if (!(new = ft_memalloc(sizeof(int) * bmap->size)))
		return (NULL);
	if (!(new->bits = ft_memdup(bmap->bits, sizeof(int) * bmap->size)))
		return (NULL);
	new->size = bmap->size;
	return (new);
}
