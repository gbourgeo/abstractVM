/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instructions.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:53:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/24 13:26:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_HPP
# define INSTRUCTIONS_HPP

# include <vector>
# include <string>
# include <stdexcept>
# include "OperandFactory.hpp"

class Instructions
{
public:
	Instructions();
	~Instructions();
	Instructions(Instructions const & src);
	Instructions & operator=(Instructions const & rhs);

	/* Instruction types enumeration */
	enum eInstructionType
	{
		Push,
		Pop,
		Dump,
		Assert,
		Add,
		Sub,
		Mul,
		Div,
		Mod,
		Print,
		Exit,
	};

	eInstructionType		getInstruction(std::string const & token) const;
	std::size_t				getInstructionNbArgs(std::string const & token) const;
	IOperand::eOperandType	getOperand(std::string const & token) const;
	std::string				getOperandValue(std::string const & token) const;

	const char *			getInstruction(eInstructionType type) const;
	const char *			getOperand(IOperand::eOperandType type) const;

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
	void			noCheck(std::string const & value) const;

	/*
	* Instructions structure
	* instructions handled by the program.
	*/
	typedef struct	s_instructions
	{
		const char			*name;
		eInstructionType	type;
		std::size_t			nbArgs;
	}				t_inst;
	/*
	* Operands structure
	* operand name, type and value
	*/
	typedef struct	s_operands
	{
		const char		*name;
		IOperand::eOperandType	type;
		void	(Instructions::*checkOperand)(std::string const &) const;
	}				t_ope;

	static t_inst	_instructions[];
	static t_ope	_values[];
};

#endif // INSTRUCTIONS_HPP
