#ifndef LEM_IN_H
# define LEM_IN_H

# define STDIN 0

# include "libft.h"

typedef struct		s_links
{
	size_t			links_nbr;
	struct s_room	*links;
}					t_links;

typedef struct		s_pos
{
	size_t			x;
	size_t			y;
}					t_pos;

typedef struct		s_room
{
	char			*comment;
	char			*name;
	struct s_links	*links;
	struct s_pos	*position;
}					t_room;

typedef struct		s_graph
{
	size_t			size;
	t_vect			*rooms;
}					t_graph;

/*
** FUNCTIONS
*/

void	init_graph(t_graph *graph);
char	**get_input();
int		get_ants_nbr(char **input, unsigned int *ants);
int		get_rooms(char **input, t_graph *graph);

#endif
