#pragma once

#include <memory>


class ManagerSolution
{
    public:
        ManagerSolution() = delete;

        template<typename TManager>
        static std::shared_ptr<TManager> getManager()
        {
            static auto instance = std::make_shared<TManager>();
            return instance;
        }
};