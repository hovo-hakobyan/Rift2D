#include "SpriteRenderer.h"
#include "Renderer.h"
#include "ResourceManager.h"

void rift2d::SpriteRenderer::Render() const
{
	//const auto& pos = m_transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void rift2d::SpriteRenderer::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}
