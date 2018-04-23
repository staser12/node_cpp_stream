#include <nan.h>
#include <iostream>
#include <string>
//#include <unistd.h>
//#include <Windows.h>
#include <math.h>
#include <cstdio>
using namespace Nan;
using namespace v8;
using namespace std;

void buffer_delete_callback(char* data, void* the_vector) {
  delete reinterpret_cast<vector<unsigned char> *> (the_vector);
}

class MyWorker : public AsyncWorker {
  public:
    MyWorker(Callback * callback) : AsyncWorker(callback) {
      //srand((unsigned)time(0));
      srand(GetTickCount());
    }

    void Execute() {
      bmp = new vector<unsigned char>();

      for (int i = 0; i < 40; i++) {
         char randomletter = 'A' + (rand() % 26);
        //usleep(1000000);

        bmp->push_back(randomletter);

      }

      bmp->push_back('\n');
      //Sleep(1000);
    }

    void HandleOKCallback () {
        Local<Object> buffData =
               NewBuffer((char *)bmp->data(),
               bmp->size(), buffer_delete_callback,
               bmp).ToLocalChecked();
        Local<Value> argv[] = { Nan::Null(), buffData };
        callback->Call(2, argv);
    }

    private:
        vector<unsigned char> png_data;
        vector<unsigned char> * bmp;
};

NAN_METHOD(GetBuffAsync) {
    Callback *callback =
      new Callback(info[0].As<Function>());

    AsyncQueueWorker(
      new MyWorker(callback));
}

NAN_MODULE_INIT(Init) {
   Nan::Set(target, New<String>("getBuffAsync").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(GetBuffAsync)).ToLocalChecked());
}

NODE_MODULE(buffer_example, Init)