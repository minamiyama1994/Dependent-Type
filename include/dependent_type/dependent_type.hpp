#ifndef DEPENDENT_TYPE_HPP
#define DEPENDENT_TYPE_HPP
#include<limits>
#include<type_traits>
namespace dependent_type
{
	template < unsigned long long int >
	class int_ ;
	template < unsigned long long int N >
	class int_
	{
		template < unsigned long long int M >
		friend class int_ ;
		template < unsigned long long M >
		friend auto create_int ( ) -> int_ < M > ;
		unsigned long long int value_ ;
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
		auto operator + ( int_ < M > m ) const -> int_ < N + M >
		{
			int_ < N + M > ret ;
			ret.value_ = value_ + m.value_ ;
			return ret ;
		}
		template < unsigned long long int M >
		auto operator - ( int_ < M > m ) const -> int_ < N >
		{
			int_ < N > ret ;
			ret.value_ = value_ - m.value_ ;
			return ret ;
		}
		template < unsigned long long int M >
		auto operator * ( int_ < M > m ) const -> int_ < N * M >
		{
			int_ < N * M > ret ;
			ret.value_ = value_ * m.value_ ;
			return ret ;
		}
		template < unsigned long long int M >
		auto operator / ( int_ < M > m ) const -> int_ < N >
		{
			int_ < N > ret ;
			ret.value_ = value_ / m.value_ ;
			return ret ;
		}
		template < unsigned long long int M , typename = typename std::enable_if < ( N >= M ) >::type >
		auto operator % ( int_ < M > m ) const-> int_ < ( ( N >= M ) ? M - 1 : N ) >
		{
			int_ < ( ( N >= M ) ? M - 1 : N ) > ret ;
			ret.value_ = value_ % m.value_ ;
			return ret ;
		}
		auto get ( ) const -> unsigned long long int
		{
			return value_ ;
		}
	} ;
	template < unsigned long long N >
	auto create_int ( ) -> int_ < N >
	{
		int_ < N > ret ;
		ret.value_ = N ;
		return ret ;
	}
	template < typename T >
	auto make_int ( T value ) -> int_ < std::numeric_limits < T >::max ( ) >
	{
		return int_ < std::numeric_limits < T >::max ( ) > { value } ;
	}
}
#endif
