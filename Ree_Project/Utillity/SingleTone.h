#pragma once

// Singletonテンプレートクラス
template <class Type>
class Singleton
{
protected:
    // 継承クラスからのみ生成・破棄を許可
    Singleton() = default;
    ~Singleton() = default;

    // コピー禁止
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // インスタンス取得（初回のみ生成）
    static Type* GetInstance()
    {
        static Type* instance = new Type(); // new は protected から呼ばれる
        return instance;
    }

    // インスタンス削除（newで作ったので delete 可）
    static void DeleteInstance()
    {
        Type* instance = GetInstance();
        delete instance;

        // 再生成のためポインタを null に戻したいが、
        // staticローカル変数なので対応できない。
        // 注意：この方法では一度 DeleteInstance すると再利用できません。
    }
};
