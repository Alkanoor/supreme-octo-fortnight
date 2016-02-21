#ifndef FILM_HPP
#define FILM_HPP


#include "Video.hpp"


class Film : public Video
{
    public:
        Film();
        Film(int delay);
        Film(const std::string& name, const std::string& path, int delay=0);
        Film(const std::string& name, const std::string& path, int* chapters, unsigned int chapterNumber);
        Film(const Film& film);
        ~Film();

        ///Redefinition of affectation operator because of pointers to copy
        Film& operator = (const Film& film);

        ///Redefinition of print method allowing child redefinition too
        std::ostream& print(std::ostream& oss) const;

        void setChaptersRelative(int* chapters, unsigned int chapterNumber);
        void setChapters(int* chapters, unsigned int chapterNumber);
        inline const int* const getChapters() const {return chapters;}
        inline unsigned int getChapterNumber() const {return chapterNumber;}

    private:
        int* chapters;
        unsigned int chapterNumber;

        void resetChapters();
};


#endif
