#pragma once

#include "DxLib.h"
#include "../Utillity/InputControl.h"
#include "../Utillity/ResourceManager.h"

// シーンの種類
enum class eSceneType
{
	eTitle,
	eInGame,
	eRanking,
	eCredit,
	eResult
};

// シーン基底クラス
class SceneBase
{
public:
	// 初期化処理
	virtual void Initialize() {}

	// 更新処理（次のシーンタイプを返す）
	virtual eSceneType Update(float delta_second)
	{
		return GetNowSceneType();
	}

	// 描画処理
	virtual void Draw() {}

	// 終了時処理
	virtual void Finalize() {}

	// 現在のシーンタイプを返す（純粋仮想関数）
	virtual eSceneType GetNowSceneType() const = 0;

	virtual ~SceneBase() {}
};
