/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:41:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/25 21:16:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"
#include "Instructions.hpp"

template<class T>
Operand<T>::Operand(): _value(0), _type(IOperand::Int8), _precision(IOperand::Int8_p)
{}

template<class T>
Operand<T>::Operand(std::string const & value, IOperand::eOperandType type, int precision):
	_s_value(value), _type(type), _precision(precision)
{
	if (type == IOperand::Int8 || type == IOperand::Int16 || type == IOperand::Int32)
		this->_value = std::stoi(value);
	if (type == IOperand::Float)
		this->_value = std::stof(value);
	if (type == IOperand::Double)
		this->_value = std::stod(value);
}

template<class T>
Operand<T>::~Operand()
{}

template<class T>
Operand<T>::Operand(Operand const & src)
{
	*this = src;
}

template<class T>
Operand<T> & Operand<T>::operator=(Operand<T> const & rhs)
{
	if (this != &rhs)
	{
		this->_value = rhs._value;
		this->_type = rhs._type;
		this->_precision = rhs._precision;
	}
	return *this;
}

template<class T>
int					Operand<T>::getPrecision( void ) const
{
	return this->_precision;
}

template<class T>
IOperand::eOperandType	Operand<T>::getType( void ) const
{
	return this->_type;
}

template<class T>
IOperand const *	Operand<T>::operator+( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

template<class T>
IOperand const * Operand<T>::operator-( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

template<class T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

template<class T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

template<class T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

template<class T>
std::string const & Operand<T>::toString( void ) const
{
	return this->_s_value;
}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
