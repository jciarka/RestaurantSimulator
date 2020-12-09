#include "ServiceQueue.h"
#include <sstream>

ServiceQueue::ServiceQueue(IRaporter* global_raporter) : Raportable(global_raporter)
{

}

/// <summary>
/// Add calling group pointer to queue
/// </summary>
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

/// <summary>
/// Return first group from queue for service
/// </summary>
IGroup* ServiceQueue::dequeue_service()
{
	if (service_queue.empty())
		return nullptr;

	// Get group that called ealriest
	IGroup* group = service_queue.front();
	service_queue.pop();
	return group;
}
