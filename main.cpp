#include "Processrequest.hpp"


const int DEFAULT_PORT = 33331;


int main()
{
    std::vector<std::shared_ptr<Multimedia> > multimediaElements;

    std::shared_ptr<Multimedia> tmp;
    std::shared_ptr<Group<Multimedia> > tmpGroup;
    std::shared_ptr<Factory> multimediaPool(new Factory());

    tmpGroup = std::shared_ptr<Group<Multimedia> >(new Group<Multimedia>("Videos"));
    int chapters[4] = {5000,1300,2200,1700};
    tmp = std::shared_ptr<Multimedia>(new Film("film1.3gp","../data",chapters,4));
    try
    {
        multimediaPool->addMultimedia("Film1\n\r",tmp); //should fail because of forbidden chars \r and \n
    }
    catch(std::exception& e)
    {
        std::cout<<"Test exception (should be printed if it works) : "<<e.what()<<std::endl;
    }
    multimediaPool->addMultimedia("Film1",tmp);
    try
    {
        multimediaPool->addMultimedia("Film1",tmp); //should fail because Film1 already exists in factory
    }
    catch(std::exception& e)
    {
        std::cout<<"Test exception (should be printed if it works) : "<<e.what()<<std::endl;
    }
    tmpGroup->push_back(tmp);
    tmp = std::shared_ptr<Multimedia>(new Video("video1.3gp","../data",1200));
    multimediaPool->addMultimedia("Video1",tmp);
    tmpGroup->push_back(tmp);
    multimediaPool->addMultimediaGroup("Videos",tmpGroup);

    tmpGroup = std::shared_ptr<Group<Multimedia> >(new Group<Multimedia>("Images"));
    tmp = std::shared_ptr<Multimedia>(new Photo("image1.ico","../data",128,128));
    multimediaPool->addMultimedia("Image1",tmp);
    tmpGroup->push_back(tmp);
    tmp = std::shared_ptr<Multimedia>(new Photo("image2.png","../data",256,256));
    multimediaPool->addMultimedia("Image2",tmp);
    tmpGroup->push_back(tmp);
    multimediaPool->addMultimediaGroup("Images",tmpGroup);


    std::shared_ptr<TCPServer> server(new TCPServer());
    ProcessRequest process(multimediaPool);
    server->setCallback(&process, &ProcessRequest::processRequest);

    int port = (argc>=2) ? atoi(argv[1]) : DEFAULT_PORT;
    std::cout<<"Starting server on port "<<port<<std::endl;
    int status = server->run(port);
    if(status<0)
    {
        std::cerr<<"Port already in use on port "<<port<<std::endl;
        return 1;
    }
    else
        return 0;
}


/*int main()
{
    std::vector<Multimedia*> multimedia;

    multimedia.push_back(new Photo("BAAL-BUG.png","/cal/homes/jschoumacher/Desktop/"));
    multimedia[multimedia.size()-1]->execute();

    int* chap = new int[50];
    for(unsigned int j=0;j<50;j++)
        chap[j] = j+5;
    Film* film = new Film("unexisting film","/cal/homes/jschoumacher/Desktop/",chap,50);
    multimedia.push_back(film);
    std::cout<<*multimedia[multimedia.size()-1];

    for(unsigned int j=0;j<50;j++)
        chap[j] = j*2+4;
    multimedia.push_back(new Film(*film));
    std::cout<<*multimedia[multimedia.size()-1];

    Film* film2 = new Film("unexisting film2","/cal/homes/jschoumacher/Desktop/",chap,40);
    *film2 = *film;
    multimedia.push_back(film2);
    std::cout<<*multimedia[multimedia.size()-1];

    const int* const cha = film2->getChapters();
    for(unsigned int i=0;i<20;i++)
        std::cout<<cha[i]<<std::endl;

    delete[] chap;
    for(unsigned int i=0;i<multimedia.size();i++)
        delete multimedia[i];

    return 0;
}*/
