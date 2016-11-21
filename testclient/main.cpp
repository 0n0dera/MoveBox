#include <iostream>
#include <enet/enet.h>
#include <string>
int main()
{
	if (enet_initialize() != 0)
	{
		std::cout << "Failed to initialize ENet" << std::endl;
		return EXIT_FAILURE;
	}

	// create client
	ENetHost* client;
	client = enet_host_create(nullptr, 1, 2, 57600 / 8, 14400 / 8);
	if (client == nullptr)
	{
		std::cout << "Failed to create a client" << std::endl;
	}

	ENetAddress address;
	ENetEvent event;
	ENetPeer* server;

	enet_address_set_host(&address, "localhost");
	address.port = 4444;

	server = enet_host_connect(client, &address, 2, 0);

	if (server == nullptr)
	{
		fprintf(stderr, "No available peers for initiating an ENet connection. \n");
		exit(EXIT_FAILURE);
	}

	std::string in;

	/* Wait up to 5 seconds for the connection attempt to succeed. */
	if (enet_host_service(client, &event, 5000) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connected to localhost:" << address.port << std::endl;
		while (1)
		{
			std::cin >> in;
			ENetPacket* packet = enet_packet_create(in.c_str(), strlen(in.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(server, 0, packet);
			while (enet_host_service(client, &event, 10) > 0)
			{
				switch (event.type)
				{
				case ENET_EVENT_TYPE_RECEIVE:
					std::cout << "data : " << event.packet->data << std::endl;
					enet_packet_destroy(event.packet);
					break;
				}
			}
		}
	}
	else
	{
		/* Either the 5 seconds are up or a disconnect event was */
		/* received. Reset the peer in the event the 5 seconds   */
		/* had run out without any significant event.            */
		std::cout << "Failed connection to localhost:" << address.port << std::endl;
	}
	enet_peer_reset(server);
	
	enet_host_destroy(client);
	atexit(enet_deinitialize);
}