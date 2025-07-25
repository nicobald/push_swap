/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:47:49 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/25 11:56:43 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_move_cost
{
	int cost_a;
	int cost_b;
	int total_cost;
	int rotate_a;
	int rotate_b;
} t_move_cost;

typedef struct s_stack
{
	int value;
	int index;
	struct s_stack *next;
	struct s_stack *prev;
} t_stack;

typedef struct s_struct
{
	t_stack *head_a;
	t_stack *head_b;
	t_stack *node;
	t_stack *tmp;
	t_stack *tmp_b;
	t_stack *tail_a;
	t_stack *tail_b;
	t_stack *tmp_check_double;
	t_move_cost *cost;
	char **splited_nbr;
	int index_argv;
	int index_node_lst;
	int i_splited;
	int pos;
	char a;
	char b;
	char c;
} t_struct;


size_t ft_strlen(const char *str);
char **ft_split(char const *s, char c);
t_stack *ft_new_node(int value, int index);
void ft_lstadd_back_double_chained(t_stack **lst, t_stack *new);
void init_var(t_struct *env);
void free_splited_nbr(t_struct *env);
void ft_free_lst(t_struct *env);
int swap(t_stack **head, char stack_id);
int main(int argc, char **argv);
void push_swap_main(t_struct *env);
int check_nbr(char **split);
int fill_double_chain(t_struct *env, char **argv);
int ft_atoi(const char *str);
int check_same_nbr(t_struct *env);
int push(t_stack **head_source, t_stack **head_dest,
		 char stack_id);
int rotate(t_stack **head, t_stack **tail, char stack_id);
int reverse_rotate(t_stack **head, t_stack **tail,
				   char stack_id);
int double_swap(t_stack **head_a, t_stack **head_b,
				char stack_id);
int double_rotate(t_struct *env, char stack_id);
int double_reverse_rotate(t_struct *env, char stack_id);
int calculate_tail(t_struct *env);
int update_index_a(t_struct *env);
int update_index_b(t_struct *env);
void sort_three(t_struct *env);
void sort_two(t_struct *env);
int stack_size(t_stack *stack);
int is_sorted(t_stack *stack);
t_stack *find_min(t_stack *stack);
t_stack *find_max(t_stack *stack);
int get_position(t_stack *stack, t_stack *target);
void push_all_but_three(t_struct *env);
t_stack *find_target_in_a(t_stack *stack_a, int value_b);
t_move_cost calculate_move_cost(t_struct *env, t_stack *node_b);
t_stack *find_cheapest_move(t_struct *env, t_move_cost *best_cost);
void execute_rotations(t_struct *env, t_move_cost cost);
void final_rotation(t_struct *env);
void turk_algorithm(t_struct *env);


#endif
