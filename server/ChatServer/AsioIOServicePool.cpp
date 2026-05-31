#include "AsioIOServicePool.h"
#include <iostream>

AsioIOServicePool::AsioIOServicePool(std::size_t size)
	:_ioServices(size), _nextIOService(0) {
	_works.reserve(size);
	_threads.reserve(size);

	for (std::size_t i = 0; i < size; ++i) {
		_works.emplace_back(std::make_unique<Work>(boost::asio::make_work_guard(_ioServices[i])));
	}

	for (std::size_t i = 0; i < size; ++i) {
		_threads.emplace_back([this, i]() {
			_ioServices[i].run();
			});
	}
}

AsioIOServicePool::~AsioIOServicePool() {
	Stop();
	std::cout << "AsioIOServicePool destruct" << endl;
}

boost::asio::io_context& AsioIOServicePool::GetIOService() {
	auto& service = _ioServices[_nextIOService++];
	if (_nextIOService == _ioServices.size()) {
		_nextIOService = 0;
	}
	return service;
}

void AsioIOServicePool::Stop() {
	for (auto& ioService : _ioServices) {
		ioService.stop();
	}

	for (auto& workGuard : _works) {
		workGuard.reset();
	}

	for (auto& thread : _threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}
