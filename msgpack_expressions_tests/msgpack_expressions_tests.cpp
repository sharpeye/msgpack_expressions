#include "stdafx.h"
#include <iostream>
#include <msgpack_expressions/pack.h>

int wmain( int argc, wchar_t * argv[] )
{
	using namespace sharpeye::msgpack_expressions;

	msgpack::sbuffer buffer;
	msgpack::packer< msgpack::sbuffer > p{ buffer };
	p << array()
		( 1 )
		( 2 )
		( map()( "k", 3 ) )
		( 4 )
			.optional( false )
			( 5 )
			( map()( "k2", 42 )
				.optional( true )
					( "k3", 100500 ) )
			;

	msgpack::unpacked u;
	msgpack::unpack( &u, buffer.data(), buffer.size() );

	std::cout << u.get() << std::endl;

	return 0;
}
