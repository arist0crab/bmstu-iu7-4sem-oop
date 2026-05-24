#include "Director.hpp"
#include "ReaderSolution.hpp"
#include "BuilderSolution.hpp"

std::shared_ptr<BaseObject> Director::build(const std::string &filename, const std::string &builderType)
{
    auto readerCreator = ReaderSolution::getCreator(filename);
    if (!readerCreator)
        return nullptr;

    auto reader = readerCreator->createReader();
    if (!reader)
        return nullptr;

    auto builder = BuilderSolution::create(builderType);
    if (!builder)
        return nullptr;

    reader->open(filename);

    auto vertices = reader->readVertices();
    auto edges = reader->readEdges();

    for (auto &v : vertices)
        builder->buildVertex(v);

    for (auto &e : edges)
        builder->buildEdge(e.getStart(), e.getEnd());

    reader->close();

    return builder->getResult();
}