/* File generated by the BNF Converter (bnfc 2.9.6). */

/*** Pretty Printer and Abstract Syntax Viewer ***/

#include <ctype.h>   /* isspace */
#include <stddef.h>  /* size_t */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Printer.h"

#define INDENT_WIDTH 2

int _n_;
char *buf_;
size_t cur_;
size_t buf_size;

/* You may wish to change the renderC functions */
void renderC(Char c)
{
  if (c == '{')
  {
     onEmptyLine();
     bufAppendC(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppendC('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppendC(c);
  else if (c == ')' || c == ']')
  {
     removeTrailingWhitespace();
     bufAppendC(c);
     bufAppendC(' ');
  }
  else if (c == '}')
  {
     _n_ = _n_ - INDENT_WIDTH;
     onEmptyLine();
     bufAppendC(c);
     bufAppendC('\n');
     indent();
  }
  else if (c == ',')
  {
     removeTrailingWhitespace();
     bufAppendC(c);
     bufAppendC(' ');
  }
  else if (c == ';')
  {
     removeTrailingWhitespace();
     bufAppendC(c);
     bufAppendC('\n');
     indent();
  }
  else if (c == ' ') bufAppendC(c);
  else if (c == 0) return;
  else
  {
     bufAppendC(c);
     bufAppendC(' ');
  }
}

int allIsSpace(String s)
{
  char c;
  while ((c = *s++))
    if (! isspace(c)) return 0;
  return 1;
}

void renderS(String s)
{
  if (*s) /* s[0] != '\0', string s not empty */
  {
    if (allIsSpace(s)) {
      backup();
      bufAppendS(s);
    } else {
      bufAppendS(s);
      bufAppendC(' ');
    }
  }
}

void indent(void)
{
  int n = _n_;
  while (--n >= 0)
    bufAppendC(' ');
}

void backup(void)
{
  if (cur_ && buf_[cur_ - 1] == ' ')
    buf_[--cur_] = 0;
}

void removeTrailingSpaces()
{
  while (cur_ && buf_[cur_ - 1] == ' ') --cur_;
  buf_[cur_] = 0;
}

void removeTrailingWhitespace()
{
  while (cur_ && (buf_[cur_ - 1] == ' ' || buf_[cur_ - 1] == '\n')) --cur_;
  buf_[cur_] = 0;
}

void onEmptyLine()
{
  removeTrailingSpaces();
  if (cur_ && buf_[cur_ - 1 ] != '\n') bufAppendC('\n');
  indent();
}
char *printProgram(Program p)
{
  _n_ = 0;
  bufReset();
  ppProgram(p, 0);
  return buf_;
}
char *showProgram(Program p)
{
  _n_ = 0;
  bufReset();
  shProgram(p);
  return buf_;
}
void ppProgram(Program p, int _i_)
{
  switch(p->kind)
  {
  case is_PExps:
    if (_i_ > 0) renderC(_L_PAREN);
    ppExp(p->u.pExps_.exp_, 0);
    if (_i_ > 0) renderC(_R_PAREN);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Program!\n");
    exit(1);
  }
}

void ppExp(Exp p, int _i_)
{
  switch(p->kind)
  {
  case is_ELet:
    if (_i_ > 1) renderC(_L_PAREN);
    renderS("let");
    ppMatchPattern(p->u.eLet_.matchpattern_, 0);
    renderC('=');
    ppExp(p->u.eLet_.exp_1, 2);
    renderC(';');
    ppExp(p->u.eLet_.exp_2, 0);
    if (_i_ > 1) renderC(_R_PAREN);
    break;

  case is_EList:
    if (_i_ > 2) renderC(_L_PAREN);
    renderC('[');
    ppListListItem(p->u.eList_.listlistitem_, 0);
    renderC(']');
    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_ERecord:
    if (_i_ > 2) renderC(_L_PAREN);
    renderC('{');
    ppListRecordField(p->u.eRecord_.listrecordfield_, 0);
    renderC('}');
    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_ETagged:
    if (_i_ > 2) renderC(_L_PAREN);
    ppIdent(p->u.eTagged_.tag_, 0);
    ppExp(p->u.eTagged_.exp_, 0);
    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_ELambda:
    if (_i_ > 2) renderC(_L_PAREN);
    renderC('|');
    ppListParam(p->u.eLambda_.listparam_, 0);
    renderC('|');
    renderC('{');
    ppExp(p->u.eLambda_.exp_, 0);
    renderC('}');
    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_EPerform:
    if (_i_ > 2) renderC(_L_PAREN);
    renderS("perform");
    ppExp(p->u.ePerform_.exp_, 2);
    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_EHandle:
    if (_i_ > 2) renderC(_L_PAREN);
    renderS("handle");
    ppIdent(p->u.eHandle_.tag_, 0);
    renderC('(');
    ppExp(p->u.eHandle_.exp_1, 2);
    renderC(',');
    ppExp(p->u.eHandle_.exp_2, 2);
    renderC(')');
    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_EMatch:
    if (_i_ > 2) renderC(_L_PAREN);
    renderS("match");
    ppExp(p->u.eMatch_.exp_, 2);
    renderC('{');
    renderS("case");
    ppListMatchItem(p->u.eMatch_.listmatchitem_, 0);
    renderC('}');
    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_EApply:
    if (_i_ > 3) renderC(_L_PAREN);
    ppExp(p->u.eApply_.exp_, 3);
    renderC('(');
    ppListExp(p->u.eApply_.listexp_, 2);
    renderC(')');
    if (_i_ > 3) renderC(_R_PAREN);
    break;

  case is_ESelect:
    if (_i_ > 3) renderC(_L_PAREN);
    ppExp(p->u.eSelect_.exp_, 3);
    renderC('.');
    ppIdent(p->u.eSelect_.id_, 0);
    if (_i_ > 3) renderC(_R_PAREN);
    break;

  case is_EVar:
    if (_i_ > 4) renderC(_L_PAREN);
    ppIdent(p->u.eVar_.id_, 0);
    if (_i_ > 4) renderC(_R_PAREN);
    break;

  case is_EInt:
    if (_i_ > 4) renderC(_L_PAREN);
    ppInteger(p->u.eInt_.integer_, 0);
    if (_i_ > 4) renderC(_R_PAREN);
    break;

  case is_ENegInt:
    if (_i_ > 4) renderC(_L_PAREN);
    renderC('-');
    ppInteger(p->u.eNegInt_.integer_, 0);
    if (_i_ > 4) renderC(_R_PAREN);
    break;

  case is_EString:
    if (_i_ > 4) renderC(_L_PAREN);
    ppString(p->u.eString_.string_, 0);
    if (_i_ > 4) renderC(_R_PAREN);
    break;

  case is_ENamedReference:
    if (_i_ > 4) renderC(_L_PAREN);
    ppIdent(p->u.eNamedReference_.namedreference_, 0);
    if (_i_ > 4) renderC(_R_PAREN);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Exp!\n");
    exit(1);
  }
}

void ppListListItem(ListListItem listlistitem, int i)
{
  if (listlistitem == 0)
  { /* nil */
  }
  else if (listlistitem->listlistitem_ == 0)
  { /* last */
    ppListItem(listlistitem->listitem_, 0);
  }
  else
  { /* cons */
    ppListItem(listlistitem->listitem_, 0);
    renderC(',');
    ppListListItem(listlistitem->listlistitem_, 0);
  }
}

void ppListRecordField(ListRecordField listrecordfield, int i)
{
  if (listrecordfield == 0)
  { /* nil */
  }
  else if (listrecordfield->listrecordfield_ == 0)
  { /* last */
    ppRecordField(listrecordfield->recordfield_, 0);
  }
  else
  { /* cons */
    ppRecordField(listrecordfield->recordfield_, 0);
    renderC(',');
    ppListRecordField(listrecordfield->listrecordfield_, 0);
  }
}

void ppListMatchItem(ListMatchItem listmatchitem, int i)
{
  if (listmatchitem == 0)
  { /* nil */
  }
  else if (listmatchitem->listmatchitem_ == 0)
  { /* last */
    ppMatchItem(listmatchitem->matchitem_, 0);
  }
  else
  { /* cons */
    ppMatchItem(listmatchitem->matchitem_, 0);
    renderS("case");
    ppListMatchItem(listmatchitem->listmatchitem_, 0);
  }
}

void ppListExp(ListExp listexp, int i)
{
  if (listexp == 0)
  { /* nil */
  }
  else if (listexp->listexp_ == 0)
  { /* last */
    ppExp(listexp->exp_, 2);
  }
  else
  { /* cons */
    ppExp(listexp->exp_, 2);
    renderC(',');
    ppListExp(listexp->listexp_, 2);
  }
}

void ppListParam(ListParam listparam, int i)
{
  if (listparam == 0)
  { /* nil */
  }
  else if (listparam->listparam_ == 0)
  { /* last */
    ppParam(listparam->param_, 0);
  }
  else
  { /* cons */
    ppParam(listparam->param_, 0);
    renderC(',');
    ppListParam(listparam->listparam_, 0);
  }
}

void ppMatchItem(MatchItem p, int _i_)
{
  switch(p->kind)
  {
  case is_MatchItem0:
    if (_i_ > 0) renderC(_L_PAREN);
    ppMatchPattern(p->u.matchItem0_.matchpattern_, 0);
    renderS("->");
    ppExp(p->u.matchItem0_.exp_, 0);
    if (_i_ > 0) renderC(_R_PAREN);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing MatchItem!\n");
    exit(1);
  }
}

void ppMatchPattern(MatchPattern p, int _i_)
{
  switch(p->kind)
  {
  case is_MPTagged:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.mPTagged_.tag_, 0);
    ppMatchPattern(p->u.mPTagged_.matchpattern_, 0);
    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_MPRecord:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('{');
    ppListRecordField(p->u.mPRecord_.listrecordfield_, 0);
    renderC('}');
    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_MPId:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.mPId_.id_, 0);
    if (_i_ > 0) renderC(_R_PAREN);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing MatchPattern!\n");
    exit(1);
  }
}

void ppRecordField(RecordField p, int _i_)
{
  switch(p->kind)
  {
  case is_RFKeyVal:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.rFKeyVal_.id_, 0);
    renderC(':');
    ppExp(p->u.rFKeyVal_.exp_, 0);
    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_RFSpread:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("..");
    ppExp(p->u.rFSpread_.exp_, 0);
    if (_i_ > 0) renderC(_R_PAREN);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing RecordField!\n");
    exit(1);
  }
}

