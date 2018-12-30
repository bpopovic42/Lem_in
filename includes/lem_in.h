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

typedef struct		s_cmd
{
	char			*command;
	char			*room_name;
}					t_cmd;

typedef struct		s_graph
{
	size_t			nbr_of_rooms;
	size_t			nbr_of_links;
	t_room			*start;
	t_room			*end;
	t_vect			*room_list;
	t_vect			*command_list;
	t_htable		*rooms;
}					t_graph;

/*
** FUNCTIONS
*/

void	init_graph(t_graph *graph);
int		parse_input(int *ants, t_graph *graph, char **file);
int		parse_line(t_graph *graph, const char *line);
int		record_room_if_valid(t_graph *graph, char **input);
t_room	*record_room(t_graph *graph, char **room_data, char **cmd);
int		record_link_if_valid(t_graph *graph, const char *link);
void	record_link(t_graph *graph, char *room_a, char *room_b);
char	*get_last_command(t_graph *graph);
void	print_result(t_graph *graph, char *file);
void	lemin_perror(const char *msg);
void	free_graph(t_graph *graph);
void	free_room(void *room);

#endif
