#include "../includes/server.hpp"
#include <sstream>

// PASS <password>

void Server::handlePass(Client* client, std::stringstream &password)
{
    if (client->getHasPassword())
    {
        std::cerr << "[SERVER] Client [" << client->getFd() << "] is already connected" << std::endl;
        client->sendMessage(":ircserv 462 * :You may not re-register\n");
        return;
    }

    std::string pass;
    password >> pass;

    if (pass.empty())
    {
        std::cerr << "[SERVER] Client [" << client->getFd() << "] has entered an empty password" << std::endl;
        client->sendMessage(":ircserv 461 PASS :Not enough parameters\n");
        return;
    }
    if (pass == _password)
    {
    	client->setPassword(pass);
        std::cout << "[SERVER] Client [" << client->getFd() << "] has entered a correct password" << std::endl;
    }
    else
    {
        std::cout << "[SERVER] Client [" << client->getFd() << "] has entered the wrong password" << std::endl;
        client->sendMessage(":ircserv 464 * :Password incorrect\n");
    }
}

// NICK <nickname>

void Server::handleNick(Client* client, std::stringstream &nickname)
{
    std::string nick;
    nickname >> nick;

    if (nick.empty())
    {
        std::cerr << "[SERVER] Client [" << client->getFd() << "] has entered an empty nickname" << std::endl;
        client->sendMessage(":ircserv 431 * :No nickname given\n");
        return;
    }

    if (!isNickValid(nick))
    {
        client->sendMessage(":ircserv 432 * " + nick + " :Erroneous nickname\n");
        return;
    }

    if (isNickInUse(nick, client->getFd()))
    {
        client->sendMessage(std::string(":ircserv 433 * ") + nick + " :Nickname is already in use\n");
        return;
    }

    std::string oldNick = client->getNickname();

    client->setNickname(nick);

    if (!oldNick.empty())
    {
        std::cout << "[SERVER] Client [" << client->getFd() << "] changed nickname from " << oldNick << " to " << nick << std::endl;
        client->sendMessage(":" + oldNick + " NICK :" + nick + "\n");
    }
}

// USER <username> <hostname> <servername> :<realname> (USER <username>  0 * :<realname>)

void Server::handleUser(Client* client, std::stringstream &username)
{
    std::string user, hostname, servername, realname;
    username >> user >> hostname >> servername;

    if (client->getHasUsername())
    {
        client->sendMessage(":ircserv 462 * :You may not re-register\n");
        return;
    }

    if (user.empty() || hostname.empty() || servername.empty())
    {
        std::cerr << "[SERVER] Client [" << client->getFd() << "] has entered an empty username" << std::endl;
        client->sendMessage(":ircserv 461 USER :Not enough parameters\n");
        return;
    }

    if (hostname == "0") 
        hostname = client->checkHostname();

    if (servername == "*")
        servername = "ircserv";

    while (username.peek() == ' ' || username.peek() == ':')
        username.ignore(1);
    std::getline(username, realname);
    if (realname.empty())
        realname = user;
    client->setUsername(user);
    client->setHostname(hostname);
    client->setServername(servername);
    client->setRealname(realname);

    std::cout << "[SERVER] Client [" << client->getFd() << "] set username='" << user << "' realname='" << realname << "'\n";
}


// QUIT <message>

void Server::handleQuit(Client* client, std::stringstream &quitMessage)
{
    while (quitMessage.peek() == ':' || quitMessage.peek() == ' ')
        quitMessage.ignore(1);
    std::string message;
    std::string senderInfo = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname();
    std::getline(quitMessage, message);

    if (message.empty())
        std::cout << "[SERVER] Client [" << client->getFd() << "] is leaving the server at index " << client->getIndexInVector() << "]" << std::endl;
    else
        std::cout << "[SERVER] Client [" << client->getFd() << "] quit message: " << message << std::endl;
    client->sendMessage(senderInfo + " QUIT :" + " :You have left the server\n");
	deleteFromPollFileDescriptorVector(client->getIndexInVector());
    int clientFd = client->getFd();
    removeClient(clientFd, message);
    std::cout << "[SERVER] Client [" << clientFd << "] has been disconnected" << std::endl;
}

// JOIN <channel>{,<channel>} [<key>{,<key}]

