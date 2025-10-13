#include <string.h>

/******************************************************************************/
#include "Beagle.h"
/******************************************************************************/

BEGIN_CLASS_IMPLEMENTATION

	BEGIN_CONSTRUCTOR
	{}
	END_CONSTRUCTOR

	BEGIN_DESTRUCTOR
	{}
	END_DESTRUCTOR
	

	BEGIN_VIRTUAL_METHOD( void, GetBreed )( CLASS* this, char* breed )
	{
		strcpy( breed, "Beagle" );
	}
	END_VIRTUAL_METHOD

	
	BEGIN_OVERRIDES
		OVERRIDE( Dog, GetBreed )
	END_OVERRIDES

END_CLASS_IMPLEMENTATION
