#include "Player.h"

unsigned Player::players = 0;

enum controls { UP = 73, DOWN = 74, LEFT = 71, RIGHT = 72, SHOOT = 0, JUMP = 57 };

Player::Player(Texture *texture, Texture *bulletTexture, int UP, int DOWN, int LEFT, int RIGHT, int SHOOT, int JUMP)
	: hp(1), damage(1), score(0)
{
	this->texture = texture;
	this->bulletTexture = bulletTexture;
	this->sprite.setTexture(*this->texture);

	this->sprite.setScale(0.3f, 0.3f);

	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;
	this->controls[controls::JUMP] = JUMP;

	this->playerNr = Player::players;
	Player::players++;
}



Player::~Player()
{
}

void Player::Movement()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP] = UP)))
		this->sprite.move(0.0f, -10.0f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN] = DOWN)))
		this->sprite.move(0.0f, 10.0f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT] = LEFT)))
		this->sprite.move(-10.0f, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT] = RIGHT)))
		this->sprite.move(10.0f, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT])))
	{
		this->bullets.push_back(Bullet(bulletTexture, this->sprite.getPosition()));
	}
		
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::JUMP]))){}
		
}

void Player::Draw(RenderTarget &target)
{

	target.draw(this->sprite);

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}

}

void Player::Update()
{
	this->Movement();

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Update();
	}

}