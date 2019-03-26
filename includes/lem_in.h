#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

/*
** DEFINES
*/

# define ERR_DBG 1
# define STDIN 0
# define EINVANT	1
# define ENEROOM	2
# define ENELINK	3
# define EINVMAP	4
# define EINVANT_MSG "Invalid number of ants."
# define ENEROOM_MSG "Invalid number of rooms."
# define ENELINK_MSG "Invalid number of links."
# define EINVMAP_MSG "Invalid map."

/*
** STRUCTURES
*/

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_room
{
	char			*command;
	char			*name;
	int				depth;
	int				start_len;
	int				start_id;
	int				end_len;
	int				end_id;
	t_vect			*links;
	struct s_pos	pos;
}					t_room;

typedef struct		s_graph
{
	size_t			nbr_of_rooms;
	size_t			nbr_of_links;
	t_room			*start;
	t_room			*end;
	t_vect			*room_list;
	t_htable		*rooms;
	char			*last_command;
}					t_graph;

typedef struct		s_path
{
	size_t			size;
	int				path_id;
	t_room			*head;
}					t_path;

/*
** PARSING
*/

int		parse_input(int *ants, t_graph *graph, char **file);
int		parse_line(t_graph *graph, int *ants, const char *line, char **cmd_list);

// GRAPH_UTILS
int		init_graph(t_graph *graph);
void	free_graph(t_graph *graph);

// ROOM_UTILS
t_room	*new_room(char *name, char **cmd, t_pos *coord);
void	free_room(void *room);
int		room_has_id(t_room *room, int id);
int		room_is_end(t_room *room);
int		room_is_start(t_room *room);

// RECORD LINK
int		record_link_if_valid(t_graph *graph, const char *link);
int		record_link(t_graph *graph, char *room_a, char *room_b);

// RECORD ROOM
int		record_room_if_valid(t_graph *graph, char **input);
t_room	*record_room(t_graph *graph, char **room_data);

/*
** ALGO
*/

int		get_best_route(t_graph *graph);
int		weight_graph(t_room *target);
t_list	*get_paths(t_room *source, int is_start);
int		mark_paths(t_list *source, int is_start);
int		**get_paths_matrix(t_list *start_paths, t_list *end_paths);
void	get_best_combinations_from_matrix(int **matrix, size_t x_size, size_t y_size);

//DBG


void	dbg_print_next_rooms(t_room *target, int from_start);
void	dbg_print_paths(t_list *path_list);
void	dbg_array_print(int **matrix, int x, int y);

/*
** IO
*/

void	print_result(t_graph *graph, char *file);
void	lemin_perror(int error_code, char *line);

#endif
