/* -------------------------------------------------------------------------
 *
 * dllist.h
 *		simple doubly linked list primitives
 *		the elements of the list are void* so the lists can contain anything
 *		Dlelem can only be in one list at a time
 *
 *
 *	 Here's a small example of how to use Dllists:
 *
 *	 Dllist *lst;
 *	 Dlelem *elt;
 *	 void	*in_stuff;	  -- stuff to stick in the list
 *	 void	*out_stuff
 *
 *	 lst = DLNewList();				   -- make a new dllist
 *	 DLAddHead(lst, DLNewElem(in_stuff)); -- add a new element to the list
 *											 with in_stuff as the value
 *	  ...
 *	 elt = DLGetHead(lst);			   -- retrieve the head element
 *	 out_stuff = (void*)DLE_VAL(elt);  -- get the stuff out
 *	 DLRemove(elt);					   -- removes the element from its list
 *	 DLFreeElem(elt);				   -- free the element since we don't
 *										  use it anymore
 *
 *
 * It is also possible to use Dllist objects that are embedded in larger
 * structures instead of being separately malloc'd.  To do this, use
 * DLInitElem() to initialize a Dllist field within a larger object.
 * Don't forget to DLRemove() each field from its list (if any) before
 * freeing the larger object!
 *
 *
 * Portions Copyright (c) 1996-2012, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/lib/dllist.h
 *
 * -------------------------------------------------------------------------
 */

#ifndef DLLIST_H
#define DLLIST_H

struct Dllist;
struct Dlelem;

// Dlelem is a node in a doubly linked list.
typedef struct Dlelem {
    struct Dlelem* dle_next; /* next element */
    struct Dlelem* dle_prev; /* previous element */
    void* dle_val;           /* value of the element */
    struct Dllist* dle_list; /* what list this element is in */
} Dlelem;

typedef struct Dllist {
    Dlelem* dll_head;       /* head of list */
    Dlelem* dll_tail;       /* tail of list */
    uint64      dll_len;    /* number of elements in list */
} Dllist;

class DllistWithLock : public BaseObject {
    public:
    DllistWithLock();       // constructor
    ~DllistWithLock();      // destructor
    void Remove(Dlelem* e) {
        (void)RemoveConfirm(e);
    }
    bool RemoveConfirm(Dlelem* e);  // remove element from list, return true if removed
    void AddHead(Dlelem* e);    // add element to head of list
    void AddTail(Dlelem* e);    // add element to tail of list
    Dlelem* RemoveHead();       // remove element from head of list
    Dlelem* RemoveHeadNoLock(); // remove element from head of list without lock
    Dlelem* RemoveTail();       // remove element from tail of list
    bool IsEmpty();                     // is the list empty?
    Dlelem* GetHead();                  // get the head of the list
    void GetLock();                     // get the lock
    void ReleaseLock();                 // release the lock

    inline uint64 GetLength() {     // get the length of the list
        return m_list.dll_len;
    }

    private:
    slock_t m_lock;                 // lock for the list
    Dllist m_list;                  // the list
};

extern Dllist* DLNewList(void);       /* allocate and initialize a list header */
extern void DLInitList(Dllist* list); /* init a header alloced by caller */
extern void DLFreeList(Dllist* list); /* free up a list and all the nodes in
                                       * it */
extern Dlelem* DLNewElem(void* val);    /* allocate a new list element */
extern void DLInitElem(Dlelem* e, void* val);   /* initialize caller-allocated node */
extern void DLFreeElem(Dlelem* e);          /* free a list element */
extern void DLRemove(Dlelem* e); /* removes node from list */
extern void DLAddHead(Dllist* list, Dlelem* node);  /* add node to head of list */
extern void DLAddTail(Dllist* list, Dlelem* node);  /* add node to tail of list */
extern Dlelem* DLRemHead(Dllist* list); /* remove and return the head */
extern Dlelem* DLRemTail(Dllist* list); /* remove and return the tail */
extern void DLMoveToFront(Dlelem* e); /* move node to front of its list */
extern uint64 DLListLength(Dllist* list);

/* These are macros for speed */
#define DLGetHead(list) ((list)->dll_head)  /* get the head of the list */
#define DLGetTail(list) ((list)->dll_tail)  /* get the tail of the list */
#define DLIsNIL(list) ((list)->dll_head == NULL)    /* is the list empty? */
#define DLGetSucc(elem) ((elem)->dle_next)          /* get the successor */
#define DLGetPred(elem) ((elem)->dle_prev)          /* get the predecessor */
#define DLGetListHdr(elem) ((elem)->dle_list)       /* get the list header */

#define DLE_VAL(elem) ((elem)->dle_val)        /* get the value of the * element */

#endif /* DLLIST_H */

