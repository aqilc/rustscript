#include <stdint.h>
#include <string.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/// FUNCTIONS COPIED FROM XXH HASH LIBRARY FOR USES IN EFFICIENT LINKING ///
#define XXH_PRIME64_1  0x9E3779B185EBCA87ULL  /*!< 0b1001111000110111011110011011000110000101111010111100101010000111 */
#define XXH_PRIME64_2  0xC2B2AE3D27D4EB4FULL  /*!< 0b1100001010110010101011100011110100100111110101001110101101001111 */
#define XXH_PRIME64_3  0x165667B19E3779F9ULL  /*!< 0b0001011001010110011001111011000110011110001101110111100111111001 */
#define XXH_PRIME64_4  0x85EBCA77C2B2AE63ULL  /*!< 0b1000010111101011110010100111011111000010101100101010111001100011 */
#define XXH_PRIME64_5  0x27D4EB2F165667C5ULL  /*!< 0b0010011111010100111010110010111100010110010101100110011111000101 */
#ifdef __has_builtin
#  define XXH_HAS_BUILTIN(x) __has_builtin(x)
#else
#  define XXH_HAS_BUILTIN(x) 0
#endif
#ifdef __has_attribute
# define XXH_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
# define XXH_HAS_ATTRIBUTE(x) 0
#endif
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= XXH_C23_VN) && defined(__has_c_attribute)
# define XXH_HAS_C_ATTRIBUTE(x) __has_c_attribute(x)
#else
# define XXH_HAS_C_ATTRIBUTE(x) 0
#endif
#define XXH_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#if !defined(NO_CLANG_BUILTIN) && XXH_HAS_BUILTIN(__builtin_rotateleft32) \
                               && XXH_HAS_BUILTIN(__builtin_rotateleft64)
#  define XXH_rotl32 __builtin_rotateleft32
#  define XXH_rotl64 __builtin_rotateleft64
/* Note: although _rotl exists for minGW (GCC under windows), performance seems poor */
#elif defined(_MSC_VER)
#  define XXH_rotl32(x,r) _rotl(x,r)
#  define XXH_rotl64(x,r) _rotl64(x,r)
#else
#  define XXH_rotl32(x,r) (((x) << (r)) | ((x) >> (32 - (r))))
#  define XXH_rotl64(x,r) (((x) << (r)) | ((x) >> (64 - (r))))
#endif
#if defined (__GNUC__)
# define XXH_CONSTF  __attribute__((__const__))
# define XXH_PUREF   __attribute__((__pure__))
# define XXH_MALLOCF __attribute__((__malloc__))
#else
# define XXH_CONSTF  /* disable */
# define XXH_PUREF
# define XXH_MALLOCF
#endif
#if defined(__GNUC__) || defined(__clang__)
#  define XXH_FORCE_INLINE static __inline__ __attribute__((__always_inline__, __unused__))
#  define XXH_NO_INLINE static __attribute__((__noinline__))
#elif defined(_MSC_VER)  /* Visual Studio */
#  define XXH_FORCE_INLINE static __forceinline
#  define XXH_NO_INLINE static __declspec(noinline)
#elif defined (__cplusplus) \
  || (defined (__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))   /* C99 */
#  define XXH_FORCE_INLINE static inline
#  define XXH_NO_INLINE static
#else
#  define XXH_FORCE_INLINE static
#  define XXH_NO_INLINE static
#endif
#if XXH_HAS_ATTRIBUTE(noescape)
# define XXH_NOESCAPE __attribute__((__noescape__))
#else
# define XXH_NOESCAPE
#endif

static void* XXH_memcpy(void* dest, const void* src, size_t size) { return memcpy(dest,src,size); }

#  if defined(__GNUC__) && !(defined(__ARM_ARCH) && __ARM_ARCH < 7 && defined(__ARM_FEATURE_UNALIGNED))
#    define XXH_FORCE_MEMORY_ACCESS 1
#  endif

