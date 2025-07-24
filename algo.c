/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:46:49 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/24 15:40:12 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// create/use algo
// enlever toutes les valeurs de stack a et les mettre dans stack b sauf le
// + grand nombre + une valeur random
// pour chaque valeur de a tu cherche une valeur plus petite dans b par le haut et par le bas de la stack b
// repete l etape 2 tant que b n est pas vide
// faire un algo different pour 3 et 5

void	sort_two(t_struct *env)
{
	if (env->head_a->value > env->head_a->next->value)
		swap(&env->head_a, env->a);
	return ;
}

void	sort_tree(t_struct *env)
{
	int	first;
	int	second;
	int	third;

	first = env->head_a->value;
	second = env->head_a->next->value;
	third = env->head_a->next->next->value;
	if (first < second && second > third && third > first)
	{
		reverse_rotate(&env->head_a, &env->tail_a, env->a);
		swap(&env->head_a, env->a);
	}
	else if (first > second && second < third && third > first)
		swap(&env->head_a, env->a);
	else if (first < second && second > third && third < first)
		reverse_rotate(&env->head_a, &env->tail_a, env->a);
	else if (first > second && second > third && third < first)
	{
		rotate(&env->head_a, &env->tail_a, env->a);
		swap(&env->head_a, env->a);
	}
	else if (first > second && second < third && third < first)
		rotate(&env->head_a, &env->tail_a, env->a);
	return ;
}

int	found_max(t_stack **head_a)
{
	t_stack	*tmp;
	int		index_max;
	int		tmp_value;

	tmp = *head_a;
	while (tmp)
	{
		if (tmp->prev == NULL)
		{
			tmp_value = tmp->value;
			index_max = tmp->index;
		}
		if (tmp_value < tmp->value)
		{
			tmp_value = tmp->value;
			index_max = tmp->index;
		}
		tmp = tmp->next;
	}
	return (index_max);
}
int	found_min(t_stack **head_a)
{
	t_stack	*tmp;
	int		index_min;
	int		tmp_value;

	tmp = *head_a;
	while (tmp)
	{
		if (tmp->prev == NULL)
		{
			tmp_value = tmp->value;
			index_min = tmp->index;
		}
		if (tmp_value > tmp->value)
		{
			tmp_value = tmp->value;
			index_min = tmp->index;
		}
		tmp = tmp->next;
	}
	return (index_min);
}

void	fill_stack_b(t_struct *env)
{
	t_stack	*tmp;
	int		max;
	int		min;

	tmp = env->head_a;
	(void)tmp;
	max = found_max(&env->head_a);
	min = found_min(&env->head_a);
	if (max < min)
		max_smaller(env, max, min);
	if (min < max)
		min_smaller(env, max, min);
	tmp = env->head_a;
	while (tmp && tmp->next && tmp->next->next)
	{
		push(&env->head_a, &env->head_b, env->b);
		tmp = env->head_a;
	}
	return ;
}

void	max_smaller(t_struct *env, int max, int min)
{
	while (max-- && min--)
	{
		push(&env->head_a, &env->head_b, env->b);
		env->tmp = env->head_a;
	}
	rotate(&env->head_a, &env->tail_a, env->a);
	env->tmp = env->head_a;
	min--;
	while (min--)
	{
		push(&env->head_a, &env->head_b, env->b);
		env->tmp = env->head_a;
	}
	reverse_rotate(&env->head_a, &env->tail_a, env->a);
	swap(&env->head_a, env->a);
	rotate(&env->head_a, &env->tail_a, env->a);
	rotate(&env->head_a, &env->tail_a, env->a);
	env->tmp = env->head_a;
}
void	min_smaller(t_struct *env, int max, int min)
{
	while (min-- && max--)
	{
		push(&env->head_a, &env->head_b, env->b);
		env->tmp = env->head_a;
	}
	rotate(&env->head_a, &env->tail_a, env->a);
	env->tmp = env->head_a;
	max--;
	while (max--)
	{
		push(&env->head_a, &env->head_b, env->b);
		env->tmp = env->head_a;
	}
	rotate(&env->head_a, &env->tail_a, env->a);
	env->tmp = env->head_a;
}
void	calculate_cost(t_struct *env)
{
	if (!env || !env->cost)
		return ;
	env->cost->cost_min = INT_MAX;
	env->tmp_b = env->head_b;
	while (env->tmp_b)
	{
		env->cost->max_b = update_index_b(env);
		env->tmp_b = env->head_b;
		env->cost->max_a = update_index_a(env);
		env->tmp = env->head_a;
		if (env->tmp_b->index <= env->cost->max_b / 2)
			env->cost->cost_b = env->tmp_b->index;
		else if (env->tmp_b->index > env->cost->max_b / 2)
			env->cost->cost_b = env->cost->max_b - env->tmp_b->index;
		while (env->tmp && env->tmp->next)
		{
			calculate_stock_cost(env);
			env->tmp = env->tmp->next;
		}
		env->tmp_b = env->tmp_b->next;
	}
	return ;
}

