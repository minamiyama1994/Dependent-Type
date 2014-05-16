#include<iostream>
#include"dependent_type/dependent_type.hpp"
auto main ( ) -> int
{
	auto ulonglong_ = dependent_type::make_int ( std::numeric_limits < unsigned long long int >::max ( ) ) ;
	auto ulong_ = dependent_type::make_int ( std::numeric_limits < unsigned long int >::max ( ) ) ;
	auto uint_ = dependent_type::make_int ( std::numeric_limits < unsigned int >::max ( ) ) ;
	auto ushort_ = dependent_type::make_int ( std::numeric_limits < unsigned short int >::max ( ) ) ;
	std::cout << ulonglong_.get ( ) << std::endl ;
	std::cout << ulong_.get ( ) << std::endl ;
	std::cout << uint_.get ( ) << std::endl ;
	std::cout << ushort_.get ( ) << std::endl ;
	std::cout << ( ulonglong_ / ulonglong_ ).get ( ) << std::endl ;
	std::cout << ( ulonglong_ / ulong_ ).get ( ) << std::endl ;
	std::cout << ( ulonglong_ / uint_ ).get ( ) << std::endl ;
	std::cout << ( ulonglong_ / ushort_ ).get ( ) << std::endl ;
}
