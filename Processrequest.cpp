#include "processrequest.hpp"


ProcessRequest::ProcessRequest(const std::shared_ptr<Factory>& factory) :
    factory(factory)
{}

bool ProcessRequest::process(TCPServer::Cnx& cnx, const string& request, string& response)
{
    if(!factory)
    {
        response = "NOK internalError";
        return;
    }

    std::istreamstring iss(request);
    std::string cmd;
    iss>>cmd;

    std::string line;
    std::getline(iss,line);

    //Data processing and actions depend on the command entered
    if(cmd=="search")
    {
        std::shared_ptr<Multimedia> resource = factory->search(line);
        if(resource)
            response = "OK resourceFound";
        else
            response = "OK noResourceFound";
    }
    else if(cmd=="play")
    {
        std::shared_ptr<Multimedia> resource = factory->search(line);
        //We check if resource is available first (before playing it)
        if(resource)
        {
            factory->play(line);
            response = "OK resourcePlayed";
        }
        else
            response = "OK noResourceFound";
    }
    else if(cmd=="print")
    {
        std::shared_ptr<Multimedia> resource = factory->search(line);
        //We check if resource is available first (before printing it)
        if(resource)
        {
            std::ostringstream oss;
            factory->printByName(line,oss);
            response = "OK "+oss.str();
        }
        else
            response = "OK noResourceFound";
    }
    else if(cmd=="delete")
    {
        TCPServer::Lock lock(cnx, true);
        if(factory->deleteByName(line))
            response = "OK destructionOK";
        else
            response = "OK destructionNOK";
        TCPServer::Lock lock(cnx, false);
    }
    else
        response = "NOK badCommand";
}
