#include "TrashTheCache.h"

#include <algorithm>
#include <chrono>
#include <imgui.h>
#include <numeric>

#include "GameObject.h"

rift2d::TrashTheCache::TrashTheCache(GameObject* owner):
BaseComponent(owner)
{
}

void rift2d::TrashTheCache::init()
{
	BaseComponent::init();
	m_pLineGraph = getOwner()->addComponent<LineGraph>("GameObject3D");
	m_pLineGraphAlt = getOwner()->addComponent<LineGraph>("GameObject3DAlt");
	m_pLineGraphCombined = getOwner()->addComponent<LineGraph>("Combined");
	m_pLineGraphBasic = getOwner()->addComponent<LineGraph>("Basic");

	m_pLineGraph->registerWatcher(this);
	m_pLineGraphAlt->registerWatcher(this);
	m_pLineGraphCombined->registerWatcher(this);
	m_pLineGraphBasic->registerWatcher(this);

	m_pLineGraph->addLine("GameObject3D");
	m_pLineGraphAlt->addLine("GameObject3DAlt");
	m_pLineGraphCombined->addLine("GameObject3D");
	m_pLineGraphCombined->addLine("GameObject3DAlt");
	m_pLineGraphBasic->addLine("Basic");
}

void rift2d::TrashTheCache::update()
{
	if (m_shouldTrashGameObj) TrashTheCacheEx2();
	if (m_shouldTrashGameObjAlt) TrashTheCacheEx3();
	if (m_shouldTrashBasic) TrashTheCacheEx1();
}

void rift2d::TrashTheCache::onImGui()
{
	ImGui::Begin("Exercise 2");
	ImGui::InputInt("# samples", &m_nrSamples);

	if(!m_shouldTrashGameObj)
	{
		if (ImGui::Button("Trash the cache with GameObject3D"))
		{
			m_shouldTrashGameObj = true;
			m_pLineGraph->setShouldPlot(false);
		}
	}
	else
	{
		ImGui::Text("Wait for it ...");
	}

	if(!m_shouldTrashGameObjAlt)
	{
		if (ImGui::Button("Trash the cache with GameObject3DAlt"))
		{
			m_shouldTrashGameObjAlt = true;
			m_pLineGraphAlt->setShouldPlot(false);
		}
	}
	else
	{
		ImGui::Text("Wait for it ...");
	}

	ImGui::End();

	ImGui::Begin("Exercise 1");
	ImGui::InputInt("# samples", &m_nrSamples);
	if (!m_shouldTrashBasic)
	{
		if (ImGui::Button("Trash the cache basic"))
		{
			m_shouldTrashBasic = true;
			m_pLineGraphBasic->setShouldPlot(false);
		}
	}
	else
	{
		ImGui::Text("Wait for it ...");
	}
	ImGui::End();

}

void rift2d::TrashTheCache::end()
{
	if(m_pLineGraph)
	{
		m_pLineGraph->unregisterWatcher(this);
		m_pLineGraph = nullptr;
	}
	if(m_pLineGraphAlt)
	{
		m_pLineGraphAlt->unregisterWatcher(this);
		m_pLineGraphAlt = nullptr;
	}
	if (m_pLineGraphCombined)
	{
		m_pLineGraphCombined->unregisterWatcher(this);
		m_pLineGraphCombined = nullptr;
	}
	if (m_pLineGraphBasic)
	{
		m_pLineGraphBasic->unregisterWatcher(this);
		m_pLineGraphBasic = nullptr;
	}

}

void rift2d::TrashTheCache::onComponentRemoved(BaseComponent* component)
{
	//Incomplete, removing 1 of the line graphs will remove all
	if (component == static_cast<BaseComponent*>(m_pLineGraph))
	{
		m_pLineGraph = nullptr;
	}

	if (component == static_cast<BaseComponent*>(m_pLineGraphAlt))
	{
		m_pLineGraph = nullptr;
	}

	if (component == static_cast<BaseComponent*>(m_pLineGraphCombined))
	{
		m_pLineGraphCombined = nullptr;
	}
	if (component == static_cast<BaseComponent*>(m_pLineGraphBasic))
	{
		m_pLineGraphBasic = nullptr;
	}
}

