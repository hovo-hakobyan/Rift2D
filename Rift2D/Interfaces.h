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

    class GameObject;
    class ICommand
    {
    public:
        ICommand(GameObject* Obj): m_pObj(Obj){}
        virtual ~ICommand() = default;
        virtual void execute() = 0;
        GameObject* getObject() const { return m_pObj; }

    private:
        GameObject* m_pObj;
    };

}
