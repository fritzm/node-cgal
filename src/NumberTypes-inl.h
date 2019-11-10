#include "NumberTypes.h"
#include "cgal_args.h"

#include <iomanip>
#include <sstream>

using namespace std;

template<typename CGALNumberType>
NumberType<CGALNumberType>::NumberType(Napi::CallbackInfo const& info)
:   CGALWrapper<NumberType, CGALNumberType>(info)
{
}


template<typename CGALNumberType>
char const* NumberType<CGALNumberType>::Name = "NumberType";


template<typename CGALNumberType>
void NumberType<CGALNumberType>::AddProperties(Napi::Env env, vector<typename NumberType::PropertyDescriptor>& properties)
{
}


template<typename CGALNumberType>
bool NumberType<CGALNumberType>::ParseArg(Napi::Env env, Napi::Value arg, CGALNumberType& receiver)
{
    if (arg.IsObject() && arg.As<Napi::Object>().InstanceOf(NumberType::sConstructor.Value())) {
        receiver = NumberType::Unwrap(arg.As<Napi::Object>())->mWrapped;
        return true;
    }

    if (arg.IsNumber()) {
        receiver = arg.As<Napi::Number>().DoubleValue();
        return true;
    }

    if (arg.IsString()) {
        std::istringstream str(arg.As<Napi::String>());
        str >> receiver;
        return !str.fail();
    }

    return false;
}


template<typename CGALNumberType>
Napi::Value NumberType<CGALNumberType>::ToPOD(Napi::Env env, CGALNumberType const& num, bool precise)
{
    if (precise) {
        ostringstream str;
#if CGAL_USE_EPECK
        str << num.exact();
#else
        str << setprecision(20) << num;
#endif
        return Napi::String::New(env, str.str());
    } else {
        return Napi::Number::New(env, CGAL::to_double(num));
    }
}
