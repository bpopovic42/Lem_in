/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 20:29:17 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 20:32:56 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STRUCTS_H
# define LEM_IN_STRUCTS_H

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_file
{
	char			*data;
	size_t			capacity;
	size_t			size;
}					t_file;

typedef struct		s_room
{
	char			*command;
	char			*name;
	int				end_distance;
	int				start_distance;
	int				final_distance;
	int				blocked;
	int				cleaned;
	struct s_room	*from;
	struct s_room	*to;
	struct s_room	*solution_to;
	struct s_room	*solution_from;
	int				solution_len;
	int				ant;
	t_list			*links;
	struct s_pos	pos;
}					t_room;

typedef struct		s_score
{
	int				total_ants;
	int				diff;
	int				output_size;
	int				nbr_of_paths;
	int				longest_path_size;
}					t_score;

typedef struct		s_path
{
	t_room			*head;
	t_room			*last_ant;
	int				length;
	int				final_length;
	int				is_solution;
	int				recorded;
	int				ants;
}					t_path;

typedef struct		s_route
{
	t_score			*score;
	t_list			*paths;
}					t_route;

typedef struct		s_output
{
	int				longest_path_len;
	t_list			*paths;
}					t_output;

typedef struct		s_graph
{
	int				ants;
	size_t			nbr_of_rooms;
	size_t			nbr_of_links;
	t_room			*start;
	t_room			*end;
	t_vect			*room_list;
	t_htable		*rooms;
	char			*last_command;
}					t_graph;

typedef struct		s_queue
{
	t_room			**rooms;
	size_t			capacity;
	size_t			size;
	size_t			head;
	size_t			tail;
}					t_queue;

#endif
