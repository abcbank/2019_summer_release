library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_vector.all;

entity mux is
  port (
  a,b,c,d : in std_logic;
  sel : in std_logic_vector (1 downto 0);
  y : out std_logic
  ) ;
end mux;

architecture behave of mux is
begin
  select sel with
  y <= a when "00",
       b when "01",
       c when "10",
       d when others;
end behave ; -- behave