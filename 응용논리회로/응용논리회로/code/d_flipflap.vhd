-- 1. w/ rst : most general
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity dff is
  port (
  clk, rst, d : in std_logic;
  q : out std_logic
  ) ;
end dff;

architecture behave of dff is
begin
  process(clk, rst)
    if rst = '1' then
      q <= '0';
    elsif clk = '1' and clk'EVENT then
      q <= d;
    end if;
  end process;
end behave ; -- behave

-- 2. w/ rst, set
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Dff is
  port (
    clk, set, rst, d : in std_logic;
    q : out std_logic
  ) ;
end Dff;

architecture behave of Dff is
begin
    process(clk, set, rst)
        if rst = '1' then
            q <= '0';
        elsif set = '1' then
            q <= '1';
        elsif clk = '1' then clk'EVENT then
            q <= d;
        end if;
    end process;
end behave ; -- behave

-- 3. w/o rst, set
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Dff is
  port (
    clk, d : in std_logic;
    q : out std_logic
  ) ;
end Dff;

architecture behave of Dff is
begin
    process(clk, d)
        if clk = '1' and clk'EVENT then
            q <= d;
        end if;
    end process;
end behave; -- behave