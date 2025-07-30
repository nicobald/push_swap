/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:46:49 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/30 13:52:33 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void sort_two(t_struct *env)
{
	if (env->head_a->value > env->head_a->next->value)
		swap(&env->head_a, env->a);
}

void sort_three(t_struct *env)
{
	int a;
	int b;
	int c;

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
}

void sort_four_five(t_struct *env)
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

void sort_four_five_pars (t_struct *env)
{
	if (env->head_b->value > env->min && env->head_b->value < env->max)
		{
			if (env->head_a->value > env->head_b->value && env->tail_a->value < env->head_b->value)
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

t_stack *find_max(t_stack *stack)
{
	t_stack *max_node;
	int max_value;

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

t_stack *find_pos(t_stack *stack_a, int value_b)
{
	t_stack *best_target;
	t_stack *current;
	int min_diff;
	int diff;

	best_target = NULL;
	current = stack_a;
	min_diff = INT_MAX;
	while (current)
	{
		if (current->value > value_b)
		{
			diff = current->value - value_b;
			if (diff < min_diff)
			{
				min_diff = diff;
				best_target = current;
			}
		}
		current = current->next;
	}
	if (!best_target)
		best_target = find_min(stack_a);
	return (best_target);
}
int *sort_array(t_stack *stack, int size)
{
    int *arr;
    int i;
    int j;
    int temp;
    t_stack *current;

    arr = malloc(sizeof(int) * size);
    i = 0;
    current = stack;
    while (current && i < size)
    {
        arr[i++] = current->value;
        current = current->next;
    }
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
    return (arr);
}

void sort_push(t_struct *env)
{
    int total_size;
    int *sorted_vals;
    int chunk_size;
    int pushed;
    int target_push;
    int chunk;
    int chunk_min;
    int chunk_max;
    int initial_size_a;
    int rotations;

    total_size = stack_size(env->head_a);
    sorted_vals = sort_array(env->head_a, total_size);
    chunk_size = total_size / 7;
    pushed = 0;
    target_push = total_size - 3;
    chunk = 0;

    while (chunk < 6 && pushed < target_push)
    {
        chunk_min = sorted_vals[chunk * chunk_size];
        if (chunk == 5)
            chunk_max = sorted_vals[total_size - 4];
        else
            chunk_max = sorted_vals[(chunk + 1) * chunk_size - 1];
        
        initial_size_a = stack_size(env->head_a);
        rotations = 0;
        
        while (rotations < initial_size_a && pushed < target_push)
        {
            if (env->head_a->value >= chunk_min && env->head_a->value <= chunk_max)
            {
                push(&env->head_a, &env->head_b, env->b);
                calculate_tail(env);
                pushed++;
            }
            else
            {
                rotate(&env->head_a, &env->tail_a, env->a);
                calculate_tail(env);
            }
            rotations++;
        }
        chunk++;
    }
    free(sorted_vals);
}


t_move_info calculate_cost(t_struct *env, t_stack *node_b)
{
	t_move_info info;
	int size_a;
	int size_b;
	int pos_a;
	int pos_b;

	info.node_b = node_b;
	info.target_a = find_pos(env->head_a, node_b->value);
	size_a = stack_size(env->head_a);
	size_b = stack_size(env->head_b);
	pos_a = get_position(env->head_a, info.target_a);
	pos_b = get_position(env->head_b, node_b);
	if (pos_a <= size_a / 2)
	{
		info.cost_a = pos_a;
		info.dir_a = 1;
	}
	else
	{
		info.cost_a = size_a - pos_a;
		info.dir_a = 0;
	}
	if (pos_b <= size_b / 2)
	{
		info.cost_b = pos_b;
		info.dir_b = 1;
	}
	else
	{
		info.cost_b = size_b - pos_b;
		info.dir_b = 0;
	}
	info.can_combine = (info.dir_a == info.dir_b);

	if (info.can_combine)
	{
		int combined_moves = (info.cost_a > info.cost_b) ? info.cost_a : info.cost_b;
		info.total_cost = combined_moves;
	}
	else
	{
		info.total_cost = info.cost_a + info.cost_b;
	}
	return (info);
}

t_move_info best_move(t_struct *env)
{
	t_stack *current_b = env->head_b;
	t_move_info best_move;
	int first = 1;

	while (current_b)
	{
		t_move_info current_move = calculate_cost(env, current_b);

		if (first || current_move.total_cost < best_move.total_cost)
		{
			best_move = current_move;
			first = 0;
		}
		current_b = current_b->next;
	}

	return (best_move);
}

void combine_move(t_struct *env, t_move_info move)
{
    int combined;
    int i;

    if (move.can_combine)
    {
        if (move.cost_a < move.cost_b)
            combined = move.cost_a;
        else
            combined = move.cost_b;
        
        i = 0;
        while (i < combined)
        {
            if (move.dir_a)
                double_rotate(env, env->c);
            else
                double_reverse_rotate(env, env->c);
            calculate_tail(env);
            i++;
        }
        move.cost_a -= combined;
        move.cost_b -= combined;
    }
    
    while (move.cost_a > 0)
    {
        if (move.dir_a)
            rotate(&env->head_a, &env->tail_a, env->a);
        else
            reverse_rotate(&env->head_a, &env->tail_a, env->a);
        move.cost_a--;
        calculate_tail(env);
    }
    
    while (move.cost_b > 0)
    {
        if (move.dir_b)
            rotate(&env->head_b, &env->tail_b, env->b);
        else
            reverse_rotate(&env->head_b, &env->tail_b, env->b);
        move.cost_b--;
        calculate_tail(env);
    }
}

void final_sort(t_struct *env)
{
	int size_b;
	while (env->head_b)
	{
		size_b = stack_size(env->head_b);
		if (size_b <= 5)
		{
			t_stack *max_b = env->head_b;
			t_stack *current = env->head_b;

			while (current)
			{
				if (current->value > max_b->value)
					max_b = current;
				current = current->next;
			}

			int pos_max = get_position(env->head_b, max_b);
			if (pos_max <= size_b / 2)
			{
				while (env->head_b != max_b)
				{
					rotate(&env->head_b, &env->tail_b, env->b);
					calculate_tail(env);
				}
			}
			else
			{
				while (env->head_b != max_b)
				{
					reverse_rotate(&env->head_b, &env->tail_b, env->b);
					calculate_tail(env);
				}
			}
		}

		t_move_info move = best_move(env);
		combine_move(env, move);
		push(&env->head_b, &env->head_a, env->a);
		calculate_tail(env);
	}
}

void final_rotate(t_struct *env)
{
	t_stack *min_node;
	int min_pos;
	int size;
	
	min_node = find_min(env->head_a);
	min_pos = get_position(env->head_a, min_node);
	size = stack_size(env->head_a);
	if (is_sorted(env->head_a))
		return;
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

void algorithm(t_struct *env)
{
	int size;

	size = stack_size(env->head_a);
	if (is_sorted(env->head_a))
		return;
	if (size <= 5)
	{
		if (size == 2)
			sort_two(env);
		else if (size == 3)
			sort_three(env);
		else if (size == 4 || size == 5)
			sort_four_five(env);
		return;
	}
	sort_push(env);
	if (stack_size(env->head_a) == 3)
		sort_three(env);
	else if (stack_size(env->head_a) == 2)
		sort_two(env);
	final_sort(env);
	final_rotate(env);
}
