#include "network.h"

Network::Network()
	: client(nullptr), server(nullptr), event()
{
	try 
	{
		if (enet_initialize() != 0)
		{
			std::cout << "Failed to initialize ENet" << std::endl;
			throw;
		}
		// create client
		client = enet_host_create(nullptr, 1, 2, 57600 / 8, 14400 / 8);
		if (client == nullptr)
		{
			std::cout << "Failed to create a client" << std::endl;
			throw;
		}

		ENetAddress address;
		ENetEvent event;

		enet_address_set_host(&address, host);
		address.port = port;

		server = enet_host_connect(client, &address, 2, 0);

		if (server == nullptr)
		{
			fprintf(stderr, "No available peers for initiating an ENet connection. \n");
			throw;
		}

		std::cout << "Waiting to connect to server..." << std::endl;

		/* Wait up to 5 seconds for the connection attempt to succeed. */
		if (enet_host_service(client, &event, 5000) > 0 &&
			event.type == ENET_EVENT_TYPE_CONNECT)
		{
			std::cout << "Connected to localhost:" << address.port << std::endl;
		}
		else
		{
			/* Either the 5 seconds are up or a disconnect event was */
			/* received. Reset the peer in the event the 5 seconds   */
			/* had run out without any significant event.            */
			std::cout << "Failed connection to localhost:" << address.port << std::endl;
			enet_peer_reset(server);
			throw;
		}
	}
	catch (std::exception)
	{
		enet_host_destroy(client);
		enet_deinitialize();
		exit(EXIT_FAILURE);
	}
}

Network::~Network()
{
	ENetEvent event;
	enet_peer_disconnect(server, 0);
	while (enet_host_service(client, &event, 1000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			enet_packet_destroy(event.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			std::cout << "Disconnection succeeded." << std::endl;
			break;
		}
	}
	enet_peer_reset(server);
	enet_host_destroy(client);
	enet_deinitialize();
}

void Network::SendPositionInfo(const Player& player)
{
	// send position/rotation
	// packet_type network_id x y z yaw pitch
	const std::string packet_str = 
		PacketBuilder::BuildPositionPacket( id,
											player.Position.x,
											player.Position.y,
											player.Position.z,
											player.Yaw,
											player.Pitch);
	ENetPacket* packet = enet_packet_create(packet_str.c_str(), strlen(packet_str.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(server, 0, packet);
}

void Network::ReceiveInfo(const Scene& scene)
{
	if (enet_host_service(client, &event, 0) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			std::istringstream iss((char*)event.packet->data);
			std::cout << iss.str();
			enet_packet_destroy(event.packet);
			break;
		}
	}
}
