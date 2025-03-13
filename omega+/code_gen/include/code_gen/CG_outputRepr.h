/*****************************************************************************
 Copyright (C) 1994-2000 University of Maryland
 Copyright (C) 2008 University of Southern California
 Copyright (C) 2009 University of Utah
 All Rights Reserved.

 Purpose:
   abstract base class of omega code generation representation

 Notes:

 History:
   04/17/96 - Lei Zhou - created
*****************************************************************************/

#ifndef CG_outputRepr_h
#define CG_outputRepr_h

#include <stdio.h>
#include <basic/Tuple.h>
#include <string>

namespace omega {

class CG_outputRepr {
public:
  virtual ~CG_outputRepr() {};
  virtual CG_outputRepr *clone() = 0;
  virtual void clear() {};

  //---------------------------------------------------------------------------
  // Dump operations
  //---------------------------------------------------------------------------
  virtual void Dump() const = 0; 
  virtual void DumpToFile(FILE *fp = stderr) const = 0;
};

class stmt_info {
public:
  stmt_info() {};
  virtual ~stmt_info() {};
  virtual std::string debug_name() const = 0;
  virtual CG_outputRepr* place_holder() const = 0;
};

} // namespace

#endif
