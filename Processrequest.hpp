#ifndef PROCESSREQUEST_HPP
#define PROCESSREQUEST_HPP


#include "TCPServer.h"
#include "Factory.hpp"

#include <sstream>


class ProcessRequest
{
    public:
        ProcessRequest(const std::shared_ptr<Factory>& factory);

        bool process(TCPServer::Cnx& cnx, const std::string& request, std::string& response);

    private:
        std::shared_ptr<Factory> factory;
};


#endif
