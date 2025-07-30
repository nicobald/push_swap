/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_part_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:14:54 by utilisateur       #+#    #+#             */
/*   Updated: 2025/07/30 23:06:57 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_push_chunk(t_struct *env)
{
	env->loop = stack_size(env->head_a);
	while (env->loop > 0 && env->pushed < env->target_push)
	{
		env->val = env->head_a->value;
		if (env->val >= env->min && env->val <= env->max)
		{
			push(&env->head_a, &env->head_b, env->b);
			calculate_tail(env);
			env->pushed++;
		}
		else
		{
			rotate(&env->head_a, &env->tail_a, env->a);
			calculate_tail(env);
		}
		env->loop--;
	}
	return ;
}

void	sort_push(t_struct *env)
{
	env->total_size = stack_size(env->head_a);
	env->sorted_vals = sort_array(env->head_a, env->total_size);
	env->chunk_size = env->total_size / 7;
	env->pushed = 0;
	env->target_push = env->total_size - 3;
	env->chunk = 0;
	while (env->chunk < 7 && env->pushed < env->target_push)
	{
		env->min = env->sorted_vals[env->chunk * env->chunk_size];
		if (env->chunk == 6)
			env->max = env->sorted_vals[env->total_size - 4];
		else
			env->max = env->sorted_vals[(env->chunk + 1) * env->chunk_size - 1];
		sort_push_chunk(env);
		env->chunk++;
	}
	free(env->sorted_vals);
	return ;
}

void	calc_cost_dir(int size, int pos, int *cost, int *dir)
{
	if (pos <= size / 2)
	{
		*cost = pos;
		*dir = 1;
	}
	else
	{
		*cost = size - pos;
		*dir = 0;
	}
	return ;
}
t_move_info calculate_cost(t_struct *env, t_stack *node_b)
{
	env->cost->node_b = node_b;
	env->cost->target_a = find_pos(env->head_a, node_b->value);
	env->size_a = stack_size(env->head_a);
	env->size_b = stack_size(env->head_b);
	env->pos = get_position(env->head_a, env->cost->target_a);
	env->pos_b = get_position(env->head_b, node_b);
	calc_cost_dir(env->size_a, env->pos, &env->cost->cost_a, &env->cost->dir_a);
	calc_cost_dir(env->size_b, env->pos_b, &env->cost->cost_b, &env->cost->dir_b);
	env->cost->can_combine = (env->cost->dir_a == env->cost->dir_b);
	if (env->cost->can_combine)
	{
		if (env->cost->cost_a > env->cost->cost_b)
			env->cost->total_cost = env->cost->cost_a;
		else
			env->cost->total_cost = env->cost->cost_b;
	}
	else
		env->cost->total_cost = env->cost->cost_a + env->cost->cost_b;
	return (*(env->cost));
}

t_move_info	best_move(t_struct *env)
{
	t_stack		*current_b;
	t_move_info	best_move;
	int			first;
	t_move_info	current_move;

	current_b = env->head_b;
	first = 1;
	while (current_b)
	{
		current_move = calculate_cost(env, current_b);
		if (first || current_move.total_cost < best_move.total_cost)
		{
			best_move = current_move;
			first = 0;
		}
		current_b = current_b->next;
	}
	return (best_move);
}
