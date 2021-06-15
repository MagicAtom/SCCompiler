#ifndef _WINDS_POOL_H_
#define _WINDS_POOL_H_

#include<cstddef>
#include <vector>


class Pool{
public:
    Pool():allocated_(0){}
    virtual ~Pool(){}
    Pool(const Pool& example) = delete;
    Pool& operator=(const Pool& example) = delete;
    virtual void* Alloc() = 0;
    virtual void Free(void* addr) = 0;
    virtual void Clear() = 0;

protected:
    size_t allocated_;
}

template <class T>
class PoolImp: public Pool{
public:
    PoolImp():root_(nullptr){}
    virtual ~PoolImp(){}
    PoolImp(const Pool& example) = delete;
    PoolImp& operator=(Pool& example) = delete;
    virtual void* Alloc();
    virtual void Free(void* addr);
    virtual void Clear();
private:
    enum{
        COUNT = (4 * 1024) / sizeof(T);
    };

    

}


#endif