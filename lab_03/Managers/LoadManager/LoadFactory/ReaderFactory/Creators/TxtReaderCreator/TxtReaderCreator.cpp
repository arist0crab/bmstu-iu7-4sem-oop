#include "TxtReaderCreator.hpp"


std::shared_ptr<BaseReader> TxtReaderCreator::createReader()
{   
    return std::make_shared<TxtReader>();
}