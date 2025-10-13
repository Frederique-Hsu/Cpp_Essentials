#ifndef H_WHO_H
#define H_WHO_H

#include "SOOC.h"
#include "Animal.h"

/******************************************************************************/
#undef	CLASS
#define CLASS		Who
#undef	BASECLASS
#define BASECLASS 	Animal
/******************************************************************************/

BEGIN_CLASS
	/* Data members */
	char* m_name;

	/* Virtual methods */
	BEGIN_VIRTUAL_METHODS
	END_VIRTUAL_METHODS
	
	/* Non-virtual methods */
	BEGIN_NONVIRTUAL_METHODS
		NONVIRTUAL_METHOD( void, SetName )( CLASS* this, const char* );
		NONVIRTUAL_METHOD( void, GetName )( CLASS* this, char* );
	END_NONVIRTUAL_METHODS
	
END_CLASS

#endif
