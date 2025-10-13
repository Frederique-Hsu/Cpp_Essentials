#include <stdio.h>
#include "SOOC.h"
#include "Animal.h"
#include "Who.h"
#include "Human.h"
#include "Dog.h"
#include "ShihTzu.h"
#include "Beagle.h"
#include "Cat.h"
#include "Giraffe.h"
#include "Cow.h"

/* Must list base classes before derived classes. */
BEGIN_DECLARE_APPLICATION_CLASSES
	DECLARE_APPLICATION_CLASS( Animal )
	DECLARE_APPLICATION_CLASS( Who )
	DECLARE_APPLICATION_CLASS( Human )
	DECLARE_APPLICATION_CLASS( Dog )
	DECLARE_APPLICATION_CLASS( ShihTzu )
	DECLARE_APPLICATION_CLASS( Beagle )
	DECLARE_APPLICATION_CLASS( Cat )
	DECLARE_APPLICATION_CLASS( Giraffe )
	DECLARE_APPLICATION_CLASS( Cow )
END_DECLARE_APPLICATION_CLASSES

int main( int argc, char* argv[] )
{
	INITIALIZE_SOOC;
	
	{
	Animal animal;
	int x = sizeof( Animal );	//  x = x;
	CONSTRUCT( Animal, &animal );
	printf( "Animal species: %s\n", animal.m_species );
	puts( "" );
	
	{
	Dog dog;
	CONSTRUCT( Dog, &dog );
	printf( "Dog species: %s\n", ((Animal*)&dog)->m_species );
	puts( "" );
	
	{
	Cat* pCat = NEW( Cat );
	CONSTRUCT( Cat, pCat );
	CALL( Who, SetName )( (Who*)pCat, "Mimi" );
	printf( "Cat species: %s\n", ((Animal*)pCat)->m_species );
	puts( "" );
	
	{
	ShihTzu shihTzu;
	CONSTRUCT( ShihTzu, &shihTzu );
	CALL( Who, SetName )( (Who*)&shihTzu, "Brandon" );
	printf( "ShihTzu species: %s\n", ((Animal*)&shihTzu)->m_species );
	puts( "" );
	
	{
	Beagle beagle;
	CONSTRUCT( Beagle, &beagle );
	CALL( Dog, SetBreeder )( (Dog*)&beagle, "Joyce" );
	printf( "Beagle species: %s\n", ((Animal*)&beagle)->m_species );
	puts( "" );
	
	{
	Giraffe giraffe;
	CONSTRUCT( Giraffe, &giraffe );
	printf( "Giraffe species: %s\n", ((Animal*)&giraffe)->m_species );
	puts( "" );

	{
	Cow cow;
	CONSTRUCT( Cow, &cow );
	printf( "Cow species: %s\n", ((Animal*)&cow)->m_species );
	puts( "" );

	
	printf( "Animal says: " );
	VCALL( RVOID, Animal, Talk, &animal )( &animal );  
	printf( "Is Animal domesticated: %d\n", VCALL( RINT, Animal, IsDomesticated, &animal )( &animal ) );
	puts( "" );

	{
	char name[32];
	char breeder[32];
	CALL( Who, GetName )( (Who*)&dog, name );
	CALL( Dog, GetBreeder )( &dog, breeder );
	printf( "Dog, named %s, says: ", name );
	VCALL( RVOID, Animal, Talk, &dog )( &dog );
	printf( "Is Dog, bred by %s, domesticated: %d\n", breeder,
			VCALL( RINT, Animal, IsDomesticated, &dog )( &dog ) );
	puts( "" );

	CALL( Who, GetName )( (Who*)pCat, name );
	printf( "Cat, named %s, says: ",  name );
	VCALL( RVOID, Animal, Talk, pCat )( pCat );
	printf( "Is Cat domesticated: %d\n", VCALL( RINT, Animal, IsDomesticated, pCat )( pCat ) );
	puts( "" );

	CALL( Who, GetName )( (Who*)&shihTzu, name );
	CALL( Dog, GetBreeder )( (Dog*)&shihTzu, breeder );
	printf( "Shih Tzu, named %s, says: ", name );
	VCALL( RVOID, Animal, Talk, &shihTzu )( &shihTzu );
	printf( "Is Shih Tzu, bred by %s, domesticated: %d\n", breeder,
			VCALL( RINT, Animal, IsDomesticated, &shihTzu )( &shihTzu ) );
	puts( "" );

	CALL( Dog, GetBreeder )( (Dog*)&beagle, breeder );
	printf( "Beagle says: " );
	VCALL( RVOID, Animal, Talk, &beagle )( &beagle );
	printf( "Is Beagle, bred by %s, domesticated: %d\n", breeder,
			VCALL( RINT, Animal, IsDomesticated, &beagle )( &beagle ) );
	puts( "" );

	printf( "Giraffe says: " );
	VCALL( RVOID, Animal, Talk, &giraffe )( &giraffe );
	printf( "Is Giraffe domesticated: %d\n", VCALL( RINT, Animal, IsDomesticated, &giraffe)( &giraffe ) );
	puts( "" );
	
	printf( "Cow says: " );
	VCALL( RVOID, Animal, Talk, &cow )( &cow );
	printf( "Is Cow domesticated: %d\n", VCALL( RINT, Animal, IsDomesticated, &cow)( &cow ) );
	puts( "" );
	
	CALL( Animal, Report )( (Animal*)&animal );
	CALL( Animal, Report )( (Animal*)&dog );
	CALL( Animal, Report )( (Animal*)pCat );
	CALL( Animal, Report )( (Animal*)&shihTzu );
	CALL( Animal, Report )( (Animal*)&beagle );
	CALL( Animal, Report )( (Animal*)&giraffe );
	CALL( Animal, Report )( (Animal*)&cow );
	puts( "" );

	{
	char breed[64];
	VCALL( RVOID, Dog, GetBreed, &dog )( &dog, breed );
	printf( "Dog breed: %s\n", breed );
	puts( "" );

	VCALL( RVOID, Dog, GetBreed, &shihTzu )( &shihTzu, breed );
	printf( "Shih Tzu breed: %s\n", breed );
	puts( "" );

	VCALL( RVOID, Dog, GetBreed, &beagle )( &beagle, breed );
	printf( "Beagle breed: %s\n", breed );
	puts( "" );
	
	{
	Animal* pCatAnimal = (Animal*)pCat; /* Demonstrate virtual destructor */

	DESTRUCT( &cow );
	DESTRUCT( &giraffe );
	DESTRUCT( &beagle );
	DESTRUCT( &shihTzu );
	DESTRUCT( pCatAnimal );
	DELETE( pCat );
	DESTRUCT( &dog );
	DESTRUCT( &animal );
	
	}}}}}}}}}}

	return 1;
	
} /* main */

