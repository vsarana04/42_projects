#include "Channel.hpp"
#include <sstream>

/* Default Constructor */
Channel::Channel(const std::string& name) :
	_name(name), _topic(),
	_password(), _invite_only(), _topic_op_only(), _limit(0),
	_clients(), _operators(), _invited()
{
}

/* Copy Constructor */
Channel::Channel(const Channel& other)
{
	*this = other;
}

/* Copy Assign Constructor */
Channel&	Channel::operator=(const Channel& other)
{
	// Copy Assign is expected to be safe on self-assignment
	if (this == &other)
		return (*this);

	// copy data first into temp local vars (int new_var = other.var)

	// Assign values (first releasing own vars if you need) (var = new_var)
	_name = other._name;
	_topic = other._topic;
	_password = other._password;
	_invite_only = other._invite_only;
	_topic_op_only = other._topic_op_only;
	_limit = other._limit;
	_clients = other._clients;
	_operators = other._clients;
	_invited = other._invited;
	return (*this);
}

/* Default Destructor */
Channel::~Channel(void)
{
}

const std::string& Channel::getName() const { return (_name); }
const std::string& Channel::getName() { return (_name); }

const std::string& Channel::getTopic() const { return (_topic); }
const std::string& Channel::getTopic() { return (_topic); }
void Channel::setTopic(const std::string& topic) {
	_topic = topic;
}

bool Channel::isTopic() const {
	return !_topic.empty();
}

const std::vector<Client*>& Channel::getClients() const { return (_clients); }
const std::vector<Client*>& Channel::getClients() { return (_clients); }

const bool& Channel::getModeInvOnly() { return _invite_only; }
const bool& Channel::getModeInvOnly() const { return _invite_only; }
void Channel::setModeInvOnly(const bool& val) {
	_invite_only = val;
}

const bool& Channel::getModeTopicOpOnly() { return _topic_op_only; }
const bool& Channel::getModeTopicOpOnly() const { return _topic_op_only; }
void Channel::setModeTopicOpOnly(const bool& val) {
	_topic_op_only = val;
}

const size_t& Channel::getModeLimit() { return _limit; }
const size_t& Channel::getModeLimit() const { return _limit; }
void Channel::setModeLimit(const size_t& limit) {
	_limit = limit;
}

bool Channel::isLimitReached() {
	return (_limit > 0 && _clients.size() >= _limit);
}

bool Channel::isBadKey(const std::string& key) {
	return (!_password.empty() && _password != key);
}

void Channel::addClient(Client* client)
{
	if (!client)
	{
		return;
	}
	std::cout << "\033[36m[CHANNEL] adding client fd: " << client->getFd() << " addr: " << client << "\033[0m" << std::endl;
	_clients.push_back(client);

	if (_clients.size() == 1)
	{
		std::cout << "\033[36m[CHANNEL] adding operator: " << client->getNickname() << "\033[0m" << std::endl;
		_operators.push_back(client);
	}
}

bool Channel::removeClient(Client* client)
{
	if (!client)
	{
		return (false);
	}
	std::cout << "\033[36m[CHANNEL] searching to remove client fd: " << client->getFd() << " addr: " << client << "\033[0m" << std::endl;
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (*it == client)
		{
			std::cout << "\033[36m[CHANNEL] removing client vector elem with fd: " << (*it)->getFd() << " addr: " << *it << "\033[0m" << std::endl;
			_clients.erase(it);
			if (isOperator(client))
			{
				std::cout << "\033[36m[CHANNEL] removing operator: " << client->getNickname() << "\033[0m" << std::endl;
				removeOperator(client);
			}
			return (true);
		}
	}
	return (false);
}

bool Channel::isMember(Client* client)
{
	if (!client)
	{
		return (false);
	}
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (*it == client)
			return (true);
	}
	return (false);
}

void Channel::sendTopic(Client* client)
{
	if (!client)
		return;

	if (!isMember(client)) {
        client->sendMessage(":ircserv 442 " + _name + " :You're not on that channel\n");
        return;
	}

	if (!isTopic()) {
		client->sendMessage(":ircserv 331 " + client->getNickname() + " " + _name + " :No topic is set");
		return;
	}
	
	// RPL_TOPIC 332
	client->sendMessage(":ircserv 332 " + client->getNickname() + " " + _name + " :" + _topic);
}

