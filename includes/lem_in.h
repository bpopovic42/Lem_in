#ifndef LEM_IN_H
# define LEM_IN_H

# define ERR_DBG 1
# define STDIN 0

# include "libft.h"

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_room
{
	char			*command;
	char			*name;
	t_vect			*links;
	struct s_pos	pos;
}					t_room;

typedef struct		s_graph
{
	size_t			size;
	size_t			links;
	t_room			*start;
	t_room			*end;
	t_vect			*room_list;
	t_htable		*rooms;
}					t_graph;

/*
** FUNCTIONS
*/

void	init_graph(t_graph *graph);
int		parse_input(int *ants, t_graph *graph, char **file);
int		get_ants_nbr(char *input, int *ants);
int		record_room_if_valid(char **input, char **cmd, t_graph *graph);
int		record_link_if_valid(t_graph *graph, const char *link);
void	record_link(t_graph *graph, char *room_a, char *room_b);
t_room	*record_room(t_graph *graph, char **room_data, char **cmd);
void	lemin_perror(const char *msg);
void	print_links_for_all_rooms(t_graph *graph);
void	print_result(t_graph *graph, char *file);
void	print_all_rooms(t_graph *graph);
void	free_room(void *room);

#endif
