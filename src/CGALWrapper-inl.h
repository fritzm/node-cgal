#ifndef CGALWRAPPER_INL_H
#define CGALWRAPPER_INL_H

#include "CGAL/Object.h"
#include "cgal.h"
#include "cgal_args.h"
#include "napi.h"

#include <sstream>
#include <typeinfo>
#include <vector>


template<typename WrapperClass, typename CGALClass>
Napi::FunctionReference CGALWrapper<WrapperClass, CGALClass>::sConstructor;


template<typename WrapperClass, typename CGALClass>
CGALWrapper<WrapperClass, CGALClass>::CGALWrapper(Napi::CallbackInfo const& info)
:   Napi::ObjectWrap<WrapperClass>(info) 
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() <= 1);
    if (info.Length() == 1) {
        ARGS_ASSERT(env, WrapperClass::ParseArg(env, info[0], mWrapped));
    }
}


template<typename WrapperClass, typename CGALClass>
CGALWrapper<WrapperClass, CGALClass>::~CGALWrapper()
{
}


template<typename WrapperClass, typename CGALClass>
Napi::Object CGALWrapper<WrapperClass, CGALClass>::Init(Napi::Env env, Napi::Object exports)
{
    std::vector<typename CGALWrapper<WrapperClass, CGALClass>::PropertyDescriptor> properties;
    WrapperClass::AddProperties(env, properties);

    properties.insert(properties.end(), {
       CGALWrapper::StaticValue("wrappedClass", Napi::String::New(env, Demangle(typeid(CGALClass).name()))),
       CGALWrapper::InstanceMethod("toPOD", &CGALWrapper::ToPOD), 
       CGALWrapper::InstanceMethod("inspect", &CGALWrapper::Inspect), 
       CGALWrapper::InstanceMethod("toString", &CGALWrapper::ToString) 
    });

    Napi::Function func = CGALWrapper::DefineClass(env, WrapperClass::Name, properties);

    sConstructor = Napi::Persistent(func);
    sConstructor.SuppressDestruct();

    exports.Set(WrapperClass::Name, func);
    return exports;
}


template<typename WrapperClass, typename CGALClass>
Napi::Object CGALWrapper<WrapperClass, CGALClass>::New(Napi::Env env, const CGALClass &CGALInstance)
{
    Napi::Object obj = sConstructor.New({});
    CGALWrapper::Unwrap(obj)->mWrapped = CGALInstance;
    return obj;
}


template<typename NumberType>
bool ParseNumberArg(Napi::Env env, Napi::Value arg, NumberType& parsed)
{
    if (arg.IsNumber()) {
        parsed = arg.As<Napi::Number>();
        return true;
    } else if (arg.IsString()) {
        std::istringstream str(arg.As<Napi::String>());
        str >> parsed;
        return !str.fail();
    } else {
        return false;
    }
    return false;
}


template<typename WrapperClass, typename CGALClass>
template<typename ForwardIterator>
Napi::Value CGALWrapper<WrapperClass, CGALClass>::SeqToPOD(
    Napi::Env env,
    ForwardIterator first, ForwardIterator last,
    bool precise)
{
    Napi::Array array = Napi::Array::New(env);
    ForwardIterator it;
    uint32_t i;
    for(it=first,i=0; it!=last; ++it,++i) {
        array[i] = WrapperClass::ToPOD(env, *it, precise);
    }
    return array;
}


template<typename WrapperClass, typename CGALClass>
template<typename OutputIterator>
bool CGALWrapper<WrapperClass, CGALClass>::ParseSeqArg(
    Napi::Env env,
    Napi::Value arg,
    OutputIterator iterator)
{
    if (!arg.IsObject()) return false;
    Napi::Array wrappers = arg.As<Napi::Array>();
    for(uint32_t i=0; i<wrappers.Length(); ++i) {
        CGALClass newCGALInstance;
        if (WrapperClass::ParseArg(env, wrappers[i], newCGALInstance)) {
            *(iterator++) = newCGALInstance;
        } else {
            return false;
        }
    }
    return true;
}


template<typename WrapperClass, typename CGALClass>
Napi::Value CGALWrapper<WrapperClass, CGALClass>::ToPOD(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();

    ARGS_ASSERT(env, info.Length() <= 1)

    bool precise = true;
    if (info.Length() == 1) {
        ARGS_ASSERT(env, info[0].IsBoolean())
        precise = info[0].As<Napi::Boolean>();
    }

    return WrapperClass::ToPOD(env, mWrapped, precise);
}


template<typename WrapperClass, typename CGALClass>
Napi::Value CGALWrapper<WrapperClass, CGALClass>::Inspect(Napi::CallbackInfo const& info)
{
    return info.This().ToString();
}


template<typename WrapperClass, typename CGALClass>
Napi::Value CGALWrapper<WrapperClass, CGALClass>::ToString(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    std::ostringstream str;
    str << "[object "  << WrapperClass::Name << " " << mWrapped << "]";
    return Napi::String::New(env, str.str());
}


#endif // !defined(CGALWRAPPER_INL_H)
