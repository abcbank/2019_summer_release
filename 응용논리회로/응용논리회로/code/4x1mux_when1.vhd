library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity mux is
  port (
  a,b,c,d : in std_logic;
  sel : in std_logic_vector (1 downto 0);
  y : out std_logic
  ) ;
end mux;

architecture behave of mux is
begin
  y <= a when sel = "00" else
       b when sel = "01" else
       c when sel = "10" else
       d when others;
end behave ; -- behave