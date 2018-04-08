NAME = ft_retro
CC = clang++
CPPFLAGS = -Wall -Wextra -Werror

OBJECTS = main.o \
			Enemy.o \
			Game.o \
			GameEntity.o \
			Missile.o \
			Player.o \

.PHONY : clean all fclean re

all : $(NAME)
	
$(NAME) : $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $(NAME) $(OBJECTS) -lncurses

clean :
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

Enemy.o : Enemy.cpp
	$(CC) $(CPPFLAGS) -c Enemy.cpp

Game.o : Game.cpp
	$(CC) $(CPPFLAGS) -c Game.cpp

Bullet.o : GameEntity.cpp
	$(CC) $(CPPFLAGS) -c GameEntity.cpp

GameObject.o : Missile.cpp
	$(CC) $(CPPFLAGS) -c Missile.cpp

Battlefield.o : Player.cpp
	$(CC) $(CPPFLAGS) -c Player.cpp
