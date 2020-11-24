#include "ServiceQueue.h"
#include <sstream>

ServiceQueue::ServiceQueue(IRaporter& global_raporter) : Raportable(global_raporter)
{

}

void ServiceQueue::queue_service(IGroup* group)
{
	if (group == nullptr)
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Service Queue queue_service called with nullptr argument";
		throw std::logic_error(error_txt_stream.str());
	}
	service_queue.push(group);
}

IGroup* ServiceQueue::dequeue_service()
{
	if (service_queue.empty())
		return nullptr;

	// Pobierz najstarzy element
	IGroup* group = service_queue.front();
	// Usuñ go z kolejki
	service_queue.pop();
	return group;
}
