/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:51:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/31 12:21:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <fstream>
# include <iostream>
# include <stdexcept>
# include <vector>
# include <sstream>
# include <iterator>
# include <functional>
# include "Token.hpp"
# include "Instructions.hpp"

class Lexer
{
public:
	Lexer();
	Lexer(char const * file, Instructions const & instructions);
	~Lexer();
	Lexer(Lexer const & src);
	Lexer & operator=(Lexer const & rhs);

	void		tokenise( Token & token );

	class LexerException : public std::exception
	{
	public:
		LexerException(std::size_t lineNb, const char *file);
		LexerException(std::size_t lineNb, Instructions const * instrutions);
		LexerException(std::size_t lineNb, Instructions::InstructionsException & e);
		LexerException(std::size_t lineNb, const char *error, std::string const & value);
		LexerException(std::size_t lineNb, const char *error, Token::t_token const * token);

		virtual const char * what() const throw()
		{
			return this->_error.c_str();
		}
	private:
		std::string		_error;
	};

private:
	const char			*_file;
	std::fstream		_ifs;
	std::streambuf		*_cinbuf;
	std::size_t			_lineNb;
	Instructions 		const *_instructions;
};

# endif // Lexer_HPP
