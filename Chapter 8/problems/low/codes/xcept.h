
#ifndef Xcept_
#define Xcept_
using namespace std;

class BadInitializers {
   public:
      BadInitializers() {}
};

class NoMem {
   public:
      NoMem() {cout<<"insufficient memory!"<<endl;}
};

void my_new_handler()
{
   throw NoMem();
};

class OutOfBounds {
   public:
      OutOfBounds() {}
};

class SizeMismatch {
   public:
      SizeMismatch() {}
};

class MustBeZero {
   public:
      MustBeZero() {}
};

class BadInput {
   public:
      BadInput() {}
};

#endif
