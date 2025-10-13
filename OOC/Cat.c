#include <stdio.h>
#include <string.h>

/******************************************************************************/
#include "Cat.h"
/******************************************************************************/

BEGIN_CLASS_IMPLEMENTATION

	BEGIN_CONSTRUCTOR
	{
		strcpy( ((Animal*)this)->m_species, "Cat" );
	}
	END_CONSTRUCTOR

	BEGIN_DESTRUCTOR
	{}
	END_DESTRUCTOR

	
	BEGIN_VIRTUAL_METHOD( void, Talk )( CLASS* this )
	{
		puts( "Meow" );
	}
	END_VIRTUAL_METHOD

	
	BEGIN_OVERRIDES
		OVERRIDE( Animal, Talk )
	END_OVERRIDES

END_CLASS_IMPLEMENTATION