#if (defined(XXH_FORCE_MEMORY_ACCESS) && (XXH_FORCE_MEMORY_ACCESS==3))
#elif (defined(XXH_FORCE_MEMORY_ACCESS) && (XXH_FORCE_MEMORY_ACCESS==2))
static u64 XXH_read64(const void* memPtr) {
    return *(const u64*) memPtr;
}
static u32 XXH_read32(const void* memPtr) { return *(const u32*) memPtr; }
#elif (defined(XXH_FORCE_MEMORY_ACCESS) && (XXH_FORCE_MEMORY_ACCESS==1))
#ifdef XXH_OLD_NAMES
typedef union { u32 u32; u64 u64; } __attribute__((__packed__)) unalign64;
#endif
static u64 XXH_read64(const void* ptr) {
    typedef __attribute__((__aligned__(1))) u64 unalign64;
    return *((const unalign64*)ptr);
}
#ifdef XXH_OLD_NAMES
typedef union { u32 u32; } __attribute__((__packed__)) unalign;
#endif
static u32 XXH_read32(const void* ptr)
{
    typedef __attribute__((__aligned__(1))) u32 xxh_unalign32;
    return *((const xxh_unalign32*)ptr);
}
#else
static u64 XXH_read64(const void* memPtr) {
    u64 val;
    XXH_memcpy(&val, memPtr, sizeof(val));
    return val;
}
static u32 XXH_read32(const void* memPtr) {
    u32 val;
    XXH_memcpy(&val, memPtr, sizeof(val));
    return val;
}
#endif   /* XXH_FORCE_DIRECT_MEMORY_ACCESS */
#if defined(_MSC_VER)     /* Visual Studio */
#  define XXH_swap64 _byteswap_uint64
#elif XXH_GCC_VERSION >= 403
#  define XXH_swap64 __builtin_bswap64
#else
static u64 XXH_swap64(u64 x)
{
    return  ((x << 56) & 0xff00000000000000ULL) |
            ((x << 40) & 0x00ff000000000000ULL) |
            ((x << 24) & 0x0000ff0000000000ULL) |
            ((x << 8)  & 0x000000ff00000000ULL) |
            ((x >> 8)  & 0x00000000ff000000ULL) |
            ((x >> 24) & 0x0000000000ff0000ULL) |
            ((x >> 40) & 0x000000000000ff00ULL) |
            ((x >> 56) & 0x00000000000000ffULL);
}
#endif
#if defined(_MSC_VER)     /* Visual Studio */
#  define XXH_swap32 _byteswap_ulong
#elif XXH_GCC_VERSION >= 403
#  define XXH_swap32 __builtin_bswap32
#else
static u32 XXH_swap32 (u32 x)
{
    return  ((x << 24) & 0xff000000 ) |
            ((x <<  8) & 0x00ff0000 ) |
            ((x >>  8) & 0x0000ff00 ) |
            ((x >> 24) & 0x000000ff );
}
#endif
/* XXH_FORCE_MEMORY_ACCESS==3 is an endian-independent byteshift load. */
#if (defined(XXH_FORCE_MEMORY_ACCESS) && (XXH_FORCE_MEMORY_ACCESS==3))
XXH_FORCE_INLINE u64 XXH_readLE64(const void* memPtr) {
    const u8* bytePtr = (const u8 *)memPtr;
    return bytePtr[0]
         | ((u64)bytePtr[1] << 8)
         | ((u64)bytePtr[2] << 16)
         | ((u64)bytePtr[3] << 24)
         | ((u64)bytePtr[4] << 32)
         | ((u64)bytePtr[5] << 40)
         | ((u64)bytePtr[6] << 48)
         | ((u64)bytePtr[7] << 56);
}

XXH_FORCE_INLINE u64 XXH_readBE64(const void* memPtr) {
    const u8* bytePtr = (const u8 *)memPtr;
    return bytePtr[7]
         | ((u64)bytePtr[6] << 8)
         | ((u64)bytePtr[5] << 16)
         | ((u64)bytePtr[4] << 24)
         | ((u64)bytePtr[3] << 32)
         | ((u64)bytePtr[2] << 40)
         | ((u64)bytePtr[1] << 48)
         | ((u64)bytePtr[0] << 56);
}
XXH_FORCE_INLINE u32 XXH_readLE32(const void* memPtr) {
    const u8* bytePtr = (const u8 *)memPtr;
    return bytePtr[0]
         | ((u32)bytePtr[1] << 8)
         | ((u32)bytePtr[2] << 16)
         | ((u32)bytePtr[3] << 24);
}

XXH_FORCE_INLINE u32 XXH_readBE32(const void* memPtr) {
    const u8* bytePtr = (const u8 *)memPtr;
    return bytePtr[3]
         | ((u32)bytePtr[2] << 8)
         | ((u32)bytePtr[1] << 16)
         | ((u32)bytePtr[0] << 24);
}
#else
XXH_FORCE_INLINE u64 XXH_readLE64(const void* ptr) {
    return XXH_read64(ptr);
}
static u64 XXH_readBE64(const void* ptr) {
    return XXH_swap64(XXH_read64(ptr));
}
XXH_FORCE_INLINE u32 XXH_readLE32(const void* ptr) {
    return XXH_read32(ptr);
}

