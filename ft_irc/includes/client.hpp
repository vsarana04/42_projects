#pragma once

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"
#include "Channel.hpp"

class Channel;

class Client
{
    private:
        int             _fd;
		int				_indexInVector;
        std::string     _nickname;
        std::string     _username;
        std::string     _hostname;
        std::string     _servername;
        std::string     _realname;
        std::string     _password;

        bool            _hasPassword;
        bool            _hasNickname;
        bool            _hasUsername;
        bool            _authenticated;
		bool			_receivedWelcome;

		std::vector<Channel*> _channels;
		std::string		_inputStr;

    public:
        //constructor and destructor
        Client();
        Client(int fd, int index);
        ~Client();

        //methods
        void    sendMessage(std::string message);
        bool    isAuthenticated();
        std::string checkHostname();
		void	addRawToInput(std::string& content);
		std::string getNextLine();

        //getters
        int             getFd() const;
		int				getIndexInVector() const;
        std::string     getNickname() const;
        std::string     getUsername() const;
        std::string     getHostname() const;
        std::string     getServername() const;
        std::string     getRealname()  const;
        std::string     getPassword() const;
		std::string		getInputStr() const;

        bool            getAuthenticated() const;
        bool            getHasNickname() const;
        bool            getHasUsername() const;
        bool            getHasPassword() const;
		bool			getReceivedWelcome() const;
		const std::vector<Channel*>& getChannels() const;


        //setters
        void setFd(int fd);
		void setIndexInVector(int index);
        void setNickname(std::string &nickname);
        void setUsername(std::string &username);
        void setHostname(std::string &hostname);
        void setServername(std::string &servername);
        void setRealname(std::string &realname);
        void setPassword(std::string &password);

        void setHasNickname(bool hasNickname);
        void setHasUsername(bool hasUsername);
        void setHasPassword(bool hasPassword);
        void setAuthenticated(bool authenticated);
		void setReceivedWelcome(bool receivedWelcome);

		bool joinChannel(Channel *channel, const std::string& key);
		void partChannel(Channel *channel);

};

std::ostream &operator<<(std::ostream &out, const Client &client);

#endif
