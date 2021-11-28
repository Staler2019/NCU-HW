LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY COUNTER4BIT IS
    PORT
    (
        CL, PulseIn : IN std_logic;
        Q           : OUT STD_LOGIC_VECTOR(3 DOWNTO 0)
    );
END COUNTER4BIT;

ARCHITECTURE ARCH OF COUNTER4BIT IS
    COMPONENT DFF1
        PORT
        (
            CL, CK, T : IN STD_LOGIC;
            Q, Qbar   : OUT std_LOGIC
        );
    END COMPONENT;
    SIGNAL TMP : STD_LOGIC_VECTOR(4 DOWNTO 0);
BEGIN
    TMP(0) <= PulseIn;
    LP1 : FOR I IN 0 TO 3 GENERATE
        U : DFF1 PORT MAP
            (CL, TMP(I), '1', Q(I), TMP(I + 1));
    END GENERATE;
END ARCH;