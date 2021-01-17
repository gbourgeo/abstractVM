/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:51:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/17 11:53:13 by gbourgeo         ###   ########.fr       */
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

class Lexer
{
public:
	Lexer();
	Lexer(char const * file);
	~Lexer();
	Lexer(Lexer const & src);
	Lexer & operator=(Lexer const & rhs);

	void		tokenise( Token & token );

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

	class LexerException : public std::exception
	{
		public:
			LexerException(std::size_t lineNb, const char *error, std::string const & instruction);

			virtual const char * what() const throw()
			{
				return this->_error.c_str();
			}
		private:
			std::string		_error;
	};

private:
	/*
	* Instructions structure
	* instructions handled by the program.
	*/
	typedef struct	s_instructions
	{
		const char			*name;
		Token::eTokenType	type;
		std::size_t			nbArgs;
	}				t_inst;
	/*
	* Operands structure
	* operand name, type and value
	*/
	typedef struct	s_operands
	{
		const char		*name;
		eOperandType	type;
		void			(Lexer::*checkValue)(std::string const &) const;
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

# endif // Lexer_HPP
