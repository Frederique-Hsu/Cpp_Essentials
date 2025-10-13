#include <stdio.h>
#include <string.h>

/******************************************************************************/
#include "Dog.h"
/******************************************************************************/

BEGIN_CLASS_IMPLEMENTATION

	BEGIN_CONSTRUCTOR
	{
		this->m_breeder = NEW( Human );
		CONSTRUCT( Human, this->m_breeder );
		CALL( Who, SetName )( (Who*)this->m_breeder, "Unknown breeder" );
		
		strcpy( ((Animal*)this)->m_species, "Dog" );
	}
	END_CONSTRUCTOR

	BEGIN_DESTRUCTOR
	{}
	END_DESTRUCTOR

	
	BEGIN_NONVIRTUAL_METHOD( void, SetBreeder )( CLASS* this, const char* name )
	{
		CALL( Who, SetName )( (Who*)this->m_breeder, name );
	}
	END_NONVIRTUAL_METHOD
	
	BEGIN_NONVIRTUAL_METHOD( void, GetBreeder )( CLASS* this, char* name )
	{
		CALL( Who, GetName )( (Who*)this->m_breeder, name );
	}
	END_NONVIRTUAL_METHOD
	
	BEGIN_VIRTUAL_METHOD( void, Talk )( CLASS* this )
	{
		puts( "Ruff! Ruff!" );
	}
	END_VIRTUAL_METHOD
	
	BEGIN_VIRTUAL_METHOD( int, IsDomesticated )( CLASS* this )
	{
		return 1;
	}
	END_VIRTUAL_METHOD
	
	BEGIN_VIRTUAL_METHOD( void, GetBreed )( CLASS* this, char* breed )
	{
		strcpy( breed, "unknown" );
	}
	END_VIRTUAL_METHOD
	
	
	BEGIN_OVERRIDES
		OVERRIDE( Animal, Talk )
		OVERRIDE( Animal, IsDomesticated )
		OVERRIDE( Dog, GetBreed )
	END_OVERRIDES

END_CLASS_IMPLEMENTATION
