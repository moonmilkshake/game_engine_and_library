#ifndef INSTANCECOUNT_H
#define INSTANCECOUNT_H

namespace crane
{
    template <typename T>
    class InstanceCount
    {
    public:
        virtual ~InstanceCount() { instanceCount--; }
        static int getInstanceCount() { return instanceCount; }

    protected:
        InstanceCount() { instanceCount++; }

    private:
        static int instanceCount;
        InstanceCount(const InstanceCount &) = delete;
        const InstanceCount &operator=(const InstanceCount &) = delete;
    };
    
    template <typename T>
    int InstanceCount<T>::instanceCount = 0;

}

#endif