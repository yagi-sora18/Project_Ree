#include "ObjectManager.h"

ObjectManager::~ObjectManager() {
    ClearAll();
}

void ObjectManager::Add(Object* obj) {
    objects.push_back(obj);
}

void ObjectManager::UpdateAll(float delta_time) {
    for (auto* obj : objects) {
        if (obj && obj->IsActive()) {
            obj->Update(delta_time);
        }
    }

    // 不要オブジェクト削除（非アクティブ）
    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [](Object* obj) {
                if (!obj->IsActive()) {
                    delete obj;
                    return true;
                }
                return false;
            }),
        objects.end()
    );
}

void ObjectManager::DrawAll(int camera_y) {
    for (auto* obj : objects) {
        if (obj && obj->IsActive()) {
            obj->Draw(camera_y);
        }
    }
}

void ObjectManager::ClearAll() {
    for (auto* obj : objects) {
        delete obj;
    }
    objects.clear();
}
