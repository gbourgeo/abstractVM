/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:28:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/31 10:51:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

# include <stdexcept>
# include <bits/stdc++.h>
# include "IOperand.hpp"

template<class T>
class Operand: public IOperand
{
public:
	Operand();
	~Operand();
	Operand(Operand const & src);
	Operand & operator=(Operand const & rhs);

	int getPrecision( void ) const;
	eOperandType getType( void ) const;
	IOperand const * operator+( IOperand const & rhs ) const;
	IOperand const * operator-( IOperand const & rhs ) const;
	IOperand const * operator*( IOperand const & rhs ) const;
	IOperand const * operator/( IOperand const & rhs ) const;
	IOperand const * operator%( IOperand const & rhs ) const;

	std::string const & toString( void ) const;

	Operand(std::string const & value, eOperandType type);
	Operand(T const & value, eOperandType type);

	class OperandException : public std::exception
	{
	public:
		OperandException(const char *error);

		virtual const char * what() const throw()
		{
			return this->_error.c_str();
		}
	private:
		std::string		_error;
	};

private:
	T				_value;
	std::string		_s_value;
	eOperandType	_type;
	ePrecision		_precision;
};

#endif	// OPERAND_HPP
