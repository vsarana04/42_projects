#include "../includes/client.hpp"

// constructor & destructor

Client::Client():
	_fd(-1), _indexInVector(-1), _nickname(""), _username(""), _realname(""), _password(""),
	_hasPassword(false), _hasNickname(false), _hasUsername(false),
	_authenticated(false), _receivedWelcome(false), _channels(0), _inputStr("")
{
    std::cout << "The client constructor has been called" << std::endl;
}

Client::Client(int fd, int index):
	_fd(fd), _indexInVector(index), _nickname(""), _username(""), _realname(""), _password(""),
	_hasPassword(false), _hasNickname(false), _hasUsername(false),
	_authenticated(false), _receivedWelcome(false), _channels(0), _inputStr("")
{
    std::cout << "The client constructor has been called" << std::endl;
}

Client::~Client()
{
}
// getters

int Client::getFd() const { return (_fd); }
int Client::getIndexInVector() const { return (_indexInVector); }
std::string Client::getNickname() const { return (_nickname); }
std::string Client::getUsername() const { return (_username); }
std::string Client::getHostname() const { return (_hostname); }
std::string Client::getServername() const { return (_servername); }
std::string Client::getRealname() const { return (_realname); }
std::string Client::getPassword() const { return (_password); }
std::string Client::getInputStr() const { return (_inputStr); }
bool Client::getAuthenticated() const { return (_authenticated); }
bool Client::getHasNickname() const { return (_hasNickname); }
bool Client::getHasUsername() const { return (_hasUsername); }
bool Client::getHasPassword() const { return (_hasPassword); }
bool Client::getReceivedWelcome() const { return (_receivedWelcome); }


const std::vector<Channel*>& Client::getChannels() const { return (_channels); }


// setters

void Client::setFd(int fd) { _fd = fd; }
void Client::setIndexInVector(int index) { _indexInVector = index; }
void Client::setNickname(std::string &nickname)
{
    _nickname = nickname;
    _hasNickname = true;
}
void Client::setUsername(std::string &username)
{
    _username = username; 
    _hasUsername = true;
}

void Client::setHostname(std::string &hostname)
{
     _hostname = hostname;     
}

void Client::setServername(std::string &servername)
{
    _servername = servername;
}


void Client::setPassword(std::string &password)
{
    _password = password;
    _hasPassword = true;
}


void Client::setRealname(std::string &realname) { _realname = realname; }
void Client::setHasNickname(bool hasNickname) { _hasNickname = hasNickname; }
void Client::setHasUsername(bool hasUsername) { _hasUsername = hasUsername; }
void Client::setHasPassword(bool hasPassword) { _hasPassword = hasPassword; }
void Client::setAuthenticated(bool authenticated) { _authenticated = authenticated; }
void Client::setReceivedWelcome(bool receivedWelcome) { _receivedWelcome = receivedWelcome; }

// methods

void Client::sendMessage(std::string message)
{
    if (_fd < 0)
    {
       std::cerr << "\033[31m[CLIENT] Error sending message [" << _fd << "] (fd is -1)\033[0m" << std::endl;
       return;
    }

    std::string msg = message;
	msg += "\r\n";

	std::cout << "\033[35m[CLIENT] Sending message to\033[0m \"" << this->_nickname << "\" : \"" << unescape(msg) << "\"" << std::endl;

    if (send(_fd, msg.c_str(), msg.size(), 0) == -1)
        std::cerr << "\033[31m[CLIENT] Error sending message [" << _fd << "] (" << strerror(errno) << ")\033[0m" << std::endl;
}

bool Client::isAuthenticated()
{

    if (_hasNickname && _hasUsername && _hasPassword && !_authenticated)
    {
        _authenticated = true;
        std::cout << "[CLIENT] Client " << _fd << " has been authenticated" << std::endl;
    }
    return (_authenticated);
}

bool Client::joinChannel(Channel *channel, const std::string& key)
{
	if (channel == NULL)
	{
		std::cout << "[CLIENT] bad channel to join" << std::endl;
		return false;
	}

	std::cout << "[CLIENT] Client tries joining channel \"" << channel->getName() << "\"" << std::endl;

	if (channel->isMember(this))
	{
		std::cout << "[CLIENT] already joined this channel" << std::endl;
		return false;
	}

	bool chan_inv_only = channel->getModeInvOnly();
	if (chan_inv_only && !channel->isInvited(this))
	{
		// RPL_INVITEONLYCHAN 473
		sendMessage(":ircserv 473 " + _nickname + " " + channel->getName() + " :Cannot join invite only channel");
		return false;
	}

	if (channel->isBadKey(key)) {
		// ERR_BADCHANNELKEY 475
		sendMessage(":ircserv 475 " + _nickname + " " + channel->getName() + " :Cannot join channel (+k)");
		return false;
	}

	if (channel->isLimitReached()) {
		// ERR_CHANNELISFULL 471
		sendMessage(":ircserv 471 " + _nickname + " " + channel->getName() + " :Cannot join channel (+l)");
		return false;
	}

	_channels.push_back(channel);
	channel->addClient(this);
	if (chan_inv_only)
		channel->removeInvite(this);
	return true;
}

void Client::partChannel(Channel *channel)
{
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (*it == channel)
		{
			_channels.erase(it);
			break;
		}
	}
}

std::string Client::checkHostname()
{
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    
    if (getpeername(_fd, (struct sockaddr *)&addr, &addr_size) == -1)
        return ("UnknownHost");

    char host[NI_MAXHOST];
    if (getnameinfo((struct sockaddr *)&addr, addr_size, host, sizeof(host), NULL, 0, NI_NAMEREQD) != 0)
        return (inet_ntoa(addr.sin_addr));

    return (std::string(host));
}

void Client::addRawToInput(std::string& content) {
	_inputStr += content;
}

std::string Client::getNextLine() {
	std::string::size_type crlfPos = _inputStr.find(CRLF);
	if (crlfPos == std::string::npos)
		return "";
	std::string res = _inputStr.substr(0, crlfPos);
	_inputStr.erase(0, crlfPos + 2);
	return res;
}


std::ostream &operator<<(std::ostream &out, const Client &client)
{
    out << "Client fd: " << client.getFd() << std::endl;
	out << "Client index in vector: " << client.getIndexInVector() << std::endl;
    out << "Client nickname: " << client.getNickname() << std::endl;
    out << "Client username: " << client.getUsername() << std::endl;
    out << "Client realname: " << client.getRealname() << std::endl;
    out << "Client password: " << client.getPassword() << std::endl;
    out << "Client authenticated: " << client.getAuthenticated() << std::endl;
    out << "Client hasNickname: " << client.getHasNickname() << std::endl;
    out << "Client hasUsername: " << client.getHasUsername() << std::endl;
    out << "Client hasPassword: " << client.getHasPassword() << std::endl;
    return (out);
}

