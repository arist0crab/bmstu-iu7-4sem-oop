#pragma once

#include "BaseCommand.hpp"


class ObjectCommand : public BaseCommand
{
    public:
        ObjectCommand() = default;
        virtual ~ObjectCommand() = default;
};


class AddObjectCommand : public ObjectCommand
{   
    // TODO
};