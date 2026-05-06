#include "BaseObject.hpp"


class InvisibleObject : public BaseObject
{
    public:
        InvisibleObject() = default;
        virtual ~InvisibleObject() override = default;

        bool isVisible() const noexcept override { return false; }
        bool isComposite() const noexcept override { return false; }
};