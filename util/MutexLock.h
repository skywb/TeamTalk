#ifndef MUTEXLOCK_H_HXOKDXQ3
#define MUTEXLOCK_H_HXOKDXQ3

#include <iostream>
#include <pthread.h>
#include <assert.h>
#include <boost/noncopyable.hpp>


namespace Util {


	/*
	 * 借鉴了muduo的设计， 但是有修改， 将lock函数设置为私有方法， 不允许除了MutexLockGuard以外调用
	 * 所以需要将MutexLockGuard设置为友元类
	 */
	class MutexLock : public boost::noncopyable
	{
		friend class MutexLockGuard;
	public:
		MutexLock () {
			pthread_mutex_init(&_mutex, NULL);
		}

		virtual ~MutexLock () {
			pthread_mutex_destroy(&_mutex);
		}

	private:
		pthread_mutex_t _mutex;


		//只能被MutexLockGuard调用
		void lock() {
			pthread_mutex_lock(&_mutex);
		}

		//只能被MutexLockGuard调用
		void unlock() {
			pthread_mutex_unlock(&_mutex);
		}
	};



	//不允许被继承和拷贝， 防止死锁
	class MutexLockGuard final : public boost::noncopyable
	{
	public:
		explicit MutexLockGuard (MutexLock &_mutex) : _mutex(_mutex) {
			_mutex.lock();
		}
		~MutexLockGuard () {
			_mutex.unlock();
		}
	
	private:
		MutexLock& _mutex;
	};
}

#define MutexLockGuard(x) std::static_assert(false, "missing mutex guard var name");

#endif /* end of include guard: MUTEXLOCK_H_HXOKDXQ3 */
