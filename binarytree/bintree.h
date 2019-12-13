class BinaryTree {
public:
    virtual void add(int what) = 0;
    virtual int getMin() const = 0;
    virtual void remove(int what) = 0;
    virtual void removeMin() = 0;
    virtual bool isEmpty()  const = 0;
    virtual ~BinaryTree() {}
};