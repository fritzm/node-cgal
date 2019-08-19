#ifndef NODE_CGAL_H
#define NODE_CGAL_H

#include "napi.h"

std::string Demangle(char const* mangled);

Napi::Object Init(Napi::Env env, Napi::Object exports);

#endif
