LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY BCDCOUNTER IS
    GENERIC
        (N : INTEGER RANGE 0 TO 999 := 168);
    PORT
        (CK:IN STD_LOGIC;
            Y2, Y1, Y0 : OUT STD_LOGIC_VECTOR(3 DOWNTO 0));
END BCDCOUNTER;

ARCHITECTURE ARCH OF BCDCOUNTER IS
    SIGNAL TMP2, TMP1, TMP0 : INTEGER RANGE 0 TO 9;
    SIGNAL N2, N1, N0       : STD_LOGIC_VECTOR(3 DOWNTO 0);
BEGIN
    PROCESS (TMP2, TMP1, TMP0)
        VARIABLE OUTPUT : STD_LOGIC_VECTOR(3 DOWNTO 0);
        VARIABLE A      : INTEGER RANGE 0 TO 9;
    BEGIN
        A := TMP0;
        DIG0 : FOR I IN 0 TO 3 LOOP
            IF ((A MOD 2) = 1) THEN
                OUTPUT(I) := '1';
            ELSE
                OUTPUT(I) := '0';
            END IF;
            A := A/2;
        END LOOP;
        N0 <= OUTPUT;
        ----------------------------------------------------------------
        A := TMP1;
        DIG1 : FOR I IN 0 TO 3 LOOP
            IF ((A MOD 2) = 1) THEN
                OUTPUT(I) := '1';
            ELSE
                OUTPUT(I) := '0';
            END IF;
            A := A/2;
        END LOOP;
        N1 <= OUTPUT;
        ----------------------------------------------------------------
        A := TMP2;
        DIG2 : FOR I IN 0 TO 3 LOOP
            IF ((A MOD 2) = 1) THEN
                OUTPUT(I) := '1';
            ELSE
                OUTPUT(I) := '0';
            END IF;
            A := A/2;
        END LOOP;
        N2 <= OUTPUT;
    END PROCESS;

    BCDCOUNT : PROCESS (CK)
        VARIABLE DIGIT2 : STD_LOGIC_VECTOR(3 DOWNTO 0) := "0000";
        VARIABLE DIGIT1 : STD_LOGIC_VECTOR(3 DOWNTO 0) := "0000";
        VARIABLE DIGIT0 : STD_LOGIC_VECTOR(3 DOWNTO 0) := "0000";
    BEGIN
        IF RISING_EDGE(CK) THEN
            DIGIT0 := DIGIT0 + '1';
            IF (DIGIT0 = N0) AND (DIGIT1 = N1) AND (DIGIT2 = N2) THEN
                DIGIT0 := "0000";
                DIGIT1 := "0000";
                DIGIT2 := "0000";
            ELSIF DIGIT0 = "1010" THEN
                DIGIT0 := "0000";
                DIGIT1 := DIGIT1 + '1';
                IF DIGIT1 = "1010" THEN
                    DIGIT1 := "0000";
                    DIGIT2 := DIGIT2 + '1';
                END IF;
            END IF;
        END IF;
        Y0 <= DIGIT0;
        Y1 <= DIGIT1;
        Y2 <= DIGIT2;
END PROCESS BCDCOUNT;
END ARCH;