#include "../includes/irc.hpp"
#include "../includes/server.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);
	if (port <= 0 || port > 65535) {
        std::cerr << "Usage: <port> should be integer in range [1, 65535]" << std::endl;
        return 1;
	}
    std::string password = argv[2];
	printHeader(password);

    Server server(port, 1, password);

    if (server.createServer())
		return 1;

    if (server.initializeServer())
		return 1;

    server.runServer();

    return 0;
}
