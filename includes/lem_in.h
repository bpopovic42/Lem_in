/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 08:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 20:31:13 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "lem_in_structs.h"

# define LMN_BUFF_SIZE	15000
# define ERR_DBG		1
# define DBG_PRINT		0
# define STDIN			0
# define EINVANT		1
# define ENEROOM		2
# define ENELINK		3
# define EINVMAP		4
# define ENOPATH		5
# define EINVANT_MSG	"Invalid number of ants."
# define ENEROOM_MSG	"Invalid number of rooms."
# define ENELINK_MSG	"Invalid number of links."
# define EINVMAP_MSG	"Invalid map."
# define ENOPATH_MSG	"No valid path."
# define START_CMD		"##start"
# define END_CMD		"##end"
# define HTABLE_SIZE	1000

/*
** PARSING
*/

int		parse_input(int *ants, t_graph *graph, t_file *file);
int		parse_line(t_graph *graph, int *ants, const char *line, char **cmds);
int		line_is_comment(const char *line);
int		line_is_command(const char *line);
int		line_is_link(const char *line);
int		line_is_room(const char *line);
int		parse_command(t_graph *graph, const char *cmd, char **cmds);
int		parse_room(t_graph *graph, const char *line);
int		parse_link(t_graph *graph, const char *link);
int		file_append(t_file *file, char *line);
t_room	*new_room(char *name, t_pos *coord);
void	free_room(t_room **room);
void	free_room_ptr(void *data, size_t data_size);
int		create_room_if_valid(char **room_data, t_room **room);
int		room_has_conflict(t_graph *graph, t_room *room);
int		init_graph(t_graph *graph);
void	free_graph(t_graph *graph);

/*
** COMMON
*/

t_room	*get_room_from_node(t_node *node);
t_path	*get_path_from_node(t_node *path_container);
void	print_dbg(int is_msg_last, const char *fmt_msg, ...);
int		init_file(t_file *file);
void	free_file(t_file *file);
int		link_add(t_graph *graph, t_room *a, t_room *b);
int		room_has_link(t_room *room_a, t_room *room_b);
int		room_is_end(t_room *room);
int		room_is_start(t_room *room);
int		room_has_multiple_links(t_room *room);
int		room_is_end_connected(t_room *room);

/*
** ALGO
*/

int		init_bfs_queue(t_queue **bfs, size_t nbr_of_rooms);
void	free_bfs_queue(t_queue **bfs);
void	bfs_add(t_queue *bfs, t_room *room);
t_room	*bfs_pop(t_queue *bfs);
int		break_link(t_path *path);
int		find_best_route(t_graph *graph, t_route *route, t_queue *bfs);
int		get_best_route(t_graph *graph, t_route *route);
void	get_new_score(t_route *route, t_score *new_score);
void	clean_graph(t_graph *graph);
void	clean_weight(t_graph *graph);
void	reweight_graph(t_graph *graph, t_queue *bfs);
void	mark_next_paths(t_graph *graph, t_list *paths, t_queue *bfs);
void	mark_path(t_path *path);
void	free_path(t_path **path);
void	free_path_from_node(t_path ***path);
t_path	*path_new();
void	path_set_head(t_path *path, t_room *head);
void	path_set_final_length(t_path *path, int final_length);
void	path_set_length(t_path *path, int length);
int		init_route(t_route *route);
void	free_route(t_route *route);
t_score	*score_new(void);
void	free_score(t_score **score);
void	init_score(t_score *score);
void	sort_paths_by_head_distance(t_list *paths);
int		update_score(t_graph *graph, t_route *route);
void	mark_new_route(t_route *route);
void	path_remove_recorded_mark(t_path ***path_container);
void	path_remove_solution_mark(t_path ***path_container);

/*
** OUTPUT
*/

void	lemin_perror(int error_code, char *line);
void	move_ants(t_path *path, int *ants_count, int *first_ant);
int		print_ants(t_graph *graph, t_route *route);
void	print_dbg(int is_msg_last, const char *fmt_msg, ...);

#endif
