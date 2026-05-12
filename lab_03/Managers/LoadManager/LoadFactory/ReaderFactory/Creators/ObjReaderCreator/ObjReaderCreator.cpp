#include "ObjReaderCreator.hpp"


std::shared_ptr<BaseReader> ObjReaderCreator::createReader()
{
    return std::make_shared<ObjReader>();
}