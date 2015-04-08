#pragma once

namespace sharpeye
{
	namespace msgpack_expressions
	{
		template< typename T, typename P >
		struct array_node;

		template< typename K, typename V, typename P >
		struct map_node;

		template< typename B >
		struct array_node_base
		{
			template< typename T >
			decltype(auto) operator ()( T const & value ) const
			{
				return array_node< T, B >{ value, static_cast< B const & >( *this ) };
			}

		}; // array_node_base<>

		template< typename B >
		struct map_node_base
		{
			template< typename K, typename V >
			decltype(auto) operator ()( K const & key, V const & value ) const
			{
				return map_node< K, V, B >{ key, value, static_cast< B const & >( *this ) };
			}

		}; // map_node_base<>

		template< typename T, typename P >
		struct array_node : array_node_base< array_node< T, P > >
		{
			T const & value;
			P const & parent;

			array_node( T const & value, P const & parent )
				: value{ value }
				, parent{ parent }
			{}

		}; // array_node<>

		template< typename K, typename V, typename P >
		struct map_node : map_node_base< map_node< K, V, P > >
		{
			K const & key;
			V const & value;
			P const & parent;

			map_node( K const & key, V const & value, P const & parent )
				: key{ key }
				, value{ value }
				, parent{ parent }
			{}

		}; // map_node<>

		struct Array : array_node_base< Array >
		{
			explicit Array( unsigned n = 0 )
				: size{ n }
			{}

			unsigned size;

		}; // Array

		struct Map : map_node_base< Map >
		{
			explicit Map( unsigned n = 0 )
				: size{ n }
			{}

			unsigned size;

		}; // Map

		inline Array array( unsigned n = 0 )
		{
			return Array{ n };
		}

		inline Map map( unsigned n = 0 )
		{
			return Map{ n };
		}

	} // ns msgpack_expressions

} // ns sharpeye
