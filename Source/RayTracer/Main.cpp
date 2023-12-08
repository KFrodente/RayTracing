#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include <glm/gtx/color_space.hpp>
#include "Mesh.h"

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);

int main(int argc, char**)
{
	int windWidth = 1920;
	int windHeight = 1080;
	int canvWidth = 1920;
	int canvHeight = 1080;
	int samples = 15;
	int depth = 5;

	seedRandom((unsigned int)time(nullptr));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Window", windWidth, windHeight);

	Canvas canvas(canvWidth, canvHeight, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 90.0f, aspectRatio);

	Scene scene; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

		

	//// create material
	//auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

	//// create material
	//auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);


	InitScene01(scene, canvas);

	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
	canvas.Update();
	


	bool quit = false;
	while (!quit)
	{
		renderer.PresentCanvas(canvas);
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 3, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 90.0f, aspectRatio);
	scene.SetCamera(camera);

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -3, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Dielectric>(color3_t{ 1 }, .1f));
	scene.AddObject(std::move(plane));
	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::vec3{ random(.4f, .9f),  random(.4f, .9f),  random(.4f, .9f) });
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(.4f, .9f),  random(.4f, .9f),  random(.4f, .9f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::vec3{ random(.4f, .9f),  random(.4f, .9f),  random(.4f, .9f) }, 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			r = random01();
			if (r < .5f)
			{
				auto object = std::make_unique<Sphere>(glm::vec3{ random(-3.0f, 3.0f), random(-4.0f, 4.0f), random(-3.0f, 3.0f) }, radius, material);
				scene.AddObject(std::move(object));
			}
			else
			{
				auto object = std::make_unique<Mesh>(material); //position, rotation scale
				object->Load("models/cube-1.obj", glm::vec3{ random(-3.0f, 3.0f), random(-4.0f, 4.0f), random(-3.0f, 3.0f) }, glm::vec3{ random(0.0f, 360.0f), random(0.0f, 360.0f), random(0.0f, 360.0f)}, glm::vec3{random(0.1f, .4f)});
				scene.AddObject(std::move(object));
			}

			// add sphere to the scene
		}
	}

	auto triangle = std::make_unique<Triangle>(glm::vec3{ 30, 100, -5 }, glm::vec3{ -30, 100, -5 }, glm::vec3{ 0, -4, -5 }, std::make_shared<Emissive>(glm::vec3{ 1 }, 3.0f));
	scene.AddObject(std::move(triangle));

}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 7 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//floor
	auto material = std::make_shared<Lambertian>(color3_t{ 1 });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, material);
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1.0f, 1.0f, 1.0f }));
	mesh->Load("models/cube-1.obj", glm::vec3{ 0, .4f, 0 }, glm::vec3{ 0, 45, 0 }, glm::vec3{ 0.5f });
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1.0f, 0.6f, 0.6f }));
	mesh->Load("models/cube-1.obj", glm::vec3{ -5.0f, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 6 });
	scene.AddObject(std::move(mesh));

	/*mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1 }));
	mesh->Load("models/cube-1.obj", glm::vec3{ 0, 0, 5 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 6 });
	scene.AddObject(std::move(mesh));*/


	mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1.0f }));
	mesh->Load("models/cube-1.obj", glm::vec3{ 0, 0, -5 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 6 });
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.6f, 1.0f, 0.6f }));
	mesh->Load("models/cube-1.obj", glm::vec3{ 5.0f, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 6 });
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1.0, 0.5f, 1 }));
	mesh->Load("models/cube-1.obj", glm::vec3{ 0, 5.5f, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 6 });
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 3, 3, 3 }, 50.0f));
	mesh->Load("models/cube-1.obj", glm::vec3{ 0, 4, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1 });
	scene.AddObject(std::move(mesh));
}