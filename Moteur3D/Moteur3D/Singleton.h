#ifndef  SINGLETON_H
#define SINGLETON_H

#pragma once
template<class T>
class Singleton //REVIEW : See if we can (or if it need) changes.
{
public:
	Singleton();

	static T* GetInstance();

protected:

	virtual ~Singleton();

	static T* instance;
};

template<class T>
Singleton<T>::Singleton()
{
	if (instance == nullptr)
	{
		instance = static_cast<T*>(this);
	}
}

template<class T>
Singleton<T>::~Singleton()
{
	if (instance == this)
	{
		instance = nullptr;
	}
}

template<class T>
T* Singleton<T>::instance = nullptr;

template<class T>
T* Singleton<T>::GetInstance()
{
	return instance;
}
#endif
