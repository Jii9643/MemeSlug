#include "Box.h"



class Bullet
{
public:
	Bullet(Texture *texture, Vector2f position, float maxVelocity, Vector2f direction, float initialVelocity, float acceleration);
	virtual ~Bullet();

	void Movement();

	void Update();
	void Draw(RenderTarget &target);

private:
    
	Texture * texture;
	Sprite sprite;

	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
};
