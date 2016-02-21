#ifndef VIDEO_HPP
#define VIDEO_HPP


#include <cstdlib>

#include "Multimedia.hpp"


class Video : public Multimedia
{
    public:
        Video(int delay=0);
        Video(const std::string& name, const std::string& path, int delay=0);
        virtual ~Video();

        ///Redefinition of print method allowing child redefinition too///
        virtual std::ostream& print(std::ostream& oss) const;

        ///Open the video inside Unix environment (doesn't work within windows if no unix environment with mpv command is installed)///
        virtual void execute() const;

        inline void setDelay(int delay);
        inline int getDelay() const;

    protected:
        int delay;
};


#endif
