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

void Render::load(GLFWwindow* window)
{
	this->myCamera = Camera(window);

	objectShader.createShader("./Models/shaders/basic", "NULL", "./Models/shaders/basic");
	//objectShader.createShader("./Graphic/Shaders/vertex", "NULL", "./Graphic/Shaders/fragment");
	//terrainShader.createShader("./Graphic/Shaders/vertex", "NULL", "./Graphic/Shaders/fragment");

	objectWorldLocation = objectShader.getUniform("WorldMatrices");
	objectProjectionLocation = objectShader.getUniform("ProjectionMatrix");
	objectViewLocation = objectShader.getUniform("ViewMatrix");

	myCamera.setPosition(glm::vec3(0, 35, -20));
	//myCamera.

}

void Render::unload()
{
	// unload shaders
	objectShader.unload();
	//terrainShader.unload();
}

void Render::begin()
{
	objectElements.clear();
	objectInstances.clear();
	worldMatrices.clear();
}

void Render::end()
{
	// sort elements
	std::qsort(objectElements.getData(), objectElements.getSize(), sizeof(ObjectElement), compareElements);

	// create world matrices from positions
	const glm::mat4 IDENT;
	for (int i = 0; i<objectElements.getSize(); i++)
	{
		worldMatrices[i] = glm::translate(IDENT, objectElements[i].position);
	}

	// convert elements to instances
	int first = 0;
	while (first < objectElements.getSize())
	{
		int last = first;
		int curModel = objectElements[first].model;
		int curTexture = objectElements[first].texture;

		for (int i = first + 1; i<objectElements.getSize() && last - first + 1 < MAX_INSTANCES_PER_DRAW; i++, last++)
		{
			if (objectElements[i].model != curModel || objectElements[i].texture != curTexture)
			{
				break;
			}
		}

		int instances = last - first + 1;
		ObjectInstance instance = { curModel, curTexture, instances };
		objectInstances.add(instance);

		first = last + 1;
	}
}

void Render::addElement(int model, int texture, const glm::vec3& position)
{
	assert(model >= 0);
	assert(texture >= 0);

	ObjectElement element = { model, texture, position };

	objectElements.add(element);
	worldMatrices.add(glm::mat4());
}

void Render::render(ModelLoader* models)
{
	std::cout << "Camera x-Position: " << myCamera.getLookAtVector().x;
	std::cout << " Camera y-Position: " << myCamera.getLookAtVector().y;
	std::cout << "Camera z-Position: " << myCamera.getLookAtVector().z << std::endl;

	//Cleans the color buffer and set the defaultbacgroundcolor
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Shader setup
	glUseProgram(objectShader.getShaderProgramID());
	objectShader.setMat4(objectProjectionLocation, myCamera.getProjection());
	objectShader.setMat4(objectViewLocation, myCamera.getView());

	int worldMatrixOffset = 0;
	//std::cout << objectInstances.getSize() << std::endl;
	for (int i = 0; i < objectInstances.getSize(); i++)
	{
		ObjectInstance& instance = objectInstances[i];
		objectShader.setMat4v(objectWorldLocation, &worldMatrices[worldMatrixOffset], instance.instances);
		models->bindTexture(instance.texture);
		models->renderModel(instance.model, instance.instances);
		worldMatrixOffset += instance.instances;
	}
}

Camera* Render::getCamera()
{
	return &myCamera;
}

GLuint Render::getObjectShader()
{
	return objectShader.getShaderProgramID();
}