#ifndef PHOTO_HPP
#define PHOTO_HPP


#include <cstdlib>

#include "Multimedia.hpp"


class Photo : public Multimedia
{
    public:
        Photo(float lattitude, float longitude);
        Photo(const std::string& name, const std::string& path, float lattitude=0, float longitude=0);
        ~Photo();

        ///Redefinition of print method///
        std::ostream& print(std::ostream& oss) const;

        ///Open the photo inside Unix environment (doesn't work within windows if no unix environment with display command is installed)///
        void execute() const;

        inline void setLattitude(float lattitude);
        inline void setLongitude(float lattitude);
        inline float getLattitude() const;
        inline float getLongitude() const;

    private:
        float lattitude;
        float longitude;
};


#endif
