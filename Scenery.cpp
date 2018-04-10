/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scenery.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:57:34 by ddenkin           #+#    #+#             */
/*   Updated: 2018/04/08 20:01:38 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scenery.hpp"

Scenery::Scenery(Scenery const &e): GameEntity(e) {
	return ;
}

Scenery::Scenery(const int x, const int y, const int dir): GameEntity(x, y, dir, "scenery", 2) {
	return ;
}

Scenery& Scenery::operator=(Scenery &e) {
	if (this != &e) {
		setX(e.getX());
		setY(e.getY());
		setAlive(e.isAlive());
		setDir(e.getDir());
		setTeam(e.getTeam());
	}
	return *this;
}

Scenery::~Scenery() {
	return ;
}