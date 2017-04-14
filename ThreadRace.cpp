// ConsoleApplication21.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <gtest\gtest.h>
#include <atomic>
#include <thread>
#include <iostream>

void function1(std::atomic<int>& it)
{
	for (int i = 0; i < 100; ++i)
	{
		it = i;
		std::cout << "Atomic : " << it << std::endl;
	}
}
void function2(std::atomic<int>& it)
{
	for (int i = 0; i < 10; ++i)
	{
		it = i;
		std::cout << "To 10 : " <<  it << std::endl;
	}
}

void function1Int(int& it)
{
	for (int i = 0; i < 100; ++i)
	{
		it = i;
		std::cout << "Int : " << it << std::endl;
	}
}

void function2Int(int& it)
{
	for (int i = 0; i < 10; ++i)
	{
		it = i;
		std::cout << "To 10 : " << it << std::endl;
	}
}


void function1t()
{
	std::atomic<int> it;
	std::thread t1(function1, std::ref(it));
	std::thread t2 (function2, std::ref(it));
	t1.join();
	t2.join();
	std::cout << it << std::endl;
}
void function2t()
{
	std::atomic<int> it;
	std::thread t1(function1, std::ref(it));
	std::thread t2(function2, std::ref(it));
	t2.join();
	t1.join();
	std::cout << it << std::endl;
}

void function3t()
{
	int it;
	std::thread t1(function1Int, std::ref(it));
	std::thread t2(function2Int, std::ref(it));
	t1.join();
	t2.join();
	std::cout << it << std::endl;
}
int main(int argc, char **argv)  // bug, no thread-safe
{
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
TEST(firstTest, schouldExecuteFunction)
{
	function1t();
}
TEST(secondTest, schouldExecuteFunction)
{
	function2t();
}

TEST(thirdTest, schouldExecuteFunction)
{
	function3t();
}

