#pragma once
#include <cstdint>
#include <string>


namespace rift2d
{
    
    class IRenderable
    {
    public:
        virtual void render() const = 0;
        virtual ~IRenderable() = default;
    };

    class BaseComponent;
    class IComponentWatcher
    {
    public:
        virtual void onComponentRemoved(BaseComponent* component) = 0;
        virtual ~IComponentWatcher() = default;
    };

    class ICommand
    {
    public:
        virtual ~ICommand() = default;
        virtual void execute() = 0;
    };

    using soundId = uint8_t;
    class ISoundSystem
    {
    public:
        virtual ~ISoundSystem() = default;
        virtual void play(const soundId id, const float volume = 1.f) = 0;
        virtual void setPath(const std::string& dataPath) = 0;
        virtual void addSoundMapping(int id, const std::string& filename) = 0;
    };

    class GameObject;
    class IState
    {
    public:
        virtual ~IState() = default;
        virtual void onEnter(GameObject* gameObject) = 0;
        virtual void update(GameObject* gameObject) = 0;
        virtual void onExit(GameObject* gameObject) = 0;
    };


}
