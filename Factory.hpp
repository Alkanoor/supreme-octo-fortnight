#ifndef FACTORY_HPP_INCLUDED
#define FACTORY_HPP_INCLUDED


#include <memory>
#include <map>

#include "Photo.hpp"
#include "Group.hpp"
#include "Film.hpp"


class Factory
{
    public:
        std::shared_ptr<Multimedia> createFilm(const std::string& path, const std::string& name);
        std::shared_ptr<Multimedia> createVideo(const std::string& path, const std::string& name);
        std::shared_ptr<Multimedia> createPhoto(const std::string& path, const std::string& name);
        std::shared_ptr<Multimedia> createGroup(const std::string& name);
        std::shared_ptr<Multimedia> createGroup(const std::string& name, const std::list<std::shared_ptr<Multimedia> >& l);

        ///Add multimedia object (can be a group) inside the name referenced map of multimedia objects///
        void addMultimedia(const std::string& name, std::shared_ptr<Multimedia> multimedia);
        ///Add group of multimedia object inside the name referenced map of group objects///
        void addMultimediaGroup(const std::string& name, std::shared_ptr<Group<Multimedia> > multimedia);

        ///Delete an object by its name, either if it's in map of multimedia objects or in map of group objects. Return true if some objects have been found and deleted///
        bool deleteByName(const std::string& name);
        ///Search an object by its name, only if it's in map of multimedia objects///
        std::shared_ptr<Multimedia> searchByName(const std::string& name);
        ///Print an object by its name, either if it's in map of multimedia objects or in map of group objects///
        void printByName(const std::string& name);
        ///Print an object by its name in argument ofstream, either if it's in map of multimedia objects or in map of group objects///
        void printByName(const std::string& name, std::ofstream& stream);
        ///Call the execute method an object identified by its name, either if it's in map of multimedia objects or in map of group objects///
        void play(const std::string& name);

        std::ostream& operator << (std::ostream& oss) const;
        std::ostream& print(std::ostream& oss) const;

    private:
        std::map<std::string,std::shared_ptr<Multimedia> > multimediaObjects;
        std::map<std::string,std::shared_ptr<Group<Multimedia> > > groupObjects;
};


#endif
