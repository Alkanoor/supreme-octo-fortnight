#include "Factory.hpp"


std::shared_ptr<Multimedia> Factory::createFilm(const std::string& path, const std::string& name)
{
    throwIfBadName(name);
    auto tmp = std::shared_ptr<Film>(new Film(name,path,-1));
    throwIfNameExistsInMultimedia(name);
    multimediaObjects[name] = tmp;
    return tmp;
}

std::shared_ptr<Multimedia> Factory::createVideo(const std::string& path, const std::string& name)
{
    throwIfBadName(name);
    auto tmp = std::shared_ptr<Video>(new Video(name,path,-1));
    throwIfNameExistsInMultimedia(name);
    multimediaObjects[name] = tmp;
    return tmp;
}

std::shared_ptr<Multimedia> Factory::createPhoto(const std::string& path, const std::string& name)
{
    throwIfBadName(name);
    auto tmp = std::shared_ptr<Photo>(new Photo(name,path,-1,-1));
    throwIfNameExistsInMultimedia(name);
    multimediaObjects[name] = tmp;
    return tmp;
}

std::shared_ptr<Multimedia> Factory::createGroup(const std::string& name)
{
    throwIfBadName(name);
    auto tmp = std::shared_ptr<Group<Multimedia> >(new Group<Multimedia>(name));
    throwIfNameExistsInGroups(name);
    groupObjects[name] = tmp;
    return tmp;
}

std::shared_ptr<Multimedia> Factory::createGroup(const std::string& name, const std::list<std::shared_ptr<Multimedia> >& l)
{
    throwIfBadName(name);
    auto tmp = std::shared_ptr<Group<Multimedia> >(new Group<Multimedia>(name,l));
    throwIfNameExistsInGroups(name);
    groupObjects[name] = tmp;
    return tmp;
}

void Factory::addMultimedia(const std::string& name, std::shared_ptr<Multimedia> multimedia)
{
    throwIfBadName(name);
    throwIfNameExistsInMultimedia(name);
    multimediaObjects[name] = multimedia;
}

void Factory::addMultimediaGroup(const std::string& name, std::shared_ptr<Group<Multimedia> > multimedia)
{
    throwIfBadName(name);
    throwIfNameExistsInGroups(name);
    groupObjects[name] = multimedia;
}

bool Factory::deleteByName(const std::string& name)
{
    return multimediaObjects.erase(name)||groupObjects.erase(name);
}

std::shared_ptr<Multimedia> Factory::searchByName(const std::string& name)
{
    auto it = multimediaObjects.find(name);
    if(it != multimediaObjects.end())
        return it->second;
    else
    {
        auto it2 = groupObjects.find(name);
        if(it2 != groupObjects.end())
            return it2->second;
    }
    return std::shared_ptr<Multimedia>();
}

void Factory::printByName(const std::string& name)
{
    auto it1 = multimediaObjects.find(name);
    if(it1 != multimediaObjects.end())
        std::cout<<*(it1->second);
    auto it2 = groupObjects.find(name);
    if(it2 != groupObjects.end())
        std::cout<<*(it2->second);
}

void Factory::printByName(const std::string& name, std::ostream& ofs)
{
    auto it1 = multimediaObjects.find(name);
    if(it1 != multimediaObjects.end())
        ofs<<*(it1->second);
    auto it2 = groupObjects.find(name);
    if(it2 != groupObjects.end())
        ofs<<*(it2->second);
}

void Factory::play(const std::string& name)
{
    auto it1 = multimediaObjects.find(name);
    if(it1 != multimediaObjects.end())
        it1->second->execute();
    auto it2 = groupObjects.find(name);
    if(it2 != groupObjects.end())
        it2->second->execute();
}


std::ostream& Factory::operator << (std::ostream& oss) const
{return print(oss);}

std::ostream& Factory::print(std::ostream& oss) const
{
    oss<<"Factory object which contains"<<std::endl;
    for(auto it=multimediaObjects.begin();it!=multimediaObjects.end();it++)
        oss<<"Multimedia object : "<<(*it->second)<<std::endl;
    for(auto it=groupObjects.begin();it!=groupObjects.end();it++)
        oss<<"Group object : "<<(*it->second)<<std::endl;
    return oss;
}


void Factory::throwIfBadName(const std::string& name)
{
    for(unsigned int i=0;i<name.size();i++)
        if(name[i]<32||name[i]>127)
            throw std::string("Bad char in name");
}

void Factory::throwIfNameExistsInMultimedia(const std::string& name)
{
    if(multimediaObjects.count(name))
        throw std::string("Multimedia object existing");
}

void Factory::throwIfNameExistsInGroups(const std::string& name)
{
    if(groupObjects.count(name))
        throw std::string("Group existing");
}
