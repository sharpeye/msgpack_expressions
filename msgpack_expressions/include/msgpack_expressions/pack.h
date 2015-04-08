#pragma once
#include <msgpack_expressions/expressions.h>
#include <msgpack.hpp>

namespace sharpeye
{
	namespace msgpack_expressions
	{
		namespace et = msgpack_expressions;

		template< typename S, typename T >
		inline void pack( msgpack::packer< S > & p, T const & value )
		{
			p << value;
		}

		template< typename S >
		inline void pack( msgpack::packer< S > & p, Array const & map, unsigned n )
		{
			p.pack_array( map.size + n );
		}

		template< typename S >
		inline void pack( msgpack::packer< S > & p, Map const & map, unsigned n )
		{
			p.pack_map( map.size + n );
		}

		template< typename S, typename K, typename V, typename P >
		inline void pack( msgpack::packer< S > & p, map_node< K, V, P > const & node, unsigned n )
		{
			pack( p, node.parent, n + 1 );
			(pack)( p, node.key );
			(pack)( p, node.value );
		}

		template< typename S, typename T, typename P >
		inline void pack( msgpack::packer< S > & p, array_node< T, P > const & node, unsigned n )
		{
			pack( p, node.parent, n + 1 );
			(pack)( p, node.value );
		}

		template< typename S, typename K, typename V, typename P >
		inline msgpack::packer< S > & operator << ( msgpack::packer< S > & p, map_node< K, V, P > const & node )
		{
			pack( p, node, 0 );

			return p;
		}

		template< typename S, typename T, typename P >
		inline msgpack::packer< S > & operator << ( msgpack::packer< S > & p, array_node< T, P > const & node )
		{
			pack( p, node, 0 );

			return p;
		}

	} // ns msgpack_expressions

} // ns sharpeye
