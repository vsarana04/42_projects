#include "../includes/server.hpp"
#include "../includes/irc.hpp"
#include <cstring>
#include <sstream>

Server::Server(int port, int amountOfPollFds, const std::string &password):
	_serverSocket(), _port(port), _status(), _amountOfPollFds(amountOfPollFds),
	_password(password), _sa(), _pollFileDescriptors(), _clients(), _channels(),
	_stopRunning(0)
{
	std::cout << "The server constructor has been called" << std::endl;
}

Server::~Server()
{
	std::cout << "The destructor has been called" << std::endl;
	close(_serverSocket);
}

//getters
int Server::getServerSocket()
{
	return (_serverSocket);
}

Client* Server::getClient(int fd)
{
	for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->getFd() == fd)
			return (&(*it));
	}
	return (NULL);
}

Client* Server::checkClientByNick(const std::string& nickname)
{
    for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->getNickname() == nickname)
            return (&(*it));
    }
    return (NULL);
}


Channel* Server::getChannel(const std::string& name)
{
	for (std::list<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (it->getName() == name)
			return (&*it);
	}
	return (NULL);
}

std::list<Channel>::iterator Server::getChannelIt(const std::string& name)
{
	for (std::list<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (it->getName() == name)
			return (it);
	}
	return (_channels.end());
}

//setters
void Server::setPort(int port)
{
	_port = port;
}

//methods

int Server::setNonBlocking(int fd)
{
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		return errorStop("\033[31m[SERVER] fcntl SETFL error\033[0m");
	return 0;
}

int Server::createServer()
{
	memset(&_sa, 0, sizeof _sa);	
	_sa.sin_family = AF_INET;
	_sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	_sa.sin_port = htons(_port);

	_serverSocket = socket(_sa.sin_family, SOCK_STREAM, 0);
	if (_serverSocket == -1)
		return errorStop("\033[31m[SERVER] Socket creation error\033[0m");
	std::cout << "\033[32m[SERVER] Socket created ✅ \033[0m" << std::endl;

	if (setNonBlocking(_serverSocket))
		return 1;

	if (bind(_serverSocket, (struct sockaddr*)&_sa, sizeof _sa) == -1)
		return errorStop("\033[31m[SERVER] Bind error\033[0m");
	std::cout << "\033[32m[SERVER] Socket bound to port " << _port << " ✅\033[0m" << std::endl;

	return 0;
}

int Server::initializeServer()
{
	if (listen(_serverSocket, 10) != 0)
		return errorStop("[SERVER] Listening Error");
	std::cout << "\033[32m[SERVER] Listening on port " <<  _port << " ✅\033[0m" << std::endl;

	struct pollfd serverPollFileDescriptor;
	serverPollFileDescriptor.fd = _serverSocket;
	serverPollFileDescriptor.events = POLLIN;
	serverPollFileDescriptor.revents = 0;

	_pollFileDescriptors.push_back(serverPollFileDescriptor);
	
	std::cout << "\033[32m[SERVER] The poll array is ready ✅\033[0m" << std::endl;
	return 0;
}

void Server::runServer()
{
	while (!_stopRunning)
	{
		_status = poll(&_pollFileDescriptors[0], _amountOfPollFds, 5000);
		if (_status == -1)
		{
			errorStop("[SERVER] Poll error");
			break;
		}
		else if (_status == 0)
		{
			std::cout << "\033[33m[SERVER] Waiting for connections...\033[0m" << std::endl;
			continue;
		}
		for (int i = _amountOfPollFds - 1; !_stopRunning && i >= 0; i--)
		{
			if (!(_pollFileDescriptors[i].revents & POLLIN))
				continue;
			if (_pollFileDescriptors[i].fd == _serverSocket)
				acceptConnection();
			else
				readData(i);
		}
	}
}

void Server::addToPollFileDescriptorVector(int &clientFd)
{
	struct pollfd newPollFileDescriptor;
	newPollFileDescriptor.fd = clientFd;
	newPollFileDescriptor.events = POLLIN;
	newPollFileDescriptor.revents = 0;
	_pollFileDescriptors.push_back(newPollFileDescriptor);
	_amountOfPollFds++;
}
void Server::addClient(int fd, int index)
{
	Client newClient(fd, index);
	_clients.push_back(newClient);
	std::cout << "\033[36m[SERVER] Added new client with fd: " << fd  << "\033[0m" << std::endl;
}

