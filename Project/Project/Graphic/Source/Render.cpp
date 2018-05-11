#include "../header/Render.h"

int compareElements(const void* a, const void* b)
{
	uint64_t akey = *(uint64_t*)a;
	uint64_t bkey = *(uint64_t*)b;

	return (int)(akey - bkey);
}

Render::Render()
{
}

Render::~Render()
{
}

void Render::load()
{

}

void Render::unload()
{

}

void Render::begin()
{

}

void Render::end()
{

}

void Render::addElement(int model, int texture, const glm::vec3& position)
{

}

void Render::render(ModelLoader* models)
{

}