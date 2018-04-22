#include "Box.h"



class Bullet
{
public:
	
	Bullet(Texture *texture, Vector2f position, Vector2f scale,
		float maxVelocity, Vector2f direction, float initialVelocity, float acceleration);
	virtual ~Bullet();
	
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }

	void Movement(const float &dt);
    void Update(const float &dt);
	void Draw(RenderTarget &target);

private:
    
	float dtMultiplier;

	Texture * texture;
	Sprite sprite;


	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
};
