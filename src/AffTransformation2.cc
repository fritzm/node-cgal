#include "AffTransformation2.h"
#include "Direction2.h"
#include "cgal_args.h"

using namespace std;


AffTransformation2::AffTransformation2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *AffTransformation2::Name = "AffTransformation2";


void AffTransformation2::AddProperties(std::vector<PropertyDescriptor>& properties)
{
}


bool AffTransformation2::ParseArg(Napi::Env env, Napi::Value arg, Aff_transformation_2& receiver)
{
    if (arg.IsObject() && arg.As<Napi::Object>().InstanceOf(sConstructor.Value())) {
        receiver = Unwrap(arg.As<Napi::Object>())->mWrapped;
        return true;
    }

    if (arg.IsArray()) {
        Napi::Array inits = arg.As<Napi::Array>();

        if (inits.Length() >= 6 && inits.Length() <= 7) {
            K::RT m00, m01, m02, m10, m11, m12, hw(1);
            if (::ParseNumberArg(env, inits[0u], m00) &&
                ::ParseNumberArg(env, inits[1], m01) &&
                ::ParseNumberArg(env, inits[2], m02) &&
                ::ParseNumberArg(env, inits[3], m10) &&
                ::ParseNumberArg(env, inits[4], m11) &&
                ::ParseNumberArg(env, inits[5], m12))
            {
                if ((inits.Length() == 7) && !::ParseNumberArg(env, inits[6], hw))
                    return false;
                receiver = Aff_transformation_2(m00, m01, m02, m10, m11, m12, hw);
                return true;
            }
        }

        if (inits.Length() >= 2 && inits.Length() <= 3) {
            Direction_2 dir;
            K::RT num, den(1);
            if (Direction2::ParseArg(env, inits[0u], dir) &&
                ::ParseNumberArg(env, inits[1], num))
            {
                if ((inits.Length() == 3) && !::ParseNumberArg(env, inits[2], den))
                    return false;
                receiver = Aff_transformation_2(Rotation(), dir, num, den);
                return true;
            }
        }

    }

    return false;
}


Napi::Value AffTransformation2::ToPOD(Napi::Env env, Aff_transformation_2 const& aff, bool precise)
{
    Napi::Array array = Napi::Array::New(env, 7);

    for(int i=0; i<7; ++i) {
        int r = (i == 6) ? 2 : i/3;
        int c = (i == 6) ? 2 : i%3;
        K::RT a = aff.hm(r, c);
        if (precise) {
            ostringstream str;
#ifdef CGAL_USE_EPECK
            str << a.exact();
#else
            str << a;
#endif
            array.Set(i, str.str());
        } else {
            array.Set(i, CGAL::to_double(a));
        }
    }

    return array;
}

