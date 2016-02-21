#include "Photo.hpp"


Photo::Photo(float lattitude, float longitude)
{
    this->lattitude = lattitude;
    this->longitude = longitude;
}

Photo::Photo(const std::string& name, const std::string& path, float lattitude, float longitude) :
    Multimedia(name,path)
{
    this->lattitude = lattitude;
    this->longitude = longitude;
}

Photo::~Photo()
{}

std::ostream& Photo::print(std::ostream& oss) const
{
    oss<<"Photo object "<<name<<" with path "<<path<<". Lattitude : "<<lattitude<<" and longitude : "<<longitude<<std::endl;
    return oss;
}

void Photo::execute() const
{
    system(("display "+path+"/"+name+" &").c_str());
}

void Photo::setLattitude(float lattitude)
{this->lattitude = lattitude;}

void Photo::setLongitude(float longitude)
{this->longitude = longitude;}

float Photo::getLattitude() const
{return lattitude;}

float Photo::getLongitude() const
{return longitude;}
