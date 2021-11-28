LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY ADDER4 IS
    PORT (
        CIN  : IN BIT;
        A, B : IN BIT_VECTOR(3 DOWNTO 0);
        Cout : OUT BIT;
        SUM  : OUT BIT_VECTOR(3 DOWNTO 0)
    );
END ADDER4;

ARCHITECTURE Structural OF ADDER4 IS
    COMPONENT FA
        PORT (
            CI, XI, YI : IN BIT;
            CO, SI     : OUT BIT
        );
    END COMPONENT;

    SIGNAL CARRYV : BIT_VECTOR(4 DOWNTO 0);

BEGIN
    CARRYV(0) <= CIN;

    ADDER : FOR K IN 3 DOWNTO 0 GENERATE
        FULLADDER : FA PORT MAP
            (CARRYV(K), A(K), B(K), CARRYV(K + 1), SUM(K));
    END GENERATE ADDER;

    COUT <= CARRYV(4);
END Structural;