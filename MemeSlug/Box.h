#include "dArr.h"


using namespace sf;

class Box
{
public:
	Box();
	Box(Texture* texture);
	~Box();
	void Draw(RenderTarget& target);
	void Update();

	FloatRect boxBounds;
	static unsigned boxes;


private:

	RectangleShape box;
	Texture* texture;
	Sprite sprite;

};

