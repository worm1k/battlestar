/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scenery.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:55:21 by ddenkin           #+#    #+#             */
/*   Updated: 2018/04/08 20:01:06 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENERY_HPP
#define SCENERY_HPP

#include "GameEntity.hpp"

class	Scenery: public GameEntity
{
public:
	Scenery(const int x, const int y, const int dir);
	Scenery(Scenery const &e);
	virtual ~Scenery();

	Scenery& operator=(Scenery &e);
protected:
private:
	Scenery();
};

#endif