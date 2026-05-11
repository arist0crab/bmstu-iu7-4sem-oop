#pragma once

#include <memory>
#include <BaseManager.hpp>

class ManagerSolution
{
    public:
        ManagerSolution() = default;
        ~ManagerSolution() = default;

        template<typename TManager>
        static std::shared_ptr<TManager> getManager();
};
