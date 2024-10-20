//
// do this:
//
// #include "common/json.h"
//
// to include this file
//
// no other headers will be included here
//

#define TAG "json"

//
// From Switch Off Exceptions here:
// https://json.nlohmann.me/home/exceptions/
//
#define JSON_TRY_USER if (true)
#define JSON_CATCH_USER(exception) if (false)
#define JSON_THROW_USER(exception) \
    { ABORT("JSON exception: %s", (exception).what()); }

#include <nlohmann/json.hpp>

#undef TAG
















