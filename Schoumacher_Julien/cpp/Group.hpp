#ifndef MULTIMEDIAGROUP_HPP
#define MULTIMEDIAGROUP_HPP


#include <iostream>
#include <memory>
#include <string>
#include <list>

#include "Multimedia.hpp"


template <typename T>
class Group : public std::list<std::shared_ptr<T> >, public Multimedia
{
    public:
        Group(const std::string& name);
        Group(const std::string& name, const std::list<std::shared_ptr<T> >& l);
        ~Group();

        ///Redefinition of print method///
        std::ostream& print(std::ostream& oss) const;

        ///Redefinition of execute method : that executes all the execute methods of objects in group///
        void execute() const;

        inline void setName(const std::string& str) {name = str;}
        inline std::string getName() const {return name;}

    private:
        std::string name;
};


///We redefine the operator << in order to call ofstream<<(a group) easily///
template <typename T>
inline std::ostream& operator<<(std::ostream& oss, const Group<T>& gr)
{
    return gr.print(oss);
}


template <typename T>
Group<T>::Group(const std::string& name)
{this->name = name;}

template <typename T>
Group<T>::Group(const std::string& name, const std::list<std::shared_ptr<T> >& l) :
    std::list<std::shared_ptr<T> >(l)
{this->name = name;}

template <typename T>
Group<T>::~Group()
{
    std::cout<<"Destruction group "<<name<<std::endl;
}

template <typename T>
std::ostream& Group<T>::print(std::ostream& oss) const
{
    oss<<"Group "<<name<<" :"<<std::endl;
    for(typename std::list<std::shared_ptr<T> >::const_iterator it=this->begin();it!=this->end();it++)
        oss<<(*(*it));
    return oss;
}

template <typename T>
void Group<T>::execute() const
{
    for(typename std::list<std::shared_ptr<T> >::const_iterator it=this->begin();it!=this->end();it++)
        (*it)->execute();
}


#endif
