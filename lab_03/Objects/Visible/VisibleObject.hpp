#include "BaseObject.hpp"


class VisibleObject : public BaseObject
{
    public:
        VisibleObject() = default;
        virtual ~VisibleObject() override = default;

        bool isVisible() const noexcept override { return true; }
        bool isComposite() const noexcept override { return false; }
};