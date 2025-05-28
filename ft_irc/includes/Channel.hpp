#pragma once

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "client.hpp"
#include <vector>
#include <string>
#include <iostream>

class Client;

class Channel
{
	public:
		Channel(const std::string& name);
		Channel(const Channel& other);
		Channel& operator = (const Channel& other);
		~Channel();

		const std::string& getName() const;
		const std::string& getName();

		const std::string& getTopic() const;
		const std::string& getTopic();
		void setTopic(const std::string& topic);

		const std::vector<Client*>& getClients() const;
		const std::vector<Client*>& getClients();

		const std::string& getPassword();
		const std::string& getPassword() const;

		const bool& getModeInvOnly();
		const bool& getModeInvOnly() const;
		void setModeInvOnly(const bool&);

		const bool& getModeTopicOpOnly();
		const bool& getModeTopicOpOnly() const;
		void setModeTopicOpOnly(const bool&);

		const size_t& getModeLimit();
		const size_t& getModeLimit() const;
		void setModeLimit(const size_t&);

		bool isLimitReached();
		bool isBadKey(const std::string& key);

		void addClient(Client* client);
		bool removeClient(Client* client);
		bool isMember(Client* client);
		void broadcast(const std::string& msg);
		void broadcastFromClient(const std::string& msg, Client* client);
		void sendTopic(Client* client);
		void sendNames(Client* client);
		void sendWho(Client* client);
		void sendModeInfo(Client* client);
		void applyModeChange(Client* client, std::string& modestring, std::string modeargs);

		void addOperator(Client* client);
		void addInvite(Client* client);
		void removeOperator(Client* client);
		void removeInvite(Client* client);
		bool isOperator(Client* client);
		bool isInvited(Client* client);
		bool isTopic() const;
		Client* getClientByNick(const std::string& nick);
		
	private:
		std::string buildModeInfo(void);

		std::string _name;
		std::string _topic;
		std::string _password;
		bool _invite_only;
		bool _topic_op_only;
		size_t _limit;
		std::vector<Client*> _clients;
		std::vector<Client*> _operators;
		std::vector<Client*> _invited;

};

#endif
