library IEEE;
Use IEEE.std_logic_1164.all;

ENtity SRegister is
    Port( Si,CK,CL:in std_logic;
          Q:out std_logic_vector(7 downto 0));
End SRegister;

Architecture ARCH of SRegister is
Begin
    Process(Si,CK,CL)
        Variable RegT: std_logic_vector(7 downto 0);
    Begin
        if  Rising_Edge(CK) then
            If CL='1' then
               RegT := "00000000";
            else
               RegT := Regt(6 downto 0) & Si;
            End If;
            Q <= RegT;
        end if;
    End Process;
End ARCH;