void ppParam(Param p, int _i_)
{
  switch(p->kind)
  {
  case is_PId:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.pId_.id_, 0);
    if (_i_ > 0) renderC(_R_PAREN);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Param!\n");
    exit(1);
  }
}

void ppListItem(ListItem p, int _i_)
{
  switch(p->kind)
  {
  case is_LIExpr:
    if (_i_ > 0) renderC(_L_PAREN);
    ppExp(p->u.lIExpr_.exp_, 0);
    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_LISpread:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("..");
    ppExp(p->u.lISpread_.exp_, 0);
    if (_i_ > 0) renderC(_R_PAREN);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing ListItem!\n");
    exit(1);
  }
}

void ppInteger(Integer n, int i)
{
  char tmp[20];
  sprintf(tmp, "%d", n);
  renderS(tmp);
}
void ppDouble(Double d, int i)
{
  char tmp[24];
  sprintf(tmp, "%.15g", d);
  renderS(tmp);
}
void ppChar(Char c, int i)
{
  bufAppendC('\'');
  bufEscapeC(c);
  bufAppendC('\'');
  bufAppendC(' ');
}
void ppString(String s, int i)
{
  bufAppendC('\"');
  bufEscapeS(s);
  bufAppendC('\"');
  bufAppendC(' ');
}
void ppIdent(String s, int i)
{
  renderS(s);
}

