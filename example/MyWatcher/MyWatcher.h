#ifndef MyWatcher_h
#define MyWatcher_h

#include <Watcher.h>

class MyWatcher: public ACL::Watcher {
public:
    MyWatcher(const String& name):
        ACL::Watcher(name)
    {
        // 在这里编写初始化代码
    }

    ACL::Variant value() override
    {
        // 在这里编写读数和数值处理代码
        // 把要返回的内容写在 ACL::Variant() 里
        // 若获取数据的过程中遇到错误，则返回 ACL::Variant(ACL::null)
        return ACL::Variant();
    }

private:
    // 可以在这里编写 MyWatcher 实例所需的变量等
};

#endif