void rift2d::TrashTheCache::TrashTheCacheEx1()
{
	m_shouldTrashBasic = false;
	const int size = static_cast<int>(std::pow(2, 26));
	std::vector<int> arr(size);

	m_pLineGraphBasic->clearData(0);
	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		std::vector<float> timings;
		timings.reserve(m_nrSamples);

		for (int rep = 0; rep < m_nrSamples; ++rep)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < size; i += stepSize)
			{
				arr[i] *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration<float, std::micro>(end - start).count();
			timings.push_back(elapsedTime);

			std::sort(timings.begin(), timings.end());
			if (timings.size() > 2)
			{
				timings.erase(timings.begin());
				timings.pop_back();
			}
			const float averageTime = std::accumulate(timings.begin(), timings.end(), 0.0f) / static_cast<float>(timings.size());
			m_pLineGraphBasic->addDataPoint(0, static_cast<float>(stepSize), averageTime);
		}

		m_pLineGraphBasic->setShouldPlot(true);
	}
}

void rift2d::TrashTheCache::TrashTheCacheEx2()
{
	m_shouldTrashGameObj = false;

	const int size = static_cast<int>(std::pow(2, 26));
	std::vector<gameObject3D> arr(size);

	m_pLineGraph->clearData(0);
	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		std::vector<float> timings;
		timings.reserve(m_nrSamples);
		
		for (int rep = 0; rep < m_nrSamples; ++rep)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < size; i += stepSize)
			{
				arr[i].id *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration<float, std::micro>(end - start).count();
			timings.push_back(elapsedTime);
		}

		std::sort(timings.begin(), timings.end());
		if (timings.size() > 2)
		{
			timings.erase(timings.begin());
			timings.pop_back();
		}
		const float averageTime = std::accumulate(timings.begin(), timings.end(), 0.0f) / static_cast<float>(timings.size());
		m_pLineGraph->addDataPoint(0, static_cast<float>(stepSize),averageTime);
	}
	m_pLineGraph->setShouldPlot(true);

	if (m_pLineGraph->isPlotting() && m_pLineGraphAlt->isPlotting())
	{
		m_pLineGraphCombined->addDataPoints(0, m_pLineGraph->getDataX(0), m_pLineGraph->getDataY(0));
		m_pLineGraphCombined->addDataPoints(1, m_pLineGraphAlt->getDataX(0), m_pLineGraphAlt->getDataY(0));
		m_pLineGraphCombined->setShouldPlot(true);
	}
	else
	{
		m_pLineGraphCombined->setShouldPlot(false);
	}
}

void rift2d::TrashTheCache::TrashTheCacheEx3()
{
	m_shouldTrashGameObjAlt = false;

	const int size = static_cast<int>(std::pow(2, 26));
	std::vector<gameObject3DAlt> arr(size);

	m_pLineGraphAlt->clearData(0);
	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		std::vector<float> timings;
		timings.reserve(m_nrSamples);
		for (int rep = 0; rep < m_nrSamples; ++rep)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < size; i += stepSize)
			{
				arr[i].id *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			const float elapsedTime = std::chrono::duration<float, std::micro>(end - start).count();
			timings.push_back(elapsedTime);
		}

		std::sort(timings.begin(), timings.end());
		if (timings.size() > 2)
		{
			timings.erase(timings.begin());
			timings.pop_back();
		}
		const float averageTime = std::accumulate(timings.begin(), timings.end(), 0.0f) / static_cast<float>(timings.size());
		m_pLineGraphAlt->addDataPoint(0, static_cast<float>(stepSize), averageTime);
	}
	m_pLineGraphAlt->setShouldPlot(true);

	if (m_pLineGraph->isPlotting() && m_pLineGraphAlt->isPlotting())
	{
		m_pLineGraphCombined->addDataPoints(0, m_pLineGraph->getDataX(0), m_pLineGraph->getDataY(0));
		m_pLineGraphCombined->addDataPoints(1, m_pLineGraphAlt->getDataX(0), m_pLineGraphAlt->getDataY(0));
		m_pLineGraphCombined->setShouldPlot(true);
	}
	else
	{
		m_pLineGraphCombined->setShouldPlot(false);
	}
}


