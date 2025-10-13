#include <stdio.h>
#include <string.h>

/******************************************************************************/
#include "Who.h"
/******************************************************************************/

BEGIN_CLASS_IMPLEMENTATION

	BEGIN_CONSTRUCTOR
	{
		const char s[] = "No name";
		this->m_name = strcpy( (char*) malloc( sizeof( s ) ), s );
	}
	END_CONSTRUCTOR

	BEGIN_DESTRUCTOR
	{
		free( this->m_name );
	}
	END_DESTRUCTOR

	
	BEGIN_NONVIRTUAL_METHOD( void, SetName )( CLASS* this, const char* name )
	{
		free( this->m_name );
		this->m_name = strcpy( (char*) malloc( strlen( name ) + sizeof( '\0' ) ), name );
	}
	END_NONVIRTUAL_METHOD
	
	BEGIN_NONVIRTUAL_METHOD( void, GetName )( CLASS* this, char* name )
	{
		strcpy( name, this->m_name );
	}
	END_NONVIRTUAL_METHOD
	
	BEGIN_VIRTUAL_METHOD( int, IsDomesticated )( CLASS* this )
	{
		return 1;
	}
	END_VIRTUAL_METHOD
	
	
	BEGIN_OVERRIDES
		OVERRIDE( Animal, IsDomesticated )
	END_OVERRIDES

END_CLASS_IMPLEMENTATION
