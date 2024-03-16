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
        enum class BindingType
        {
            GamepadAction, KeyboardAction, GamepadAxis, KeyboardAxis
        };

        ICommand(GameObject* Obj): m_pObj(Obj){}
        virtual ~ICommand() = default;
        virtual void execute() = 0;
        GameObject* getObject() const { return m_pObj; }
        void setBindingType(BindingType type) { m_bindingType = type; }
        BindingType getBindingType() const { return m_bindingType; }
    private:
        GameObject* m_pObj;
        BindingType m_bindingType{};

    };

}
