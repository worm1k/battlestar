/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:57:34 by ddenkin           #+#    #+#             */
/*   Updated: 2018/04/07 21:11:14 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Enemy.hpp"

Enemy::Enemy(Enemy const &e): GameEntity(e) {
	return ;
}

Enemy::Enemy(const int x, const int y, const int dir): GameEntity(x, y, dir, "enemy") {
	return ;
}

Enemy& Enemy::operator=(Enemy &e) {
	if (this != &e) {
		setX(e.getX());
		setY(e.getY());
		setAlive(e.isAlive());
		setDir(e.getDir());
	}
	return *this;
}

Enemy::~Enemy() {
	return ;
}