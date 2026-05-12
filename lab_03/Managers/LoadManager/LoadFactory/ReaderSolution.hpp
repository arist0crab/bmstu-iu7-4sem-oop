#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include "BaseReaderCreator.hpp"
#include "TxtReaderCreator.hpp"
#include "ObjReaderCreator.hpp"

class ReaderSolution
{
    public:
        static std::shared_ptr<BaseReader> create(const std::string &filename)
        {
            static const std::unordered_map<std::string, std::shared_ptr<BaseReaderCreator>> creators = {
                {".txt", std::make_shared<TxtReaderCreator>()},
                {".obj", std::make_shared<ObjReaderCreator>()}
            };
            
            auto ext = filename.substr(filename.find_last_of('.'));
            auto it = creators.find(ext);
            
            return (it != creators.end()) ? it->second->createReader() : nullptr;
        }
};