#include <string.h>

/******************************************************************************/
#include "ShihTzu.h"
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
		strcpy( breed, "Shih Tzu" );
	}
	END_VIRTUAL_METHOD

	
	BEGIN_OVERRIDES
		OVERRIDE( Dog, GetBreed )
	END_OVERRIDES

END_CLASS_IMPLEMENTATION
