/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:03 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/25 11:55:27 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	swap(t_stack **head, char stack_id)
{
	t_stack	*tmp;
	t_stack	*tmp_next;

	if (!(*head) || !(*head)->next)
		return (1);
	tmp = (*head);
	tmp_next = tmp->next;
	tmp->next = tmp_next->next;
	tmp_next->next = tmp;
	tmp_next->prev = NULL;
	tmp->prev = tmp_next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp;
	*head = tmp_next;
	if (stack_id == 'a')
		write(1, "sa\n", 3);
	if (stack_id == 'b')
		write(1, "sb\n", 3);
	return (0);
}
int	push(t_stack **head_source, t_stack **head_dest, char stack_id)
{
	t_stack *tmp;

	if (!(*head_source))
		return (1);
	tmp = *head_source;
	*head_source = (*head_source)->next;
	if (*head_source)
		(*head_source)->prev = NULL;
	tmp->next = *head_dest;
	if (*head_dest)
		(*head_dest)->prev = tmp;
	*head_dest = tmp;
	tmp->prev = NULL;
	if (stack_id == 'a')
		write(1, "pa\n", 3);
	if (stack_id == 'b')
		write(1, "pb\n", 3);
	return (0);
}
int    rotate(t_stack **head, t_stack **tail, char stack_id)
{
    t_stack    *tmp;

    if (!(*head) || !(*head)->next)
        return (1);
    tmp = *head;
    *head = (*head)->next;
    (*head)->prev = NULL;
    tmp->prev = *tail;
    (*tail)->next = tmp;
    *tail = (*tail)->next;
    (*tail)->next = NULL;
	if (stack_id == 'a')
		write(1, "ra\n", 3);
	if (stack_id == 'b')
		write(1, "rb\n", 3);
    return (0);
}
int	reverse_rotate(t_stack **head, t_stack **tail, char stack_id)
{
	t_stack *tmp;

	if (!(*head) || !(*head)->next)
		return (1);
	tmp = *tail;
	*tail = (*tail)->prev;
	(*tail)->next = NULL;
	tmp->prev = NULL;
	tmp->next = *head;
	(*head)->prev = tmp;
	*head = tmp;
	if (stack_id == 'a')
		write(1, "rra\n", 4);
	if (stack_id == 'b')
		write(1, "rrb\n", 4);
	return (0);
}
