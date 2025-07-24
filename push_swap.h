/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:47:49 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/24 15:37:43 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// STRUCT
typedef struct s_cost
{
	int				max_b;
	int				max_a;
	int				cost_a;
	int				cost_b;
	int				direction_a;
	int				direction_b;
	int				index_a;
	int				index_b;
	int				cost_min;
	int				cost_tot;
}					t_cost;

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
	struct s_stack	*prev;
}					t_stack;

typedef struct s_struct
{
	t_stack			*head_a;
	t_stack			*head_b;
	t_stack			*node;
	t_stack			*tmp;
	t_stack			*tmp_b;
	t_stack			*tail_a;
	t_stack			*tail_b;
	t_stack			*tmp_check_double;
	t_cost			*cost;
	char			**splited_nbr;
	int				index_argv;
	int				index_node_lst;
	int				i_splited;
	int				pos;
	char			a;
	char			b;
	char			c;
}					t_struct;

// function

size_t				ft_strlen(const char *str);
char				**ft_split(char const *s, char c);
t_stack				*ft_new_node(int value, int index);
void				ft_lstadd_back_double_chained(t_stack **lst, t_stack *new);
void				init_var(t_struct *env);
void				free_splited_nbr(t_struct *env);
void				ft_free_lst(t_struct *env);
int					swap(t_stack **head, char stack_id);
int					main(int argc, char **argv);
int					check_nbr(char **split);
int					fill_double_chain(t_struct *env, char **argv);
int					ft_atoi(const char *str);
int					check_same_nbr(t_struct *env);
int					push(t_stack **head_source, t_stack **head_dest,
						char stack_id);
int					rotate(t_stack **head, t_stack **tail, char stack_id);
int					reverse_rotate(t_stack **head, t_stack **tail,
						char stack_id);
int					double_swap(t_stack **head_a, t_stack **head_b,
						char stack_id);
int					double_rotate(t_struct *env, char stack_id);
int					double_reverse_rotate(t_struct *env, char stack_id);
int					calculate_tail(t_struct *env);
int					update_index_a(t_struct *env);
int					update_index_b(t_struct *env);
int					found_max(t_stack **head_a);
void				sort_tree(t_struct *env);
void				sort_two(t_struct *env);
void				fill_stack_b(t_struct *env);
void				push_back(t_struct *env);
void				max_smaller(t_struct *env, int max, int min);
void				min_smaller(t_struct *env, int max, int min);
void				calculate_cost(t_struct *env);
void				calculate_stock_cost(t_struct *env);
void				push_back(t_struct *env);
void				move_same_time(t_struct *env);
int					found_min(t_stack **head_a);
int					calculate_insertion_cost(t_struct *env);

#endif
