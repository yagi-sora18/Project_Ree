#include "Collision.h"
#include <cmath>  // fabs �̂���

// �I�u�W�F�N�g�^�C�v�������蔻��Ώۂ��m�F
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

// 2��Collision���Փ˂��Ă��邩�𔻒�
bool Collision::IsCheckHitCollision(Collision target1, Collision target2)
{
	Vector2D distance, size;

	// �ʒu�����i��Βl�j
	distance.x = fabs(target1.pivot.x - target2.pivot.x);
	distance.y = fabs(target1.pivot.y - target2.pivot.y);

	// �Փ˔���Ɏg���T�C�Y�iAABB����j
	size.x = (target1.box_size.x + target2.box_size.x) / 2;
	size.y = (target1.box_size.y + target2.box_size.y) / 2;

	// �����̎��ŏd�Ȃ��Ă���ΏՓ�
	return (distance.x <= size.x && distance.y <= size.y);
}

/// <summary>
/// ��`�̕ӂ̊֌W�ʒu�œ����蔻����`�F�b�N
/// </summary>
/// <param name="c1">�v���C���[</param>
/// <param name="c2">�G</param>
/// <returns>�������Ă�����true�A�������Ă��Ȃ�������false</returns>
bool IsCheckCollision(const Collision& c1, const Collision& c2)
{
    // ��`1�̍��ӂƋ�`2�̉E�ӂ̈ʒu�֌W
    bool is_left_less_right = false;
    if (c1.point[0].x <= c2.point[1].x)
    {
        is_left_less_right = true;
    }

    // ��`1�̉E�ӂƋ�`2�̍��ӂ̈ʒu�֌W
    bool is_right_greater_left = false;
    if (c1.point[1].x >= c2.point[0].x)
    {
        is_right_greater_left = true;
    }

    // ��`1�̏�ӂƋ�`2�̉��ӂ̈ʒu�֌W
    bool is_top_less_bottom = false;
    if (c1.point[0].y <= c2.point[1].y)
    {
        is_top_less_bottom = true;
    }

    // ��`1�̉��ӂƋ�`2�̏�ӂ̈ʒu�֌W
    bool is_bottom_greater_top = false;
    if (c1.point[1].y >= c2.point[0].y)
    {
        is_bottom_greater_top = true;
    }

    // �S�Ă̏��������Ă͂܂��Ă�����A�q�b�g
    if (is_left_less_right == true &&
        is_right_greater_left == true &&
        is_top_less_bottom == true &&
        is_bottom_greater_top == true)
    {
        return true;
    }

    // ������1�ł������Ă��Ȃ�������A�m�[�q�b�g
    return false;
}
