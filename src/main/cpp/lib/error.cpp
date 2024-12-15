
#include "common/error.h"

#include "common/logging.h"

#include <cerrno> // for E2BIG et al


#define TAG "error"


//
// switch to using strerrorname_np when Android minimum API is 35
//
// Android:
// `strerrorname_np(38)` would return "ENOSYS", because `ENOSYS` is errno 38
// Available since API level 35.
//
//

const char *ErrorName(int e) {
    switch (e) {
    //
    // defined by C++11
    //
    case E2BIG: return "E2BIG";
    case EACCES: return "EACCES";
    case EADDRINUSE: return "EADDRINUSE";
    case EADDRNOTAVAIL: return "EADDRNOTAVAIL";
    case EAFNOSUPPORT: return "EAFNOSUPPORT";
    case EAGAIN: return "EAGAIN"; // also EWOULDBLOCK
    case EALREADY: return "EALREADY";
    case EBADF: return "EBADF";
    case EBADMSG: return "EBADMSG";
    case EBUSY: return "EBUSY";
    case ECANCELED: return "ECANCELED";
    case ECHILD: return "ECHILD";
    case ECONNABORTED: return "ECONNABORTED";
    case ECONNREFUSED: return "ECONNREFUSED";
    case ECONNRESET: return "ECONNRESET";
    case EDEADLK: return "EDEADLK";
    case EDESTADDRREQ: return "EDESTADDRREQ";
    case EDOM: return "EDOM";
    case EEXIST: return "EEXIST";
    case EFAULT: return "EFAULT";
    case EFBIG: return "EFBIG";
    case EHOSTUNREACH: return "EHOSTUNREACH";
    case EIDRM: return "EIDRM";
    case EILSEQ: return "EILSEQ";
    case EINPROGRESS: return "EINPROGRESS";
    case EINTR: return "EINTR";
    case EINVAL: return "EINVAL";
    case EIO: return "EIO";
    case EISCONN: return "EISCONN";
    case EISDIR: return "EISDIR";
    case ELOOP: return "ELOOP";
    case EMFILE: return "EMFILE";
    case EMLINK: return "EMLINK";
    case EMSGSIZE: return "EMSGSIZE";
    case ENAMETOOLONG: return "ENAMETOOLONG";
    case ENETDOWN: return "ENETDOWN";
    case ENETRESET: return "ENETRESET";
    case ENETUNREACH: return "ENETUNREACH";
    case ENFILE: return "ENFILE";
    case ENOBUFS: return "ENOBUFS";
    case ENODATA: return "ENODATA";
    case ENODEV: return "ENODEV";
    case ENOENT: return "ENOENT";
    case ENOEXEC: return "ENOEXEC";
    case ENOLCK: return "ENOLCK";
    case ENOLINK: return "ENOLINK";
    case ENOMEM: return "ENOMEM";
    case ENOMSG: return "ENOMSG";
    case ENOPROTOOPT: return "ENOPROTOOPT";
    case ENOSPC: return "ENOSPC";
    case ENOSR: return "ENOSR";
    case ENOSTR: return "ENOSTR";
    case ENOSYS: return "ENOSYS";
    case ENOTCONN: return "ENOTCONN";
    case ENOTDIR: return "ENOTDIR";
    case ENOTEMPTY: return "ENOTEMPTY";
    case ENOTRECOVERABLE: return "ENOTRECOVERABLE";
    case ENOTSOCK: return "ENOTSOCK";
//    case ENOTSUP: return "ENOTSUP";
    case ENOTTY: return "ENOTTY";
    case ENXIO: return "ENXIO";
    // On Linux, ENOTSUP and EOPNOTSUPP are the same despite POSIX saying they should be distinct.
    case EOPNOTSUPP: return "EOPNOTSUPP";
    case EOVERFLOW: return "EOVERFLOW";
    case EOWNERDEAD: return "EOWNERDEAD";
    case EPERM: return "EPERM";
    case EPIPE: return "EPIPE";
    case EPROTO: return "EPROTO";
    case EPROTONOSUPPORT: return "EPROTONOSUPPORT";
    case EPROTOTYPE: return "EPROTOTYPE";
    case ERANGE: return "ERANGE";
    case EROFS: return "EROFS";
    case ESPIPE: return "ESPIPE";
    case ESRCH: return "ESRCH";
    case ETIME: return "ETIME";
    case ETIMEDOUT: return "ETIMEDOUT";
    case ETXTBSY: return "ETXTBSY";
    case EXDEV: return "EXDEV";
    default: LOGE("ErrorName: unhandled error: %d", e); return "UNKNOWN";
    }
}
















