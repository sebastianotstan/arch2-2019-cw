#include<iostream>
#include<exception>
using namespace std;

struct Exception : public exception{
  struct arithmetic_exception{
    virtual const char * what () const throw(){
      return "arithmetic exception";
    }
    virtual int code_num(){
      return -10;
    }
  };

  struct memory_exception : public exception{
    virtual const char * what () const throw(){
      return "memory exception";
    }
    virtual int code_num(){
      return -11;
    }
  };

  struct invalid_instructions : public exception{
    virtual const char * what () const throw(){
      return "invalid instructions";
    }
    virtual int code_num(){
      return -12;
    }
  };

  struct internal_error : public exception{
    virtual const char * what () const throw(){
      return "internal error";
    }
    virtual int code_num(){
      return -20;
    }
  };

  struct IO_error : public exception{
    virtual const char * what () const throw(){
      return "invalid instructions";
    }
    virtual int code_num(){
      return -21;
    }
  };
};
