// File generated by the BNF Converter (bnfc 2.9.6).

package eyg.Absyn;

public class ESelect  extends Exp {
  public final Exp exp_;
  public final String id_;
  public ESelect(Exp p1, String p2) { exp_ = p1; id_ = p2; }

  public <R,A> R accept(eyg.Absyn.Exp.Visitor<R,A> v, A arg) { return v.visit(this, arg); }

  public boolean equals(java.lang.Object o) {
    if (this == o) return true;
    if (o instanceof eyg.Absyn.ESelect) {
      eyg.Absyn.ESelect x = (eyg.Absyn.ESelect)o;
      return this.exp_.equals(x.exp_) && this.id_.equals(x.id_);
    }
    return false;
  }

  public int hashCode() {
    return 37*(this.exp_.hashCode())+this.id_.hashCode();
  }


}
