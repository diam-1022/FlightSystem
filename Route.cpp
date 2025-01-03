#include "Route.h"
#include<sstream>

Route::Route()
{
}

Route::Route(const std::string& routeCode, const std::string& departure, const std::string& destination, uint32 distance, uint32 flightDuration)
	:routeCode(routeCode), departure(departure), destination(destination), distance(distance), flightDuration(flightDuration)
{

}

std::string Route::formatInfo()
{
	std::stringstream ss;
	ss<< routeCode <<"\t"<< departure << "\t" << destination << "\t" << distance << "\t" << flightDuration<<std::endl;
	return ss.str();
}

Route Route::fromString(const std::string& str)
{
	Route rot;
	std::stringstream ss(str);
	ss >> rot.routeCode >> rot.departure >> rot.destination >> rot.distance >> rot.flightDuration;

	return rot;
}
