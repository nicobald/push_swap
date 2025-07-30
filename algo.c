/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:46:49 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/31 00:09:24 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_struct *env)
{
	if (env->head_a->value > env->head_a->next->value)
		swap(&env->head_a, env->a);
	return ;
}

void	sort_three(t_struct *env)
{
	int	a;
	int	b;
	int	c;

	a = env->head_a->value;
	b = env->head_a->next->value;
	c = env->head_a->next->next->value;
	if (a > b && b < c && c > a)
		swap(&env->head_a, env->a);
	else if (a > b && b > c)
	{
		swap(&env->head_a, env->a);
		reverse_rotate(&env->head_a, &env->tail_a, env->a);
	}
	else if (a < b && b > c && c > a)
		reverse_rotate(&env->head_a, &env->tail_a, env->a);
	else if (a > b && b < c && c < a)
		rotate(&env->head_a, &env->tail_a, env->a);
	else if (a < b && b > c && c < a)
	{
		swap(&env->head_a, env->a);
		rotate(&env->head_a, &env->tail_a, env->a);
	}
	return ;
}

void	sort_four_five(t_struct *env)
{
	while (stack_size(env->head_a) > 3)
	{
		env->min = find_min(env->head_a)->value;
		while (env->head_a->value != env->min)
			rotate(&env->head_a, &env->tail_a, env->a);
		push(&env->head_a, &env->head_b, env->b);
	}
	sort_three(env);
	while (env->head_b)
	{
		env->node = find_pos(env->head_a, env->head_b->value);
		env->pos = get_position(env->head_a, env->node);
		while (env->head_a->value != env->node->value)
			rotate(&env->head_a, &env->tail_a, env->a);
		push(&env->head_b, &env->head_a, env->a);
	}
	while (!is_sorted(env->head_a))
		rotate(&env->head_a, &env->tail_a, env->a);
}


int	stack_size(t_stack *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}