void	calculate_stock_cost(t_struct *env)
{
	if (env->tmp->value < env->tmp_b->value
		&& env->tmp_b->value < env->tmp->next->value)
	{
		if (env->tmp->index <= env->cost->max_a / 2)
			env->cost->cost_a = env->tmp->index;
		else if (env->tmp->index > env->cost->max_a / 2)
			env->cost->cost_a = env->cost->max_a - env->tmp->index;
	}
	env->cost->cost_tot = env->cost->cost_a + env->cost->cost_b;
	if (env->cost->cost_tot < env->cost->cost_min)
	{
		if (env->tmp_b->index <= env->cost->max_b / 2)
			env->cost->direction_b = 0;
		else if (env->tmp_b->index > env->cost->max_b / 2)
			env->cost->direction_b = 1;
		if (env->tmp->index <= env->cost->max_a / 2)
			env->cost->direction_a = 0;
		else if (env->tmp->index > env->cost->max_a / 2)
			env->cost->direction_a = 1;
		env->cost->index_a = env->tmp->index;
		env->cost->index_b = env->tmp_b->index;
		env->cost->cost_min = env->cost->cost_tot;
	}
	return ;
}
void	push_back(t_struct *env)
{
	if (env->cost->direction_a == env->cost->direction_b)
		move_same_time(env);
	else if (env->cost->direction_a != env->cost->direction_b)
	{
		while (env->cost->index_b--)
		{
			if (env->cost->direction_b == 0)
				rotate(&env->head_b, &env->tail_b, env->b);
			else if (env->cost->direction_b == 1)
				reverse_rotate(&env->head_b, &env->tail_b, env->b);
			calculate_tail(env);
		}
		while (env->cost->index_a--)
		{
			if (env->cost->direction_a == 0)
				rotate(&env->head_a, &env->tail_a, env->a);
			else if (env->cost->direction_a == 1)
				reverse_rotate(&env->head_a, &env->tail_a, env->a);
			calculate_tail(env);
		}
	}
	push(&env->head_b, &env->head_a, env->a);
	return ;
}

void	move_same_time(t_struct *env)
{
	while (env->cost->index_a-- && env->cost->index_b--)
	{
		if (env->cost->direction_a == 0)
			double_rotate(env, env->c);
		else if (env->cost->direction_a == 1)
			double_reverse_rotate(env, env->c);
		calculate_tail(env);
	}
	while (env->cost->index_a || env->cost->index_b)
	{
		while (env->cost->index_b--)
		{
			if (env->cost->direction_b == 0)
				rotate(&env->head_b, &env->tail_b, env->b);
			else if (env->cost->direction_b == 1)
				reverse_rotate(&env->head_b, &env->tail_b, env->b);
			calculate_tail(env);
		}
		while (env->cost->index_a--)
		{
			if (env->cost->direction_a == 0)
				rotate(&env->head_a, &env->tail_a, env->a);
			else if (env->cost->direction_a == 1)
				reverse_rotate(&env->head_a, &env->tail_a, env->a);
			calculate_tail(env);
		}
	}
	return ;
}