Channel& Server::addChannel(const std::string& name)
{
	Channel newChannel(name);
	_channels.push_back(newChannel);
	std::cout << "\033[36m[SERVER] Added new Channel with name: " << name << "\033[0m" << std::endl;
	return _channels.back();
}

void Server::acceptConnection()
{
	int					clientFd;
	int					indexInVector;
	std::string 		message;
	std::string 		capMessage;
	std::ostringstream 	ss;

	clientFd = accept(_serverSocket, NULL, NULL);
	if (clientFd == -1) {
		errorStop("[SERVER] Cannot accept new connection of client");
		return;
	}

	indexInVector = _pollFileDescriptors.size();

	if (setNonBlocking(clientFd))
		return;
	addClient(clientFd, indexInVector);
	addToPollFileDescriptorVector(clientFd);

	ss << "Welcome to the server! You are client [" << clientFd << "] \nEnter the authentication command: PASS, NICK, USER or QUIT: \n";
	message = ss.str();
	
	if (send(clientFd, message.c_str(), message.size(), 0) == -1)
		std::cerr << "[SERVER] Error sending message to client [" << clientFd << "] (" << strerror(errno) << std::endl;
}

void Server::readData(int index)
{
    char buffer[512];
    memset(buffer, 0, sizeof(buffer));

    int clientFd = _pollFileDescriptors[index].fd;
    Client* client = getClient(clientFd);
    if (client == NULL)
    {
        std::cerr << "\033[31m[SERVER] Client not found for fd: " 
                  << clientFd << "\033[0m" << std::endl;
        return;
    }
    int bytesRead = recv(clientFd, buffer, sizeof(buffer), 0);
    std::cout << "The amount of bytes that are read is: " << bytesRead << std::endl;

    if (bytesRead <= 0)
    {
        if (bytesRead == 0)
        {
            std::cout << "\033[47;30m[CLIENT " << clientFd 
                      << "] socket has closed the connection\033[0m" << std::endl;
        }
        else
        {
            errorStop("[SERVER] Reading data resulted in an error");
			return;
        }
        removeClient(clientFd, "");
        deleteFromPollFileDescriptorVector(index);
    }
    else
    {
        std::string rawInput(buffer, bytesRead);

		std::cout << "[SERVER] Received raw input from client " << clientFd << ": " << unescape(buffer) << std::endl;

		client->addRawToInput(rawInput);
		std::string line = client->getNextLine();
		while (!line.empty())
		{
			std::cout << "[SERVER] Received line from client " << clientFd << ": " << line << std::endl;
			parseCommand(client, line);
			if (!client)
				break;
			line = client->getNextLine();
		}
    }
}

void Server::deleteFromPollFileDescriptorVector(int index)
{
	_pollFileDescriptors.erase(_pollFileDescriptors.begin() + index);
	_amountOfPollFds--;
}

void Server::removeClient(int fd, std::string reason)
{

	if (!reason.empty() && reason[0] != ':')
		reason = ":" + reason;

	for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->getFd() == fd)
		{
			for (std::vector<Channel*>::const_iterator chit = it->getChannels().begin(); chit != it->getChannels().end(); ++chit)
			{
				std::string channelName((*chit)->getName());
				std::list<Channel>::iterator channel = getChannelIt(channelName);

				std::stringstream broadcastMsgSs;
				broadcastMsgSs << ":" << it->getNickname() + "!" + it->getUsername() << " PART " << channel->getName() << " " + reason << std::endl;

				if (channel != _channels.end() && channel->isMember(&*it))
				{
					std::cout << "[SERVER] client " << it->getFd() << " has parted with channel \"" << channel->getName() << "\"" << std::endl;
					channel->broadcast(broadcastMsgSs.str());
					channel->removeClient(&*it);
					if (channel->getClients().size() == 0)
					{
						std::cout << "[SERVER] channel \"" << channel->getName() << "\" has been removed" << std::endl;
						_channels.erase(channel);
					}
				}
			}
			for (std::list<Client>::iterator iter = _clients.erase(it); iter != _clients.end(); ++iter)
                iter->setIndexInVector(iter->getIndexInVector() - 1);
			close(fd);
			break;
		}
	}
}

int Server::error(const std::string& message) {
	std::cerr << "\033[1;31m" << message << " ❌\033[0m" << std::endl;
	return 1;
}

int Server::errorStop(const std::string& message) {
	std::cerr << "\033[1;31m" << message << " ❌\033[0m" << std::endl;
	_stopRunning = true;
	return 1;
}
