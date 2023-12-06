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
	int samples = 5;
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

		

	// create material
	auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

	// create material
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	/*for (int i = 0; i < 35; i++)
	{
		auto lambertian = std::make_shared<Lambertian>(color3_t{ random(.5f, 1.0f), random(.5f, 1.0f), random(.5f, 1.0f) });
		std::shared_ptr<Material> material = (int(random(0, 100)) >= 25) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(random({ -10, -5, -15 }, { 10, 5, -5 }), random01() * 3, material);
		scene.AddObject(std::move(sphere));
	}*/

	//auto lambertian = std::make_shared<Lambertian>(color3_t{ random(.5f, 1.0f), random(.5f, 1.0f), random(.5f, 1.0f) });
	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 1, 1 }, glm::vec3{ 1, 1, 1 }, glm::vec3{ 1.5f, 2, 1 }, lambertian);
	//scene.AddObject(std::move(triangle));

	/*

	//floor
	material = std::make_shared<Lambertian>(color3_t{ .8f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, material);
	scene.AddObject(std::move(plane));
	
	////back wall
	//plane = std::make_unique<Plane>(glm::vec3{ 0, 0, -5 }, glm::vec3{ 0, 0, 1 }, material);
	//scene.AddObject(std::move(plane));

	////left wall
	//material = std::make_shared<Lambertian>(color3_t{ 0.8f, .2f, .2f });
	//plane = std::make_unique<Plane>(glm::vec3{ 0, 0, -5 }, glm::vec3{ 1, 0, 0 }, material);
	//scene.AddObject(std::move(plane));

	//for (int x = -10; x < 0; x++)
	//{
	//	for (int z = -1; z < 0; z++)
	//	{

	//		std::shared_ptr<Material> material;

	//		// create random material
	//		float r = random01();
	//		if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
	//		else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
	//		else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
	//		else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

	//		// set random sphere radius
	//		float radius = random(0.2f, 0.3f);
	//		// create sphere using random radius and material
	//		auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
	//		// add sphere to the scene
	//		scene.AddObject(std::move(sphere));
	//	}
	//}

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.6f, 0.4f, 0.4f }));
	mesh->Load("models/cube-1.obj", glm::vec3{ 0, .4f, 0 }, glm::vec3{ 0, 45, 0 }, glm::vec3{5});
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1.0f, 0.6f, 0.6f }));
	mesh->Load("models/cube-1.obj", glm::vec3{ -4, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 5 });
	scene.AddObject(std::move(mesh));
		*/

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
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}