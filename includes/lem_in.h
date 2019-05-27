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

typedef struct		s_solution
{
	int				value;
	int				nbr_of_paths;
	int				diff;
	int				longest_path_size;
}					t_solution;

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct	s_bmap
{
	size_t		size;
	int			*bits;
}				t_bmap;

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

typedef struct		s_path
{
	t_room			*src;
	t_room			*last_ant;
	int				ants;
}					t_path;

typedef struct		s_output
{
	int				nbr_of_paths;
	int				longest_path_len;
	t_path			**paths;
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

/*
** PARSING
*/

int		parse_input(int *ants, t_graph *graph, t_file *file);
int		parse_line(t_graph *graph, int *ants, const char *line, char **cmd_list);

// GRAPH_UTILS
int		init_graph(t_graph *graph);
void	free_graph(t_graph *graph);

// ROOM_UTILS
t_room	*new_room(char *name, char **cmd, t_pos *coord);
void	free_room(void *room);
void	free_room_ptr(void *data, size_t data_size);

// RECORD LINK
int		record_link_if_valid(t_graph *graph, const char *link);
int		record_link(t_graph *graph, char *room_a, char *room_b);

// RECORD ROOM
int		record_room_if_valid(t_graph *graph, char **input);
t_room	*record_room(t_graph *graph, char **room_data);

// FILE UTILS
int		init_file(t_file **file);
void	free_file(t_file *file);

/*
** ALGO
*/

int		weight_graph(t_queue *bfs, t_room *src, t_room *target);
int		get_best_paths(t_graph *graph, t_solution *solution);
int		compute_solution(t_graph *graph, t_list *start_rooms, t_solution *solution, int ants);
void	clean_weight(t_graph *graph);
void	clean_graph(t_graph *graph);
int		break_link(t_room *initial);
void	init_solution(t_solution *solution);

int		init_bfs_queue(t_queue **bfs, size_t nbr_of_rooms);
void	bfs_add(t_queue *bfs, t_room *room);
t_room	*bfs_pop(t_queue *bfs);
void	free_bfs_queue(t_queue **bfs);

t_bmap	*ft_bitmap_new(size_t binary_size);
void	ft_bitmap_set_bit(t_bmap *bmap, size_t bit);
void	ft_bitmap_clear_bit(t_bmap *bmap, size_t bit);
int		ft_bitmap_has_bit(t_bmap *bmap, size_t bit);
t_bmap	*ft_bitmap_dup(t_bmap *bmap);

int		print_ants(int ants, t_room *start, t_room *end);
t_list	*get_sorted_start_rooms(t_room *start);

void	clean_previous_solution_marks(t_list *start_rooms);
void	replace_solution(t_list *initial_rooms, t_solution *old, t_solution *new);


void	move_ants(t_path *path, int *ants_count, int *first_ant);

/*
** IO
*/

int		init_output(t_output **output);
int		get_output_data(t_output *out, t_room *start);
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

#endif
