#include "Line2.h"
#include "Point2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Line2::Name = "Line2";


void Line2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isEqual", IsEqual);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isDegenerate", IsDegenerate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isHorizontal", IsHorizontal);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isVertical", IsVertical);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "opposite", Opposite);
}


bool Line2::ParseArg(Isolate *isolate, Local<Value> arg, Line_2 &receiver)
{
    HandleScope scope(isolate);
    Local<Context> context = isolate->GetCurrentContext();

    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> inits = Local<Object>::Cast(arg);

        K::FT a, b, c;
        if (::ParseArg(isolate, inits->Get(context, SYMBOL(isolate, "a")).ToLocalChecked(), a) &&
            ::ParseArg(isolate, inits->Get(context, SYMBOL(isolate, "b")).ToLocalChecked(), b) &&
            ::ParseArg(isolate, inits->Get(context, SYMBOL(isolate, "c")).ToLocalChecked(), c))
        {
            receiver = Line_2(a, b, c);
            return true;
        }

        Point_2 p, q;
        if (Point2::ParseArg(isolate, inits->Get(context, SYMBOL(isolate, "p")).ToLocalChecked(), p) &&
            Point2::ParseArg(isolate, inits->Get(context, SYMBOL(isolate, "q")).ToLocalChecked(), q))
        {
            receiver = Line_2(p, q);
            return true;
        }

    }

    return false;
}


Local<Value> Line2::ToPOD(Isolate *isolate, const Line_2 &line, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> obj = Object::New(isolate);

    if (precise) {

        ostringstream astr;
#if CGAL_USE_EPECK
        astr << line.a().exact();
#else
        astr << setprecision(20) << line.a();
#endif
        (void)obj->Set(context, SYMBOL(isolate, "a"), String::NewFromUtf8(isolate, astr.str().c_str(), NewStringType::kNormal).ToLocalChecked());

        ostringstream bstr;
#if CGAL_USE_EPECK
        bstr << line.b().exact();
#else
        bstr << setprecision(20) << line.b();
#endif
        (void)obj->Set(context, SYMBOL(isolate, "b"), String::NewFromUtf8(isolate, bstr.str().c_str(), NewStringType::kNormal).ToLocalChecked());

        ostringstream cstr;
#if CGAL_USE_EPECK
        cstr << line.c().exact();
#else
        cstr << setprecision(20) << line.c();
#endif
        (void)obj->Set(context, SYMBOL(isolate, "c"), String::NewFromUtf8(isolate, cstr.str().c_str(), NewStringType::kNormal).ToLocalChecked());

    } else {

        (void)obj->Set(context, SYMBOL(isolate, "a"), Number::New(isolate, CGAL::to_double(line.a())));
        (void)obj->Set(context, SYMBOL(isolate, "b"), Number::New(isolate, CGAL::to_double(line.b())));
        (void)obj->Set(context, SYMBOL(isolate, "c"), Number::New(isolate, CGAL::to_double(line.c())));

    }

    return scope.Escape(obj);
}


void Line2::IsEqual(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Line_2 &thisLine = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Line2::ParseArg, Line_2, otherLine, info[0]);
        info.GetReturnValue().Set(Boolean::New(isolate, thisLine == otherLine));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what(), NewStringType::kNormal).ToLocalChecked());
    }
}


void Line2::IsDegenerate(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Line_2 &line = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, line.is_degenerate()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what(), NewStringType::kNormal).ToLocalChecked());
    }
}


void Line2::IsHorizontal(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Line_2 &line = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, line.is_horizontal()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what(), NewStringType::kNormal).ToLocalChecked());
    }
}


void Line2::IsVertical(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Line_2 &line = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, line.is_vertical()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what(), NewStringType::kNormal).ToLocalChecked());
    }
}


void Line2::Opposite(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Line_2 &line = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Line2::New(isolate, line.opposite()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what(), NewStringType::kNormal).ToLocalChecked());
    }
}
