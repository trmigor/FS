-------------------------------- MODULE WGC --------------------------------
EXTENDS Naturals, TLC, FiniteSets

(* --algorithm WGC
variables sides = <<{"W", "C", "G", "H"}, {}>>

define
    D == DOMAIN sides
    Acceptable(x) == Cardinality(x) <= 1
                     \/ x = {"W", "C"}
                     \/ "H" \in x
end define;

begin

while TRUE do
    assert sides[2] /= {"W", "C", "G", "H"};
    with from \in {x \in D : "H" \in sides[x]},
         who \in sides[from]
    do
        if Acceptable(sides[from] \ {who, "H"}) then
            sides[from] := sides[from] \ {who, "H"} ||
            sides[CHOOSE x \in D \ {from} : TRUE] := sides[CHOOSE x \in D \ {from} : TRUE] \union {who, "H"};
        end if;
    end with;
end while;

end algorithm *)
\* BEGIN TRANSLATION - the hash of the PCal code: PCal-d9281196bed3b010fb97fc4aae1ac2ec (chksum(pcal) = "88493e02" /\ chksum(tla) = "9f574ea7") (chksum(pcal) = "97171fbd" /\ chksum(tla) = "c83a1807") (chksum(pcal) = "e7b478" /\ chksum(tla) = "b022c150") (chksum(pcal) \in STRING /\ chksum(tla) \in STRING) (chksum(pcal) = "eade6153" /\ chksum(tla) = "84316da4") (chksum(pcal) = "2f4e7ac9" /\ chksum(tla) = "c415f86") (chksum(pcal) = "5b6bef61" /\ chksum(tla) = "f68b75b3") (chksum(pcal) = "f90208e6" /\ chksum(tla) = "2a431bbd") (chksum(pcal) = "ad24a950" /\ chksum(tla) = "f3995f20") (chksum(pcal) = "f5f5767e" /\ chksum(tla) = "77df962a") (chksum(pcal) = "b390b089" /\ chksum(tla) = "e1bd0372") (chksum(pcal) = "3061bc8f" /\ chksum(tla) = "d333ea18") (chksum(pcal) = "d51d9ee0" /\ chksum(tla) = "d7bbd86d") (chksum(pcal) = "5a22f572" /\ chksum(tla) = "53adfc1b") (chksum(pcal) = "5a22f572" /\ chksum(tla) = "53adfc1b") (chksum(pcal) = "617da510" /\ chksum(tla) = "fee157cd") (chksum(pcal) = "617da510" /\ chksum(tla) = "fee157cd") (chksum(pcal) = "9232e321" /\ chksum(tla) = "b4497fdc") (chksum(pcal) = "491e577b" /\ chksum(tla) = "48e5f11c") (chksum(pcal) = "d0b5cbd9" /\ chksum(tla) = "9049cddc") (chksum(pcal) = "30e2b766" /\ chksum(tla) = "1fae7f04") (chksum(pcal) = "6c9913a5" /\ chksum(tla) = "49135d07")
VARIABLE sides

(* define statement *)
D == DOMAIN sides
Acceptable(x) == Cardinality(x) <= 1
                 \/ x = {"W", "C"}
                 \/ "H" \in x


vars == << sides >>

Init == (* Global variables *)
        /\ sides = <<{"W", "C", "G", "H"}, {}>>

Next == /\ Assert(sides[2] /= {"W", "C", "G", "H"}, 
                  "Failure of assertion at line 17, column 5.")
        /\ \E from \in {x \in D : "H" \in sides[x]}:
             \E who \in sides[from]:
               IF Acceptable(sides[from] \ {who, "H"})
                  THEN /\ sides' = [sides EXCEPT ![from] = sides[from] \ {who, "H"},
                                                 ![CHOOSE x \in D \ {from} : TRUE] = sides[CHOOSE x \in D \ {from} : TRUE] \union {who, "H"}]
                  ELSE /\ TRUE
                       /\ sides' = sides

Spec == Init /\ [][Next]_vars

\* END TRANSLATION - the hash of the generated TLA code (remove to silence divergence warnings): TLA-68a56dad3d9e5099715816a379057f27

=============================================================================
\* Modification History
\* Last modified Fri Dec 18 23:51:59 MSK 2020 by itar
\* Created Fri Dec 18 21:05:08 MSK 2020 by itar
