// File generated by the BNF Converter (bnfc 2.9.6).

package eyg.Absyn;

public class RFKeyVal  extends RecordField {
  public final String id_;
  public final Exp exp_;
  public RFKeyVal(String p1, Exp p2) { id_ = p1; exp_ = p2; }

  public <R,A> R accept(eyg.Absyn.RecordField.Visitor<R,A> v, A arg) { return v.visit(this, arg); }

  public boolean equals(java.lang.Object o) {
    if (this == o) return true;
    if (o instanceof eyg.Absyn.RFKeyVal) {
      eyg.Absyn.RFKeyVal x = (eyg.Absyn.RFKeyVal)o;
      return this.id_.equals(x.id_) && this.exp_.equals(x.exp_);
    }
    return false;
  }

  public int hashCode() {
    return 37*(this.id_.hashCode())+this.exp_.hashCode();
  }


}