static u32 XXH_readBE32(const void* ptr) {
    return XXH_swap32(XXH_read32(ptr));
}
#endif
XXH_FORCE_INLINE u32
XXH_readLE32_align(const void* ptr, bool align)
{
    if (align==1 /*XXH_unaligned*/) {
        return XXH_readLE32(ptr);
    } else {
        return *(const u32*)ptr;
    }
}

XXH_FORCE_INLINE u64
XXH_readLE64_align(const void* ptr, bool align) {
    if (align==1 /*XXH_unaligned*/)
        return XXH_readLE64(ptr);
    else
        return *(const u64*)ptr;
}

static u64 XXH64_round(u64 acc, u64 input) {
    acc += input * XXH_PRIME64_2;
    acc  = XXH_rotl64(acc, 31);
    acc *= XXH_PRIME64_1;
    return acc;
}
static u64 XXH64_mergeRound(u64 acc, u64 val) {
    val  = XXH64_round(0, val);
    acc ^= val;
    acc  = acc * XXH_PRIME64_1 + XXH_PRIME64_4;
    return acc;
}
static u64 XXH64_avalanche(u64 hash) {
    hash ^= hash >> 33;
    hash *= XXH_PRIME64_2;
    hash ^= hash >> 29;
    hash *= XXH_PRIME64_3;
    hash ^= hash >> 32;
    return hash;
}
#define XXH_get32bits(p) XXH_readLE32_align(p, align)
#define XXH_get64bits(p) XXH_readLE64_align(p, align)
static XXH_PUREF u64 XXH64_finalize(u64 hash, const u8* ptr, size_t len, bool align) {
    len &= 31;
    while (len >= 8) {
        u64 const k1 = XXH64_round(0, XXH_get64bits(ptr));
        ptr += 8;
        hash ^= k1;
        hash  = XXH_rotl64(hash,27) * XXH_PRIME64_1 + XXH_PRIME64_4;
        len -= 8;
    }
    if (len >= 4) {
        hash ^= (u64)(XXH_get32bits(ptr)) * XXH_PRIME64_1;
        ptr += 4;
        hash = XXH_rotl64(hash, 23) * XXH_PRIME64_2 + XXH_PRIME64_3;
        len -= 4;
    }
    while (len > 0) {
        hash ^= (*ptr++) * XXH_PRIME64_5;
        hash = XXH_rotl64(hash, 11) * XXH_PRIME64_1;
        --len;
    }
    return  XXH64_avalanche(hash);
}
XXH_FORCE_INLINE XXH_PUREF u64 XXH64_endian_align(const u8* input, size_t len, u64 seed, bool align) {
    u64 h64;

    if (len>=32) {
        const u8* const bEnd = input + len;
        const u8* const limit = bEnd - 31;
        u64 v1 = seed + XXH_PRIME64_1 + XXH_PRIME64_2;
        u64 v2 = seed + XXH_PRIME64_2;
        u64 v3 = seed + 0;
        u64 v4 = seed - XXH_PRIME64_1;

        do {
            v1 = XXH64_round(v1, XXH_get64bits(input)); input+=8;
            v2 = XXH64_round(v2, XXH_get64bits(input)); input+=8;
            v3 = XXH64_round(v3, XXH_get64bits(input)); input+=8;
            v4 = XXH64_round(v4, XXH_get64bits(input)); input+=8;
        } while (input<limit);

        h64 = XXH_rotl64(v1, 1) + XXH_rotl64(v2, 7) + XXH_rotl64(v3, 12) + XXH_rotl64(v4, 18);
        h64 = XXH64_mergeRound(h64, v1);
        h64 = XXH64_mergeRound(h64, v2);
        h64 = XXH64_mergeRound(h64, v3);
        h64 = XXH64_mergeRound(h64, v4);

    } else {
        h64  = seed + XXH_PRIME64_5;
    }

    h64 += (u64) len;

    return XXH64_finalize(h64, input, len, align);
}
static u64 XXH64 (XXH_NOESCAPE const void* input, size_t len, u64 seed) {
    if ((((size_t)input) & 7)==0) {  /* Input is aligned, let's leverage the speed advantage */
        return XXH64_endian_align((const u8*)input, len, seed, 0/*XXH_aligned*/);
    }

    return XXH64_endian_align((const u8*)input, len, seed, 1);
}
