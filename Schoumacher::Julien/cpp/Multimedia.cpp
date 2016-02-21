#include "Multimedia.hpp"


Multimedia::Multimedia(const std::string& name, const std::string& path)
{
    this->name = name;
    this->path = path;
}

Multimedia::~Multimedia()
{}

std::ostream& Multimedia::operator << (std::ostream& oss) const
{return print(oss);}

///Default print method
std::ostream& Multimedia::print(std::ostream& oss) const
{
    oss<<"Multimedia object "<<name<<" with path "<<path<<std::endl;
    return oss;
}
