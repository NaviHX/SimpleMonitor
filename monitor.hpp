#ifndef __MONITOR_HPP__
#define __MONITOR_HPP__

#include <mutex>
#include <functional>

template <class T>
class Monitor
{
public:
    template <typename... ARGS>
    Monitor(ARGS &&...args) : _t(std::forward<ARGS>(args)...){};

    struct MonitorHelper
    {
        MonitorHelper(Monitor *mon) : _mon(mon), _lock(mon->_mutex) {}
        T *operator->() { return &_mon->_t; }

        Monitor *_mon;
        std::unique_lock<std::mutex> _lock;
    };

    MonitorHelper operator->() { return MonitorHelper(this); }
    MonitorHelper get_access() { return MonitorHelper(this); }
    T &unsafe_get_access() { return _t; }

private:
    std::mutex _mutex;
    T _t;
};

#endif
