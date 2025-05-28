#ifndef SERVER_HPP
#define SERVER_HPP

#include <netinet/in.h>
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <netinet/in.h>
#include <vector>
#include <ostream>
#include <poll.h>
#include <algorithm>
#include <list>

#include "client.hpp"
#include "Channel.hpp"

class Client;
class Channel;

class Server
{
	private:
		int							_serverSocket;
		int							_port;
		int							_status;
		int							_amountOfPollFds;
		std::string					_password;
		struct sockaddr_in 			_sa;
		std::vector<struct pollfd> 	_pollFileDescriptors;
		std::list<Client>			_clients;
		std::list<Channel>			_channels;
		bool						_stopRunning;
		
	public:
		//constructor and destructor
		Server(int port, int amountOfPollFd, const std::string &passwords);
		~Server();

		//methods
		int setNonBlocking(int fd);
		int createServer();
		int initializeServer();
		void runServer();
		void acceptConnection();
		void addToPollFileDescriptorVector(int &clientFd);
		void addClient(int fd, int index);
		void readData(int index);
		void deleteFromPollFileDescriptorVector(int fd);
		void removeClient(int fd, std::string reason);
		Channel& addChannel(const std::string& name);

		// commands
		void parseCommand(Client*& client, const std::string &line);
		void toUpperCase(std::string &str);
		void handlePass(Client* client, std::stringstream &password);
		void handleNick(Client* client, std::stringstream &nickname);
		void handleUser(Client* client, std::stringstream &username);
		void handleQuit(Client* client, std::stringstream &quitMessage);
		void handleJoin(Client* client, std::stringstream &cmd);
		void handlePart(Client* client, std::stringstream &cmd);
		void handlePrivMsg(Client* client, std::stringstream &cmd);
		void handleChannelMsg(Client* client, const std::string &receiver, const std::string &message, const std::string &senderInfo);
		void handleClientMsg(Client* client, const std::string &receiver, const std::string &message, const std::string &senderInfo);
		void handleKick(Client* client, std::stringstream &cmd);
		void handleInvite(Client* client, std::stringstream &cmd);
		void handleTopic(Client* client, std::stringstream &cmd);
		void handleMode(Client* client, std::stringstream &cmd);
		void handlePing(Client* client, std::stringstream &cmd);
		void handleNames(Client *client, std::stringstream &cmd);
		void handleWho(Client *client, std::stringstream &cmd);
	
		bool isNickInUse(const std::string &nick, int excludeFd);
		bool isNickValid(const std::string &nick);
		void AuthenticatedClient(Client* client, const std::string &command, std::stringstream &cmd);
		void cleanMessage(std::string &message);
		bool validateInviteParams(Client* client, const std::string &targetNick, const std::string &channelName);
		Channel* validateKickParams(Client* client, const std::string &channelName, const std::string &target);
		bool validateInvite(Client* client, Channel* channel, Client* targetClient);
		bool validateKick(Client* client, Channel* channel, Client* targetClient, const std::string &target);
	
		//getters
		int	getServerSocket();
		Client* getClient(int fd);
		Client* checkClientByNick(const std::string& nickname);
		Channel* getChannel(const std::string& name);
		std::list<Channel>::iterator getChannelIt(const std::string& name);

		//setters
		void setPort(int port);
		
		//helpers
		int error(const std::string& message);
		int errorStop(const std::string& message);
};

#endif
