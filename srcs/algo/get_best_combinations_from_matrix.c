/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_best_combinations_from_matrix.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 23:57:26 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/26 06:46:00 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

typedef struct		s_matrix
{
	int				**matrix;
	size_t			x_size;
	size_t			y_size;
}					t_matrix;

typedef struct		s_backtrack
{
	char			**array;
	size_t			x_pos;
	size_t			y_pos;
}					t_backtrack;

static int check_conflict(int *array, size_t pos)
{
	size_t i;

	i = 0;
	while (i < pos)
	{
		if (array[i] == array[pos])
			return (1);
		i++;
	}
	return (0);
}

static int get_next_value(t_matrix *matrix_data, int *array, size_t y)
{
	array[y]++;
	while (array[y] < (int)matrix_data->x_size + 1)
	{
		if (matrix_data->matrix[array[y]][y] != 0 && !check_conflict(array, y))
			return (1);
		array[y]++;
	}
	array[y] = -1;
	return (0);
}

static void print_array(t_matrix *matrix_data, int *array)
{
	size_t i;

	i = 0;
	while (i < matrix_data->y_size + 1)
	{
		ft_printf("%d ", array[i]);
		i++;
	}
	ft_putchar('\n');
}

static int backtrack(t_matrix *matrix_data, int *array, size_t y)
{
	if (get_next_value(matrix_data, array, y))
	{
		if (y < matrix_data->y_size)
		{
			if (backtrack(matrix_data, array, y + 1) == 0)
				return (backtrack(matrix_data, array, y));
			else
			{
				ft_printf("EXIT 1 ");
				print_array(matrix_data, array);
				return (1);
			}
		}
		else
		{
			ft_printf("EXIT 2 ");
			print_array(matrix_data, array);
			return (1);
		}
	}
	else
	{
		ft_printf("EXIT 3 ");
		print_array(matrix_data, array);
		return (0);
	}
}


static int	find_next_combination(t_matrix *matrix_data)
{
	int		*array;
	size_t	i;

	if (!(array = ft_memalloc(sizeof(int) * matrix_data->x_size + 1)))
		return (-1);
	i = 0;
	while (i < matrix_data->x_size + 1)
	{
		array[i] = -1;
		i++;
	}
	backtrack(matrix_data, array, 0);
	return (0);
}

void		get_best_combinations_from_matrix(int **matrix, size_t x_size, size_t y_size)
{
	t_matrix	matrix_data;

	matrix_data.matrix = matrix;
	matrix_data.x_size = x_size - 1;
	matrix_data.y_size = y_size - 1;
	find_next_combination(&matrix_data);
}
