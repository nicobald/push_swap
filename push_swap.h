/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:47:49 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/31 10:03:30 by utilisateur      ###   ########.fr       */
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

typedef struct s_chunk
{
	int				min_val;
	int				max_val;
	int				priority;
}					t_chunk;

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
	struct s_stack	*prev;
}					t_stack;

typedef struct s_move_info
{
	int				cost_a;
	int				cost_b;
	int				total_cost;
	int				dir_a;
	int				dir_b;
	int				can_combine;
	t_stack			*target_a;
	t_stack			*node_b;
}					t_move_info;

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
	t_move_info		*cost;
	char			**splited_nbr;
	char			a;
	char			b;
	char			c;
	int				index_argv;
	int				index_node_lst;
	int				i_splited;
	int				total_size;
	int				*sorted_vals;
	int				chunk_size;
	int				pushed;
	int				target_push;
	int				min;
	int				max;
	int				chunk;
	int				loop;
	int				val;
	int				size_a;
	int				size_b;
	int				pos;
	int				pos_b;
}					t_struct;

//Parsing
size_t				ft_strlen(const char *str);
t_stack				*ft_new_node(int value, int index);
char				**ft_split(char const *s, char c);
void				ft_lstadd_back_double_chained(t_stack **lst, t_stack *new);
void				init_var(t_struct *env);
void				free_splited_nbr(t_struct *env);
void				ft_free_lst(t_struct *env);
void				push_swap_main(t_struct *env);
int					main(int argc, char **argv);
int					check_nbr(char **split);
int					fill_double_chain(t_struct *env, char **argv);
int					ft_atoi(const char *str);
int					check_same_nbr(t_struct *env);
int					calculate_tail(t_struct *env);
int					update_index_a(t_struct *env);
int					update_index_b(t_struct *env);

// Operation
int					swap(t_stack **head, char stack_id);
int					push(t_stack **head_source, t_stack **head_dest,
						char stack_id);
int					rotate(t_stack **head, t_stack **tail, char stack_id);
int					reverse_rotate(t_stack **head, t_stack **tail,
						char stack_id);
int					double_swap(t_stack **head_a, t_stack **head_b,
						char stack_id);
int					double_rotate(t_struct *env, char stack_id);
int					double_reverse_rotate(t_struct *env, char stack_id);

//Algo
t_stack				*find_min_node(t_stack *a);
t_stack				*find_min(t_stack *stack);
t_stack				*find_max(t_stack *stack);
t_stack				*find_pos(t_stack *stack_a, int value_b);
t_move_info			calculate_cost(t_struct *env, t_stack *node_b);
t_move_info			best_move(t_struct *env);
int					algorithm(t_struct *env);
int					stack_size(t_stack *stack);
int					is_sorted(t_stack *stack);
int					get_position(t_stack *stack, t_stack *target);
int					*sort_array(t_stack *stack, int size);
void				sort_three(t_struct *env);
void				sort_two(t_struct *env);
void				sort_push(t_struct *env);
void				combine_move(t_struct *env, t_move_info move);
void				final_sort(t_struct *env);
void				final_rotate(t_struct *env);
void				sort_four_five_pars(t_struct *env);
void				sort_four_five(t_struct *env);
void				bubble_sort(int *arr, int size);
void				sort_push_chunk(t_struct *env);
void				calc_cost_dir(int size, int pos, int *cost, int *dir);
void				exec_remaining(t_struct *env, t_move_info *move);
void 				sort_last_two(t_struct *env);

#endif
