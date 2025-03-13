#ifndef CG_stringRepr_h
#define CG_stringRepr_h

#include <stdio.h>
#include <code_gen/CG_outputRepr.h>
#include <string>

namespace omega {

class CG_stringRepr : public CG_outputRepr {
public:
  CG_stringRepr();
  CG_stringRepr(const std::string& _s);
  virtual ~CG_stringRepr();
  virtual CG_outputRepr *clone();

  //---------------------------------------------------------------------------
  // basic operation
  //---------------------------------------------------------------------------
  std::string GetString() const;

  //---------------------------------------------------------------------------
  // Dump operations
  //---------------------------------------------------------------------------
  virtual void Dump() const;
  virtual void DumpToFile(FILE *fp = stderr) const;
private:
  std::string s;
};

class default_stmt_info: public stmt_info {
public:
  default_stmt_info(int stmt);
  virtual std::string debug_name() const;
  virtual CG_outputRepr* place_holder() const;
protected:
  int stmt_num;
};

} // namespace

#endif
