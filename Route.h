#pragma once
#include"Configure.h"
using uint32 = unsigned int;
class Route
{
public:
	Route();
	Route(const std::string& routeCode, const std::string& departure, const std::string& destination, uint32 distance, uint32 flightDuration);
	std::string formatInfo(); //��ʽ������
	static Route fromString(const  std::string& str);

public:
	//���߱���			��ɵ�				�����			������			����ʱ��
	std::string routeCode;
	std::string departure;
	std::string destination;
	uint32 distance;
	uint32 flightDuration;


};


