/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 19:25:28 by acakste           #+#    #+#             */
/*   Updated: 2018/09/23 19:25:29 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>
#include <ft_printf.h>

void    print_usage(void)
{
    ft_printf("usage: ft_ssl command [command opts] [command args]\n");
    exit (1);
}

void	handle_flags(char *str, t_flags *flags)
{
	if (str)
		flags->p_flag = 1;
}
/*
t_table_entry *dispatch(void)
{
	t_table_entry *table;

	table = (t_table_entry*)malloc(sizeof(t_table_entry) * NUM_COM + 1);
	if (!table)
		return (NULL);
	table[0].function = &md5sum;
	table[0].command = "md5sum";
	table[1].function = &SHA256;
	table[1].command = "SHA256";
	return (table);
}*/

int     main(int argc, char **argv)
{
    int				i;
    //t_table_entry	*table;
	t_flags			flags;

    if (argc < 2)
        print_usage();
    //table = dispatch();
    i = 1;
    while (argv[i])
    {
		if (argv[i][0] == '-')
			handle_flags(argv[i], &flags);
		//else
			//check command
        i++;
    }
	md5(argv[1]);
    return (0);
}
