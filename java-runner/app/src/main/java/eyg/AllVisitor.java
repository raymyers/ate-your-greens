// File generated by the BNF Converter (bnfc 2.9.6).

package eyg;

/** All Visitor */

public interface AllVisitor<R,A> extends
  eyg.Absyn.Program.Visitor<R,A>,
  eyg.Absyn.Exp.Visitor<R,A>,
  eyg.Absyn.MatchItem.Visitor<R,A>,
  eyg.Absyn.MatchPattern.Visitor<R,A>,
  eyg.Absyn.RecordField.Visitor<R,A>,
  eyg.Absyn.Param.Visitor<R,A>,
  eyg.Absyn.ListItem.Visitor<R,A>
{}
