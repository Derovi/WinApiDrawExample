#include "objectmanager.h"

const std::vector<std::function<GraphicObject*()>>& ObjectManager::getCreators() const {
    return creators;
}

const std::vector<std::string>& ObjectManager::getNames() const {
    return names;
}

int ObjectManager::getCurrentId() const {
    return currentId;
}

void ObjectManager::next() {
    currentId = (currentId + 1) % size();
}

GraphicObject* ObjectManager::create() {
    return creators[currentId]();
}

std::string ObjectManager::getName() {
    return names[currentId];
}

ObjectManager::ObjectManager() : currentId(0) {}

int ObjectManager::size() {
    return names.size();
}

void ObjectManager::prev() {
    currentId = (size() + currentId - 1) % size();
}
