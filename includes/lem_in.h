#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

/*
** DEFINES
*/

# define LMN_BUFF_SIZE 15000
# define ERR_DBG 1
# define STDIN 0
# define EINVANT	1
# define ENEROOM	2
# define ENELINK	3
# define EINVMAP	4
# define ENOPATH	5
# define EINVANT_MSG "Invalid number of ants."
# define ENEROOM_MSG "Invalid number of rooms."
# define ENELINK_MSG "Invalid number of links."
# define EINVMAP_MSG "Invalid map."
# define ENOPATH_MSG "No valid path."

/*
** STRUCTURES
*/

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct	s_file
{
	char		*data;
	size_t		capacity;
	size_t		size;
}				t_file;

typedef struct		s_room
{
	char			*command;
	char			*name;
	int				end_distance;
	int				start_distance;
	int				final_distance;
	int				blocked;
	int				pid;
	int				cleaned;
	int				recorded;
	struct s_room	*from;
	struct s_room	*to;
	struct s_room	*solution_to;
	struct s_room	*solution_from;
	int				solution_len;
	int				is_solution;
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
	int				ants;
}					t_path;

typedef struct	s_route
{
	t_score		*score;
	t_list		*paths;
}				t_route;


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

/*******************************************************************************
*********************************** PARSING ************************************
*******************************************************************************/

/*
** parse_input.c
*/

int		parse_input(int *ants, t_graph *graph, t_file *file);

/*
** file_append.c
*/

int		file_append(t_file *file, char *line);

/*
** parse_line.c
*/

int		parse_line(t_graph *graph, int *ants, const char *line, char **cmd_list);

/*
** parse_line_utils.c
*/

int		line_is_comment(const char *line);
int		line_is_command(const char *line);
int		line_is_link(const char *line);
int		line_is_room(const char *line);

// GRAPH_UTILS
int		init_graph(t_graph *graph);
void	free_graph(t_graph *graph);

/*
** room_utils.c
*/

t_room	*new_room(char *name, t_pos *coord);
void	free_room(t_room **room);
void	free_room_ptr(void *data, size_t data_size);

/*
** parse_link.c
*/

int		parse_link(t_graph *graph, const char *link);

/*
** parse_room.c
*/

int		parse_room(t_graph *graph, const char *line);

/*
** create_room_if_valid.c
*/

int		create_room_if_valid(char **room_data, t_room **room);

/*
** room_has_conflict.c
*/

int		room_has_conflict(t_graph *graph, t_room *room);

/*
** parse_command.c
*/

int		parse_command(t_graph *graph, const char *cmd, char **cmd_list);

/*
** data_access_utils.c
*/

t_room	*get_room_from_node(t_node *node);

// FILE UTILS
int		init_file(t_file *file);
void	free_file(t_file *file);

/*
** ALGO
*/

int		get_initial_paths(t_graph *graph, t_queue *bfs, t_list *paths);
int		weight_graph(t_queue *bfs, t_room *src, t_room *target);
void	clean_weight(t_graph *graph);
void	clean_graph(t_graph *graph);
int		break_link(t_path *path);
int		init_bfs_queue(t_queue **bfs, size_t nbr_of_rooms);
void	bfs_add(t_queue *bfs, t_room *room);
t_room	*bfs_pop(t_queue *bfs);
void	free_bfs_queue(t_queue **bfs);
int		print_ants(int ants, t_list *paths, t_room *end);
void	sort_paths(t_list *paths);
void	move_ants(t_path *path, int *ants_count, int *first_ant);

/*
** IO
*/

int		init_output(t_output **output);
void	get_output_data(t_output *out);
void	free_output(t_output **output);

void	print_result(t_graph *graph, char *file);
void	lemin_perror(int error_code, char *line);

/*
** COMMON
*/

int		room_is_end(t_room *room);
int		room_is_start(t_room *room);
int		room_has_multiple_links(t_room *room);
int		room_is_end_connected(t_room *room);

/*
** link_utils.c
*/

int		link_add(t_graph *graph, t_room *a, t_room *b);
int		room_has_link(t_room *room_a, t_room *room_b);

/*
** ALGO 2
*/


t_path	*get_path_from_node(t_node *path_container);
int		find_best_route(t_graph *graph, t_route *route, t_queue *bfs);
int		get_best_route(t_graph *graph, t_route *route);
void	get_new_score(t_route *route, t_score **new_score);
void	mark_next_paths(t_graph *graph, t_list *paths, t_queue *bfs);
void	mark_path(t_path *path);
void	sort_paths_by_head_distance(t_list *paths);
int		update_score(t_graph *graph, t_route *route);

// route_utils.c

int		init_route(t_route *route);
void	free_route(t_route *route);

// path_utils.c

void	free_path(t_path **path);
t_path	*path_new();
void	path_set_head(t_path *path, t_room *head);
void	path_set_final_length(t_path *path, int final_length);
void	path_set_length(t_path *path, int length);

// score_utils.c

t_score	*score_new();
void	free_score(t_score **score);

// update_paths_length.c

void	update_paths_length(t_list *paths);

#endif
