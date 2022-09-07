#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <objbase.h>
#else
#include <uuid/uuid.h>
#endif

namespace UUIDGen
{
#ifndef _WIN32
    /* This is the linux friendly implementation, but it could work on other
     * systems that have libuuid available
     */
    void create_guid(char guid[])
    {
        uuid_t out;
        uuid_generate(out);
        uuid_unparse_lower(out, guid);
    }
#else
    void create_guid(char guid[])
    {
        GUID out = {0};
        CoCreateGuid(&out);
        sprintf(guid, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", out.Data1, out.Data2, out.Data3, out.Data4[0], out.Data4[1], out.Data4[2], out.Data4[3], out.Data4[4], out.Data4[5], out.Data4[6], out.Data4[7]);
        for (; *guid; ++guid)
            *guid = tolower(*guid); // To lower one-liner
    }
#endif
}