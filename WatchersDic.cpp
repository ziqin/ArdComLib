#include "WatchersDic.h"
#include "Watcher.h"
#include "List.h"
#include <Arduino.h>
#include <stdlib.h>

using namespace ACL;

int cmp_Watcher_by_name(const void *_left, const void *_right) {
    if (!(_left && _right))
        return 1;
    const Watcher *left = static_cast<const Watcher*>(_left);
    const Watcher *right = static_cast<const Watcher*>(_right);
    return left->name() < right->name() ?
           -1 :
           left->name() != right->name();
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
    qsort(watchers, size, sizeof(Watcher*), cmp_Watcher_by_name);
}


WatchersDic::~WatchersDic() {
    delete[] watchers;
}


/// 查找 name 匹配的 watcher，返回其指针
/// 若找不到，则返回 NULL
Watcher* WatchersDic::operator[](const String& name) {
    Watcher *w = new Watcher(name);
    Watcher *ans = *static_cast<Watcher**>(bsearch(w, watchers, size, sizeof(Watcher*), cmp_Watcher_by_name));
    delete w;
    return ans;
}