Library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity hexconvertor is 
port(
    src_input : in std_logic_vector(3 downto 0);
    hex_output : out std_logic_vector(6 downto 0)
);
end hexconvertor;

architecture behave of hexconvertor is
begin

    with src_input select
    hex_output <= "00111111" when "0000", 
    "00000110" when "0001" ,
    "01011011" when "0010" ,
    "01001111" when "0011" ,
    "01100110" when "0100" ,
    "01101101" when "0101" ,
    "01111101" when "0110" ,
    "00100111" when "0111" ,
    "01111111" when "1000" ,
    "01100111" when "1001" ,
    "00000000" when others;

end behave;