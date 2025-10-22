#pragma once


template <class Type>
class Singleton {
protected:
	Singleton() = default;
	~Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
public:
	static Type* GetInstance() {
		static Type instance; // à¿ëSÇ»ê√ìIéıñΩ
		return &instance;
	}
	static void DeleteInstance() { /* no-op */ }
};