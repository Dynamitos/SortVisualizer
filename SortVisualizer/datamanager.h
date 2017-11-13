
#ifndef DATAMANAGER
#define DATAMANAGER

#include <stack>
#include <list>
#include <memory>
#include <vector>
#include <mutex>
#include "display.h"
class VulkanContext;

class DataManager
{
public:
	static DataManager& getInstance();
	virtual ~DataManager();
	void cleanUp();
	VulkanContext* getContext();
	
private:
	VulkanContext* context;
	DataManager(void);
	DataManager(const DataManager& src);
	static std::unique_ptr<DataManager> m_instance;
	static std::once_flag m_onceFlag;
};

#endif


