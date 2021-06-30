LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;

ENTITY UDC_4B IS
    PORT
    (
        CL, UD, PulseIn : IN std_logic;
        Q               : OUT std_logic_vector(3 DOWNTO 0));
END UDC_4B;

ARCHITECTURE ARCH OF UDC_4B IS
    COMPONENT DFF1
        PORT
        (
            CL, CK, T : IN std_logic;
            Q, Qbar   : OUT std_logic);
    END COMPONENT;
    SIGNAL TMP : std_logic_vector(4 DOWNTO 0);
BEGIN
    TMP(0) <= PulseIn;
    LP1 : FOR I IN 0 TO 3 GENERATE
        U : DFF1 PORT MAP
            (CL, Tmp(I) XOR UD, '1', Q(I), TMP(I + 1));
    END GENERATE;
END ARCH;