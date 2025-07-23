#ifndef IntCell_h
#define IntCell_h

class IntCell {
  //sometimes you will just see the int storedValue up here and then not including the private section

  public:
    explicit IntCell(int initialValue = 0);
    int read() const;
    void write(int x);

  private:
    int storedValue;
};

#endif
