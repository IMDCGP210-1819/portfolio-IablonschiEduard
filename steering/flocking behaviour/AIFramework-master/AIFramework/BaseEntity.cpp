#include "BaseEntity.h"
#include "UtilRandom.h"

std::vector<BaseEntity*> BaseEntity::Renderables;

BaseEntity::BaseEntity()
{
	// with no further information, we make some assumptions and set default values.
	filename = "assets\\boid.png";
	colourTint = sf::Color::White;
	Initialize();
}

BaseEntity::BaseEntity(std::string file) : filename(file)
{
	// with just a texture file, we default to a white tint (so no tint at all).
	colourTint = sf::Color::White;
	Initialize();
}

BaseEntity::BaseEntity(std::string file, sf::Color colour) : filename(file), colourTint(colour)
{
	Initialize();
}

BaseEntity::~BaseEntity()
{
	
}

void BaseEntity::Think()
{
	sf::Vector2f separation;
	sf::Vector2f alignment;
	sf::Vector2f cohesion;

	int neighbours = 0;

	const float MaxDistance = 200.0f;

	for (auto boid : Renderables) {
		if (boid == this) continue;

		sf::Vector2f diff = getPosition() - boid->getPosition();

		float distance = std::sqrtf(diff.x*diff.x + diff.y*diff.y);

		if (distance > MaxDistance) continue;

		neighbours++;

		if (distance == 0) distance = 1; // in case a boid overlaps the one in the middle, count the distance between them as 1
		
		diff = diff / distance; // normalizes the diff variable
		diff /= distance;

		separation += diff;
		alignment += boid->GetVelocity();
		cohesion += boid->getPosition();
	}

	if (neighbours > 0) { // checks if there are any other boids, except for the one in the middle, in the neighbourhood
		float normal = std::sqrtf(separation.x*separation.x + separation.y*separation.y);
		separation /= normal > 0 ? normal : 1.0f; // if the value of the normal variable is greater than 0, keep it; otherwise, set it to the specified value (1.0f) 
		separation /= (float)neighbours;

		normal = std::sqrtf(alignment.x*alignment.x + alignment.y*alignment.y);
		alignment /= normal > 0 ? normal : 1.0f; // if the value of the normal variable is greater than 0, keep it; otherwise, set it to the specified value (1.0f)
		alignment /= (float)neighbours;

		normal = std::sqrtf(cohesion.x*cohesion.x + cohesion.y*cohesion.y);
		cohesion /= normal > 0 ? normal : 1.0f; // if the value of the normal variable is greater than 0, keep it; otherwise, set it to the specified value (1.0f)
		cohesion /= (float)neighbours;
	}

	velocity += separation * 0.6f; 
	velocity += alignment * 0.2f;
	velocity += cohesion * 0.2f;

	// build a new position vector by adding a scaled version of the velocity vector
	sf::Vector2f pos = getPosition() + (velocity * 0.001f);
	// update our position
	setPosition(pos);
}

void BaseEntity::Initialize()
{
	// set a default position - could be randomised.
	setPosition(400.0f, 300.0f);

	// load the texture into memory
	texture.loadFromFile(filename);
	texture.setSmooth(true);
	// and provide the sprite with a pointer to the texture object
	// if the texture object is destroyed (goes out of scope etc) then the sprite will display weirdly
	sprite.setTexture(texture);
	// set up our colour tint
	sprite.setColor(colourTint);
	
	// select a random angle
	float angle = UtilRandom::instance()->GetRange(0, 361);
	// set our rotation value
	setRotation(angle);
	// and assign a velocity, we need to convert angle to radians so it plays nicely with cos and sin.
	velocity = sf::Vector2f(cos(angle * M_PI / 180), sin(angle * M_PI / 180));

	// add the entity to the list of renderables.
	Renderables.push_back(this);
}