#include "WatchersDic.h"
#include "Watcher.h"
#include "List.h"
#include <Arduino.h>

using namespace ACL;

template <typename T>
inline void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}


WatchersDic::WatchersDic(const List<Watcher*> *watchersList) {
    if (!watchersList) {
        size = 0;
        watchers = NULL;
    } else { // 复制 watchers
        size = watchersList->size();
        watchers = new Watcher*[size];
        unsigned i = 0;
        for (List<Watcher*>::iterator itr = watchersList->begin(); itr != watchersList->end(); ++itr)
            if (*itr)
                watchers[i++] = *itr;
    }

    // 对 watchers 按 name 排序
    // O(n^2) （实际应用中，watchers[] 的元素个数通常不多）
    for (unsigned i = 0; i < size; ++i)
        for (unsigned j = i; j < size; ++j)
            if (watchers[i] && watchers[j] && watchers[i]->name() > watchers[j]->name())
                swap(watchers[i], watchers[j]);
}


WatchersDic::~WatchersDic() {
    delete[] watchers;
}


/// 查找 name 匹配的 watcher，返回其指针
/// 若找不到，则返回 NULL
Watcher* WatchersDic::operator[](const String& name) {
    if (!size)
        return NULL;

    // 二分查找
    unsigned left = 0, right = size - 1;
    while (right - left > 1) {
        unsigned mid = (left + right) >> 1;
        if (watchers[mid]->name() > name)
            right = mid;
        else
            left = mid;
    }
    if (watchers[left]->name() == name)
        return watchers[left];
    else if (watchers[right]->name() == name)
        return watchers[right];
    else
        return NULL;
}