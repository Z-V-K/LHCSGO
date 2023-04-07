#pragma once

using hash_t = uint32_t;

namespace FNV1a
{
    constexpr uint64_t BASIS = 0x811c9dc5;
    constexpr uint64_t PRIME = 0x1000193;

    inline constexpr hash_t get_const( const char* txt, const hash_t value = BASIS ) noexcept
    {
        return ( txt[ 0 ] == '\0' ) ? value :
            get_const( &txt[ 1 ], ( value ^ hash_t( txt[ 0 ] ) ) * PRIME );
    }
    
    inline hash_t get( const char* txt )
    {
        hash_t ret = BASIS;

        hash_t length = strlen( txt );
        for ( auto i = 0u; i < length; ++i )
        {
            ret ^= txt[ i ];
            ret *= PRIME;
        }

        return ret;
    }
}

#define CT_FNV1A_HASH( str ) \
[ ]( ) { \
constexpr hash_t ret = FNV1a::get_const( str ); \
return ret; \
}( )

#define FNV1A_HASH( str ) FNV1a::get( str )