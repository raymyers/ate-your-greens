// File generated by the BNF Converter (bnfc 2.9.6).

package eyg.Absyn;

public class EInt  extends Exp {
  public final Integer integer_;
  public EInt(Integer p1) { integer_ = p1; }

  public <R,A> R accept(eyg.Absyn.Exp.Visitor<R,A> v, A arg) { return v.visit(this, arg); }

  public boolean equals(java.lang.Object o) {
    if (this == o) return true;
    if (o instanceof eyg.Absyn.EInt) {
      eyg.Absyn.EInt x = (eyg.Absyn.EInt)o;
      return this.integer_.equals(x.integer_);
    }
    return false;
  }

  public int hashCode() {
    return this.integer_.hashCode();
  }


}
