LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY DFF1 IS
    PORT
    (
        CL, CK, T : IN STD_LOGIC;
        Q, Qbar   : OUT STD_LOGIC
    );
END DFF1;
ARCHITECTURE ARCH OF DFF1 IS
BEGIN
    PROCESS (CL, CK)
        VARIABLE TMP : STD_LOGIC;
    BEGIN
        IF CL = '1' THEN
            TMP := '0';
        ELSIF RISING_EDGE(CK) THEN
            IF T = '1' THEN
                TMP := NOT TMP;
            ELSE
                NULL;
            END IF;
        END IF;
        Q    <= TMP;
        Qbar <= NOT TMP;
    END PROCESS;
END ARCH;