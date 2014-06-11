#ifndef DEPENDENT_TYPE_INT_HPP
#define DEPENDENT_TYPE_INT_HPP
#include<limits>
#include<type_traits>
namespace dependent_type
{
	template < unsigned long long int >
	class int_ ;
	struct value_holder
	{
		unsigned long long int value ;
	} ;
	template < unsigned long long int N >
	class int_
	{
		template < unsigned long long int M >
		friend class int_ ;
		template < unsigned long long M >
		friend constexpr auto create_int ( ) -> int_ < M > ;
		unsigned long long int value_ ;
		constexpr int_ ( const value_holder & v )
			: value_ { v.value }
		{
		}
	public :
		constexpr int_ ( ) = default ;
		constexpr int_ ( const int_ & ) = default ;
		constexpr int_ ( int_ && ) = default ;
		auto operator = ( const int_ & ) -> int_ & = delete ;
		auto operator = ( int_ && ) -> int_ & = delete ;
		template < unsigned long long int M , typename = typename std::enable_if < ( N > M ) >::type >
		constexpr int_ ( int_ < M > value )
			: value_ { value.value_ }
		{
		}
		template < typename T >
		constexpr int_ ( T value )
			: value_ { value }
		{
			static_assert ( N >= std::numeric_limits < T >::max ( ) , "" ) ;
		}
		template < unsigned long long int M >
		constexpr auto operator + ( int_ < M > m ) const -> int_ < N + M >
		{
			return int_ < N + M > { value_holder { value_ + m.value_ } } ;
		}
		template < unsigned long long int M >
		constexpr auto operator - ( int_ < M > m ) const -> int_ < N >
		{
			return int_ < N > { value_holder { value_ - m.value_ } } ;
		}
		template < unsigned long long int M >
		constexpr auto operator * ( int_ < M > m ) const -> int_ < N * M >
		{
			return int_ < N * M > { value_holder { value_ * m.value_ } } ;
		}
		template < unsigned long long int M >
		constexpr auto operator / ( int_ < M > m ) const -> int_ < N >
		{
			return int_ < N > { value_holder { value_ / m.value_ } } ;
		}
		template < unsigned long long int M , typename = typename std::enable_if < ( N >= M ) >::type >
		constexpr auto operator % ( int_ < M > m ) const-> int_ < ( ( N >= M ) ? M - 1 : N ) >
		{
			return int_ < ( ( N >= M ) ? M - 1 : N ) > { value_holder { value_ % m.value_ } } ;
		}
		constexpr auto get ( ) const -> unsigned long long int
		{
			return value_ ;
		}
		template < unsigned long long int M >
		constexpr auto inc ( ) const -> int_ < N + M >
		{
			return int_ < N + M > { value_holder { value_ + M } } ;
		}
		template < unsigned long long int M >
		constexpr auto dec ( ) const -> int_ < N - M >
		{
			return int_ < N - M > { value_holder { value_ - M } } ;
		}
	} ;
	template < typename T >
	constexpr auto make_int ( T value ) -> int_ < std::numeric_limits < T >::max ( ) >
	{
		return int_ < std::numeric_limits < T >::max ( ) > { value } ;
	}
	template < unsigned long long N >
	constexpr auto create_int ( ) -> int_ < N >
	{
		return int_ < N > { value_holder { N } } ;
	}
}
#endif
