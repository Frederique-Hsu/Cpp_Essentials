#ifndef H_ANIMAL_H
#define H_ANIMAL_H

#include "SOOC.h"

/******************************************************************************/
#undef	CLASS
#define CLASS		Animal
#undef	BASECLASS
#define BASECLASS 	Object
/******************************************************************************/

BEGIN_CLASS

	/* Data members */
	char m_species[32];
	
	/* Virtual methods */
	BEGIN_VIRTUAL_METHODS
		VIRTUAL_METHOD( Talk )
		VIRTUAL_METHOD( IsDomesticated )
	END_VIRTUAL_METHODS
	
	/* Non-virtual methods */
	BEGIN_NONVIRTUAL_METHODS
		NONVIRTUAL_METHOD( void, Report )( CLASS* this );
		NONVIRTUAL_METHOD( void, SaySpecies )( CLASS* this );
	END_NONVIRTUAL_METHODS
	
END_CLASS

#endif
