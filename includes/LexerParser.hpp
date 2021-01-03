/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:27:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/03 21:03:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXERPARSER_HPP
# define LEXERPARSER_HPP

# include <fstream>
# include <iostream>
# include <stdexcept>
# include <vector>
# include <sstream>
# include <iterator>
# include "Token.hpp"

class LexerParser
{
public:
	LexerParser();
	LexerParser(char const * file);
	~LexerParser();
	LexerParser(LexerParser const & src);
	LexerParser & operator=(LexerParser const & rhs);

	void		tokenise( Token & token );
	void		parse( Token & token );

	class OpenFileException : public std::exception
	{
		public:
			OpenFileException(const char *file);

			virtual const char * what() const throw()
			{
				return this->_error.c_str();
			}
		private:
			std::string		_error;
	};

	class LexerParserException : public std::exception
	{
		public:
			LexerParserException(std::size_t lineNb, const char *error, std::string & instruction);

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

	typedef struct	s_token
	{
		std::size_t			nbArgs;
		const char			*value;
		Token::eTokenType	type;
	}				t_token;
};

# endif // LEXERPARSER_HPP
