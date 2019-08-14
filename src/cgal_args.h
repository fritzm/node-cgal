#ifndef CGAL_ARGS_H
#define CGAL_ARGS_H

#define ARGS_ASSERT(ENV, ASSERTION)                     \
    if (!(ASSERTION)) {                                 \
        throw Napi::Error::New(env, "Wrong arguments"); \
    }                                                   \


#define ARGS_PARSE_LOCAL(ENV, PARSER, ARG_TYPE, RECEIVER, ARG) \
    ARG_TYPE RECEIVER;                                         \
    ARGS_ASSERT(ENV, PARSER(ENV, ARG, RECEIVER));              \


#define ARGS_PARSE_LOCAL_SEQ(ENV, PARSER, ARG_TYPE, RECEIVER, ARG)    \
    ARG_TYPE RECEIVER;                                                \
    ARGS_ASSERT(ENV, PARSER(ENV, ARG, std::back_inserter(RECEIVER))); \


#define ARGS_PARSE_NEW(ENV, PARSER, ARG_TYPE, RECEIVER, ARG) \
    ARG_TYPE *RECEIVER = new ARG_TYPE();                     \
    ARGS_ASSERT(ENV, PARSER(ENV, ARG, *RECEIVER));           \


#define NOARGS_PARSE_NEW(ENV, PARSER, ARG_TYPE, RECEIVER) \
    ARG_TYPE *RECEIVER = new ARG_TYPE();                  \
    ARGS_ASSERT(ENV, PARSER(ENV, *RECEIVER));             \

#endif // !defined(CGAL_ARGS_H)
