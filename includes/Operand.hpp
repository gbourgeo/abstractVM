/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:28:13 by gbourgeo          #+#    #+#             */
//   Updated: 2020/12/28 17:03:27 by gbourgeo         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"

template <typename T>
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

private:
	T				_value;
	eOperandType	_type;
	int				_precision;
};

#endif	// OPERAND_HPP
