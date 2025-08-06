#pragma once

// Singleton�e���v���[�g�N���X
template <class Type>
class Singleton
{
protected:
    // �p���N���X����̂ݐ����E�j��������
    Singleton() = default;
    ~Singleton() = default;

    // �R�s�[�֎~
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // �C���X�^���X�擾�i����̂ݐ����j
    static Type* GetInstance()
    {
        static Type* instance = new Type(); // new �� protected ����Ă΂��
        return instance;
    }

    // �C���X�^���X�폜�inew�ō�����̂� delete �j
    static void DeleteInstance()
    {
        Type* instance = GetInstance();
        delete instance;

        // �Đ����̂��߃|�C���^�� null �ɖ߂��������A
        // static���[�J���ϐ��Ȃ̂őΉ��ł��Ȃ��B
        // ���ӁF���̕��@�ł͈�x DeleteInstance ����ƍė��p�ł��܂���B
    }
};
