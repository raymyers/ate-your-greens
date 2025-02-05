// File generated by the BNF Converter (bnfc 2.9.6).

package eyg.Absyn;

public class ELambda  extends Exp {
  public final ListParam listparam_;
  public final Exp exp_;
  public ELambda(ListParam p1, Exp p2) { listparam_ = p1; exp_ = p2; }

  public <R,A> R accept(eyg.Absyn.Exp.Visitor<R,A> v, A arg) { return v.visit(this, arg); }

  public boolean equals(java.lang.Object o) {
    if (this == o) return true;
    if (o instanceof eyg.Absyn.ELambda) {
      eyg.Absyn.ELambda x = (eyg.Absyn.ELambda)o;
      return this.listparam_.equals(x.listparam_) && this.exp_.equals(x.exp_);
    }
    return false;
  }

  public int hashCode() {
    return 37*(this.listparam_.hashCode())+this.exp_.hashCode();
  }


}
