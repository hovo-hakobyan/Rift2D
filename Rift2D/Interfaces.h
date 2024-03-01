#pragma once
namespace rift2d
{
    
    class IRenderable
    {
    public:
        virtual void Render() const = 0;
    };

    class BaseComponent;
    class IComponentWatcher
    {
    public:
        virtual void OnComponentRemoved(BaseComponent* component) = 0;
    };
}