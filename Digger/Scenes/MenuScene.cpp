#include "MenuScene.h"
#include <imgui.h>
#include <iostream>

#include "Digger/DiggerGameMode.h"
#include "GameModeManager.h"
#include "GameScene.h"
#include "InputManager.h"
#include "Physics.h"
#include "Rift2DEngine.h"
#include "SceneManager.h"
#include "ScoreSave.h"
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

    m_pGameMode = dynamic_cast<DiggerGameMode*>(rift2d::GameModeManager::GetInstance().getGameMode());
}

void digger::MenuScene::onActivate()
{
    rift2d::InputManager::GetInstance().enableInput();
    rift2d::Physics::GetInstance().disable();

    auto scoreSave = std::make_unique<rift2d::ScoreSave>("diggerScore.rdata");
    scoreSave->update(m_pGameMode->getCurrentPlyerName(), m_pGameMode->getScore());

}

void digger::MenuScene::onImGui()
{
    ImVec2 windowSize(400, 200); 
    ImVec2 windowPos = ImVec2((ImGui::GetIO().DisplaySize.x - windowSize.x) * 0.5f, (ImGui::GetIO().DisplaySize.y - windowSize.y) * 0.5f);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(windowSize);

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

    //player name input
    static char playerName[16];
    ImGui::InputText("Player name", playerName, sizeof(playerName));
    ImGui::Spacing(); ImGui::Spacing();

    if (ImGui::Button("WorldBuilder"))
    {
        rift2d::SceneManager::GetInstance().addScene(std::make_unique<WorldBuilderScene>());
        rift2d::SceneManager::GetInstance().setActiveScene("WorldBuilderScene");
        if (m_pGameMode)
        {
            m_pGameMode->setCurrentPlayerName("");
        }
    }

    ImGui::Spacing(); ImGui::Spacing();

    if (ImGui::Button("Play"))
    {
        rift2d::SceneManager::GetInstance().addScene(std::make_unique<GameScene>(0));
        rift2d::SceneManager::GetInstance().setActiveScene("level0");
        if(m_pGameMode)
        {
            m_pGameMode->setCurrentPlayerName(playerName);
        }
    }

    ImGui::Spacing(); ImGui::Spacing();

    if (ImGui::Button("Quit"))
    {
        rift2d::Rift2DEngine::quitGame();
    }
    ImGui::End();
}
