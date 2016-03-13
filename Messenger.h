#ifndef Messenger_h
#define Messenger_h

namespace ACL {

class Watcher;
class TaskWorker;
template <typename T> class List;

/// 信使
class Messenger final {
public:
    Messenger(unsigned baudRate);
    Messenger(unsigned baudRate, unsigned long timeout);
    ~Messenger();
    void addWatcher(Watcher *watcher);
    void addWorker(TaskWorker *worker);
    void work();
private:
    List<Watcher*> *watchersList;
    List<TaskWorker*> *workersList;
};

} // namespace: ACL

#endif // Messenger_h