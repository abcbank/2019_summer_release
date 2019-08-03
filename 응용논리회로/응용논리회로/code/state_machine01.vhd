library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity state_machine is
    port(
        clk, rst, x, y : in std_logic;
        state : out std_logic_vector (1 downto 0)
    );
end state_machine;

architecture behave of state_machine is
signal cur_state : std_logic_vector(1 downto 0);
signal next_state : std_logic_vector(1 downto 0);

begin
    process(x,y,rst,cur_state)
    begin
        case cur_state is
            when "00" =>
                if x = '1' then
                    next_state <= "01";
                else
                    next_state <= cur_state;
                end if;
            when "01" =>
                if x = '0' and y = '1' then
                    next_state <= "00";
                elsif x = '0' and y = '0' then
                    next_state <= "11";
                elsif x = '1' and y = '1' then
                    next_state <= "10";
                else
                    next_state <= cur_state;
                end if;
            when "10" =>
                if y = '1' then
                    next_state <= "11";
                else
                    next_state <= cur_state;
                end if;
            when "11" =>
                if x = '0' and y = '0' then
                    next_state <= "00";
                else
                    next_state <= cur_state;
                end if;
            when others =>
                next_state <= "00";
        end case;
    end process

    process(clk,rst)
    begin
        if rst = '0' then
            next_state <= (others =>0);
        elsif clk = '1' and clk'EVENT then
            cur_state <=  next_state;
        end if;
    end process;
end behave;