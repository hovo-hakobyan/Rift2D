#pragma once

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

}
