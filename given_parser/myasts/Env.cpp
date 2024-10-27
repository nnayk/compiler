#include "Env.hpp"

Entry::Entry(std::shared_ptr<ast::Type> t): type(t) {}
Env::Env() {}

extern Env structTLE;
extern Env globalsTLE;

void Env::addBinding(const std::string &key, std::shared_ptr<Entry> entry) {
    spdlog::debug("inside Env::{}\n",__func__);
    std::cout << "Env addr = " << this << std::endl;
    spdlog::debug("Adding key={}, type={},scope={}\n",key,*entry->type,entry->scope);
    this->bindings[key] = entry;
    this->display();
}

void Env::display() {
    spdlog::debug("inside Env::{}\n",__func__);
    std::cout << "Env addr = " << this << std::endl;
    for(const auto& pair : this->bindings) {
        spdlog::info("{}: {} ",pair.first,pair.second->scope);
        std::cout << "entry = " << pair.second << std::endl;
    }
}

std::shared_ptr<Entry> Env::lookup(const std::string &id) {
    spdlog::debug("inside Env::{}\n",__func__);
    spdlog::debug("looking up {}\n",id);
    this->display();
    auto iter = this->bindings.find(id);
	std::shared_ptr<Entry> entry = nullptr;
    if(iter != this->bindings.end()) {
		entry = iter->second;
        spdlog::debug("Local env: Found {} of type {}, scope = {}\n",id,*entry->type,entry->scope);
        assert(entry->scope==0 || entry->scope==1);
	} else if(globalsTLE.bindings.find(id) != globalsTLE.bindings.end()) {
		auto it = globalsTLE.bindings.find(id);
        entry = it->second;
        assert(entry->scope==2);
		spdlog::debug("Global env: Found {} of type {}, scope = {}\n",id,*entry->type,entry->scope);
	// look in global struct env
	} else if(structTLE.bindings.find(id) != structTLE.bindings.end()) {
		auto it = structTLE.bindings.find(id);
        entry = it->second;
		spdlog::debug("Struct env: Found {} of type {}, scope = {}\n",id,*entry->type,entry->scope);
        assert(entry->scope==2);
    }
    return entry;
}
