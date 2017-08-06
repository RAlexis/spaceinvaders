#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation
{
public:
	float Frame, speed;
	sf::Sprite sprite;
	std::vector<sf::IntRect> frames;

	Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed)
	{
		finished = false;
		Frame = 0;
		speed = Speed;
		
		for (int i = 0; i < count; ++i)
			frames.push_back(sf::IntRect(x + i * w, y, w, h));

		sprite.setTexture(t);
		sprite.setOrigin(w / 2, h / 2);
		sprite.setTextureRect(frames[0]);

	}

	void update()
	{
		if (isEnd()) {
			finished = true;
		}
		//	printf("UPDATE");

		//if (finished)
			//return;

		Frame += speed;
		int n = frames.size();
		if (Frame >= n) Frame -= n;
		if (n>0) sprite.setTextureRect(frames[int(Frame)]);

		//if (isEnd())
			//finished = true;
	}

	bool isEnd()
	{
		if (Frame + speed >= frames.size())
		{
			//finished = true;
			//printf("Y\n");
		}
		//else
			//printf("N\n");

		//return finished;
		return Frame + speed >= frames.size();
	}

	bool finished;
};

#endif