#pragma once
#include <sstream>
#include <string>

namespace PacketBuilder
{
	struct PositionPacket
	{
		int id;
		float x;
		float y;
		float z;
		float yaw;
		float pitch;
	};

	static std::string BuildPositionPacket(int id, float x, float y, float z, float yaw, float pitch)
	{
		std::ostringstream packet;
		packet << 1 << " " << id << " " << x << " " << y << " " << z << " " << yaw << " " << pitch;
		return packet.str();
	}
};