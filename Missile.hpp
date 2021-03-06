/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:55:21 by ddenkin           #+#    #+#             */
/*   Updated: 2018/04/08 15:48:38 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISSILE_HPP
#define MISSILE_HPP

#include "GameEntity.hpp"

class	Missile: public GameEntity
{
public:
	Missile(const int x, const int y, const int dir, const int team);
	Missile(Missile const &e);
	virtual ~Missile();

	Missile& operator=(Missile &e);
protected:
private:
	Missile();
};

#endif