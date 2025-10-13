/* Simply Object-oriented C */

#ifndef H_SOOC_H
#define H_SOOC_H

#include <memory.h>
#include <stdlib.h>

#define P( x, y )				P_PRIMITIVE( x, y )
#define P_PRIMITIVE( x, y )		x##y
  
/* typedefs for various return types */
typedef void (*RVOID)();
typedef int (*RINT)();
typedef short (*RSHORT)();
typedef long (*RLONG)();
typedef float (*RFLOAT)();
typedef double (*RDOUBLE)();
typedef long double (*RLDOUBLE)();
typedef unsigned int (*RUINT)();
typedef unsigned short (*RUSHORT)();
typedef unsigned long (*RULONG)();

/* CLASS Object */
typedef struct
{
	RVOID* vtbl;
} Object;

void	SetupObjectInheritence( RVOID* vtbl );
void	Object_ctor( Object* this );
void	Object_dtor( Object* this );

enum
{
	vstart_Object = -1,
	vi_Object_dtor,
	vend_Object
};


/* Set up the Vtbls */
#define INITIALIZE_SOOC										\
	do														\
	{														\
		RVOID* v = vtblList;								\
		int i = sizeof vtblList / sizeof( *vtblList );		\
		while ( i-- )										\
			((void (*)())(*v++))();							\
	}														\
	while ( 0 )

/* Macros for calling non-virtual (regular) methods */
#define CALL( class, method )								\
	class##_##method
	
#define CALLME( method )									\
	P( CLASS, P( _, method ) )


/* Macros for calling virtual methods */					
#define VCALL( rettype, class, method, this )				\
	((rettype)												\
		(((Object*)this)->vtbl)[vi_##class##_##method])

#define VCALLME( rettype, method, this )					\
	((rettype)												\
		(((Object*)this)->vtbl)								\
		[P( vi_, P( CLASS, P( _, method ) ) )])

/* For declaring the application classes */
#define BEGIN_DECLARE_APPLICATION_CLASSES					\
	static RVOID* GetObjectVtbl()							\
	{														\
		static RVOID classVtbl[vend_Object];				\
		return classVtbl;									\
	}														\
	static void SetupObjectVtbl()							\
	{														\
		RVOID* classVtbl = GetObjectVtbl();					\
		classVtbl[vi_Object_dtor] = (RVOID) Object_dtor;	\
	}														\
	RVOID vtblList[] =										\
	{														\
		(RVOID) SetupObjectVtbl,
		
#define DECLARE_APPLICATION_CLASS( class )					\
	(RVOID) Setup##class##Vtbl,
	
#define END_DECLARE_APPLICATION_CLASSES						\
	};														\
	void Object_ctor( Object* this )						\
	{}														\
	void Object_dtor( Object* this )						\
	{}														\
	void SetupObjectInheritence( RVOID* vtbl )				\
	{														\
		RVOID* classVtbl = GetObjectVtbl();					\
		memcpy( vtbl, classVtbl,							\
				vend_Object * sizeof( RVOID ) );			\
	}														\

#define NEW( class )										\
	malloc( sizeof( class ) );

#define DELETE( p )											\
	free( p );

#define CONSTRUCT( class, this )							\
	class##_##ctor( this )

#define DESTRUCT( this )									\
	VCALL( RVOID, Object, dtor, this )( this );

/* Class declaration */
#define BEGIN_CLASS											\
	typedef struct P( CLASS, _t ) CLASS;					\
	struct P( CLASS, _t )									\
	{														\
		BASECLASS base;

#define END_CLASS											\
	void	P( CLASS, _ctor )( CLASS * this );				\
	void	P( CLASS, _dtor )( CLASS * this );				\
	void	P( P( Setup, CLASS ), Vtbl )();					\
	void	P( P( Setup, CLASS ), 							\
					Inheritence )( RVOID* vtbl );


/* Define class virtuals */
#define BEGIN_VIRTUAL_METHODS								\
	};														\
	enum													\
	{														\
		P( vstart_, CLASS ) =								\
				P( vend_, BASECLASS ) - 1,
		
#define VIRTUAL_METHOD( method )							\
		P( vi_, P( CLASS,									\
				P( _, method ) ) ),

#define END_VIRTUAL_METHODS									\
		P( vend_, CLASS )									\
	};

/* Define non-virtual class methods */
#define NONVIRTUAL_METHOD( rettype, method )				\
	rettype P( CLASS, P( _, method ) )
	

#define BEGIN_NONVIRTUAL_METHODS
#define END_NONVIRTUAL_METHODS

/* Class implementation */
#define BEGIN_CLASS_IMPLEMENTATION							\
	static RVOID classVtbl[P( vend_, CLASS )];				\

#define END_CLASS_IMPLEMENTATION							\
	void P( Setup, P( CLASS, Inheritence ) )				\
			( RVOID* vtbl )									\
	{														\
		memcpy( vtbl, classVtbl,							\
				P( vend_, CLASS ) * sizeof( RVOID ) );		\
	}

#define BEGIN_OVERRIDES										\
	void P( Setup, P( CLASS, Vtbl ) )()						\
	{														\
		P( Setup, P( BASECLASS, Inheritence ) )				\
				( classVtbl );								\
		classVtbl[vi_Object_dtor] =							\
				(RVOID) P( CLASS, _dtor );
	
#define OVERRIDE( overrideclass, method )					\
		classVtbl[P( vi_, P( overrideclass,					\
			P( _, method ) ) )] =							\
			(RVOID) P( CLASS, P( _, method ) );
			
#define	END_OVERRIDES										\
	}

#define BEGIN_CONSTRUCTOR									\
	void P( CLASS,_ctor )( CLASS* this )					\
	{														\
		P( BASECLASS, _ctor )( (BASECLASS*)this );			\
		((Object*)this)->vtbl = classVtbl;
		
#define END_CONSTRUCTOR										\
	}

#define BEGIN_DESTRUCTOR									\
	void P( CLASS, _dtor )( CLASS* this )					\
	{														\
		P( BASECLASS, _dtor )( (BASECLASS*)this );
				
#define END_DESTRUCTOR										\
	}
	
#define	BEGIN_VIRTUAL_METHOD( rettype, method )				\
	static rettype P( CLASS, P( _, method ) )
	
#define	END_VIRTUAL_METHOD

#define BEGIN_NONVIRTUAL_METHOD( rettype, method )			\
	rettype P( CLASS, P( _, method ) )

#define END_NONVIRTUAL_METHOD

#endif
