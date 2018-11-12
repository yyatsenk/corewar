# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayduk <mgayduk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/27 16:20:32 by mgayduk           #+#    #+#              #
#    Updated: 2018/06/02 13:56:58 by mgayduk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C libft all
	make -C asm   all
	make -C virtual_machine all

clean:
	make -C libft clean
	make -C asm   clean
	make -C virtual_machine clean

fclean: clean
	rm -f libft/libft.a
	rm -f asm/asm
	rm -f virtual_machine/corewar

re:
	make -C libft fclean
	make -C asm   fclean
	make -C virtual_machine fclean
	make -C libft all
	make -C asm   all
	make -C virtual_machine all