#ifndef H_DOG_H
#define H_DOG_H

#include "SOOC.h"
#include "Who.h"
#include "Human.h"

/******************************************************************************/
#undef	CLASS
#define CLASS		Dog
#undef	BASECLASS
#define BASECLASS 	Who
/******************************************************************************/

BEGIN_CLASS
	/* Data members */
	Human*	m_breeder;

	/* Virtual methods */
	BEGIN_VIRTUAL_METHODS
		VIRTUAL_METHOD( GetBreed )
	END_VIRTUAL_METHODS

	/* Non-virtual methods */
	BEGIN_NONVIRTUAL_METHODS
		NONVIRTUAL_METHOD( void, SetBreeder )( CLASS* this, const char* );
		NONVIRTUAL_METHOD( void, GetBreeder )( CLASS* this, char* );
	END_NONVIRTUAL_METHODS
	
END_CLASS

#endif
