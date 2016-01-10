#ifndef NameDic_h
#define NameDic_h

#include "List.h"
#include <stddef.h>

class String;

namespace ACL {

template <typename T> class List;


/// 查找字典，O(log2(n))
template <typename T>
class NameDic final {
public:
    NameDic(const List<T*> *membersList);
    ~NameDic();
    T* operator[](const String& name);
private:
    T* *members;
    unsigned size;
};


template <typename T>
NameDic<T>::NameDic(const List<T*> *membersList) {
    if (!membersList) {
        size = 0;
        members = NULL;
    } else { // 复制 members
        size = membersList->size();
        members = new T*[size];
        unsigned i = 0;
        for (typename List<T*>::iterator itr = membersList->begin(); itr != membersList->end(); ++itr)
            if (*itr)
                members[i++] = *itr;
    }

    // 对 members[] 按 name 排序
    // O(n^2) （实际应用中，members[] 的元素个数通常不多）
    for (unsigned i = 0; i < size; ++i)
        for (unsigned j = i; j < size; ++j)
            if (members[i] && members[j] && members[i]->name() > members[j]->name()) {
                T* tmp = members[i];
                members[i] = members[j];
                members[j] = tmp;
            }
}


template <typename T>
NameDic<T>::~NameDic() {
    delete[] members;
}


/// 查找 name 匹配的项，返回其指针
/// 若找不到，则返回 NULL
template <typename T>
T* NameDic<T>::operator[](const String& name) {
    if (!size)
        return NULL;

    // 二分查找
    unsigned left = 0, right = size - 1;
    while (right - left > 1) {
        unsigned mid = (left + right) >> 1;
        if (members[mid]->name() > name)
            right = mid;
        else
            left = mid;
    }
    if (members[left]->name() == name)
        return members[left];
    else if (members[right]->name() == name)
        return members[right];
    else
        return NULL;
}

} // namespace: ACL

#endif // NameDic_h