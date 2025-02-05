// File generated by the BNF Converter (bnfc 2.9.6).

package eyg.Absyn;

public class MPTagged  extends MatchPattern {
  public final String tag_;
  public final MatchPattern matchpattern_;
  public MPTagged(String p1, MatchPattern p2) { tag_ = p1; matchpattern_ = p2; }

  public <R,A> R accept(eyg.Absyn.MatchPattern.Visitor<R,A> v, A arg) { return v.visit(this, arg); }

  public boolean equals(java.lang.Object o) {
    if (this == o) return true;
    if (o instanceof eyg.Absyn.MPTagged) {
      eyg.Absyn.MPTagged x = (eyg.Absyn.MPTagged)o;
      return this.tag_.equals(x.tag_) && this.matchpattern_.equals(x.matchpattern_);
    }
    return false;
  }

  public int hashCode() {
    return 37*(this.tag_.hashCode())+this.matchpattern_.hashCode();
  }


}
