/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:46:49 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/30 23:04:31 by utilisateur      ###   ########.fr       */
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
	if (stack_size(env->head_a) == 5)
		push(&env->head_a, &env->head_b, env->b);
	push(&env->head_a, &env->head_b, env->b);
	sort_three(env);
	env->min = find_min(env->head_a)->value;
	env->max = find_max(env->head_a)->value;
	while (env->head_b)
		sort_four_five_pars(env);
	while (env->head_a->value != env->min)
		rotate(&env->head_a, &env->tail_a, env->a);
	return ;
}

void	sort_four_five_pars(t_struct *env)
{
	if (env->head_b->value > env->min && env->head_b->value < env->max)
	{
		if (env->head_a->value > env->head_b->value
			&& env->tail_a->value < env->head_b->value)
			push(&env->head_b, &env->head_a, env->a);
		else
			rotate(&env->head_a, &env->tail_a, env->a);
	}
	else if (env->head_b->value < env->min)
	{
		if (env->head_a->value == env->min)
			push(&env->head_b, &env->head_a, env->a);
		else
			rotate(&env->head_a, &env->tail_a, env->a);
	}
	else if (env->head_b->value > env->max)
	{
		if (env->head_a->value == env->max)
		{
			rotate(&env->head_a, &env->tail_a, env->a);
			push(&env->head_b, &env->head_a, env->a);
		}
		else
			rotate(&env->head_a, &env->tail_a, env->a);
	}
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