void Server::handleJoin(Client* client, std::stringstream &cmd)
{
	if (!client)
		return;

	while (cmd.peek() == ':' || cmd.peek() == ' ')
		cmd.ignore(1);

	std::string channel_names_str;
	cmd >> channel_names_str;

	// Could check and handle if param is "0" for completeness, but irssi doesn't send this it seems.

	std::string channel_keys_str;
	cmd >> channel_keys_str;

	std::vector<std::string> channel_names = splitOnDelim(channel_names_str, ',');
	std::vector<std::string> channel_keys = splitOnDelim(channel_keys_str, ',');

	if (!channel_keys_str.empty() && channel_names.size() != channel_keys.size()) {
		client->sendMessage(":ircserv 461 " + client->getNickname() + " JOIN :Not enough parameters");
		return;
	}

	for (size_t i = 0; i < channel_names.size(); ++i)
	{
		std::string name = channel_names[i];
		std::string key = channel_keys_str.empty() ? "" : channel_keys[i];

		if (name[0] != '#' && name[0] != '&') {
			name = "#" + name;
		}

		Channel* connecting_channel = getChannel(name);
		if (connecting_channel == NULL) {
			std::cout << "[SERVER] no matching channels found, creating a new one" << std::endl;
			connecting_channel = &addChannel(name);
		} else {
			std::cout << "[SERVER] matching channel found: \"" << connecting_channel->getName() << "\"" << std::endl;
		}

		std::string senderInfo = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname();
		std::stringstream broadcastMsgSs;
		broadcastMsgSs << senderInfo << " JOIN " << connecting_channel->getName();

		if (client->joinChannel(connecting_channel, key)) {
			connecting_channel->broadcast(broadcastMsgSs.str());
			connecting_channel->sendTopic(client);
			connecting_channel->sendNames(client);
		}
	}
}

// PART <channel>{,<channel>} [reason]

void Server::handlePart(Client* client, std::stringstream &params)
{
	if (!client)
		return;

	std::string channel_names_str;
	params >> channel_names_str;
	std::string reason("");

	if (channel_names_str.empty())
	{
		std::cout << "[SERVER] Client request to part is empty" << std::endl;
		client->sendMessage(":ircserv 461 " + client->getNickname() + " PART :Not enough parameters");
		return;
	}

	params >> std::ws;
	std::getline(params, reason);

	std::vector<std::string> channel_names = splitOnDelim(channel_names_str, ',');

	for (size_t i = 0; i < channel_names.size(); ++i) {
		std::string name = channel_names[i];
		std::list<Channel>::iterator channel = getChannelIt(name);
		if (channel == _channels.end()) {
			// ERR_NOSUCHCHANNEL 403
			client->sendMessage(":ircserv 403 " + client->getNickname() + " " + name + " :No such channel");
			continue;
		}
		if (!channel->isMember(client)) {
			// ERR_NOTONCHANNEL 442
			client->sendMessage(":ircserv 442 " + client->getNickname() + " " + name + " :You're not on that channel");
			continue;
		}

        std::string senderInfo = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname();
		std::stringstream broadcastMsgSs;
		broadcastMsgSs << senderInfo << " PART " << channel->getName() << " " + reason;

		channel->broadcast(broadcastMsgSs.str());

		std::cout << "[SERVER] client " << client->getFd() << " has parted with channel \"" << channel->getName() << "\"\n";
		client->partChannel(&*channel);
		channel->removeClient(client);
		if (channel->getClients().size() == 0)
		{
			std::cout << "[SERVER] channel \"" << channel->getName() << "\" has been removed" << std::endl;
			_channels.erase(channel);
		}
	}
}

// PRIVMSG <receiver> :<message> 

void Server::handlePrivMsg(Client* client, std::stringstream &cmd)
{
    std::string receiver;
    cmd >> receiver;

    if (receiver.empty() || receiver[0] == ':')
    {
        client->sendMessage(":ircserv 411 * :No recipient given\n");
        return;
    }

    if (cmd.peek() == ':')
        cmd.ignore(1);

    std::string message;
    std::getline(cmd, message);

    cleanMessage(message);

    if (message.empty())
    {
        client->sendMessage(":ircserv 412 * :No text to send\n");
        return;
    }
    std::string senderInfo = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname();
    if (receiver[0] == '#' || receiver[0] == '&')
        handleChannelMsg(client, receiver, message, senderInfo);
    else
        handleClientMsg(client, receiver, message, senderInfo);
}

// KICK <channel> <target> :<reason>

