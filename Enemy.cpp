/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:57:34 by ddenkin           #+#    #+#             */
/*   Updated: 2018/04/08 17:48:34 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Enemy.hpp"

Enemy::Enemy(Enemy const &e): GameEntity(e) {
	return ;
}

Enemy::Enemy(const int x, const int y, const int dir): GameEntity(x, y, dir, "enemy", 1) {
	return ;
}

Enemy& Enemy::operator=(Enemy &e) {
	if (this != &e) {
		setX(e.getX());
		setY(e.getY());
		setAlive(e.isAlive());
		setDir(e.getDir());
		setTeam(e.getTeam());
	}
	return *this;
}

Enemy::~Enemy() {
	return ;
}