LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.std_logic_unsigned.ALL;

ENTITY BCDADDER IS
    PORT
    (
        A, B       : IN INTEGER RANGE 0 TO 99;
        Y2, Y1, Y0 : OUT std_logic_vector(3 DOWNTO 0)
    );
END BCDADDER;

ARCHITECTURE ARCH OF BCDADDER IS
BEGIN
    PROCESS (A, B)
        VARIABLE Sum    : INTEGER RANGE 0 TO 200;
        VARIABLE Output : std_logic_vector(3 dowto 0);
        VARIABLE TMP    : INTEGER RANGE 0 TO 9;
    BEGIN
        Sum := A + B;
        TMP := Sum REM 10;
        Dig0 : FOR i IN 0 TO 3 LOOP
            IF ((TMP MOD 2) = 1) THEN
                Output(i) := '1';
            ELSE
                Output(i) := '0';
            END IF;
            TMP := TMP / 2;
        END LOOP;
        Y0 <= Output;

        TMP := (Sum / 10) REM 10;
        Dig1 : FOR i IN 0 TO 3 LOOP
            IF ((TMP MOD 2) = 1) THEN
                Output(i) := '1';
            ELSE
                Output(i) := '0';
            END IF;
            TMP := TMP / 2;
        END LOOP;
        Y1 <= Output;

        TMP := Sum / 100;
        Dig2 : FOR i IN 0 TO 3 LOOP
            IF ((TMP MOD 2) = 1) THEN
                Output(i) := '1';
            ELSE
                Output(i) := '0';
            END IF;
            TMP := TMP / 2;
        END LOOP;
        Y2 <= Output;
    END PROCESS;
END ARCH;