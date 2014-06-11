#ifndef DEPENDENT_TYPE_LIST_HPP
#define DEPENDENT_TYPE_LIST_HPP
#include<dependent_type/int.hpp>
namespace dependent_type
{
	template < typename , unsigned long long int >
	class list ;
	template < typename T , unsigned long long N >
	class list
	{
		T head_ ;
		list < T , N - 1 > tail_ ;
	public :
		constexpr list ( ) = default ;
		constexpr list ( const list & ) = default ;
		constexpr list ( list && ) = default ;
		auto operator = ( const list & ) -> list & = default ;
		auto operator = ( list && ) -> list & = default ;
		~ list ( ) = default ;
		constexpr list ( const T & head , const list < T , N - 1 > & tail )
			: head_ { head }
			, tail_ { tail }
		{
		}
		template < typename Head , typename ... Tail >
		constexpr list ( const Head & head , const Tail & ... tail )
			: head_ { head }
			, tail_ { tail ... }
		{
		}
		constexpr auto head ( ) const -> const T &
		{
			return head_ ;
		}
		constexpr auto tail ( ) const -> const list < T , N - 1 > &
		{
			return tail_ ;
		}
		// TODO : fix bug then N == 1
		constexpr auto at ( int_ < N - 1 > index ) const -> const T &
		{
			return index.get ( ) ? tail_.at ( index - create_int < 1 > ( ) ) : head_ ;
		}
		constexpr auto at ( int_ < 0 > index ) const -> const T &
		{
			return head_ ;
		}
	} ;
	template < typename T >
	class list < T , 0 >
	{
	} ;
	template < typename ... T >
	constexpr auto make_list ( const T & ... values ) -> list < typename std::common_type < T ... >::type , sizeof ... ( T ) >
	{
		return list < typename std::common_type < T ... >::type , sizeof ... ( T ) > { values ... } ;
	}
}
#endif
