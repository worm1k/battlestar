/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:57:34 by ddenkin           #+#    #+#             */
/*   Updated: 2018/04/08 17:49:18 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile(Missile const &e): GameEntity(e) {
	return ;
}

Missile::Missile(const int x, const int y, const int dir, const int team): GameEntity(x, y, dir, "missile", team) {
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
		setTeam(e.getTeam());
	}
	return *this;
}