#ifndef IRC_HPP
#define IRC_HPP

#include <cstdlib>
#include <string>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <cerrno>
#include <climits>
#include <poll.h>
#include <vector>
#include <cstring>
#include <fcntl.h>

#define CRLF "\r\n"

//helper functions
int		convertInt(char * string);
void	printHeader(std::string password);
std::string unescape(const std::string& str);
std::vector<std::string> splitModeArgs(const std::string& str);
std::vector<std::string> splitOnDelim(const std::string& str, const char& delim);

#endif
