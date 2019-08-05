#ifndef CGALWRAPPER_H
#define CGALWRAPPER_H

#include "cgal_types.h"
#include "napi.h"


template<typename WrapperClass, typename CGALClass>
class CGALWrapper : public Napi::ObjectWrap<WrapperClass>
{
public:

    CGALWrapper(Napi::CallbackInfo const& info);
    virtual ~CGALWrapper();

    static Napi::Object Init(Napi::Env env, Napi::Object exports);

    static Napi::Object New(Napi::Env env, const CGALClass &CGALInstance);

    template<typename NumberPrimitive>
    static bool ParseArg(Napi::Env env, Napi::Value arg, NumberPrimitive& parsed);

    template<typename OutputIterator>
    static bool ParseSeqArg(Napi::Env env, Napi::Value arg, OutputIterator iterator);

    template<typename ForwardIterator>
    Napi::Value SeqToPOD(
        Napi::Env env, ForwardIterator first, ForwardIterator last, bool precise
    );

protected:

    CGALClass mWrapped;

    static Napi::FunctionReference sConstructor;

    Napi::Value ToPOD(Napi::CallbackInfo const& info);
    Napi::Value Inspect(Napi::CallbackInfo const& info);
    Napi::Value ToString(Napi::CallbackInfo const& info);

};


#include "CGALWrapper-inl.h"

#endif // !defined(CGALWRAPPER_H)
