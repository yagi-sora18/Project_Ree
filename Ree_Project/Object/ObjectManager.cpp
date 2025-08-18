#include "ObjectManager.h"
#include "Player/Player.h"  // ★ 追加



ObjectManager::~ObjectManager() {
    ClearAll();
}

void ObjectManager::Add(Object* obj) {
    objects.push_back(obj);
}

void ObjectManager::UpdateAll(float delta_time) {
    // まず各オブジェクトのロジック更新
    for (auto* obj : objects) {
        if (obj && obj->IsActive()) {
            obj->Update(delta_time);
        }
    }

    // ★ プレイヤーの物理（重力・当たり判定・着地処理など）を呼ぶ
    //   必要ならここで複数プレイヤーにも対応可
    for (auto* obj : objects) {
        if (!obj || !obj->IsActive()) continue;
        if (auto* p = dynamic_cast<Player*>(obj)) {
            p->ApplyPhysics(objects);
        }
    }

    // 不要オブジェクト削除（非アクティブ）
    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [](Object* obj) {
                if (!obj || !obj->IsActive()) {
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
