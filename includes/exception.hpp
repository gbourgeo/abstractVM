/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:23:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/02 14:29:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <stdexcept>

class Exception: public std::exception
{
public:
	Exception();
	~Exception();
	Exception(Exception const & src);
	Exception & operator=(Exception const & rhs);
};

#endif // EXCEPTION_HPP
