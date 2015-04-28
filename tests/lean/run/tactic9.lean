import logic
open tactic

theorem tst {A B : Prop} (H1 : A) (H2 : B) : ((fun x : Prop, x) A) ∧ B ∧ A
:= by apply and.intro; beta; assumption; apply and.intro; assumption
