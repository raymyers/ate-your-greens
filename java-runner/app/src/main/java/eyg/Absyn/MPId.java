// File generated by the BNF Converter (bnfc 2.9.6).

package eyg.Absyn;

public class MPId  extends MatchPattern {
  public final String id_;
  public MPId(String p1) { id_ = p1; }

  public <R,A> R accept(eyg.Absyn.MatchPattern.Visitor<R,A> v, A arg) { return v.visit(this, arg); }

  public boolean equals(java.lang.Object o) {
    if (this == o) return true;
    if (o instanceof eyg.Absyn.MPId) {
      eyg.Absyn.MPId x = (eyg.Absyn.MPId)o;
      return this.id_.equals(x.id_);
    }
    return false;
  }

  public int hashCode() {
    return this.id_.hashCode();
  }


}
