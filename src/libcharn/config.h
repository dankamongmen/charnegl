#ifndef CHARN_SRC_LIB_CONFIG
#define CHARN_SRC_LIB_CONFIG

#include <map>
#include <memory>
#include <libconfig.h++>

// Each libcharn element looking to be part of the config file can register
// itself as a CharnConfigModule, implementing this interface.
class CharnConfigModule {
public:
CharnConfigModule() = default;
virtual ~CharnConfigModule() = default;
virtual void Compress() = 0;
};

class CharnConfigModuleFactory {
public:
using TCreateMethod = std::unique_ptr<CharnConfigModule>(*)();
TCreateMethod m_CreateFunc;
CharnConfigModuleFactory() = delete;
static bool Register(const std::string name, TCreateMethod createFunc){
	if(auto it = s_methods.find(name) ; it == s_methods.end()){
		s_methods[name] = createFunc;
		return true;
	}
	return false;
}

static std::unique_ptr<CharnConfigModule> Create(const std::string& name){
	if(auto it = s_methods.find(name); it != s_methods.end()){
		return it->second();
	}
	return nullptr;
}

private:
static std::map<std::string, TCreateMethod> s_methods;
};

template <typename T>
class RegisteredInFactory
{
protected:
    static bool s_bRegistered;
};

template <typename T>
bool RegisteredInFactory<T>::s_bRegistered = CharnConfigModuleFactory::Register(T::getModuleName(), T::CreateMethod);

class CharnConfig {
public:
CharnConfig() : config() {};

// Load from the specified string. Propagates libconfig++ parsing exceptions.
void loadString(const std::string& s);

// Load from the specified file. Propagates libconfig++ parsing/IO exceptions.
void loadFile(const std::string& s);

// TODO kill this off
template<typename T> bool getValue(const std::string& s, T& val){
	return config.lookupValue(s, val);
}

private:
libconfig::Config config;
void validateToplevel();
};

#endif
