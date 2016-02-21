#ifndef MULTIMEDIA_HPP
#define MULTIMEDIA_HPP


#include <ostream>
#include <string>


class Multimedia
{
    public:
        Multimedia(const std::string& name="", const std::string& path="");
        virtual ~Multimedia() = 0;

        ///Redefinition of operator << in order to print objects easily///
        std::ostream& operator << (std::ostream& oss) const;
        ///The virtual method print allow a redefinition of the way we want to print certain objects///
        virtual std::ostream& print(std::ostream& oss) const;

        ///The virtual method execute allow playing the resource on the sever///
        virtual void execute() const {}

        inline void setName(const std::string& name) {this->name = name;}
        inline void setPath(const std::string& path) {this->path = path;}

        inline const std::string& getName() const {return name;}
        inline const std::string& getPath() const {return path;}

    protected:
        std::string name;
        std::string path;
};


///We redefine the operator << in order to call ofstream<<(a multimedia object) easily///
inline std::ostream& operator<<(std::ostream& oss, const Multimedia& val)
{
    return val.print(oss);
}


#endif
