#ifndef Messenger_h
#define Messenger_h

class String;

namespace ACL {

class Watcher;
template <typename T> class List;

/// 信使
class Messenger {
public:
    Messenger(unsigned baudRate);
    Messenger(unsigned baudRate, unsigned long timeout);
    virtual ~Messenger();
    void addWatcher(Watcher *Watcher);
    void listen();
protected:
    List<Watcher*> *watchersList;
};

} // namespace: ACL

#endif // Messenger_h