void Channel::sendNames(Client* client)
{
	if (!client)
		return;

	// RPL_NAMREPLY 353
	std::string msg(":ircserv 353 ");
	msg += client->getNickname() + " = " + this->_name + " :";
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it != _clients.begin())
			msg += " ";
		if (isOperator(*it))
			msg += "@";
		msg += (*it)->getNickname();
	}
	client->sendMessage(msg);

	// RPL_ENDOFNAMES 366
	client->sendMessage(":ircserv 366 " + client->getNickname() + " " + this->_name + " :End of /NAMES list");
}

void Channel::sendWho(Client* client) {
	if (!client)
		return;

	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		Client* chanClient = *it;
		// RPL_WHOREPLY 352
		std::string msg(":ircserv 352 ");
		msg += client->getNickname() + " " + _name + " ";
		msg += chanClient->getUsername() + " " + chanClient->getHostname() + " " + chanClient->getServername() + " " + chanClient->getNickname();
		msg += " H";
		if (isOperator(chanClient))
			msg += "@";
		msg += " :0 " + chanClient->getRealname();
		client->sendMessage(msg);
	}
	// RPL_ENDOFWHO 315
	client->sendMessage(":ircserv 315 " + client->getNickname() + " " + _name + " :End of WHO list");
}

std::string Channel::buildModeInfo(void) {

	std::string modestring;
	std::string args;

	if (_invite_only)
		modestring += "i";
	if (_topic_op_only)
		modestring += "t";
	if (_limit) {
		modestring += "l";
		std::stringstream ss;
		ss << _limit;
		args += " " + ss.str();
	}
	if (!_password.empty())
		modestring += "k";

	if (!modestring.empty())
		modestring.insert(0, " +");

	return (modestring + args);
}

void Channel::sendModeInfo(Client* client) {
	if (!client)
		return;
	// RPL_CHANNELMODEIS 324
	std::string msg(":ircserv 324 ");
	msg += client->getNickname() + " " + _name + buildModeInfo();
	client->sendMessage(msg);
}

