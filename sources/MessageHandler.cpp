#include "MessageHandler.h"

#include <iostream>

namespace LedControl {

const std::string MessageHandler::PREFIX = "/tmp/";

MessageHandler::MessageHandler(const std::string& serverName, CommandFactory* cf, Logger* log): cf_(cf), log_(log), isFinished_(false) {
	std::string pathToFifo = PREFIX + serverName;
	struct stat sb;
	if ( ::stat(pathToFifo.c_str(), &sb) != 0 ) {
		if (::mkfifo(pathToFifo.c_str(), 0600) < 0) {
			throw Exception(Exception::getSystemErrorMessage());
		}
	}//end of if 

	mainDesc_ = ::open(pathToFifo.c_str(), O_RDWR);
	if(mainDesc_ < 0) {
		throw Exception(Exception::getSystemErrorMessage());
	}
}//end of MessageHandler::MessageHandler()

MessageHandler::~MessageHandler() {
	::close(mainDesc_);
}//end of  MessageHandler::~MessageHandler()

} /* LedControl */ 
