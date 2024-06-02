#include "MenuScene.h"
#include <imgui.h>
#include "GameScene.h"
#include "Rift2DEngine.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "WorldBuilderScene.h"

digger::MenuScene::MenuScene():
Scene("MenuScene")
{
}

void digger::MenuScene::init()
{
    //Logo
    auto go = createGameObject();
    auto sprite = go->addComponent<rift2d::SpriteComponent>();
    sprite->setTexture("background.tga");
}

void digger::MenuScene::onImGui()
{
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    // Window flags
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoBackground;
    ImGui::Begin("Main Menu", nullptr, window_flags);

    if (ImGui::Button("WorldBuilder"))
    {
        rift2d::SceneManager::GetInstance().addScene(std::make_unique<WorldBuilderScene>());
        rift2d::SceneManager::GetInstance().setActiveScene("WorldBuilderScene");
    }

    ImGui::Spacing(); ImGui::Spacing();

    if (ImGui::Button("Play"))
    {
        rift2d::SceneManager::GetInstance().addScene(std::make_unique<GameScene>(0));
        rift2d::SceneManager::GetInstance().setActiveScene("level0");
    }

    ImGui::Spacing(); ImGui::Spacing();

    if (ImGui::Button("Quit"))
    {
        rift2d::Rift2DEngine::quitGame();
    }
    ImGui::End();
}
