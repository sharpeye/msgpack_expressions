#include "stdafx.h"
#include <iostream>
#include <msgpack_expressions/pack.h>

int wmain( int argc, wchar_t * argv[] )
{
	using namespace sharpeye::msgpack_expressions;

	msgpack::sbuffer buffer;
	msgpack::packer< msgpack::sbuffer > p{ buffer };
	p << array()
		( map()( "cool", array()( 1 )( 2 ) ) )
		( 3 )
		( 4 );

	msgpack::unpacked u;
	msgpack::unpack( &u, buffer.data(), buffer.size() );

	std::cout << u.get() << std::endl;

	return 0;
}
