library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity mux is
    port(
        a,b,c,d :  in std_logic;
        sel : in std_logic_vector(1 downto 0);
        y : out std_logic
    );
end mux;

architecture behave of mux is
begin
    process
    begin
        if sel = "00" then
            y <= a;
        elsif sel = "01" then
            y <= b;
        elsif sel = "10" then
            y <= c;
        else
            y <= d;
        end if;
    end process;
end behave ; -- behave