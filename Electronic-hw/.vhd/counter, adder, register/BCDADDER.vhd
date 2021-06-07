library IEEE;
Use IEEE.std_logic_1164.all;
Use IEEE.std_logic_unsigned.all;

Entity BCDadder is // change to BCDcode
    Port( A,B:in integer range 0 to 99;
          Y2,Y1,Y0:out std_logic_vector(3 downto 0));
End BCDadder;

Architecture ARCH of BCDadder is
Begin
    Process(A,B)
        variable Sum:integer range 0 to 200;
        Variable Output:std_logic_vector(3 downto 0);
        Variable TMP:integer range 0 to 9;
    Begin
        Sum := A+B; // a, b: 0~99
        TMP := Sum rem 10; // REM: if sum >= 0, after rem is positive or 0
        // 十進制   // the primary digit
        Dig0: For I in 0 to 3 Loop
            If ((TMP mod 2)=1) Then Output(I):= '1';
            Else Output(I):= '0';
            End If;
            TMP := TMP/2;
        End Loop;
        Y0 <= Output;

        TMP := (Sum/10) rem 10; // 0~9 from 0~19 is the secondary digit
        Dig1: For I in 0 to 3 Loop
            If ((TMP mod 2)=1) Then Output(I):= '1';
            Else Output(I):= '0';
            End If;
            TMP := TMP/2;
        End Loop;
        Y1 <= Output;

        TMP := Sum/100; // must 0, 1, is the thired digit
        Dig2: For I in 0 to 3 Loop
            If ((TMP mod 2)=1) Then Output(I):= '1';
            Else Output(I):= '0';
            End If;
            TMP := TMP/2;
        End Loop;
        Y2 <= Output;
    End Process;
End ARCH;