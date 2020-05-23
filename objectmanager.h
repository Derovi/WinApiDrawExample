#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include <functional>
#include "graphisobject.h"

class ObjectManager {
  public:
    ObjectManager();

    void registerObject(const std::wstring& name, const std::function<GraphicObject*()>& creator);

    GraphicObject* create();

    std::wstring getName();

    void next();

    void prev();

    int size();

    [[nodiscard]] int getCurrentId() const;

    [[nodiscard]] const std::vector<std::function<GraphicObject*()>>& getCreators() const;

    [[nodiscard]] const std::vector<std::wstring>& getNames() const;

  private:
    std::vector<std::function<GraphicObject*()>> creators;
    std::vector<std::wstring> names;

    int currentId;
};

#endif  // OBJECTMANAGER_H
