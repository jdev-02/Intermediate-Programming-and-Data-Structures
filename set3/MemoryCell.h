#ifndef MemoryCell_h
#define MemoryCell_h

template <class Object>

class MemoryCell {

  public:

    explicit MemoryCell(const Object & initialValue = Object())
      : storedValue( initialValue ) {}

    const Object & read() const
      { return storedValue; }

    void write(const Object & x)
      { storedValue = x; }

  private:
    Object storedValue;

};

#endif
