#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

#define SPEED 20

class Snake
{
public:
  Snake(int x, int y);
  ~Snake();

  int getX()const;
  int getY()const;

  void updatePosition(int x, int y);

  sf::RectangleShape getRect();
  
private:
  int x;
  int y;
  sf::RectangleShape* rect;
};

Snake::Snake(int x, int y)
{
  this->x = x;
  this->y = y;
  this->rect = new sf::RectangleShape(sf::Vector2f(20.f, 20.f));
  this->rect->setPosition(this->x, this->y);
}
int Snake::getX()const
{
  return this->x;
}
int Snake::getY()const
{
  return this->y;
}
void Snake::updatePosition(int x, int y)
{
  this->x = x;
  this->y = y;
  this->rect->setPosition(this->x, this->y);
}
sf::RectangleShape Snake::getRect()
{
  return *(this->rect);
}
Snake::~Snake()
{
  delete this->rect;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 800), "Snake");

  window.setFramerateLimit(60);

  std::vector <Snake*> snake;

  int c_1(0);
  int x_1 = 400;


  while (c_1 < 2){
  snake.push_back(new Snake(x_1, 400));
  x_1-=10;
  c_1++;
  }

  int x_act, y_act, max;

  bool right, left , top , bottom;
  right = true;
  left = top = bottom = false;


  srand(time(NULL));
   int r_x, r_y; 
   r_x = rand()%799+1;
   r_y = rand()%799+1;
   sf::RectangleShape apple(sf::Vector2f(20.f, 20.f));
   apple.setPosition(r_x, r_y);

  while(window.isOpen())
    {


      x_act = snake[0]->getX();
      y_act = snake[0]->getY();
      max = snake.size();
      

      if (x_act < 0){
	x_act = 800;
	snake[0]->updatePosition(x_act, y_act); //move
      }
      if (x_act > 800){
	x_act = 0;
	snake[0]->updatePosition(x_act, y_act);
	}
      if (y_act < 0){
	y_act = 800;
	snake[0]->updatePosition(x_act, y_act);
      }
      if (y_act > 800){
	y_act = 0;
	snake[0]->updatePosition(x_act, y_act);
      }
      //std::cout << x_act << std::endl;

      if (x_act >= r_x-10 && x_act <= r_x+10 && y_act >= r_y-10 && y_act<=r_y+10)
	{
	  int t1, t2;
	  if (right==true){t1 = -10; t2=0;}
	  else if (left==true){t1 = 10; t2=0;}
	  else if (top==true){t1=0; t2=10;}
	  else {t1=0; t2=-10;}
	  for (int i=0; i<2; i++)
	    {
	  snake.push_back(new Snake(snake[max-1]->getX()+t1, snake[max-1]->getY()+t2));
	  t1*=2;
	  t2*=2;
	    }

	  
	  r_x = rand()%799+1;
          r_y = rand()%799+1;
	  apple.setPosition(r_x, r_y);
	}
      //std::cout << max <<std::endl;

      
      if (left == true)
	{
	  
	    snake[0]->updatePosition(x_act-5, y_act);
	}
      if (right==true)
	{
	  if (!left)
	    snake[0]->updatePosition(x_act+5, y_act);
	}
      if (top == true)
	{
	  if (!bottom)
	    snake[0]->updatePosition(x_act, y_act-5);
	}
      if (bottom == true)
	{
	  if (!top)
	    snake[0]->updatePosition(x_act, y_act+5);
	}
      int rX,rY;
      int cs=0;

      snake[1]->updatePosition(x_act, y_act);

      for (int i=max-1; i>1; i--)
	{
	  snake[i]->updatePosition(snake[i-1]->getX(), snake[i-1]->getY());
	}
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    {
	      window.close();
	    }
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	    {

		left = true;
		right = top = bottom = false;
	    }
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	    {
	      right = true;
	      left = top = bottom = false;
	    }
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	    {
	     top = true;
	     right = left = bottom = false;
	    }
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	    {
	      bottom = true;
	      right = left = top = 0;
	    }
	  
	}
      
      window.clear();
      for (int i=0; i<snake.size(); i++)
	{
	  window.draw(snake[i]->getRect());
	}
      window.draw(apple);

        for (int i=2; i<max; i++)
	{
	  if    (snake[0]->getX()>=snake[i]->getX()-4 && snake[0]->getX()<=snake[i]->getX()+4
	      && snake[0]->getY()>=snake[i]->getY()-4 && snake[0]->getY()<=snake[i]->getY()+4)
	    {
	      std::cout << "perdu"<<std::endl;
	      right = top = left = bottom = false;
	      
	    }
	}
      
      window.display();
    }

  for (int i=0; i<snake.size(); i++)
    {
      delete snake[i];
      snake[i] = NULL;
    }
}
