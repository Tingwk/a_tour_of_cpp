namespace utility {
  template<class T>
  class SmartPtr {
    T * data_;
   public:
    SmartPtr() :data_{nullptr} {}
    SmartPtr(T* data):data_{data} {}
    ~SmartPtr() {
      if (nullptr != data_) {
        delete data_;
        data_ = nullptr;
      }
    }
    // operator overloading
    T* operator ->() {
      return data_;
    }
    T& operator* () {
      return *data_;
    }
  };
}