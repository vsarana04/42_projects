#include "../includes/server.hpp" 
#include "../includes/irc.hpp"


void Server::toUpperCase(std::string &str)
{
    for (size_t i = 0; i < str.size(); i++)
        str[i] = std::toupper(str[i]);
}

bool Server::isNickInUse(const std::string &nick, int fd)
{
    for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->getFd() != fd && it->getNickname() == nick)
            return (true);
    }
    return (false);
}

bool Server::isNickValid(const std::string &nick)
{
    if (nick.empty())
        return (((false)));

    if (nick[0] == '#' || nick[0] == ':' || nick[0] == ' ')
        return (((false)));

    for (size_t i = 0; i < nick.size(); i++)
    {
        unsigned char c;

        c = nick[i];
        if (!std::isalnum(c) && c != '-' && c != '_' && c != '[' && c != ']' 
            && c != '{' && c != '}' && c != '\\' && c != '|')
            return (((false)));
    }
    return (true);
}

/* void Server::cleanMessage(std::string &message)
{
    size_t i = 0;
    while (i < message.size() && message[i] == ' ')
        ++i;

    if (i != std::string::npos)
        message = message.substr(i);

    if (!message.empty() && message[0] == ':')
        message = message.substr(1);
}

 */

 void Server::cleanMessage(std::string &message)
{
    size_t i = 0;
    while (i < message.size() && message[i] == ' ')
        ++i;
    if (i >= message.size())
    {
        message.clear();
        return;
    }
    message = message.substr(i);
    if (!message.empty() && message[0] == ':')
        message = message.substr(1);
}

 void Server::handleChannelMsg(Client* client, const std::string &receiver, const std::string &message, const std::string &senderInfo)
{
    Channel* channel = getChannel(receiver);
    if (!channel)
    {
        client->sendMessage(":ircserv 403 " + receiver + " :No such channel\n");
        return;
    }
    if (!channel->isMember(client))
    {
        client->sendMessage(":ircserv 442 " + receiver + " :You're not on that channel\n");
        return;
    }
    channel->broadcastFromClient(senderInfo + " PRIVMSG " + receiver + " :" + message + "\n", client);
}

void Server::handleClientMsg(Client* client, const std::string &receiver, const std::string &message, const std::string &senderInfo)
{
    if (receiver == client->getNickname())
    {
        client->sendMessage(":ircserv 402 " + receiver + " :Cannot send message to yourself\n");
        return;
    }

    Client* targetClient = NULL;
    for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->getNickname() == receiver)
        {
            targetClient = &(*it);
            break;
        }
    }

    if (!targetClient)
    {
        client->sendMessage(":ircserv 401 " + receiver + " :No such nick/channel\n");
        return;
    }
    targetClient->sendMessage(senderInfo + " PRIVMSG " + receiver + " :" + message + "\n");
}


bool Server::validateInviteParams(Client* client, const std::string &targetNick, const std::string &channelName)
{
    if (targetNick.empty() || channelName.empty())
    {
        client->sendMessage(":ircserv 461 INVITE :Not enough parameters\n");
        return ((false));
    }
    return true;
}

Channel* Server::validateKickParams(Client* client, const std::string &channelName, const std::string &target)
{
    if (channelName.empty() || channelName[0] != '#' || target.empty())
    {
        client->sendMessage(":ircserv 461 KICK :Not enough parameters\n");
        return (NULL);
    }

    Channel* channel = getChannel(channelName);
    if (!channel)
    {
        client->sendMessage(":ircserv 403 " + channelName + " :No such channel\n");
        return (NULL);
    }
    return (channel);
}


bool Server::validateInvite(Client* client, Channel* channel, Client* targetClient)
{
    if (!channel)
    {
        client->sendMessage(":ircserv 403 " + client->getNickname() + " :No such channel\n");
        return ((false));
    }

    if (!channel->isOperator(client))
    {
        client->sendMessage(":ircserv 482 " + channel->getName() + " :You're not channel operator\n");
        return ((false));
    }

    if (!targetClient)
    {
        client->sendMessage(":ircserv 401 " + client->getNickname() + " :No such nick\n");
        return ((false));
    }

    if (channel->isMember(targetClient))
    {
        client->sendMessage(":ircserv 443 " + targetClient->getNickname() + " " + channel->getName() + " :is already on channel\n");
        return ((false));
    }

    if (channel->isInvited(targetClient))
    {
        client->sendMessage(":ircserv NOTICE " + targetClient->getNickname() + " :User is already invited\n");
        return ((false));
    } 
    return (true);
}

bool Server::validateKick(Client* client, Channel* channel, Client* targetClient, const std::string &target)
{
    if (!channel->isOperator(client))
    {
        client->sendMessage(":ircserv 482 " + channel->getName() + " :You're not channel operator\n");
        return (false);
    }

    if (!targetClient)
    {
        client->sendMessage(":ircserv 441 " + target + " " + channel->getName() + " :They aren't on that channel\n");
        return (false);
    }
    return (true);
}


