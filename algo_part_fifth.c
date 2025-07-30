/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_part_fifth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 22:19:14 by utilisateur       #+#    #+#             */
/*   Updated: 2025/07/30 23:54:52 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	bubble_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	*sort_array(t_stack *stack, int size)
{
	int	*arr;
	int	i;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (stack && i < size)
	{
		arr[i] = stack->value;
		stack = stack->next;
		i++;
	}
	bubble_sort(arr, size);
	return (arr);
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
