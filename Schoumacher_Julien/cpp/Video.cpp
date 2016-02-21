#include "Video.hpp"


Video::Video(int delay)
{
    this->delay = delay;
}

Video::Video(const std::string& name, const std::string& path, int delay) :
    Multimedia(name,path)
{
    this->delay = delay;
}

Video::~Video()
{}

std::ostream& Video::print(std::ostream& oss) const
{
    oss<<"Video object "<<name<<" with path "<<path<<". Length : "<<delay<<" ms"<<std::endl;
    return oss;
}

void Video::execute() const
{
    return (void)system(("mpv "+path+"/"+name+" &").c_str());
}

void Video::setDelay(int delay)
{this->delay = delay;}

int Video::getDelay() const
{return delay;}