void ppNamedReference(String s, int i)
{
  renderS(s);
}


void ppTag(String s, int i)
{
  renderS(s);
}


void ppId(String s, int i)
{
  renderS(s);
}


void shProgram(Program p)
{
  switch(p->kind)
  {
  case is_PExps:
    bufAppendC('(');

    bufAppendS("PExps");

    bufAppendC(' ');

    shExp(p->u.pExps_.exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Program!\n");
    exit(1);
  }
}

void shExp(Exp p)
{
  switch(p->kind)
  {
  case is_ELet:
    bufAppendC('(');

    bufAppendS("ELet");

    bufAppendC(' ');

    shMatchPattern(p->u.eLet_.matchpattern_);
  bufAppendC(' ');
    shExp(p->u.eLet_.exp_1);
  bufAppendC(' ');
    shExp(p->u.eLet_.exp_2);

    bufAppendC(')');

    break;
  case is_EList:
    bufAppendC('(');

    bufAppendS("EList");

    bufAppendC(' ');

    shListListItem(p->u.eList_.listlistitem_);

    bufAppendC(')');

    break;
  case is_ERecord:
    bufAppendC('(');

    bufAppendS("ERecord");

    bufAppendC(' ');

    shListRecordField(p->u.eRecord_.listrecordfield_);

    bufAppendC(')');

    break;
  case is_ETagged:
    bufAppendC('(');

    bufAppendS("ETagged");

    bufAppendC(' ');

    shIdent(p->u.eTagged_.tag_);
  bufAppendC(' ');
    shExp(p->u.eTagged_.exp_);

    bufAppendC(')');

    break;
  case is_ELambda:
    bufAppendC('(');

    bufAppendS("ELambda");

    bufAppendC(' ');

    shListParam(p->u.eLambda_.listparam_);
  bufAppendC(' ');
    shExp(p->u.eLambda_.exp_);

    bufAppendC(')');

    break;
  case is_EPerform:
    bufAppendC('(');

    bufAppendS("EPerform");

    bufAppendC(' ');

    shExp(p->u.ePerform_.exp_);

    bufAppendC(')');

    break;
  case is_EHandle:
    bufAppendC('(');

    bufAppendS("EHandle");

    bufAppendC(' ');

    shIdent(p->u.eHandle_.tag_);
  bufAppendC(' ');
    shExp(p->u.eHandle_.exp_1);
  bufAppendC(' ');
    shExp(p->u.eHandle_.exp_2);

    bufAppendC(')');

    break;
  case is_EMatch:
    bufAppendC('(');

    bufAppendS("EMatch");

    bufAppendC(' ');

    shExp(p->u.eMatch_.exp_);
  bufAppendC(' ');
    shListMatchItem(p->u.eMatch_.listmatchitem_);

    bufAppendC(')');

    break;
  case is_EApply:
    bufAppendC('(');

    bufAppendS("EApply");

    bufAppendC(' ');

    shExp(p->u.eApply_.exp_);
  bufAppendC(' ');
    shListExp(p->u.eApply_.listexp_);

    bufAppendC(')');

    break;
  case is_ESelect:
    bufAppendC('(');

    bufAppendS("ESelect");

    bufAppendC(' ');

    shExp(p->u.eSelect_.exp_);
  bufAppendC(' ');
    shIdent(p->u.eSelect_.id_);

    bufAppendC(')');

    break;
  case is_EVar:
    bufAppendC('(');

    bufAppendS("EVar");

    bufAppendC(' ');

    shIdent(p->u.eVar_.id_);

    bufAppendC(')');

    break;
  case is_EInt:
    bufAppendC('(');

    bufAppendS("EInt");

    bufAppendC(' ');

    shInteger(p->u.eInt_.integer_);

    bufAppendC(')');

    break;
  case is_ENegInt:
    bufAppendC('(');

    bufAppendS("ENegInt");

    bufAppendC(' ');

    shInteger(p->u.eNegInt_.integer_);

    bufAppendC(')');

    break;
  case is_EString:
    bufAppendC('(');

    bufAppendS("EString");

    bufAppendC(' ');

    shString(p->u.eString_.string_);

    bufAppendC(')');

    break;
  case is_ENamedReference:
    bufAppendC('(');

    bufAppendS("ENamedReference");

    bufAppendC(' ');

    shIdent(p->u.eNamedReference_.namedreference_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Exp!\n");
    exit(1);
  }
}

void shListListItem(ListListItem listlistitem)
{
  bufAppendC('[');
  while(listlistitem != 0)
  {
    if (listlistitem->listlistitem_)
    {
      shListItem(listlistitem->listitem_);
      bufAppendS(", ");
      listlistitem = listlistitem->listlistitem_;
    }
    else
    {
      shListItem(listlistitem->listitem_);
      listlistitem = 0;
    }
  }
  bufAppendC(']');
}

void shListRecordField(ListRecordField listrecordfield)
{
  bufAppendC('[');
  while(listrecordfield != 0)
  {
    if (listrecordfield->listrecordfield_)
    {
      shRecordField(listrecordfield->recordfield_);
      bufAppendS(", ");
      listrecordfield = listrecordfield->listrecordfield_;
    }
    else
    {
      shRecordField(listrecordfield->recordfield_);
      listrecordfield = 0;
    }
  }
  bufAppendC(']');
}

void shListMatchItem(ListMatchItem listmatchitem)
{
  bufAppendC('[');
  while(listmatchitem != 0)
  {
    if (listmatchitem->listmatchitem_)
    {
      shMatchItem(listmatchitem->matchitem_);
      bufAppendS(", ");
      listmatchitem = listmatchitem->listmatchitem_;
    }
    else
    {
      shMatchItem(listmatchitem->matchitem_);
      listmatchitem = 0;
    }
  }
  bufAppendC(']');
}

void shListExp(ListExp listexp)
{
  bufAppendC('[');
  while(listexp != 0)
  {
    if (listexp->listexp_)
    {
      shExp(listexp->exp_);
      bufAppendS(", ");
      listexp = listexp->listexp_;
    }
    else
    {
      shExp(listexp->exp_);
      listexp = 0;
    }
  }
  bufAppendC(']');
}

void shListParam(ListParam listparam)
{
  bufAppendC('[');
  while(listparam != 0)
  {
    if (listparam->listparam_)
    {
      shParam(listparam->param_);
      bufAppendS(", ");
      listparam = listparam->listparam_;
    }
    else
    {
      shParam(listparam->param_);
      listparam = 0;
    }
  }
  bufAppendC(']');
}

void shMatchItem(MatchItem p)
{
  switch(p->kind)
  {
  case is_MatchItem0:
    bufAppendC('(');

    bufAppendS("MatchItem0");

    bufAppendC(' ');

    shMatchPattern(p->u.matchItem0_.matchpattern_);
  bufAppendC(' ');
    shExp(p->u.matchItem0_.exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing MatchItem!\n");
    exit(1);
  }
}

void shMatchPattern(MatchPattern p)
{
  switch(p->kind)
  {
  case is_MPTagged:
    bufAppendC('(');

    bufAppendS("MPTagged");

    bufAppendC(' ');

    shIdent(p->u.mPTagged_.tag_);
  bufAppendC(' ');
    shMatchPattern(p->u.mPTagged_.matchpattern_);

    bufAppendC(')');

    break;
  case is_MPRecord:
    bufAppendC('(');

    bufAppendS("MPRecord");

    bufAppendC(' ');

    shListRecordField(p->u.mPRecord_.listrecordfield_);

    bufAppendC(')');

    break;
  case is_MPId:
    bufAppendC('(');

    bufAppendS("MPId");

    bufAppendC(' ');

    shIdent(p->u.mPId_.id_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing MatchPattern!\n");
    exit(1);
  }
}

void shRecordField(RecordField p)
{
  switch(p->kind)
  {
  case is_RFKeyVal:
    bufAppendC('(');

    bufAppendS("RFKeyVal");

    bufAppendC(' ');

    shIdent(p->u.rFKeyVal_.id_);
  bufAppendC(' ');
    shExp(p->u.rFKeyVal_.exp_);

    bufAppendC(')');

    break;
  case is_RFSpread:
    bufAppendC('(');

    bufAppendS("RFSpread");

    bufAppendC(' ');

    shExp(p->u.rFSpread_.exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing RecordField!\n");
    exit(1);
  }
}

void shParam(Param p)
{
  switch(p->kind)
  {
  case is_PId:
    bufAppendC('(');

    bufAppendS("PId");

    bufAppendC(' ');

    shIdent(p->u.pId_.id_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Param!\n");
    exit(1);
  }
}

void shListItem(ListItem p)
{
  switch(p->kind)
  {
  case is_LIExpr:
    bufAppendC('(');

    bufAppendS("LIExpr");

    bufAppendC(' ');

    shExp(p->u.lIExpr_.exp_);

    bufAppendC(')');

    break;
  case is_LISpread:
    bufAppendC('(');

    bufAppendS("LISpread");

    bufAppendC(' ');

    shExp(p->u.lISpread_.exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing ListItem!\n");
    exit(1);
  }
}

void shInteger(Integer i)
{
  char tmp[20];
  sprintf(tmp, "%d", i);
  bufAppendS(tmp);
}
void shDouble(Double d)
{
  char tmp[24];
  sprintf(tmp, "%.15g", d);
  bufAppendS(tmp);
}
void shChar(Char c)
{
  bufAppendC('\'');
  bufEscapeC(c);
  bufAppendC('\'');
}
void shString(String s)
{
  bufAppendC('\"');
  bufEscapeS(s);
  bufAppendC('\"');
}
void shIdent(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}

void shNamedReference(String s)
{
  bufAppendC('\"');
  bufEscapeS(s);
  bufAppendC('\"');
}


void shTag(String s)
{
  bufAppendC('\"');
  bufEscapeS(s);
  bufAppendC('\"');
}


void shId(String s)
{
  bufAppendC('\"');
  bufEscapeS(s);
  bufAppendC('\"');
}


void bufEscapeS(const char *s)
{
  if (s) while (*s) bufEscapeC(*s++);
}
void bufEscapeC(const char c)
{
  switch(c)
  {
    case '\f': bufAppendS("\\f" ); break;
    case '\n': bufAppendS("\\n" ); break;
    case '\r': bufAppendS("\\r" ); break;
    case '\t': bufAppendS("\\t" ); break;
    case '\v': bufAppendS("\\v" ); break;
    case '\\': bufAppendS("\\\\"); break;
    case '\'': bufAppendS("\\'" ); break;
    case '\"': bufAppendS("\\\""); break;
    default: bufAppendC(c);
  }
}

void bufAppendS(const char *s)
{
  size_t len = strlen(s);
  size_t n;
  while (cur_ + len >= buf_size)
  {
    buf_size *= 2; /* Double the buffer size */
    resizeBuffer();
  }
  for(n = 0; n < len; n++)
  {
    buf_[cur_ + n] = s[n];
  }
  cur_ += len;
  buf_[cur_] = 0;
}
void bufAppendC(const char c)
{
  if (cur_ + 1 >= buf_size)
  {
    buf_size *= 2; /* Double the buffer size */
    resizeBuffer();
  }
  buf_[cur_] = c;
  cur_++;
  buf_[cur_] = 0;
}
void bufReset(void)
{
  cur_ = 0;
  buf_size = BUFFER_INITIAL;
  resizeBuffer();
  memset(buf_, 0, buf_size);
}
void resizeBuffer(void)
{
  char *temp = (char *) malloc(buf_size);
  if (!temp)
  {
    fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
    exit(1);
  }
  if (buf_)
  {
    strncpy(temp, buf_, buf_size); /* peteg: strlcpy is safer, but not POSIX/ISO C. */
    free(buf_);
  }
  buf_ = temp;
}
char *buf_;
size_t cur_, buf_size;

