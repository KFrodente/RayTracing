#pragma once
#include "Color.h"
#include "Ray.h"
#include "Camera.h"
#include <memory>
#include <vector>
#include "Object.h"

class Scene
{
public:
	Scene() = default;
	Scene(const color3_t& topColor, const color3_t& bottomColor) :
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}

	color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);
	void AddObject(std::unique_ptr<Object> object) { m_objects.push_back(std::move(object)); }

	void Render(class Canvas& canvas, int numSamples, int depth);
	color3_t Trace(const ray_t& ray);

	void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

private:
	std::shared_ptr<Camera> m_camera;
	std::vector<std::unique_ptr<Object>> m_objects;

	//int m_depth{ 5 };

	/*color3_t m_topColor{ 0.8f, 0.1f, 1.0f };
	color3_t m_bottomColor{ 0.5f, 0.8f, 1.0f };*/
	color3_t m_topColor{ .6f, .75f, .9f };
	color3_t m_bottomColor{ .9f, .6f, .8f };
	/*color3_t m_topColor{ 0.0f, .25f, 1.0f };
	color3_t m_bottomColor{ 1, 1, 1 };*/
};