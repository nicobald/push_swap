/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:46:49 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/25 11:58:55 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int stack_size(t_stack *stack)
{
	int size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

int is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

t_stack *find_min(t_stack *stack)
{
	t_stack *min_node;
	int min_value;

	if (!stack)
		return (NULL);
	min_value = stack->value;
	min_node = stack;
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

t_stack *find_max(t_stack *stack)
{
	t_stack *max_node;
	int max_value;

	if (!stack)
		return (NULL);
	max_value = stack->value;
	max_node = stack;
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

int get_position(t_stack *stack, t_stack *target)
{
	int pos;

	pos = 0;
	while (stack && stack != target)
	{
		pos++;
		stack = stack->next;
	}
	return (pos);
}

void sort_two(t_struct *env)
{
	if (env->head_a->value > env->head_a->next->value)
		swap(&env->head_a, env->a);
}

void sort_three(t_struct *env)
{
	int first;
	int second;
	int third;

	first = env->head_a->value;
	second = env->head_a->next->value;
	third = env->head_a->next->next->value;

	if (first > second && second < third && third > first)
		swap(&env->head_a, env->a);
	else if (first > second && second > third && third < first)
	{
		swap(&env->head_a, env->a);
		reverse_rotate(&env->head_a, &env->tail_a, env->a);
	}
	else if (first < second && second > third && third > first)
		reverse_rotate(&env->head_a, &env->tail_a, env->a);
	else if (first > second && second < third && third < first)
		rotate(&env->head_a, &env->tail_a, env->a);
	else if (first < second && second > third && third < first)
	{
		swap(&env->head_a, env->a);
		rotate(&env->head_a, &env->tail_a, env->a);
	}
}

void push_all_but_three(t_struct *env)
{
	int size;
	int pushed;

	size = stack_size(env->head_a);
	pushed = 0;

	while (size > 3 && pushed < size - 3)
	{
		push(&env->head_a, &env->head_b, env->b);
		calculate_tail(env);
		pushed++;
	}
}

t_stack *find_target_in_a(t_stack *stack_a, int value_b)
{
	t_stack *target;
	t_stack *current;
	int closest_bigger;

	target = NULL;
	closest_bigger = INT_MAX;
	current = stack_a;

	while (current)
	{
		if (current->value > value_b && current->value < closest_bigger)
		{
			closest_bigger = current->value;
			target = current;
		}
		current = current->next;
	}
	if (!target)
		target = find_min(stack_a);

	return (target);
}

t_move_cost calculate_move_cost(t_struct *env, t_stack *node_b)
{
	t_move_cost cost;
	t_stack *target_a;
	int pos_a;
	int pos_b;
	int size_a;
	int size_b;

	target_a = find_target_in_a(env->head_a, node_b->value);
	pos_a = get_position(env->head_a, target_a);
	pos_b = get_position(env->head_b, node_b);
	size_a = stack_size(env->head_a);
	size_b = stack_size(env->head_b);
	if (pos_a <= size_a / 2)
	{
		cost.cost_a = pos_a;
		cost.rotate_a = 1;
	}
	else
	{
		cost.cost_a = size_a - pos_a;
		cost.rotate_a = 0;
	}
	if (pos_b <= size_b / 2)
	{
		cost.cost_b = pos_b;
		cost.rotate_b = 1;
	}
	else
	{
		cost.cost_b = size_b - pos_b;
		cost.rotate_b = 0;
	}
	cost.total_cost = cost.cost_a + cost.cost_b;
	return (cost);
}

t_stack *find_cheapest_move(t_struct *env, t_move_cost *best_cost)
{
	t_stack *current_b;
	t_stack *cheapest_node;
	t_move_cost current_cost;

	current_b = env->head_b;
	cheapest_node = current_b;
	*best_cost = calculate_move_cost(env, current_b);

	while (current_b)
	{
		current_cost = calculate_move_cost(env, current_b);
		if (current_cost.total_cost < best_cost->total_cost)
		{
			*best_cost = current_cost;
			cheapest_node = current_b;
		}
		current_b = current_b->next;
	}

	return (cheapest_node);
}

void execute_rotations(t_struct *env, t_move_cost cost)
{
	if (cost.rotate_a == cost.rotate_b)
	{
		while (cost.cost_a > 0 && cost.cost_b > 0)
		{
			if (cost.rotate_a)
				double_rotate(env, env->c);
			else
				double_reverse_rotate(env, env->c);
			cost.cost_a--;
			cost.cost_b--;
			calculate_tail(env);
		}
	}
	while (cost.cost_a > 0)
	{
		if (cost.rotate_a)
			rotate(&env->head_a, &env->tail_a, env->a);
		else
			reverse_rotate(&env->head_a, &env->tail_a, env->a);
		cost.cost_a--;
		calculate_tail(env);
	}
	while (cost.cost_b > 0)
	{
		if (cost.rotate_b)
			rotate(&env->head_b, &env->tail_b, env->b);
		else
			reverse_rotate(&env->head_b, &env->tail_b, env->b);
		cost.cost_b--;
		calculate_tail(env);
	}
}

void final_rotation(t_struct *env)
{
	t_stack *min_node;
	int min_pos;
	int size;

	min_node = find_min(env->head_a);
	min_pos = get_position(env->head_a, min_node);
	size = stack_size(env->head_a);

	if (min_pos <= size / 2)
	{
		while (min_pos > 0)
		{
			rotate(&env->head_a, &env->tail_a, env->a);
			min_pos--;
			calculate_tail(env);
		}
	}
	else
	{
		while (min_pos < size)
		{
			reverse_rotate(&env->head_a, &env->tail_a, env->a);
			min_pos++;
			calculate_tail(env);
		}
	}
}

void	turk_algorithm(t_struct *env)
{
	t_move_cost	best_cost;

	push_all_but_three(env);
	if (stack_size(env->head_a) == 3)
		sort_three(env);
	else if (stack_size(env->head_a) == 2)
		sort_two(env);
	while (env->head_b)
	{
		find_cheapest_move(env, &best_cost);
		execute_rotations(env, best_cost);
		push(&env->head_b, &env->head_a, env->a);
		calculate_tail(env);
	}
	final_rotation(env);
}
