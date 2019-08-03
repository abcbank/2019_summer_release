library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity counter is
  port (
    clk, rst : in std_logic;
    up_dn : in std_logic;
    cnt : out std_logic_vector (3 downto 0)
  ) ;
end counter;

architecture behave of counter is
signal tmp_cnt : std_logic_vector (3 downto 0);
constant tmp_limit : std_logic_vector (3 downto 0) := "1101";
begin
    process(clk, rst)
    begin
        if rst - '1' then
            tmp_cnt <= (others => '0');
        elsif clk = '1' and clk'EVENT then
            case up_dn is
                when '1' =>
                    if tmp_cnt = tmp_limit then
                        tmp_cnt <= (others => '0');
                    else
                        tmp_cnt <= tmp_cnt + 1;
                    end if;
                when others =>
                    tmp_cnt = tmp_cnt - 1;
            end case ;
        end if;
    end process;

    cnt = tmp_cnt;

end behave ; -- behave