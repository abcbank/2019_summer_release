library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity dlatch is
  port (
  en, d : in std_logic;
  q : out std_logic
  ) ;
end dlatch;

architecture behave of dlatch is
begin
  process(en, d)
  if en = '1' then
    q <= d;
  end if;
  end process;
end behave;