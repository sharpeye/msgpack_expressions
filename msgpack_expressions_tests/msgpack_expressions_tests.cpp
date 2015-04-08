#include "stdafx.h"
#include <iostream>
#include <msgpack_expressions/msgpack_expressions.h>

using namespace sharpeye::msgpack_expressions;

template< typename T >
static void pack( std::ostream & out, T const & value )
{
	out << value;
}

static void pack( std::ostream & out, Array const & array, unsigned n )
{
	out << "[";
}

static void pack( std::ostream & out, Map const & map, unsigned n )
{
	out << "{\n";
}

template< typename T, typename P >
static void pack( std::ostream & out, array_node< T, P > const & node, unsigned n )
{
	pack( out, node.parent, n + 1 );
	out << " ";
	pack( out, node.value );
	if( n )
	{
		out << ", ";
	}
}

template< typename T, typename P >
static std::ostream & operator << ( std::ostream & out, array_node< T, P > const & node )
{
	pack( out, node, 0 );

	out << " ]";

	return out;
}

template< typename K, typename V, typename P >
static void pack( std::ostream & out, map_node< K, V, P > const & node, unsigned n )
{
	pack( out, node.parent, n + 1 );
	out << " ";
	pack( out, node.key );
	out << ": ";
	pack( out, node.value );
	if( n )
	{
		out << ",\n";
	}
}

template< typename K, typename V, typename P >
static std::ostream & operator << ( std::ostream & out, map_node< K, V, P > const & node )
{
	pack( out, node, 0 );

	out << "\n}";

	return out;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << array()( 1 )( "cool" )( 3.1 ) << std::endl;

	std::cout << map()
		( "key1", array()( 1 ) )
		( "cool", 3.1 ) 
		<< std::endl;

	return 0;
}
