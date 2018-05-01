#include "..\header\District.h"

District::District()
{
	this->noise = nullptr;
	for (int i = 0; i < MAX_DISTRICTS; i++)
	{
		this->positions.add(glm::vec2());
	}
}

District::District(PerlinNoise * noise)
{
	this->noise = noise;
	for (int i = 0; i < MAX_DISTRICTS; i++)
	{
		this->positions.add(glm::vec2());
	}
}

District::~District()
{
}

void District::setDistrict(float width, float height)
{
	double noise = 20 * this->noise->generate(1.134, 1.22, 1, 1); // Some noise with nice spread
	this->positions[0].x = (noise - floor(noise)) * width;

	noise = 10 * this->noise->generate(1.476, 1.687, 0.88, 1);
	this->positions[0].y = (noise - floor(noise)) * height;

	noise = 20 * this->noise->generate(6.745, 4.9345, 0.77, 1);
	this->positions[1].x = (noise - floor(noise)) * width;

	noise = 10 * this->noise->generate(2.975, 2.626, 0.6, 1);
	this->positions[1].y = (noise - floor(noise)) * height;

	noise = 20 * this->noise->generate(3.153, 3.754, 0.55, 1);
	this->positions[2].x = (noise - floor(noise)) * width;

	noise = 10 * this->noise->generate(4.242, 7.965, 0.44, 1);
	this->positions[2].y = (noise - floor(noise)) * height;
}

void District::setNoise(PerlinNoise * noise)
{
	this->noise = noise;
}

void District::calculateMap(Array2D<int>& map, float borderPerc)
{
	const int WIDTH = map.getWidth();
	const int HEIGHT = map.getHeight();

	for(int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			map.at(x, y) = this->closestDistrict(x, y);
		}
	}

	Array<glm::vec2> borderCoordinates;

	this->findBorder(map, borderCoordinates); // get border to alter

	const int MIN_EFFECT_AMOUNT = 2; // calculate how many nodes to effect
	int nodeEffectAmount = floor(WIDTH * borderPerc);
	if (nodeEffectAmount < MIN_EFFECT_AMOUNT)
		nodeEffectAmount = MIN_EFFECT_AMOUNT;

	this->alterBorders(map, borderCoordinates, nodeEffectAmount);
}

void District::generate(Array2D<int>& map, float width, float height, float borderPerc)
{
	assert(noise != nullptr);
	this->setDistrict(width, height);
	this->calculateMap(map, borderPerc);
}

int District::closestDistrict(int x, int y)
{
	//return closest district to pos
	glm::vec2 pos(x, y);
	int closestDistrict = INT_MIN;
	double firstDistance = vec2SquareDistance(positions[0], pos);
	double secondDistance = vec2SquareDistance(positions[1], pos);
	double thirdDistance = vec2SquareDistance(positions[2], pos);
	
	if (firstDistance < secondDistance && firstDistance < thirdDistance)
	{
		closestDistrict = 0;
	}
	else if (secondDistance < firstDistance && secondDistance < thirdDistance)
	{
		closestDistrict = 1;
	}
	else
	{
		closestDistrict = 2;
	}

	return closestDistrict;
}

double District::vec2SquareDistance(glm::vec2 first, glm::vec2 second)
{
	double xDistance = pow(first.x - second.x, 2);
	double yDistance = pow(first.y - second.y, 2);

	//No need to square it since the length diferences will still show which is closest
	return xDistance + yDistance;
}

void District::findBorder(Array2D<int>& map, Array<glm::vec2>& borders)
{
	const int WIDTH = map.getWidth();
	const int HEIGHT = map.getHeight();
	int previous = map.at(0, 0);

	for (int y = 0; y < HEIGHT; y++)
	{
		previous = map.at(0, y);
		for (int x = 0; x < WIDTH; x++)
		{
			if (previous != map.at(x, y)) //found border
			{
				previous = map.at(x, y); // Change previous
				borders.add(glm::vec2(x, y)); // change position
			}
		}
	}

}

void District::alterBorders(Array2D<int>& map, Array<glm::vec2>& borders, int nodeChangeRange)
{
	int x, y;
	int firstDistrict, secondDistrict;
	int minRangePos, maxRangePos;
	double noise;
	int halfChangeRange = nodeChangeRange / 2;
	const int WIDTH = map.getWidth();

	for(int i = 0; i < borders.getSize(); i++)
	{
		x = borders.at(i).x;
		y = borders.at(i).y;
		firstDistrict = map.at(x, y);
		secondDistrict = map.at(x - 1, y); //can't go outside the array borders

		minRangePos = x - halfChangeRange; //the range of what should be altered
		maxRangePos = x + halfChangeRange;

		if (minRangePos < 0)
		{
			minRangePos = 0;
		}
		if (maxRangePos >= WIDTH)
		{
			minRangePos -= (maxRangePos - WIDTH);
			maxRangePos = WIDTH - 1;
		}

		for (int x2 = minRangePos; x2 <= maxRangePos; x2++) // loop through nodes to be altered
		{
			noise = 20 * this->noise->generate(1.134 * x2, 1.22 * y, 1, 1);
			noise = (noise - floor(noise));


			if (noise > 0.5)
				map.at(x2, y) = firstDistrict;
			else
				map.at(x2, y) = secondDistrict;
		}
	}
}
