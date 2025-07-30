/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_part_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:10:41 by utilisateur       #+#    #+#             */
/*   Updated: 2025/07/30 22:18:15 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*find_min(t_stack *stack)
{
	t_stack	*min_node;
	int		min_value;

	min_node = stack;
	min_value = stack->value;
	while (stack)
	{
		if (stack->value < min_value)
		{
			min_value = stack->value;
			min_node = stack;
		}
		stack = stack->next;
	}
	return (min_node);
}

t_stack	*find_max(t_stack *stack)
{
	t_stack	*max_node;
	int		max_value;

	max_node = stack;
	max_value = stack->value;
	while (stack)
	{
		if (stack->value > max_value)
		{
			max_value = stack->value;
			max_node = stack;
		}
		stack = stack->next;
	}
	return (max_node);
}

int	get_position(t_stack *stack, t_stack *target)
{
	int	pos;

	pos = 0;
	while (stack && stack != target)
	{
		pos++;
		stack = stack->next;
	}
	return (pos);
}

t_stack	*find_min_node(t_stack *a)
{
	t_stack	*min;

	min = a;
	while (a)
	{
		if (a->value < min->value)
			min = a;
		a = a->next;
	}
	return (min);
}

t_stack	*find_pos(t_stack *a, int b)
{
	t_stack	*tmp;
	t_stack	*best;
	int		diff;
	int		best_diff;

	tmp = a;
	best = NULL;
	best_diff = INT_MAX;
	while (tmp)
	{
		diff = tmp->value - b;
		if (diff > 0 && diff < best_diff)
		{
			best_diff = diff;
			best = tmp;
		}
		tmp = tmp->next;
	}
	if (best)
		return (best);
	return (find_min_node(a));
}
