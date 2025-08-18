#include "ObjectManager.h"
#include "Player/Player.h"  // �� �ǉ�



ObjectManager::~ObjectManager() {
    ClearAll();
}

void ObjectManager::Add(Object* obj) {
    objects.push_back(obj);
}

void ObjectManager::UpdateAll(float delta_time) {
    // �܂��e�I�u�W�F�N�g�̃��W�b�N�X�V
    for (auto* obj : objects) {
        if (obj && obj->IsActive()) {
            obj->Update(delta_time);
        }
    }

    // �� �v���C���[�̕����i�d�́E�����蔻��E���n�����Ȃǁj���Ă�
    //   �K�v�Ȃ炱���ŕ����v���C���[�ɂ��Ή���
    for (auto* obj : objects) {
        if (!obj || !obj->IsActive()) continue;
        if (auto* p = dynamic_cast<Player*>(obj)) {
            p->ApplyPhysics(objects);
        }
    }

    // �s�v�I�u�W�F�N�g�폜�i��A�N�e�B�u�j
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
