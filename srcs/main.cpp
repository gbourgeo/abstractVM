/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:36:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/09 13:29:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "LexerParser.hpp"
#include "Token.hpp"
#include "OperandFactory.hpp"

int		main(int ac, const char **av)
{
	(void)ac;
	try
	{
		LexerParser		lp(av[1]);
		Token			token;

		lp.tokenise(token);
		lp.parse(token);
	}
	catch (LexerParser::OpenFileException & e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (LexerParser::LexerParserException & e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
