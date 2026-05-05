#pragma once

class ManagerSolution
{
    public:
        ManagerSolution() = delete;
        ~ManagerSolution() = delete;

        static std::shared_ptr<> getLoadManager();
        static std::shared_ptr<> getDrawManager();
        static std::shared_ptr<> getCameraManager();
        static std::shared_ptr<> getTransformManager();
        static std::shared_ptr<> getSceneManager();
};