void Channel::applyModeChange(Client* client, std::string& modestring, std::string modeargs) {
	if (!client)
		return;

	if (!isMember(client)) {
		// ERR_NOTONCHANNEL 442
		client->sendMessage(":ircserv 442 " + client->getNickname() + " " + _name + " :You're not on that channel");
		return;
	}

	(void)modeargs;

	if (modestring.empty()) {
		sendModeInfo(client);
		return;
	}

	// Cases where irssi wants info on list types (often to cache them)
	if (modestring == "b") {
		// No support for ban lists
		// RPL_ENDOFBANLIST 368
		client->sendMessage(":ircserv 368 " + client->getNickname() + " " + _name + " :End of channel ban list");
		return;
	} else if (modestring == "e") {
		// No support for exception lists
		// RPL_ENNOFEXCEPTLIST 349
		client->sendMessage(":ircserv 349 " + client->getNickname() + " " + _name + " :End of channel exception list");
		return;
	} else if (modestring == "I") {
		// No support for invite-exception lists
		// RPL_ENDOFINVEXLIST 347
		client->sendMessage(":ircserv 347 " + client->getNickname() + " " + _name + " :End of channel invite exception list");
		return;
	} else if (!isOperator(client)) {
		// ERR_CHANOPRIVSNEEDED 482
		client->sendMessage(":ircserv 482 " + client->getNickname() + " " + _name + " :You're not an operator here");
		return;
	}

	std::vector<std::string> args = splitModeArgs(modeargs);
	/*std::cout << "[CHANNEL] Mode modestring: " << modestring << std::endl;*/
	/*std::cout << "[CHANNEL] Mode args vector: " << std::endl;*/
	/*for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it) {*/
	/*	std::cout << "  Arg: " << *it << std::endl;*/
	/*}*/

	bool stop_flag = false;
	bool adding_flag = true;
	std::vector<std::string>::iterator argIt = args.begin();
	std::string curr_arg_str;
	std::string change_modestring;
	std::string change_modeargs;
	Client* target_client = NULL;
	for (size_t i = 0; !stop_flag && i < modestring.length(); ++i) {
		switch (modestring[i]) {
			case '+':
				adding_flag = true;
				break;
			case '-':
				adding_flag = false;
				break;
			case 'o':
				// Type B: always needs argument
				if (argIt == args.end())
					break; // silent ignore
				curr_arg_str = *argIt;
				++argIt;
				target_client = getClientByNick(curr_arg_str);
				if (!target_client) {
					// ERR_USERNOTINCHANNEL 441
					client->sendMessage(":ircserv 441 " + client->getNickname() + " " + curr_arg_str + " " + _name + " :User not on this channel");
					break;
				}
				if ((adding_flag && isOperator(target_client)) || (!adding_flag && !isOperator(target_client))) {
					break;
				}
				if (adding_flag) {
					addOperator(target_client);
					change_modestring += "+o";
				} else {
					removeOperator(target_client);
					change_modestring += "-o";
				}
				change_modeargs += " " + curr_arg_str;
				break;
			case 'k':
				// Type C: arg when setting, none when unsetting
				if (adding_flag) {
					if (argIt == args.end())
						break; // silent ignore
					curr_arg_str = *argIt;
					++argIt;
					if (_password.empty())
						change_modestring += "+k";
					_password = curr_arg_str;
					// change_modeargs += " " + curr_arg_str; // keep the change a secret as it is sensitive info
				} else {
					if (!_password.empty())
						change_modestring += "-k";
					_password = "";
				}
				break;
			case 'l':
				// Type C: arg when setting, none when unsetting
				if (adding_flag) {
					if (argIt == args.end())
						break; // silent ignore
					curr_arg_str = *argIt;
					++argIt;
					{
						std::stringstream ss;
						ss << curr_arg_str;
						size_t new_limit;
						ss >> new_limit;
						if (ss.bad() || new_limit > (2 << 16)) {
							// ERR_INVALIDMODEPARAM
							client->sendMessage(":ircserv 696 " + client->getNickname() + " " + _name + " " + modestring[i] + " " + curr_arg_str + " :Channel limit should be >= 1");
							break;
						}
						if (_limit == new_limit)
							break;
						_limit = new_limit;
						change_modestring += "+l";
						change_modeargs += " " + curr_arg_str;
					}
				} else {
					if (_limit == 0)
						break;
					_limit = 0;
					change_modestring += "-l";
				}
				break;
			case 'i':
				// Type D: never argument
				if (_invite_only == adding_flag)
					break;
				_invite_only = adding_flag;
				if (adding_flag)
					change_modestring += "+i";
				else
					change_modestring += "-i";
				break;
			case 't':
				// Type D: never argument
				if (_topic_op_only == adding_flag)
					break;
				_topic_op_only = adding_flag;
				if (adding_flag)
					change_modestring += "+t";
				else
					change_modestring += "-t";
				break;
			default:
				stop_flag = true;
				client->sendMessage(":ircserv 472 " + client->getNickname() + " " + modestring[i] + " :is unknown char to me");
				break;
		}
	}

	if (change_modestring.empty())
		return;

	broadcast(":" + client->getNickname() + "!" + client->getUsername() + " MODE " + _name + " " + change_modestring + change_modeargs);
}

void Channel::broadcast(const std::string& msg)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		(*it)->sendMessage(msg);
	}
}

void Channel::broadcastFromClient(const std::string& msg, Client* client)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (*it != client)
			(*it)->sendMessage(msg);
	}
}

void Channel::addOperator(Client* client)
{
	if (!client || isOperator(client))
		return;

	_operators.push_back(client);
}

void Channel::removeOperator(Client* client)
{
	if (!client)
		return;

	for (std::vector<Client*>::iterator it = _operators.begin(); it != _operators.end(); ++it)
	{
		if (*it == client)
		{
			_operators.erase(it);
			return;
		}
	}
}

void Channel::addInvite(Client* client)
{
    if (!client || isInvited(client))
        return;

    _invited.push_back(client);
}


void Channel::removeInvite(Client* client)
{
    for (std::vector<Client*>::iterator it = _invited.begin(); it != _invited.end(); ++it)
    {
        if (*it == client)
        {
            _invited.erase(it);
            return;
        }
    }
}

bool Channel::isOperator(Client* client)
{
	if (!client)
		return (false);
	for (std::vector<Client*>::iterator it = _operators.begin(); it != _operators.end(); ++it)
	{
		if (*it == client)
			return (true);
	}
	return (false);
}

bool Channel::isInvited(Client* client)
{
	if (!client)
		return (false);
    for (std::vector<Client*>::iterator it = _invited.begin(); it != _invited.end(); ++it)
    {
        if (*it == client)
            return (true);
    }
    return (false);
}

Client* Channel::getClientByNick(const std::string& nick)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if ((*it)->getNickname() == nick)
			return (*it);
	}
	return (NULL);
}
