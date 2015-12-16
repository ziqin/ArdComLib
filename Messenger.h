#ifndef Messenger_h
#define Messenger_h

class String;

namespace ACL {

class Watcher;
template <typename T> class List;

/// 信使
class Messenger final {
public:
    Messenger(unsigned baudRate);
    Messenger(unsigned baudRate, unsigned long timeout);
    ~Messenger();
    void addWatcher(Watcher *watcher);
    void work();
private:
    List<Watcher*> *watchersList;
};

} // namespace: ACL

#endif // Messenger_h