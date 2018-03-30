#include "Player.h"

enum controls{ UP = 73, DOWN = 74, LEFT = 71, RIGHT = 72, SHOOT = 0, JUMP = 57};

Player::Player(Texture *texture, int UP , int DOWN, int LEFT , int RIGHT , int SHOOT , int JUMP )
	: hp(1), damage(1), score(0)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);

	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;
	this->controls[controls::JUMP] = JUMP;
}



Player::~Player()
{
}

void Player::Movement()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP] = UP)))
		std::cout << "Up" << "\n";
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN] = DOWN)))
		std::cout << "Down" << "\n";
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT] = LEFT)))
		std::cout << "Left" << "\n";
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT] = RIGHT)))
		std::cout << "Right" << "\n";
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT] = SHOOT)))
		std::cout << "Shoot" << "\n";
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::JUMP] = JUMP)))
		std::cout << "Space" << "\n";
}

void Player::Draw(RenderTarget &target) 
{
	target.draw(this->sprite);
}

void Player::Update()
{
	this->Movement();
}
