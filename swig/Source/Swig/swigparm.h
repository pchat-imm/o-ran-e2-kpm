/* ----------------------------------------------------------------------------- 
 * This file is part of SWIG, which is licensed as a whole under version 3 
 * (or any later version) of the GNU General Public License. Some additional
 * terms also apply to certain portions of SWIG. The full details of the SWIG
 * license and copyrights can be found in the LICENSE and COPYRIGHT files
 * included with the SWIG source code as distributed by the SWIG developers
 * and at https://www.swig.org/legal.html.
 *
 * swigparm.h
 *
 * Functions related to the handling of function/method parameters and
 * parameter lists.  
 * ----------------------------------------------------------------------------- */

/* Individual parameters */
extern Parm      *NewParm(SwigType *type, const_String_or_char_ptr name, Node *from_node);
extern Parm      *NewParmWithoutFileLineInfo(SwigType *type, const_String_or_char_ptr name);
extern Parm      *NewParmNode(SwigType *type, Node *from_node);
extern Parm      *CopyParm(Parm *p);

/* Parameter lists */
extern ParmList  *CopyParmList(ParmList *p);
extern ParmList  *CopyParmListMax(ParmList *p, int count);
extern ParmList  *ParmList_join(ParmList *p, ParmList *p2);
extern ParmList  *ParmList_replace_last(ParmList *p, ParmList *p2);
extern Parm      *ParmList_nth_parm(ParmList *p, unsigned int n);
extern Parm      *ParmList_variadic_parm(ParmList *p);
extern Parm      *ParmList_add_parm(ParmList *p, Parm *newparm);
extern int        ParmList_numrequired(ParmList *);
extern int        ParmList_len(ParmList *);
extern int        ParmList_has_defaultargs(ParmList *p);
extern int        ParmList_has_varargs(ParmList *p);

/* Output functions */
extern String    *ParmList_str(ParmList *);
extern String    *ParmList_str_defaultargs(ParmList *);
extern String    *ParmList_str_multibrackets(ParmList *);
extern String    *ParmList_protostr(ParmList *);


