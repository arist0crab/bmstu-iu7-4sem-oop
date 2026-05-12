#pragma once

#include <memory>


class ManagerSolution
{
    public:
        ManagerSolution() = default;
        virtual ~ManagerSolution() = default;

        template<typename TManager>
        static std::shared_ptr<TManager> getManager()
        {
            static auto instance = std::make_shared<TManager>();
            return instance;
        }
};