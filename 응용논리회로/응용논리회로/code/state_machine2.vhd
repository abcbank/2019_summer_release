library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity state_machine is
    port(
        clk, rst : in std_logic;
        state : out std_logic_vector (1 downto 0)
    );
end state_machine;

architecture behave of state_machine is
signal tmp_state : std_logic_vector (1 downto 0);
constant state_0 :  std_logic_vector (1 downto 0) := "00";
constant state_1 :  std_logic_vector (1 downto 0) := "01";
constant state_2 :  std_logic_vector (1 downto 0) := "10";
constant state_3 :  std_logic_vector (1 downto 0) := "11";

begin
    process(clk, rst)
    
    begin
        if rst = '0' then
            tmp_state <= state_0;
        elsif clk = '1' and clk'EVENT then
            case state is
                when state_0 =>
                    if x = '1' then
                        tmp_state <= state_1;
                    else
                        tmp_state <= state_0;
                    end if;
                when state_1 => 
                    if x = '0' and y = '1' then
                        tmp_state <= state_0;
                    elsif x = '0' and y ='0' then
                        tmp_state <= state_3;
                    elsif x = '1' and y = '1' then
                        tmp_state <= state_2;
                    else 
                        tmp_state <= state_1;
                    end if;
                when state_2 =>
                    if y = '1' then
                        tmp_state <= state_3;
                    else
                        tmp_state <= state_2;
                    end if;
                when state_3 =>
                    if x = '0' and y = '0' then
                        tmp_state <= state_0;
                    else 
                        tmp_state <= state_3;
                    end if;
            end case;
        end if;
    end process;

    state <= tmp_state;
end behave;