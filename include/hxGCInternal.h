#ifndef HX_GC_INTERNAL_H
#define HX_GC_INTERNAL_H


// INTERNAL_GC is defined on the command-line with "-DINTERNAL_GC"


#ifdef INTERNAL_GC
  #define GC_CLEARS_OBJECTS
  #define GC_CLEARS_ALL
#else
  #define GC_CLEARS_OBJECTS
#endif


class hxObject;

typedef void (*finalizer)(hxObject *v);


void *hxInternalNew(int inSize,bool inIsObject);
void *hxInternalRealloc(void *inData,int inSize);
void hxInternalEnableGC(bool inEnable);
void *hxInternalCreateConstBuffer(const void *inData,int inSize);
void hxRegisterNewThread(void *inTopOfStack);
void hxInternalCollect();

void hxEnterGCFreeZone();
void hxExitGCFreeZone();

// Threading ...
void hxRegisterCurrentThread(void *inTopOfStack);
void hxUnregisterCurrentThread();
void hxEnterSafePoint();


void hxGCMarkNow();

void hxPrologDone();

struct hxInternalFinalizer
{
	hxInternalFinalizer(hxObject *inObj);

	void Mark() { mUsed=true; }
	void Detach();

	bool      mUsed;
	bool      mValid;
	finalizer mFinalizer;
	hxObject  *mObject;
};


void hxMarkAlloc(void *inPtr);
void hxMarkObjectAlloc(hxObject *inPtr);




#define HX_MARK_OBJECT(ioPtr) if (ioPtr) hxMarkObjectAlloc(ioPtr);

#define GC_CONST_STRING  0xffffffff

#define HX_MARK_STRING(ioPtr) \
   if (ioPtr && (((int *)ioPtr)[-1] != GC_CONST_STRING) ) hxMarkAlloc((void *)ioPtr);

#define HX_MARK_ARRAY(ioPtr) { if (ioPtr) hxMarkAlloc((void *)ioPtr); }




#endif
