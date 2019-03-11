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
	t_list			*path_ids;
	t_vect			*links;
	struct s_pos	pos;
}					t_room;

typedef struct		s_path
{
	size_t			length;
	int				id;
	int				has_end;
	int				is_stuck;
	t_list			*conflicts;
	t_dlist			*head;
}					t_path;

typedef struct		s_set
{
	size_t			nbr_of_paths;
	size_t			biggest;
	size_t			diff;
	int				id;
	t_list			*paths;
}					t_set;

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

typedef struct		s_bfs
{
	t_list			*all_paths;
	t_list			*end_paths;
	t_list			*end_sets;
	size_t			paths_nbr;
	size_t			end_paths_nbr;
	size_t			end_sets_nbr;
}					t_bfs;

/*
** FUNCTIONS
*/

/*
** PARSING
*/

int		parse_input(int *ants, t_graph *graph, char **file);
int		parse_line(t_graph *graph, int *ants, const char *line, char **cmd_list);

// GRAPH_UTILS
void	init_graph(t_graph *graph);
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

int		get_paths(t_graph *graph);

void	print_path(t_path *path);
void	print_set(t_set *set);
void	print_end_sets(t_bfs *bfs_data);

// PATH_UTILS
t_path	*init_new_path(int path_id);
void	path_set_path(t_path *path, t_dlist *head, size_t length);
int		path_add_room(t_path *path, t_room *room);
void	path_set_conflicts(t_path *path, t_list *conflicts);
int		path_add_conflict(t_path *path, int conflict_id);
t_path	*path_duplicate(t_path *origin, int new_id);
void	path_free_path(t_path *path);
void	path_free_conflicts(t_path *path);
void	path_free(t_path *path);
void	lst_free_path(t_path ***path);
int		path_get_id(t_path *path);
void	path_set_end(t_path *path);
int		path_has_end(t_path *path);
void	path_set_stuck(t_path *path);
int		path_is_stuck(t_path *path);
void	path_mark_visited(t_path *path);
int		path_get_conflicts(t_path *path);
int		path_has_conflict(t_path *path, int conflict_id);


//SET_UTILS
t_set	*init_new_set(int set_id);
void	set_free(t_set ***set);
int		set_add_path(t_set *set, t_path *path);
int		set_add_room_to_path(t_set *set, int path_id, t_room *room);
t_path	*set_get_path(t_set *set, int path_id);

// BFS_UTILS
t_bfs	*init_bfs_data(void);
int		bfs_add_path(t_bfs *bfs_data, t_path **path);
int		bfs_add_end_path(t_bfs *bfs_data, t_path **path);
int		bfs_add_set(t_bfs *bfs_data, t_set **set);
int		bfs_new_end_set(t_bfs *bfs_data, t_path **path);
void	bfs_free(t_bfs *bfs_data);

int		weight_graph(t_graph *graph);
/*
** IO
*/

void	print_result(t_graph *graph, char *file);
void	lemin_perror(int error_code, char *line);

#endif
