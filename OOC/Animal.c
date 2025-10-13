#include <stdio.h>
#include <string.h>

/******************************************************************************/
#include "Animal.h"
/******************************************************************************/

BEGIN_CLASS_IMPLEMENTATION

	BEGIN_CONSTRUCTOR
	{
		strcpy( this->m_species, "Animal" );
	}
	END_CONSTRUCTOR

	BEGIN_DESTRUCTOR
	{}
	END_DESTRUCTOR

	
	BEGIN_NONVIRTUAL_METHOD( void, SaySpecies )( CLASS* this )
	{
		printf( "A(n) %s says: ", this->m_species );
	}
	END_NONVIRTUAL_METHOD
	
	BEGIN_NONVIRTUAL_METHOD( void, Report )( CLASS* this )
	{
		CALLME( SaySpecies )( this );
		VCALLME( RVOID, Talk, this )( this );	
	}
	END_NONVIRTUAL_METHOD

	BEGIN_VIRTUAL_METHOD( void, Talk )( CLASS* this )
	{
		puts( "Can't talk" );
	}
	END_VIRTUAL_METHOD

	BEGIN_VIRTUAL_METHOD( int, IsDomesticated )( CLASS* this )
	{
		return -1;
	}
	END_VIRTUAL_METHOD

	
	BEGIN_OVERRIDES
		OVERRIDE( Animal, Talk )
		OVERRIDE( Animal, IsDomesticated )
	END_OVERRIDES

END_CLASS_IMPLEMENTATION
