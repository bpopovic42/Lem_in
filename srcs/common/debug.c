/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:20:25 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/21 13:35:16 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	algo_dbg(int is_msg_last, const char *fmt_msg, ...)
{
	va_list ap;

	if (ALGO_DBG == 1)
	{
		va_start(ap, fmt_msg);
		ft_vdprintf(2, fmt_msg, ap);
		if (is_msg_last)
			ft_putchar('\n');
		va_end(ap);
	}
}

void	print_warning(const char *fmt_msg, ...)
{
	va_list ap;

	if (WARN_DBG == 1)
	{
		va_start(ap, fmt_msg);
		ft_dprintf(2, "{yellow}", NULL);
		ft_putstr("Warning : ");
		ft_vdprintf(2, fmt_msg, ap);
		ft_dprintf(2, "{eoc}", NULL);
		ft_putchar('\n');
		va_end(ap);
	}
}
