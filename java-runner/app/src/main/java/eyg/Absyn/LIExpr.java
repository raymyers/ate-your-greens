// File generated by the BNF Converter (bnfc 2.9.6).

package eyg.Absyn;

public class LIExpr  extends ListItem {
  public final Exp exp_;
  public LIExpr(Exp p1) { exp_ = p1; }

  public <R,A> R accept(eyg.Absyn.ListItem.Visitor<R,A> v, A arg) { return v.visit(this, arg); }

  public boolean equals(java.lang.Object o) {
    if (this == o) return true;
    if (o instanceof eyg.Absyn.LIExpr) {
      eyg.Absyn.LIExpr x = (eyg.Absyn.LIExpr)o;
      return this.exp_.equals(x.exp_);
    }
    return false;
  }

  public int hashCode() {
    return this.exp_.hashCode();
  }


}
