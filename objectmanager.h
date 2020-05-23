#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include <functional>
#include "graphisobject.h"

class ObjectManager {
  public:
    ObjectManager();

    void registerObject(const std::string& name, const std::function<GraphicObject*()>& creator) {
        names.push_back(name);
        creators.push_back(creator);
    }

    GraphicObject* create();

    std::string getName();

    void next();

    void prev();

    int size();

    [[nodiscard]] int getCurrentId() const;

    [[nodiscard]] const std::vector<std::function<GraphicObject*()>>& getCreators() const;

    [[nodiscard]] const std::vector<std::string>& getNames() const;

  private:
    std::vector<std::function<GraphicObject*()>> creators;
    std::vector<std::string> names;

    int currentId;
};

#endif  // OBJECTMANAGER_H
