#pragma once
#include"Configure.h"
using uint32 = unsigned int;
class Route
{
public:
	Route();
	Route(const std::string& routeCode, const std::string& departure, const std::string& destination, uint32 distance, uint32 flightDuration);
	std::string formatInfo(); //格式化数据
	static Route fromString(const  std::string& str);

public:
	//航线编码			起飞地				降落地			公里数			飞行时长
	std::string routeCode;
	std::string departure;
	std::string destination;
	uint32 distance;
	uint32 flightDuration;


};


