// File generated by the BNF Converter (bnfc 2.9.6).

package eyg.Absyn;

public class EHandle  extends Exp {
  public final String tag_;
  public final Exp exp_1, exp_2;
  public EHandle(String p1, Exp p2, Exp p3) { tag_ = p1; exp_1 = p2; exp_2 = p3; }

  public <R,A> R accept(eyg.Absyn.Exp.Visitor<R,A> v, A arg) { return v.visit(this, arg); }

  public boolean equals(java.lang.Object o) {
    if (this == o) return true;
    if (o instanceof eyg.Absyn.EHandle) {
      eyg.Absyn.EHandle x = (eyg.Absyn.EHandle)o;
      return this.tag_.equals(x.tag_) && this.exp_1.equals(x.exp_1) && this.exp_2.equals(x.exp_2);
    }
    return false;
  }

  public int hashCode() {
    return 37*(37*(this.tag_.hashCode())+this.exp_1.hashCode())+this.exp_2.hashCode();
  }


}
