// File generated by the BNF Converter (bnfc 2.9.6).

package eyg.Absyn;

public class EMatch  extends Exp {
  public final Exp exp_;
  public final ListMatchItem listmatchitem_;
  public EMatch(Exp p1, ListMatchItem p2) { exp_ = p1; listmatchitem_ = p2; }

  public <R,A> R accept(eyg.Absyn.Exp.Visitor<R,A> v, A arg) { return v.visit(this, arg); }

  public boolean equals(java.lang.Object o) {
    if (this == o) return true;
    if (o instanceof eyg.Absyn.EMatch) {
      eyg.Absyn.EMatch x = (eyg.Absyn.EMatch)o;
      return this.exp_.equals(x.exp_) && this.listmatchitem_.equals(x.listmatchitem_);
    }
    return false;
  }

  public int hashCode() {
    return 37*(this.exp_.hashCode())+this.listmatchitem_.hashCode();
  }


}
