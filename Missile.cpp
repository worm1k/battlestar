/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:57:34 by ddenkin           #+#    #+#             */
/*   Updated: 2018/04/07 21:10:51 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile(Missile const &e): GameEntity(e) {
	return ;
}

Missile::Missile(const int x, const int y, const int dir): GameEntity(x, y, dir, "missile") {
	return ;
}

Missile::~Missile() {
	return ;
}

Missile& Missile::operator=(Missile &e) {
	if (this != &e) {
		setX(e.getX());
		setY(e.getY());
		setAlive(e.isAlive());
		setDir(e.getDir());
	}
	return *this;
}