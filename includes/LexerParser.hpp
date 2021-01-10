/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:27:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/10 02:33:17 by gbourgeo         ###   ########.fr       */
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
# include <functional>
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
			LexerParserException(std::size_t lineNb, const char *error, std::string const & instruction);

			virtual const char * what() const throw()
			{
				return this->_error.c_str();
			}
		private:
			std::string		_error;
	};

private:
	/* Instructions structure */
	typedef struct	s_instructions
	{
		const char			*name;
		Token::eTokenType	type;
		std::size_t			nbArgs;
	}				t_inst;
	/* Operands structure */
	typedef struct	s_operands
	{
		const char		*name;
		eOperandType	type;
		void			(LexerParser::*checkValue)(std::string const &) const;
	}				t_operands;
	/* */
	typedef struct s_result
	{
		eOperandType	type;
		std::string		value;
	}				t_result;

	const char			*_file;
	std::fstream		_ifs;
	std::streambuf		*_cinbuf;
	std::size_t			_lineNb;
	static t_inst		_instructions[];
	static t_operands	_values[];

	t_result		checkOperand(std::string const & operand) const;
	void			intOperandCheck(std::string const & value) const;
	void			floatOperandCheck(std::string const & value) const;
	void			doubleOperandCheck(std::string const & value) const;
};

# endif // LEXERPARSER_HPP