void Server::handleKick(Client* client, std::stringstream &cmd)
{
    std::string channelName, target, reason;
    cmd >> channelName >> target;

    Channel* channel = validateKickParams(client, channelName, target);
    if (!channel)
        return;

    Client* targetClient = NULL;
    if (channel)
        targetClient = channel->getClientByNick(target);

    if (!validateKick(client, channel, targetClient, target))
        return;

    if (cmd.peek() == ':')
        cmd.ignore(1);
    std::getline(cmd, reason);
    if (reason.empty())
        reason = "No reason specified";

    channel->removeClient(targetClient);
    std::string senderInfo = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname();
    std::string kickMessage = ":" + client->getNickname() + " KICK " + channel->getName() + " " + targetClient->getNickname() + " :" + reason + "\n";
    channel->broadcast(kickMessage);
    targetClient->sendMessage(kickMessage);

    std::cout << "[SERVER] Client [" << targetClient->getFd() << "] was kicked from channel "
              << channel->getName() << " by [" << client->getNickname() << "]\n";
}

// INVITE <target> <channel> 

void Server::handleInvite(Client* client, std::stringstream &cmd)
{
    std::string targetNick, channelName;
    cmd >> targetNick >> channelName;

    if (!validateInviteParams(client, targetNick, channelName))
        return;

    Channel* channel = getChannel(channelName);
    Client* targetClient = checkClientByNick(targetNick);

    if (!validateInvite(client, channel, targetClient))
        return;

    channel->addInvite(targetClient);
    std::string senderInfo = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname();
    targetClient->sendMessage(":" + client->getNickname() + " INVITE " + targetNick + " " + channelName + "\n");
    std::cout << "[SERVER] " << client->getNickname() << " invited " << targetNick << " to " << channelName << std::endl;
}

void Server::handleMode(Client* client, std::stringstream& cmd) {
    std::string target;
    cmd >> target;

    if (target.empty()) {
        client->sendMessage(":ircserv 461 " + client->getNickname() + " MODE :Not enough parameters\n");
        return;
    }

	if (target[0] == '#') {
		Channel* channel = getChannel(target);
		if (!channel) {
			// ERR_NOSUCHCHANNEL 403
			client->sendMessage(":ircserv 403 " + client->getNickname() + " :No such channel");
			return;
		}

		std::string modestring;
		std::string modeargs;
		cmd >> modestring;
		std::getline(cmd, modeargs);

		channel->applyModeChange(client, modestring, modeargs);

	} else {
		// ERR_UMODEUNKNOWNFLAG 501
		client->sendMessage(":ircserv 501 " + client->getNickname() + " :Unknown MODE flag(s)");
	}
}


// TOPIC <channel> :<topic> (set the topic)
// TOPIC #test  (check the topic)

void Server::handleTopic(Client* client, std::stringstream &cmd)
{
    std::string channelName, topic;
    cmd >> channelName;

    if (channelName.empty() || channelName[0] != '#') {
        client->sendMessage(":ircserv 461 TOPIC :Not enough parameters\n");
        return;
    }

    Channel* channel = getChannel(channelName);
    if (!channel) {
        client->sendMessage(":ircserv 403 " + channelName + " :No such channel\n");
        return;
    }
    if (cmd.eof()) {
		channel->sendTopic(client);
        return;
    }

    if (cmd.peek() == ':')
        cmd.ignore(1);

    std::getline(cmd, topic);
    cleanMessage(topic);
    if (channel->getModeTopicOpOnly() == true && !channel->isOperator(client)) {
        client->sendMessage(":ircserv 482 " + channelName + " :You're not channel operator\n");
        return;
    }
    std::string senderInfo = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname();
    channel->setTopic(topic);
    channel->broadcast(":" + client->getNickname() + " TOPIC " + channelName + " :" + topic + "\n");
    std::cout << "[SERVER] " << client->getNickname() << " changed topic in " << channelName << " to: " << topic << std::endl;
}


void Server::handlePing(Client *client, std::stringstream &cmd)
{
	std::string targetandtoken;
	std::getline(cmd, targetandtoken);
	client->sendMessage(":ircserv PONG ircserv" + targetandtoken);
}

