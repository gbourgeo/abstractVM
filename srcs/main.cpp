/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:36:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/17 21:32:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Token.hpp"
#include "OperandFactory.hpp"

int		main(int ac, const char **av)
{
	(void)ac;
	try
	{
		Lexer			lexer(av[1]);
		Parser			parser;
		Token			token;

		lexer.tokenise(token);
		parser.parse(token);
	}
	catch (Lexer::OpenFileException & e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (Lexer::LexerException & e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
