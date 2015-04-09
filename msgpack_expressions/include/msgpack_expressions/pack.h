#pragma once
#include <msgpack.hpp>
#include <msgpack_expressions/expressions.h>

namespace sharpeye
{
	namespace msgpack_expressions
	{
		template< typename S, typename T >
		inline void pack( msgpack::packer< S > & p, T const & value )
		{
			p << value;
		}

		template< typename S >
		inline bool pack( msgpack::packer< S > & p, Array const & map, unsigned n )
		{
			p.pack_array( map.size + n );

			return true;
		}

		template< typename S >
		inline bool pack( msgpack::packer< S > & p, Map const & map, unsigned n )
		{
			p.pack_map( map.size + n );

			return true;
		}

		template< typename S, typename P >
		bool pack( msgpack::packer< S >& out, const optional_node_base< P >& opt, unsigned n )
		{
			if( !opt.cond )
			{
				pack( out, opt.parent, 0 );

				return false;
			}

			return pack( out, opt.parent, n );
		}

		template< typename S, typename K, typename V, typename P >
		inline bool pack( msgpack::packer< S > & p, map_node< K, V, P > const & node, unsigned n )
		{
			if( pack( p, node.parent, n + 1 ) )
			{
				(pack)( p, node.key );
				(pack)( p, node.value );

				return true;
			}

			return false;
		}

		template< typename S, typename T, typename P >
		inline bool pack( msgpack::packer< S > & p, array_node< T, P > const & node, unsigned n )
		{
			if( pack( p, node.parent, n + 1 ) )
			{
				(pack)( p, node.value );

				return true;
			}

			return false;
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
