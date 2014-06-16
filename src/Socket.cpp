/*
 * Socket.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: jp
 */

#include "Socket.h"

Socket::Socket(string local_name){
    this->localName = local_name;
    this->socketFd = -1;
    this->port = -1;
    this->error = -1;
    setConfigurationFile(NETWORK_FILE);
}

Socket::Socket(int sockFd, struct sockaddr_in localAddress, struct sockaddr_in remoteAddress, string localName){
    this->socketFd = sockFd;
    this->localName = localName;
    this->localAddress = localAddress;
    this->remoteAddress = remoteAddress;
    this->port = -1;
    this->error = -1;
    setConfigurationFile(NETWORK_FILE);
}

int Socket::fileDescriptor(){
    return socketFd;
}

in_addr Socket::getRemoteAddress(){
    return remoteAddress.sin_addr;
}

in_addr Socket::getLocalAddress(){
    return localAddress.sin_addr;
}

void Socket::setConfigurationFile(string fileName) {
	this->configuration = new Configuration(fileName);
}

void Socket::setLocalAddress(unsigned short port) {
	bzero(&localAddress, sizeof(localAddress));
	localAddress.sin_family = AF_INET;
	localAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddress.sin_port = htons(port);
}

int Socket::passivate(unsigned short port){
	string backlogStr = configuration->get("backlog");
    backlog = 
    this->port = port;

    setLocalAddress(port);

    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        notifyErrorOn("get file descriptor");
        return -1;
    }
    if (bind(socketFd, (struct sockaddr *) &localAddress, sizeof (localAddress)) < 0){
        notifyErrorOn("bind");
        return -1;
    }
    if (listen(socketFd, backlog) < 0){
        notifyErrorOn("listen");
        return -1;
    }

    return 0;
}

void Socket::setRemoteAddress(unsigned short port,
		struct hostent* remote_info) {
	bzero(&remoteAddress, sizeof(remoteAddress));
	remoteAddress.sin_family = AF_INET;
	remoteAddress.sin_port = htons(port);
	memcpy(&remoteAddress.sin_addr, remote_info->h_addr, remote_info->h_length);
}

int Socket::activate(string remote_name, unsigned short port){
    this->port = port;
    this->remoteName = remote_name;
    struct hostent *remote_info = gethostbyname(remote_name.c_str());

    if((remote_info) == NULL){
        notifyErrorOn("gethostbyname");
        return -2;
    }

	setRemoteAddress(port, remote_info);

    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        notifyErrorOn("socket");
        return -1;
    }
    if (connect(socketFd, (struct sockaddr *) &remoteAddress, sizeof (remoteAddress)) < 0){
        notifyErrorOn("connect");
        return -1;
    }

    socklen_t size = sizeof (localAddress);
    bzero(&localAddress, size);

    if (getsockname(socketFd, (struct sockaddr*) &localAddress, &size) < 0){
        notifyErrorOn("getsockname");
        return -1;
    }

    return 0;
}

Socket * Socket::acceptOrCreateNew(){
    int newsockfd;
    socklen_t size = sizeof(remoteAddress);
    bzero((char *) &remoteAddress, size);
    if((newsockfd = accept(socketFd, (struct sockaddr *) &remoteAddress, &size)) <= 0){
        notifyErrorOn("accept");
        return NULL;
    }
    else return new Socket(newsockfd, localAddress, remoteAddress, localName);
}

int Socket::send(char * data, size_t size){
    int sent_bytes, last_write;
    for(sent_bytes = 0; size; sent_bytes += last_write){
        if((last_write = write(socketFd, (void*) (data + sent_bytes), size)) <= 0){
            notifyErrorOn("send");
            return sent_bytes;
        }
        size -= last_write;
    }
    return sent_bytes;
}

int Socket::receive(char * data, size_t size){
    int read_bytes, last_read;
    for(read_bytes = 0; size; read_bytes += last_read){
        if((last_read = read(socketFd, (void*) (data + read_bytes), size)) <= 0) return read_bytes;
        size -= last_read;
    }
    return read_bytes;
}

int Socket::destroy(){
    if(close(socketFd) == -1){
        notifyErrorOn("close");
        return -1;
    }
    return 0;
}

std::string Socket::socketInformation() {
	std::string message = "Socket: \n";
	message += "Local Name: " + this->localName + "Local Address: "
			+ Utils::intToString(this->localAddress.sin_addr.s_addr) + "\n";
	message += "Remote Name: " + this->remoteName + "Remote Address: "
			+ Utils::intToString(this->remoteAddress.sin_addr.s_addr) + "\n";
	return message;
}

void Socket::notifyErrorOn(string failingMethod) {
	std::string message = socketInformation();
	message += "error on " + failingMethod;
	Colors::writeerr(message, UNDERLINEDRED);
}
