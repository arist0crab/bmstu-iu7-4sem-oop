#pragma once

class BaseCommand
{
    public:
        BaseCommand() = default;
        virtual ~BaseCommand() = default;

        virtual void execute() = 0;
};

// TODO переделать нахер команды они ужасно выглядят