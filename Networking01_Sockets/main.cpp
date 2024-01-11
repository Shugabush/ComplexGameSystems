#include <WinSock2.h>
#include <WS2tcpip.h>

#include <iostream>

int main()
{
	WSADATA wsaData;
	int success = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (success != 0)
	{
		std::cerr << "ERROR: Failed to initialize WinSock :(" << std::endl;
		return -1;
	}

	addrinfo config;
	memset(&config, 0, sizeof(addrinfo)); // zero out memory for that object
	config.ai_family = AF_INET;
	config.ai_socktype = SOCK_DGRAM;
	config.ai_protocol = IPPROTO_UDP;
	config.ai_flags = AI_PASSIVE;

	addrinfo* localAddr = nullptr;
	success = getaddrinfo(nullptr, "0", &config, &localAddr);

	return 0;
}