#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include <functional>
#include <thread>
#include <atomic>

using namespace std;

class Pool
{
private:
    queue<std::function<void()>> m_function_queue;
    mutex m_locker;
    condition_variable m_data_condition;
    atomic<bool> m_accept_functions;

public:
    Pool() 
        : m_function_queue(), m_locker(), m_data_condition(), m_accept_functions(true)
        {}
    ~Pool() {}

    void push(std::function<void()> func)
    {
      unique_lock<std::mutex> lock(m_locker);
      m_function_queue.push(func);
      lock.unlock();
      m_data_condition.notify_one();
    }

    void done()
    {
      unique_lock<std::mutex> lock(m_locker);
      m_accept_functions = false;
      lock.unlock();
      m_data_condition.notify_all();
    }

    void infinite_loop_func()
    {
      std::function<void()> func;
      while (true)
    {
        {
            unique_lock<std::mutex> lock(m_locker);
            m_data_condition.wait(lock, [this]() {return !m_function_queue.empty() || !m_accept_functions; });
            if (!m_accept_functions && m_function_queue.empty())
            {
                return;
            }
            func = m_function_queue.front();
            m_function_queue.pop();
        }
        func();
    }
}

};

Pool function_pool;

void example_function()
{
    int sum = 0;
    for(int i = 1; i <= 1000; ++i)
    {
        sum += i;
    }
    cout << "Sum is: " << sum << "\n";
}


int main()
{
    int num_threads = std::thread::hardware_concurrency();
    vector<std::thread> thread_pool;
    for (int i = 0; i < num_threads; i++)
    {
        thread_pool.push_back(std::thread(&Pool::infinite_loop_func, &function_pool));
    }

    for (int i = 0; i < 3; i++)
    {
        function_pool.push(example_function);
    }
    function_pool.done();
    for (unsigned int i = 0; i < thread_pool.size(); i++)
    {
        thread_pool.at(i).join();
    }
}
