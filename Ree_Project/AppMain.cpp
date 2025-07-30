#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Utility/Vector2D.h"

//=== �萔��` ===//
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int GROUND_HEIGHT = 400;      // �n�ʂ�Y���W
const float GRAVITY = 0.5f;         // �d�͉����x
const float JUMP_POWER_MIN = 5.0f;  // �Œ�W�����v��
const float JUMP_POWER_MAX = 20.0f; // �ő�W�����v��
const float CHARGE_SPEED = 0.3f;    // �W�����v�͗��ߑ��x
const float MOVE_SPEED = 2.0f;      // ���ړ����x

//=== �\���� ===//
struct Player {
    Vector2D pos;      // �ʒu
    Vector2D vel;      // ���x
    bool isJumping;    // �󒆂ɂ��邩
    bool isCharging;   // �W�����v���ߒ���
    float chargePower; // ���߃W�����v��
};

//=== �v���g�^�C�v�錾 ===//
void Update(Player& player);
void Draw(const Player& player);

//=== ���C���֐� ===//
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    // �v���C���[������
    Player player;
    player.pos = Vector2D(300.0f, GROUND_HEIGHT - 50.0f); // �����ʒu
    player.vel = Vector2D(0.0f, 0.0f);
    player.isJumping = false;
    player.isCharging = false;
    player.chargePower = 0.0f;

    // �Q�[�����[�v
    while (ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        InputControl::GetInstance()->Update(); // ���͍X�V

        Update(player);
        Draw(player);

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}

void Update(Player& player)
{
    InputControl* input = InputControl::GetInstance();

    // --- ���͏����F���E�ړ� (��Ɏ󂯕t����) --- //
    if (input->GetKey(KEY_INPUT_A))  player.vel.x = -MOVE_SPEED;
    else if (input->GetKey(KEY_INPUT_D)) player.vel.x = MOVE_SPEED;
    else player.vel.x = 0.0f; // ���������ĂȂ��Ƃ��͒�~�i�������c�������ꍇ�͊ɂ₩�Ɍ��������Ă�OK�j

    // --- �n��ɂ��鎞�̏��� --- //
    if (!player.isJumping)
    {
        // ���ړ��i���ڈʒu�ɉ��Z�j
        player.pos.x += player.vel.x;

        // �W�����v���ߊJ�n
        if (input->GetKeyDown(KEY_INPUT_SPACE))
        {
            player.isCharging = true;
            player.chargePower = JUMP_POWER_MIN;
        }

        // ���ߒ��̓W�����v�͂𑝉�
        if (player.isCharging && input->GetKey(KEY_INPUT_SPACE))
        {
            player.chargePower += CHARGE_SPEED;
            if (player.chargePower > JUMP_POWER_MAX) player.chargePower = JUMP_POWER_MAX;
        }

        // �X�y�[�X�L�[�𗣂�����W�����v
        if (player.isCharging && input->GetKeyUp(KEY_INPUT_SPACE))
        {
            player.isJumping = true;
            player.isCharging = false;
            player.vel.y = -player.chargePower;
        }
    }
    else
    {
        // �󒆈ړ��i�����t���j
        player.pos.x += player.vel.x;

        // �d��
        player.vel.y += GRAVITY;
        player.pos.y += player.vel.y;

        // �n�ʂɒ��n
        if (player.pos.y >= GROUND_HEIGHT - 50.0f)
        {
            player.pos.y = GROUND_HEIGHT - 50.0f;
            player.isJumping = false;
            player.vel.y = 0.0f;
            player.vel.x = 0.0f; // ���n���ɉ��ړ����~�߂�i�D�݂ɂ��ȗ��\�j
        }
    }
}


//=== �`�揈�� ===//
void Draw(const Player& player)
{
    // �n��
    DrawBox(0, GROUND_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(100, 255, 100), TRUE);

    // �v���C���[
    DrawBox(
        static_cast<int>(player.pos.x),
        static_cast<int>(player.pos.y),
        static_cast<int>(player.pos.x + 50),
        static_cast<int>(player.pos.y + 50),
        GetColor(255, 0, 0), TRUE
    );

    // ���߃Q�[�W�\��
    if (player.isCharging)
    {
        int gaugeWidth = static_cast<int>((player.chargePower / JUMP_POWER_MAX) * 100);
        DrawBox(10, 10, 10 + gaugeWidth, 30, GetColor(255, 255, 0), TRUE);
    }
}
