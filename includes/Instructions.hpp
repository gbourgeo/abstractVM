/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instructions.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:53:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/23 15:56:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_HPP
# define INSTRUCTIONS_HPP

# include <stdexcept>
# include "Token.hpp"

class Instructions
{
public:
	Instructions();
	~Instructions();
	Instructions(Instructions const & src);
	Instructions & operator=(Instructions const & rhs);

	/* Operand value structure */
	typedef struct	s_result
	{
		Token::eTokenType		typeToken;
		IOperand::eOperandType	typeOperand;
		std::string				valueOperand;
	}				t_result;

	t_result const	getInstruction(std::vector<std::string> const & token) const;
	void			checkArgumentValue(IOperand::eOperandType type, std::string const & value) const;

	class	InstructionsException : public std::exception
	{
	public:
		InstructionsException(const char * error, std::string const & value);

		virtual const char * what() const throw()
		{
			return this->_error.c_str();
		}
	private:
		std::string		_error;
	};

private:
	void			intOperandCheck(std::string const & value) const;
	void			floatOperandCheck(std::string const & value) const;
	void			doubleOperandCheck(std::string const & value) const;

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
		const char				*name;
		IOperand::eOperandType	type;
		void	(Instructions::*checkOperand)(std::string const &) const;
	}				t_ope;

	static t_inst	_instructions[];
	static t_ope	_values[];
};

#endif // INSTRUCTIONS_HPP
