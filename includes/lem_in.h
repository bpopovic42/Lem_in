#ifndef LEM_IN_H
# define LEM_IN_H

# define ERR_DBG 1
# define STDIN 0

# include "libft.h"

typedef struct		s_links
{
	size_t			links_nbr;
	struct s_room	*links;
}					t_links;

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_room
{
	char			*command;
	char			*name;
	struct s_links	*links;
	struct s_pos	pos;
}					t_room;

typedef struct		s_graph
{
	size_t			size;
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
t_room	*record_room(t_graph *graph, char **room_data, char **cmd);
void	lemin_perror(const char *msg);
void	free_room(void *room);

#endif
