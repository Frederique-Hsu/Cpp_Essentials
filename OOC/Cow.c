#include <stdio.h>
#include <string.h>

/******************************************************************************/
#include "Cow.h"
/******************************************************************************/

BEGIN_CLASS_IMPLEMENTATION

	BEGIN_CONSTRUCTOR
	{
		strcpy( ((Animal*)this)->m_species, "Cow" );
	}
	END_CONSTRUCTOR

	BEGIN_DESTRUCTOR
	{}
	END_DESTRUCTOR

	
	BEGIN_VIRTUAL_METHOD( void, Talk )( CLASS* this )
	{
		puts( "Moo" );
	}
	END_VIRTUAL_METHOD
	
	BEGIN_VIRTUAL_METHOD( int, IsDomesticated )( CLASS* this )
	{
		return 1;
	}
	END_VIRTUAL_METHOD

	
	BEGIN_OVERRIDES
		OVERRIDE( Animal, Talk )
		OVERRIDE( Animal, IsDomesticated )
	END_OVERRIDES

END_CLASS_IMPLEMENTATION