void Server::AuthenticatedClient(Client* client, const std::string &command, std::stringstream &cmd)
{
    if (command == "PASS")
        handlePass(client, cmd);
    else if (command == "NICK")
        handleNick(client, cmd);
    else if (command == "USER")
        handleUser(client, cmd);
    else if (command == "QUIT")
        handleQuit(client, cmd);
    else
    {
        client->sendMessage(":ircserv 451 *: You have not authenticated yet\n");
        return;
    }

    if (!client->isAuthenticated())
    {
        std::ostringstream oss;
        oss << ":ircserv NOTICE * :Authentication required. Please use the following commands:";
        if (!client->getHasPassword())
            oss << " PASS";
        if (!client->getHasNickname())
            oss << " NICK";
        if (!client->getHasUsername())
            oss << " USER";
        oss << ".\n";
        client->sendMessage(oss.str());
    }

    if (client->isAuthenticated())
    {

        client->sendMessage(":ircserv 001 " + client->getNickname() + " :Welcome to the IRC server, " + client->getNickname() + "!\n");
        client->sendMessage(":ircserv 002 " + client->getNickname() + " :Your host is ircserv\n");
        client->sendMessage(":ircserv 003 " + client->getNickname() + " :This server was created just now\n");
        client->sendMessage(":ircserv 004 " + client->getNickname() + " ircserv 1.0\n");
        client->sendMessage(":ircserv 005 " + client->getNickname() + " PREFIX=(o)@ CHANMODES=,,kl,it CHANTYPES=# :You are " + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() + "\n");
    }
}

// NAMES <channel>

void Server::handleNames(Client *client, std::stringstream &cmd)
{
	std::string param;
	cmd >> param;
	if (param.empty())
	{
        client->sendMessage(":ircserv 461 NAMES :Not enough parameters");
		return ;
	}

	if (param.at(0) == '#')
	{
		Channel* channel = getChannel(param);
		if (!channel) {
			// RPL_NOSUCHCHANNEL 403
			client->sendMessage(":ircserv 403 " + client->getNickname() + " " + param + " :No such channel");
		}
		channel->sendNames(client);
	}
}

// WHO <mask>
// mask can be <nick> | <channel> | <search pattern>
// We do not support search pattern as mask at this moment, so return empty list

void Server::handleWho(Client *client, std::stringstream &cmd)
{
	std::string mask;
	cmd >> mask;
	if (mask.empty())
	{
		client->sendMessage(":ircserv 461 WHO :Not enough parameters");
		return ;
	}

	if (mask.at(0) == '#')
	{
		Channel* channel = getChannel(mask);
		if (!channel) {
			client->sendMessage(":ircserv 403 " + client->getNickname() + " " + mask + " :No such channel");
		}
		channel->sendWho(client);
	} else {
		Client* targetClient = checkClientByNick(mask);
		if (!targetClient)
		{
			// RPL_ENDOFWHO 315
			client->sendMessage(":ircserv 315 " + client->getNickname() + " " + mask + " :End of WHO list");
			return;
		}
		// RPL_WHOREPLY 352
		std::string msg(":ircserv 352 ");
		msg += client->getNickname() + " ";
		Channel* targetChannel = NULL;
		if (targetClient->getChannels().size())
			targetChannel = targetClient->getChannels()[0];
		if (targetChannel)
			msg += targetChannel->getName() + " ";
		else
			msg += "* ";
		msg += targetClient->getUsername() + " " + targetClient->getHostname() + " " + targetClient->getServername() + " " + targetClient->getNickname();
		msg += " H";
		if (targetChannel && targetChannel->isOperator(targetClient))
			msg += "@";
		msg += " :0 " + targetClient->getRealname();
		client->sendMessage(msg);
		// RPL_ENDOFWHO 315
		client->sendMessage(":ircserv 315 " + client->getNickname() + " " + mask + " :End of WHO list");
	}
}

void Server::parseCommand(Client*& client, const std::string &line)
{
    std::stringstream cmd(line);
    std::string command;
    cmd >> command;

    toUpperCase(command);

    if (!client->isAuthenticated())
    {
        AuthenticatedClient(client, command, cmd);
        return;
    }

	if (command == "PASS")
		handlePass(client, cmd);
	else if (command == "NICK")
		handleNick(client, cmd);
	else if (command == "USER")
		handleUser(client, cmd);
	else if (command == "QUIT") {
		handleQuit(client, cmd);
		client = NULL;
	}
	else if (command == "JOIN")
		handleJoin(client, cmd);
	else if (command == "PART")
		handlePart(client, cmd);
	else if (command == "MODE")
		handleMode(client, cmd);
	else if (command == "PRIVMSG")
		handlePrivMsg(client, cmd);
	else if (command == "KICK")
		handleKick(client, cmd);
	else if (command == "INVITE")
		handleInvite(client, cmd);
	else if (command == "TOPIC")
		handleTopic(client, cmd);
	else if (command == "PING")
		handlePing(client, cmd);
	else if (command == "NAMES")
		handleNames(client, cmd);
	else if (command == "WHO")
		handleWho(client, cmd);
	else
	{
		std::cerr << "\033[31m[SERVER] Unknown command: " << command << "\033[0m" << std::endl;
		client->sendMessage(":ircserv 421 * " + command + " :Unknown command\n");
	}
}
