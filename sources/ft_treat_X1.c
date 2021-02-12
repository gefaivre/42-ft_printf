/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_X1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gefaivre <gefaivre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 13:41:47 by gefaivre          #+#    #+#             */
/*   Updated: 2021/01/01 13:41:47 by gefaivre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"


void	ft_space_X_return(t_struct *spf)
{
	if (spf->point_2 > 0 || spf->zero > 0)
		ft_put_char_count('0', spf);
	else
		ft_put_char_count(' ', spf);
	spf->num2--;
}

void	ft_first_treat_X(unsigned int nb, t_struct *spf)
{
	if ((spf->num1 && spf->num2 && spf->minus)
	|| (spf->num1 && spf->num2 > -1 && spf->minus && spf->wildcard))
		ft_treat_X_return(nb, spf);
	else
		ft_treat_X(nb, spf);
}

void	ft_treat_X_return(unsigned int nb, t_struct *spf)
{
	spf->size = ft_len_base(nb, "0123456789ABCDEF");
	if (nb == 0)
		spf->size = 1;
	spf->m_m[1] = ft_max(spf->size, spf->num2);
	while (spf->num2 > spf->size)
		ft_space_x_return(spf);
	if (!((((spf->point_1 == 1 && spf->num1 < 0) || (spf->point_2 == 1
	&& spf->num2 < 0 && spf->wildcard == 0)) || (spf->point_2 && spf->wildcard
	&& spf->num2 == 0)) && nb == 0) || (spf->point_1 && spf->num1 < 0
	&& spf->num2 < 0 && spf->wildcard))
	{
		if (nb == 0)
			ft_put_char_count('0', spf);
		else
			ft_putnbr_base_u(nb, "0123456789ABCDEF", spf);
	}
	else if (!(spf->point_1 && nb == 0 && spf->num1 < 0))
		ft_put_char_count(' ', spf);
	while (spf->num1 > (spf->m_m[1]))
	{
		ft_put_char_count(' ', spf);
		spf->num1--;
	}
}

void	ft_treat_X(unsigned int nb, t_struct *spf)
{
	unsigned int	max_size_or_num2;

	spf->size = ft_len_base(nb, "0123456789ABCDEF");
	max_size_or_num2 = ft_max(spf->size, spf->num2);
	if (nb == 0)
		spf->size = 1;
	max_size_or_num2 = ft_max(spf->size, spf->num2);
	if (spf->nbisneg && spf->point_1 && spf->num2 == -1 && spf->printminus == 0)
	{
		ft_putchar_fd('-', 1);
		spf->print_count++;
		spf->printminus = 1;
		spf->num1++;
	}
	if ((spf->nbisneg && spf->point_1 && spf->zero == 0 && spf->printminus == 0)
	|| (spf->nbisneg && spf->point_2 == 0 && spf->zero && spf->printminus == 0))
	{
		ft_put_char_count('-', spf);
		spf->printminus = 1;
		spf->size++;
	}
	while (spf->num1 > (int)(max_size_or_num2 + spf->nbisneg))
	{
		if ((spf->zero == 1 && spf->num1 == 0 && nb == 0)
		|| (spf->zero == 1 && spf->wildcard && spf->point_2 && spf->num1 > 0
		&& spf->num2 == -1))
			ft_put_char_count('0', spf);
		else if (spf->point_1 == 1 && spf->num1 == 0 && nb == 0)
			ft_put_char_count(' ', spf);
		else if (spf->point_2 == 1 && spf->zero)
			ft_put_char_count(' ', spf);
		else if (spf->point_1 || spf->zero)
			ft_put_char_count('0', spf);
		else
			ft_put_char_count(' ', spf);
		spf->num1--;
	}
	if (((spf->minus && spf->num1 > spf->size) && !(spf->point_2 == 1
	&& spf->num2 && nb == 0)) || (spf->wildcard && ((spf->point_1
	&& spf->num1 < 0) || (spf->point_2 && spf->num1 < 2)) && spf->num2 != 0
	&& nb == 0))
	{
		if (nb == 0)
			ft_put_char_count('0', spf);
		else
			ft_putnbr_base_u(nb, "0123456789ABCDEF", spf);
		spf->allprint = 1;
	}
	if (spf->nbisneg && spf->printminus == 0)
	{
		ft_putchar_fd('-', 1);
		spf->print_count++;
		spf->printminus = 1;
		max_size_or_num2--;
	}
	while (spf->num2 > spf->size)
	{
		if (spf->point_2 == 1 && spf->num2 == 0 && spf && nb == 0)
			ft_put_char_count('0', spf);
		else if (spf->point_2 == 1 && spf->num2 == 0 && nb == 0)
			ft_put_char_count(' ', spf);
		else if (spf->point_2 || spf->zero)
			ft_put_char_count('0', spf);
		else
			ft_put_char_count(' ', spf);
		spf->num2--;
	}
	if (spf->point_1 == 1 && spf->num1 == -1 && nb == 0)
		return ;
	if (spf->point_2 == 1 && spf->num2 == -1 && nb == 0 && !spf->allprint)
	{
		ft_put_char_count(' ', spf);
		return ;
	}
	if (spf->allprint == 0 && !(nb == 0 && (spf->point_1 || spf->point_2)
	&& (spf->num2 == 0 || spf->num1 == 0)))
		if (nb == 0)
			ft_put_char_count('0', spf);
		else
			ft_putnbr_base_u(nb, "0123456789ABCDEF", spf);
	else if (nb == 0 && spf->point_2 && spf->num1 && !spf->allprint)
		ft_put_char_count(' ', spf);
}
