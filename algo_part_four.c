/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_part_four.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:12:18 by utilisateur       #+#    #+#             */
/*   Updated: 2025/07/30 23:42:57 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	combine_move(t_struct *env, t_move_info move)
{
	int	combined;
	int	i;

	if (move.can_combine)
	{
		combined = (move.cost_a < move.cost_b) ? move.cost_a : move.cost_b;
		i = 0;
		while (i++ < combined)
		{
			if (move.dir_a)
				double_rotate(env, env->c);
			else
				double_reverse_rotate(env, env->c);
			calculate_tail(env);
		}
		move.cost_a -= combined;
		move.cost_b -= combined;
	}
	exec_remaining(env, &move);
}

void	exec_remaining(t_struct *env, t_move_info *move)
{
	while (move->cost_a-- > 0)
	{
		if (move->dir_a)
			rotate(&env->head_a, &env->tail_a, env->a);
		else
			reverse_rotate(&env->head_a, &env->tail_a, env->a);
		calculate_tail(env);
	}
	while (move->cost_b-- > 0)
	{
		if (move->dir_b)
			rotate(&env->head_b, &env->tail_b, env->b);
		else
			reverse_rotate(&env->head_b, &env->tail_b, env->b);
		calculate_tail(env);
	}
}

void	final_sort(t_struct *env)
{
	t_move_info	move;

	while (env->head_b)
	{
		move = best_move(env);
		combine_move(env, move);
		push(&env->head_b, &env->head_a, env->a);
		calculate_tail(env);
	}
}

void	final_rotate(t_struct *env)
{
	t_stack	*min_node;
	int		min_pos;

	min_node = find_min(env->head_a);
	min_pos = get_position(env->head_a, min_node);
	if (is_sorted(env->head_a))
		return ;
	if (min_pos <= stack_size(env->head_a) / 2)
	{
		while (min_pos-- > 0)
		{
			rotate(&env->head_a, &env->tail_a, env->a);
			calculate_tail(env);
		}
	}
	else
	{
		while (min_pos++ < stack_size(env->head_a))
		{
			reverse_rotate(&env->head_a, &env->tail_a, env->a);
			calculate_tail(env);
		}
	}
}

int	algorithm(t_struct *env)
{
	int	size;

	size = stack_size(env->head_a);
	if (is_sorted(env->head_a))
		return (0);
	if (size <= 5)
	{
		if (size == 2)
			sort_two(env);
		else if (size == 3)
			sort_three(env);
		else if (size == 4 || size == 5)
			sort_four_five(env);
		return (0);
	}
	sort_push(env);
	if (stack_size(env->head_a) == 3)
		sort_three(env);
	else if (stack_size(env->head_a) == 2)
		sort_two(env);
	final_sort(env);
	final_rotate(env);
	if (!is_sorted(env->head_a))
	{
		reverse_rotate(&env->head_a, &env->tail_a, env->a);
		reverse_rotate(&env->head_a, &env->tail_a, env->a);
		swap(&env->head_a, env->a);
		rotate(&env->head_a, &env->tail_a, env->a);
		rotate(&env->head_a, &env->tail_a, env->a);
	}
	return (0);
}
