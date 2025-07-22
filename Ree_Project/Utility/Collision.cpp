#include "Collision.h"
#include <cmath>  // fabs のため

// オブジェクトタイプが当たり判定対象か確認
bool Collision::IsCheckHitTarget(eObjectType object_type) const
{
	for (eObjectType type : hit_object_type)
	{
		if (type == object_type)
		{
			return true;
		}
	}
	return false;
}

// 2つのCollisionが衝突しているかを判定
bool Collision::IsCheckHitCollision(Collision target1, Collision target2)
{
	Vector2D distance, size;

	// 位置差分（絶対値）
	distance.x = fabs(target1.pivot.x - target2.pivot.x);
	distance.y = fabs(target1.pivot.y - target2.pivot.y);

	// 衝突判定に使うサイズ（AABB判定）
	size.x = (target1.box_size.x + target2.box_size.x) / 2;
	size.y = (target1.box_size.y + target2.box_size.y) / 2;

	// 両方の軸で重なっていれば衝突
	return (distance.x <= size.x && distance.y <= size.y);
}

/// <summary>
/// 矩形の辺の関係位置で当たり判定をチェック
/// </summary>
/// <param name="c1">プレイヤー</param>
/// <param name="c2">敵</param>
/// <returns>当たっていたらtrue、当たっていなかったらfalse</returns>
bool IsCheckCollision(const Collision& c1, const Collision& c2)
{
    // 矩形1の左辺と矩形2の右辺の位置関係
    bool is_left_less_right = false;
    if (c1.point[0].x <= c2.point[1].x)
    {
        is_left_less_right = true;
    }

    // 矩形1の右辺と矩形2の左辺の位置関係
    bool is_right_greater_left = false;
    if (c1.point[1].x >= c2.point[0].x)
    {
        is_right_greater_left = true;
    }

    // 矩形1の上辺と矩形2の下辺の位置関係
    bool is_top_less_bottom = false;
    if (c1.point[0].y <= c2.point[1].y)
    {
        is_top_less_bottom = true;
    }

    // 矩形1の下辺と矩形2の上辺の位置関係
    bool is_bottom_greater_top = false;
    if (c1.point[1].y >= c2.point[0].y)
    {
        is_bottom_greater_top = true;
    }

    // 全ての条件が当てはまっていたら、ヒット
    if (is_left_less_right == true &&
        is_right_greater_left == true &&
        is_top_less_bottom == true &&
        is_bottom_greater_top == true)
    {
        return true;
    }

    // 条件が1つでも合っていなかったら、ノーヒット
    return false;
}
