#pragma once
namespace rift2d
{
    class IRenderable
    {
    public:
        virtual void Render() const = 0;
    };
}