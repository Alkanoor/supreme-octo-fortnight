#include "Film.hpp"


Film::Film() :
    chapterNumber(0)
{}

Film::Film(int delay) :
    Video(delay),
    chapters(nullptr),
    chapterNumber(0)
{}

Film::Film(const std::string& name, const std::string& path, int delay) :
    Video(name,path,delay),
    chapters(nullptr),
    chapterNumber(0)
{}

Film::Film(const std::string& name, const std::string& path, int* chapters, unsigned int chapterNumber) :
    Video(name,path),
    chapters(nullptr),
    chapterNumber(0)
{
    setChaptersRelative(chapters, chapterNumber);
}

Film::Film(const Film& film) :
    Video(film),
    chapters(nullptr),
    chapterNumber(0)
{
    setChapters(film.chapters,film.chapterNumber);
}

Film::~Film()
{
    resetChapters();
}

Film& Film::operator = (const Film& film)
{
    setName(film.name);
    setPath(film.path);
    setChapters(film.chapters,film.chapterNumber);
    return *this;
}

std::ostream& Film::print(std::ostream& oss) const
{
    oss<<"Film object "<<name<<" with path "<<path<<". Length : "<<delay<<" ms"<<std::endl;
    for(unsigned int i=0;i<chapterNumber;i++)
        oss<<"Chapter "<<i<<" : "<<chapters[i]<<std::endl;
    return oss;
}

void Film::setChaptersRelative(int* chapters, unsigned int chapterNumber)
{
    resetChapters();
    this->chapterNumber = chapterNumber;
    delay = 0;
    if(chapterNumber>0)
    {
        this->chapters = new int[chapterNumber];
        delay += chapters[0];
        this->chapters[0] = chapters[0];
        for(unsigned int i=1;i<chapterNumber;i++)
        {
            delay += chapters[i];
            this->chapters[i] = chapters[i]+this->chapters[i-1];
        }
    }
}

void Film::setChapters(int* chapters, unsigned int chapterNumber)
{
    resetChapters();
    this->chapterNumber = chapterNumber;
    delay = 0;
    if(chapterNumber>0)
    {
        this->chapters = new int[chapterNumber];
        for(unsigned int i=0;i<chapterNumber;i++)
        {
            delay += chapters[i];
            this->chapters[i] = chapters[i];
        }
    }
}

void Film::resetChapters()
{
    if(chapterNumber>0)
    {
        delete[] chapters;
        chapters = nullptr;
        chapterNumber = 0;
    }
}
