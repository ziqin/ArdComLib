#ifndef WatchersDic_h
#define WatchersDic_h

class String;

namespace ACL {

class Watcher;
template <typename T> class List;


/// Watchers 查找字典，O(n^2)
class WatchersDic final {
public:
    WatchersDic(const List<Watcher*> *watchersList);
    ~WatchersDic();
    Watcher* operator[](const String& name);
private:
    Watcher* *watchers;
    unsigned size;
};

} // namespace: ACL

#endif // WatchersDic_h