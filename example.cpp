#include<iostream>
#include"dependent_type/list.hpp"
#include"dependent_type/int.hpp"
template < unsigned long long int N >
struct print_list_impl
{
public :
	template < typename L >
	static auto func ( const L & l ) -> void
	{
		print_list_impl < N - 1 >::func ( l ) ;
		std::cout << l.at ( dependent_type::create_int < N - 1 > ( ) ) << std::endl ;
	}
} ;
template < >
struct print_list_impl < 1 >
{
public :
	template < typename L >
	static auto func ( const L & l ) -> void
	{
		std::cout << l.at ( dependent_type::create_int < 0 > ( ) ) << std::endl ;
	}
} ;
template < unsigned long long int N , typename L >
auto print_list ( const L & l ) -> void
{
	print_list_impl < N >::func ( l ) ;
}
auto main ( ) -> int
{
	constexpr auto ulonglong_ = dependent_type::make_int ( std::numeric_limits < unsigned long long int >::max ( ) ) ;
	constexpr auto ulong_ = dependent_type::make_int ( std::numeric_limits < unsigned long int >::max ( ) ) ;
	constexpr auto uint_ = dependent_type::make_int ( std::numeric_limits < unsigned int >::max ( ) ) ;
	constexpr auto ushort_ = dependent_type::make_int ( std::numeric_limits < unsigned short int >::max ( ) ) ;
	// dependent_type::int < 1 > u1 = ulonglong_ ; // Compile Error!
	std::cout << ulonglong_.get ( ) << std::endl ;
	std::cout << ulong_.get ( ) << std::endl ;
	std::cout << uint_.get ( ) << std::endl ;
	std::cout << ushort_.get ( ) << std::endl ;
	std::cout << ( ulonglong_ / ulonglong_ ).get ( ) << std::endl ;
	std::cout << ( ulonglong_ / ulong_ ).get ( ) << std::endl ;
	std::cout << ( ulonglong_ / uint_ ).get ( ) << std::endl ;
	std::cout << ( ulonglong_ / ushort_ ).get ( ) << std::endl ;
	std::cout << dependent_type::create_int < 1 > ( ).get ( ) << std::endl ;
	constexpr auto list = dependent_type::make_list ( 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 ) ;
	print_list < 10 > ( list ) ;
	// print_list < 11 > ( list ) ; // Compile Error!
}
