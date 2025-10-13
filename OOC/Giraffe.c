#include <stdio.h>
#include <string.h>

/******************************************************************************/
#include "Giraffe.h"
/******************************************************************************/

BEGIN_CLASS_IMPLEMENTATION

	BEGIN_CONSTRUCTOR
	{
		strcpy( ((Animal*)this)->m_species, "Giraffe" );
	}
	END_CONSTRUCTOR

	BEGIN_DESTRUCTOR
	{}
	END_DESTRUCTOR

	
	BEGIN_VIRTUAL_METHOD( int, IsDomesticated )( CLASS* this )
	{
		return 0;
	}
	END_VIRTUAL_METHOD

	
	BEGIN_OVERRIDES
		OVERRIDE( Animal, IsDomesticated )
	END_OVERRIDES

END_CLASS_IMPLEMENTATION
