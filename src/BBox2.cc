#include "BBox2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *BBox2::Name = "BBox2";


void BBox2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "overlaps", Overlaps);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "add", Add);
}


bool BBox2::ParseArg(Isolate *isolate, Local<Value> arg, Bbox_2 &receiver)
{
    HandleScope scope(isolate);
    Local<Context> context = isolate->GetCurrentContext();

    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> bounds = Local<Object>::Cast(arg);

        if (bounds->Get(context, SYMBOL(isolate, "xmin")).ToLocalChecked()->IsNumber() &&
            bounds->Get(context, SYMBOL(isolate, "ymin")).ToLocalChecked()->IsNumber() &&
            bounds->Get(context, SYMBOL(isolate, "xmax")).ToLocalChecked()->IsNumber() &&
            bounds->Get(context, SYMBOL(isolate, "ymax")).ToLocalChecked()->IsNumber())
        {
            receiver = Bbox_2(
                bounds->Get(context, SYMBOL(isolate, "xmin")).ToLocalChecked()->NumberValue(context).ToChecked(),
                bounds->Get(context, SYMBOL(isolate, "ymin")).ToLocalChecked()->NumberValue(context).ToChecked(),
                bounds->Get(context, SYMBOL(isolate, "xmax")).ToLocalChecked()->NumberValue(context).ToChecked(),
                bounds->Get(context, SYMBOL(isolate, "ymax")).ToLocalChecked()->NumberValue(context).ToChecked()
            );
            return true;
        }

    }

    return false;
}


Local<Value> BBox2::ToPOD(Isolate *isolate, const Bbox_2 &box, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> obj = Object::New(isolate);
    (void)obj->Set(context, SYMBOL(isolate, "xmin"), Number::New(isolate, box.xmin()));
    (void)obj->Set(context, SYMBOL(isolate, "ymin"), Number::New(isolate, box.ymin()));
    (void)obj->Set(context, SYMBOL(isolate, "xmax"), Number::New(isolate, box.xmax()));
    (void)obj->Set(context, SYMBOL(isolate, "ymax"), Number::New(isolate, box.ymax()));
    return scope.Escape(obj);
}


void BBox2::Overlaps(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Bbox_2 &thisBox = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, BBox2::ParseArg, Bbox_2, otherBox, info[0]);
        return info.GetReturnValue().Set(Boolean::New(isolate, do_overlap(thisBox, otherBox)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what(), NewStringType::kNormal).ToLocalChecked());
    }
}


void BBox2::Add(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Bbox_2 &thisBox = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, BBox2::ParseArg, Bbox_2, otherBox, info[0]);
        return info.GetReturnValue().Set(BBox2::New(isolate, thisBox + otherBox));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what(), NewStringType::kNormal).ToLocalChecked());
    }
}
