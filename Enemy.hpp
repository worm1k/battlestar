/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:55:21 by ddenkin           #+#    #+#             */
/*   Updated: 2018/04/07 21:10:21 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "GameEntity.hpp"

class	Enemy: public GameEntity
{
public:
	Enemy(const int x, const int y, const int dir);
	Enemy(Enemy const &e);
	virtual ~Enemy();

	Enemy& operator=(Enemy &e);
protected:
private:
	Enemy();
};

#endif