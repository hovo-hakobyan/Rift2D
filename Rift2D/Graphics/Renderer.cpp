#include <stdexcept>
#include <cstring>
#include "Renderer.h"
#include <imgui.h>
#include <iostream>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include <glm/detail/func_trigonometric.inl>

#include "SceneManager.h"
#include "Texture2D.h"
#include "Interfaces.h"
#include "implot.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}





void rift2d::Renderer::init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
	ImPlot::CreateContext();
}

void rift2d::Renderer::render() const
{
	const auto& color = getBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	for (auto& renderable : m_renderables)
	{
		renderable->render();
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	SceneManager::GetInstance().onImGui();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void rift2d::Renderer::destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	ImPlot::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void rift2d::Renderer::reset()
{
	m_renderables.clear();
}

void rift2d::Renderer::renderTexture(const Texture2D& texture, const float x, const float y, float angle) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.getSdlTexture(), nullptr, nullptr, &dst.w, &dst.h);

	SDL_Point centerPt;
	centerPt.x = dst.w / 2;
	centerPt.y = dst.h / 2;

	SDL_RendererFlip flip{SDL_FLIP_NONE};
	if ((angle > 135) && (angle <= 225))
	{
		// Left
		flip = SDL_FLIP_VERTICAL;
	}

	// Render with rotation
	SDL_RenderCopyEx(m_renderer, texture.getSdlTexture(), nullptr, &dst, angle, &centerPt, flip);
}


void rift2d::Renderer::renderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, float angle) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_Point centerPt;
	centerPt.x = dst.w / 2;
	centerPt.y = dst.h / 2;


	SDL_RenderCopyEx(m_renderer, texture.getSdlTexture(), nullptr, &dst,angle,&centerPt, SDL_FLIP_NONE);
}

void rift2d::Renderer::renderBox(const float x, const float y, const float width, const float height,
	RiftColor color) const
{
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(m_renderer, &r, &g, &b, &a);
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	SDL_Rect rect{};
	rect.x = static_cast<int>(x);
	rect.y = static_cast<int>(y);
	rect.w = static_cast<int>(width);
	rect.h = static_cast<int>(height);

	SDL_RenderDrawRect(m_renderer, &rect);
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

SDL_Renderer* rift2d::Renderer::getSDLRenderer() const { return m_renderer; }

glm::vec2 rift2d::Renderer::getWindowSize() const
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(m_window, &width, &height);
	return glm::vec2{ width,height };
}

void rift2d::Renderer::registerComponent(IRenderable* component)
{
	m_renderables.push_back(component);
}

void rift2d::Renderer::unregisterComponent(IRenderable* component)
{
	auto newEnd = std::remove(m_renderables.begin(), m_renderables.end(), component);
	m_renderables.erase(newEnd, m_renderables.end());
}
