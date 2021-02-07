/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instructions.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:53:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/31 13:16:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_HPP
# define INSTRUCTIONS_HPP

# include <vector>
# include <string>
# include <stdexcept>
# include <limits>
# include "IOperand.hpp"

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
	std::size_t				getInstructionNbArgs(std::string const & token, std::size_t nbArgs) const;
	IOperand::eOperandType	getOperand(std::string const & token) const;
	std::string				getOperandValue(IOperand::eOperandType type, std::string const & token) const;

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
	void			intOperandCheck(IOperand::eOperandType type, std::string const & value) const;
	void			pointOperandCheck(IOperand::eOperandType type, std::string const & value) const;
	void			noCheck(IOperand::eOperandType type, std::string const & value) const;

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
		void	(Instructions::*checkOperand)(IOperand::eOperandType, std::string const &) const;
	}				t_ope;

	static t_inst	_instructions[];
	static t_ope	_values[];
};

#endif // INSTRUCTIONS_HPP
