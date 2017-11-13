#include "datamanager.h"
#include "utils.h"
#include "loader.h"

DataManager::DataManager()
{
	this->context = new VulkanContext();
	context->loader = new Loader(context);
}

std::unique_ptr<DataManager> DataManager::m_instance;
std::once_flag DataManager::m_onceFlag;
DataManager & DataManager::getInstance()
{
	std::call_once(m_onceFlag,
		[] {
		m_instance.reset(new DataManager);
	});
	return *m_instance.get();
}

DataManager::~DataManager()
{
}

void DataManager::cleanUp()
{
	delete context;
}

VulkanContext * DataManager::getContext()
{
	return context;
}

