#include "ObjectManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Item/Coin.h"



ObjectManager::~ObjectManager() { ClearAll(); }



void ObjectManager::ClearAll() {
	for (auto* o : objects) delete o;
	objects.clear();
	score = 0;

}


void ObjectManager::UpdateAll(float dt) {
	// 1) 各オブジェクトのUpdate
	for (auto* obj : objects) if (obj && obj->IsActive()) obj->Update(dt);


	// 2) プレイヤーの物理適用
	for (auto* obj : objects) {
		if (!obj || !obj->IsActive()) continue;
		if (auto* p = dynamic_cast<Player*>(obj)) {
			p->ApplyPhysics(objects, dt);
		}
	}


	// 3) コイン取得
	for (auto* objP : objects) {
		auto* p = dynamic_cast<Player*>(objP);
		if (!p || !p->IsActive()) continue;
		for (auto* objC : objects) {
			auto* c = dynamic_cast<Coin*>(objC);
			if (!c || !c->IsActive() || c->collected) continue;
			if (IsCheckCollision(p->collision, c->collision)) { c->collected = true; AddScore(10); }
		}
	}



	// 4) 破棄
	objects.erase(std::remove_if(objects.begin(), objects.end(), [](Object* o) {
		if (!o || !o->IsActive()) { delete o; return true; }
		return false;
		}), objects.end());

}


//void ObjectManager::DrawAll(int camera_y) {
//	for (auto* obj : objects) if (obj && obj->IsActive()) obj->Draw(camera_y);
//}

void ObjectManager::DrawAll(int camera_x, int camera_y, int off_x, int off_y)
{
	//for (auto* obj : objects) if (obj && obj->IsActive()) obj->Draw(camera_x, camera_y);
	for (auto* obj : objects) if (obj && obj->IsActive()) obj->Draw(camera_x, camera_y, off_x, off_y);

}

Player* ObjectManager::GetPlayer() const
{
	return nullptr;
}
