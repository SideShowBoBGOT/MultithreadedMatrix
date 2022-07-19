#pragma once
#include <atomic>
#include <thread>
#include<future>
#include <vector>
#include <functional>
#include "TQueue.h"
class FunctionWrapper {
	struct ImplBase {
		virtual void call() = 0;
		virtual ~ImplBase() {}
	};
	template<typename F>
	struct ImplType :ImplBase {
		F f;
		ImplType(F&& f_) :f(std::move(f_)) {}
		void call() { f(); }
	};
	std::unique_ptr<ImplBase> impl;
public:
	template<typename F>
	FunctionWrapper(F&& f) :impl(new ImplType<F>(std::move(f)))
	{}
	void operator()() { impl->call(); }
	FunctionWrapper() {}
	FunctionWrapper(FunctionWrapper&& other):impl(std::move(other.impl))
	{}
	FunctionWrapper& operator=(FunctionWrapper&& other){
		impl = std::move(other.impl);
		return *this;
	}
	FunctionWrapper(const FunctionWrapper&) = delete;
	FunctionWrapper(FunctionWrapper&) = delete;
	FunctionWrapper& operator=(const FunctionWrapper&) = delete;

};
class ThreadPool {
	std::atomic_bool done;
	TQueue <FunctionWrapper> workQueue;
	std::vector<std::thread> threads;
	void WorkrerThread() {
		while (!done) {
			FunctionWrapper task;
			if (workQueue.TryPop(task)) {
				task();
			}
			else {
				std::this_thread::yield();
			}
		}
	}
public:
	ThreadPool() {
		done = false;
		unsigned const threadCount = std::thread::hardware_concurrency();
		try {
			for (unsigned i = 0; i < threadCount; i++) {
				threads.push_back(std::thread(&ThreadPool::WorkrerThread, this));
			}
		}
		catch (...) {
			done = true;
			throw;
		}
	}
	~ThreadPool() {
		done = true;
		for (auto& t : threads)
			t.join();
	}
	template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type> Submit(FunctionType f)
	{
		typedef typename std::result_of<FunctionType()>::type
			result_type;
		std::packaged_task<result_type()> task(std::move(f));
		std::future<result_type> res(task.get_future());
		workQueue.Push(std::move(task));
		return res;
	}
};


